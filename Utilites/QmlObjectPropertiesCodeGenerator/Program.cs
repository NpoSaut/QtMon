using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Xml.Linq;
using System.Text.RegularExpressions;

namespace QmlObjectPropertiesCodeGenerator
{
    class Program
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

        static void Main(string[] args)
        {
            string WorkigDirectory = (args.Length > 0) ? args[0] : "";
            string TaskPath = Path.Combine(WorkigDirectory, "properties.xml");
            string SourcePaths = WorkigDirectory;

            XDocument doc = XDocument.Load(TaskPath);

            string ClassName = doc.Root.Element("ClassInfo").Attribute("name").Value;

            FileInfo hFile = new FileInfo(Path.Combine(SourcePaths, ClassName.ToLower() + ".h"));
            FileInfo cppFile = new FileInfo(Path.Combine(SourcePaths, ClassName.ToLower() + ".cpp"));

            StringBuilder PrivateProperties = new StringBuilder();
            StringBuilder PublicPropertyGetters = new StringBuilder();
            StringBuilder PublicSlotsAndPropertySetters = new StringBuilder();
            StringBuilder PropertiesSignals = new StringBuilder();
            StringBuilder GettersAndSetters = new StringBuilder();
            StringBuilder PropertyInits = new StringBuilder();

            Dictionary<StringBuilder, String> LabelFormats = new Dictionary<StringBuilder, string>()
            {
                { PrivateProperties,              "    // private properties {0}" },
                { PublicPropertyGetters,          "    // public properties getters {0}" },
                { PublicSlotsAndPropertySetters,  "    // public properties setters {0}" },
                { PropertiesSignals,              "    // properties signals {0}" },
                { GettersAndSetters,              "// -- {0}: Properties Getters and Setters --" },
                { PropertyInits,                  "    // fileds init {0}" }
            };
            //LabelFormats.Add(PrivateProperties, "    // private properties {0}");
            //LabelFormats.Add(PublicPropertyGettersSetters, "    // public properties {0}");
            //LabelFormats.Add(PropertiesSignals, "    // properties signals {0}");
            //LabelFormats.Add(GettersAndSetters, "// -- {0}: Properties Getters and Setters --");
            //LabelFormats.Add(PropertyInits, "    // fileds init start {0}");

            foreach (var fl in LabelFormats)
                fl.Key.AppendFormat(fl.Value + "\n", "start");

            //PrivateProperties.AppendLine("    // private properties start");
            //PublicPropertyGettersSetters.AppendLine("    // public properties start");
            //PropertiesSignals.AppendLine("    // properties signals start");
            //GettersAndSetters.AppendLine("// -- start: Properties Getters and Setters --");
            //PropertyInits.AppendLine("    // fileds init start");

            foreach (var XProperty in doc.Root.Element("Properties").Elements("Property"))
            {
                string PropertyName = XProperty.Attribute("name").Value;
                string PropertyType = XProperty.Attribute("type").Value;
                string PropertyDescription = (String)XProperty.Attribute("description");
                //string FiledName = XProperty.Attribute("filed").Value;
                string FiledValue = XProperty.Attribute("def").Value;
                string FiledName = String.Format("{0}Value", ToFirstLower(PropertyName));
                string GetterName = String.Format("get{0}", ToFirstUpper(PropertyName));
                string SetterName = String.Format("set{0}", ToFirstUpper(PropertyName));
                string SignalName = ((bool?)XProperty.Attribute("signalsafe") == true) ?
                                        String.Format("{0}Changed", ToFirstLower(PropertyName)) :
                                        String.Format("{0}Changed", PropertyName);

                if (PropertyDescription != null) PrivateProperties.AppendFormat("    // {0}\n", PropertyDescription);
                PrivateProperties.AppendFormat("    {0} {1};\n", PropertyType, FiledName);
                PrivateProperties.AppendFormat("    Q_PROPERTY({0} {1} READ {2} WRITE {3} NOTIFY {4})\n\n",
                                                                     PropertyType, PropertyName, GetterName, SetterName, SignalName);

                //if (PropertyDescription != null) PublicPropertyGetters.AppendFormat("    // {0}\n", PropertyDescription);
                PublicPropertyGetters.AppendFormat("    const {0} {1}() const;\n", PropertyType, GetterName);
                PublicSlotsAndPropertySetters.AppendFormat("    void {1}(const {0});\n", PropertyType, SetterName);

                PropertiesSignals.AppendFormat("    void {0}(const {1} value);\n", SignalName, PropertyType);

                PropertyInits.AppendFormat("    {0} = {1};\n", FiledName, FiledValue);
                if (PropertyDescription != null) GettersAndSetters.AppendFormat("// {0}\n", PropertyDescription);
                GettersAndSetters.AppendFormat(Properties.Resources.DefaultGetter, PropertyType, GetterName, FiledName, ClassName);
                GettersAndSetters.AppendFormat(Properties.Resources.DefaultSetter, PropertyType, SetterName, FiledName, ClassName, SignalName);
                GettersAndSetters.AppendLine();
            }

            //PrivateProperties.Append("    // private properties end");
            //PublicPropertyGettersSetters.Append("    // public properties end");
            //PropertiesSignals.Append("    // properties signals end");
            //GettersAndSetters.Append("// -- end: Properties Getters and Setters --");
            //PropertyInits.Append("    // fileds init end");

            foreach (var fl in LabelFormats)
                fl.Key.AppendFormat(fl.Value, "end");

            string hLines = File.ReadAllText(hFile.FullName);
            hLines = GetRegexForLabel(LabelFormats[PrivateProperties])
                            .Replace(hLines, PrivateProperties.ToString());
            hLines = GetRegexForLabel(LabelFormats[PublicPropertyGetters])
                            .Replace(hLines, PublicPropertyGetters.ToString());
            hLines = GetRegexForLabel(LabelFormats[PublicSlotsAndPropertySetters])
                            .Replace(hLines, PublicSlotsAndPropertySetters.ToString());
            hLines = GetRegexForLabel(LabelFormats[PropertiesSignals])
                            .Replace(hLines, PropertiesSignals.ToString());
            File.WriteAllText(hFile.FullName, hLines);

            string cppLines = File.ReadAllText(cppFile.FullName);
            cppLines = GetRegexForLabel(LabelFormats[PropertyInits])
                            .Replace(cppLines, PropertyInits.ToString());
            cppLines = GetRegexForLabel(LabelFormats[GettersAndSetters])
                            .Replace(cppLines, GettersAndSetters.ToString());
            File.WriteAllText(cppFile.FullName, cppLines);
        }
    }
}
