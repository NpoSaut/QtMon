using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Xml.Linq;
using QmlObjectPropertiesCodeGenerator.Properties;

namespace QmlObjectPropertiesCodeGenerator
{
    internal class Program
    {
        private static void Main(string[] args)
        {
            string workingDirectory = (args.Length > 0) ? args[0] : "";
            string sourcePaths = workingDirectory;
            string viewModelsPath = Path.Combine(workingDirectory, "viewmodels");
            string tasksDirectoryPath = viewModelsPath;

            foreach (string taskPath in Directory.EnumerateFiles(tasksDirectoryPath, "*.xml"))
            {
                XDocument doc = XDocument.Load(taskPath);

                string className = doc.Root.Element("ClassInfo").Attribute("name").Value;
                var modelSource = new SourceFile(viewModelsPath, className);
                var serializerSource = new SourceFile(sourcePaths, "StateSerializer");

                var privateProperties = new List<String>();
                var publicPropertyGetters = new List<String>();
                var publicSlotsAndPropertySetters = new List<String>();
                var propertiesSignals = new List<String>();
                var gettersAndSetters = new List<String>();
                var propertyInits = new List<String>();

                var propertySerializers = new List<String>();
                var propertyDeserializers = new List<String>();

                var replacements = new[]
                                   {
                                       new CodeReplacement(new CodeLocation(modelSource.HeaderFilePath, "// private properties {0}"), privateProperties),
                                       new CodeReplacement(new CodeLocation(modelSource.HeaderFilePath, "// public properties getters {0}"),
                                                           publicPropertyGetters),
                                       new CodeReplacement(new CodeLocation(modelSource.HeaderFilePath, "// public properties setters {0}"),
                                                           publicSlotsAndPropertySetters),
                                       new CodeReplacement(new CodeLocation(modelSource.HeaderFilePath, "// properties signals {0}"), propertiesSignals),
                                       new CodeReplacement(new CodeLocation(modelSource.SourceFilePath, "// -- {0}: Properties Getters and Setters --"),
                                                           gettersAndSetters),
                                       new CodeReplacement(new CodeLocation(modelSource.SourceFilePath, "// fileds init {0}"), propertyInits),
                                       new CodeReplacement(new CodeLocation(serializerSource.SourceFilePath, "// save parameters {0} : " + className), propertySerializers),
                                       new CodeReplacement(new CodeLocation(serializerSource.SourceFilePath, "// load parameters {0} : " + className), propertyDeserializers)
                                   };

                var typeConverters = new Dictionary<String, ITypeConverter>
                                     {
                                         { "double", new NumericTypeConverter("double") },
                                         { "float", new NumericTypeConverter("float") },
                                         { "int", new NumericTypeConverter("int") },
                                         { "QString", new QStringConverter() },
                                         { "bool", new NumericTypeConverter("int") }
                                     };

                int i = 0;
                foreach (XElement XProperty in doc.Root.Element("Properties").Elements("Property"))
                {
                    string propertyName = XProperty.Attribute("name").Value;
                    string propertyType = XProperty.Attribute("type").Value;
                    var propertyDescription = (String)XProperty.Attribute("description");
                    string filedValue = XProperty.Attribute("def").Value;
                    string filedName = String.Format("{0}Value", propertyName.ToFirstLower());
                    string getterName = String.Format("get{0}", propertyName.ToFirstUpper());
                    string setterName = String.Format("set{0}", propertyName.ToFirstUpper());
                    string signalName = ((bool?)XProperty.Attribute("signalsafe") == true)
                                            ? String.Format("{0}Changed", propertyName.ToFirstLower())
                                            : String.Format("{0}Changed", propertyName);

                    if (propertyDescription != null) privateProperties.Add(String.Format("// {0}", propertyDescription));
                    privateProperties.Add(String.Format("{0} {1};", propertyType, filedName));
                    privateProperties.Add(String.Format("Q_PROPERTY({0} {1} READ {2} WRITE {3} NOTIFY {4})\n",
                                                        propertyType, propertyName, getterName, setterName, signalName));

                    publicPropertyGetters.Add(String.Format("{0} {1}() const;", propertyType, getterName));
                    publicSlotsAndPropertySetters.Add(String.Format("void {1}(const {0});", propertyType, setterName));

                    propertiesSignals.Add(String.Format("void {0}(const {1} value);", signalName, propertyType));

                    propertyInits.Add(String.Format("{0} = {1};", filedName, filedValue));
                    if (propertyDescription != null) gettersAndSetters.Add(String.Format("// {0}", propertyDescription));
                    gettersAndSetters.Add(String.Format(Resources.DefaultGetter, propertyType, getterName, filedName, className));
                    gettersAndSetters.Add(String.Format(Resources.DefaultSetter, propertyType, setterName, filedName, className, signalName));
                    gettersAndSetters.Add("");

                    propertyDeserializers.Add(String.Format("model->{0}({1});", setterName, typeConverters[propertyType].FromQString("parameters[{0}]", i)));
                    propertySerializers.Add(String.Format("parameters.append({0});", typeConverters[propertyType].ToQString("model->{0}()", getterName)));

                    i++;
                }

                foreach (var fileReplacements in replacements.GroupBy(r => r.Location.FileName))
                {
                    IEnumerable<String> fileContent = File.ReadAllLines(fileReplacements.Key);
                    fileContent = fileReplacements.Aggregate(fileContent, (current, replacement) => replacement.ApplyTo(current));
                    File.WriteAllLines(fileReplacements.Key, fileContent);
                }
            }
        }
    }
}
