using System;
using System.IO;

namespace QmlObjectPropertiesCodeGenerator
{
    public class SourceFile
    {
        public SourceFile(string DirectoryPath, string ClassName)
        {
            this.ClassName = ClassName;
            this.DirectoryPath = DirectoryPath;
        }

        public String DirectoryPath { get; private set; }
        public String ClassName { get; private set; }

        public String HeaderFilePath
        {
            get { return Path.Combine(DirectoryPath, string.Format("{0}.h", ClassName.ToLower())); }
        }

        public String SourceFilePath
        {
            get { return Path.Combine(DirectoryPath, string.Format("{0}.cpp", ClassName.ToLower())); }
        }
    }
}
