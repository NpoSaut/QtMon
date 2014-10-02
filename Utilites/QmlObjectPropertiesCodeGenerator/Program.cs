using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Text.RegularExpressions;
using System.Xml.Linq;
using QmlObjectPropertiesCodeGenerator.Properties;

namespace QmlObjectPropertiesCodeGenerator
{
    internal class Program
    {
        private static String ToFirstLower(String s)
        {
            if (s.Length < 2) return s.ToLower();
            return s.Substring(0, 1).ToLower() + s.Substring(1);
        }

        private static String ToFirstUpper(String s)
        {
            if (s.Length < 2) return s.ToUpper();
            return s.Substring(0, 1).ToUpper() + s.Substring(1);
        }

        private static Regex GetRegexForLabel(String LabelFormat)
        {
            return new Regex(String.Format("[ ]*{0}.*[ ]*{1}",
                                           String.Format(LabelFormat.Trim(), "start"),
                                           String.Format(LabelFormat.Trim(), "end")),
                             RegexOptions.Singleline);
        }

        private static void Main(string[] args)
        {
            string workingDirectory = (args.Length > 0) ? args[0] : "";
            string taskPath = Path.Combine(workingDirectory, "properties.xml");
            string sourcePaths = workingDirectory;

            XDocument doc = XDocument.Load(taskPath);

            string className = doc.Root.Element("ClassInfo").Attribute("name").Value;

            var hFile = new FileInfo(Path.Combine(sourcePaths, className.ToLower() + ".h"));
            var cppFile = new FileInfo(Path.Combine(sourcePaths, className.ToLower() + ".cpp"));

            var privateProperties = new StringBuilder();
            var publicPropertyGetters = new StringBuilder();
            var publicSlotsAndPropertySetters = new StringBuilder();
            var propertiesSignals = new StringBuilder();
            var gettersAndSetters = new StringBuilder();
            var propertyInits = new StringBuilder();

            var labelFormats = new Dictionary<StringBuilder, string>
                               {
                                   { privateProperties, "    // private properties {0}" },
                                   { publicPropertyGetters, "    // public properties getters {0}" },
                                   { publicSlotsAndPropertySetters, "    // public properties setters {0}" },
                                   { propertiesSignals, "    // properties signals {0}" },
                                   { gettersAndSetters, "// -- {0}: Properties Getters and Setters --" },
                                   { propertyInits, "    // fileds init {0}" }
                               };

            foreach (var fl in labelFormats)
                fl.Key.AppendFormat(fl.Value + "\n", "start");

            foreach (XElement XProperty in doc.Root.Element("Properties").Elements("Property"))
            {
                string propertyName = XProperty.Attribute("name").Value;
                string propertyType = XProperty.Attribute("type").Value;
                var propertyDescription = (String)XProperty.Attribute("description");
                string filedValue = XProperty.Attribute("def").Value;
                string filedName = String.Format("{0}Value", ToFirstLower(propertyName));
                string getterName = String.Format("get{0}", ToFirstUpper(propertyName));
                string setterName = String.Format("set{0}", ToFirstUpper(propertyName));
                string signalName = ((bool?)XProperty.Attribute("signalsafe") == true)
                                        ? String.Format("{0}Changed", ToFirstLower(propertyName))
                                        : String.Format("{0}Changed", propertyName);

                if (propertyDescription != null) privateProperties.AppendFormat("    // {0}\n", propertyDescription);
                privateProperties.AppendFormat("    {0} {1};\n", propertyType, filedName);
                privateProperties.AppendFormat("    Q_PROPERTY({0} {1} READ {2} WRITE {3} NOTIFY {4})\n\n",
                                               propertyType, propertyName, getterName, setterName, signalName);

                publicPropertyGetters.AppendFormat("    const {0} {1}() const;\n", propertyType, getterName);
                publicSlotsAndPropertySetters.AppendFormat("    void {1}(const {0});\n", propertyType, setterName);

                propertiesSignals.AppendFormat("    void {0}(const {1} value);\n", signalName, propertyType);

                propertyInits.AppendFormat("    {0} = {1};\n", filedName, filedValue);
                if (propertyDescription != null) gettersAndSetters.AppendFormat("// {0}\n", propertyDescription);
                gettersAndSetters.AppendFormat(Resources.DefaultGetter, propertyType, getterName, filedName, className);
                gettersAndSetters.AppendFormat(Resources.DefaultSetter, propertyType, setterName, filedName, className, signalName);
                gettersAndSetters.AppendLine();
            }

            foreach (var fl in labelFormats)
                fl.Key.AppendFormat(fl.Value, "end");

            string hLines = File.ReadAllText(hFile.FullName);
            hLines = GetRegexForLabel(labelFormats[privateProperties])
                .Replace(hLines, privateProperties.ToString());
            hLines = GetRegexForLabel(labelFormats[publicPropertyGetters])
                .Replace(hLines, publicPropertyGetters.ToString());
            hLines = GetRegexForLabel(labelFormats[publicSlotsAndPropertySetters])
                .Replace(hLines, publicSlotsAndPropertySetters.ToString());
            hLines = GetRegexForLabel(labelFormats[propertiesSignals])
                .Replace(hLines, propertiesSignals.ToString());
            File.WriteAllText(hFile.FullName, hLines);

            string cppLines = File.ReadAllText(cppFile.FullName);
            cppLines = GetRegexForLabel(labelFormats[propertyInits])
                .Replace(cppLines, propertyInits.ToString());
            cppLines = GetRegexForLabel(labelFormats[gettersAndSetters])
                .Replace(cppLines, gettersAndSetters.ToString());
            File.WriteAllText(cppFile.FullName, cppLines);
        }
    }
}
