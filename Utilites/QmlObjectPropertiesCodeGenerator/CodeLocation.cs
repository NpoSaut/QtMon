using System;

namespace QmlObjectPropertiesCodeGenerator
{
    public class CodeLocation
    {
        private const string EndLabelKeyword = "end";
        private const String StartLabelKeyword = "start";
        private readonly string _labelFormat;

        public CodeLocation(string FileName, string LabelFormat)
        {
            this.FileName = FileName;
            _labelFormat = LabelFormat;
        }

        public string FileName { get; private set; }

        public String StartLabel
        {
            get { return string.Format(_labelFormat, StartLabelKeyword); }
        }

        public String EndLabel
        {
            get { return string.Format(_labelFormat, EndLabelKeyword); }
        }
    }
}
