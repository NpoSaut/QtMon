using System;

namespace QmlObjectPropertiesCodeGenerator
{
    public interface ITypeConverter
    {
        String ToQString(String NativeValue);
        String ToQString(String NativeValueFormat, params object[] NativeValueParams);
        String FromQString(String QStringValue);
        String FromQString(String QStringValueFormat, params object[] QStringValueParams);
    }

    public abstract class TypeConverterBase : ITypeConverter
    {
        public abstract string ToQString(string NativeValue);
        public abstract string FromQString(string QStringValue);

        public string ToQString(string NativeValueFormat, params object[] NativeValueParams)
        {
            return ToQString(string.Format(NativeValueFormat, NativeValueParams));
        }

        public string FromQString(string QStringValueFormat, params object[] QStringValueParams)
        {
            return FromQString(string.Format(QStringValueFormat, QStringValueParams));
        }
    }

    public class FormatTypeConverter : TypeConverterBase
    {
        private readonly string _fromQStringPattern;
        private readonly string _toQStringPattern;

        public FormatTypeConverter(string ToQStringPattern, string FromQStringPattern)
        {
            _toQStringPattern = ToQStringPattern;
            _fromQStringPattern = FromQStringPattern;
        }

        public override string ToQString(string NativeValue) { return string.Format(_toQStringPattern, NativeValue); }
        public override string FromQString(string QStringValue) { return string.Format(_fromQStringPattern, QStringValue); }
    }

    public class NumericTypeConverter : FormatTypeConverter
    {
        public NumericTypeConverter(string TypeName) : base("QString::number({0})", "{0}.to" + TypeName.ToFirstUpper() + "()") { }
    }

    public class QStringConverter : TypeConverterBase
    {
        public override string ToQString(string NativeValue) { return NativeValue; }
        public override string FromQString(string QStringValue) { return QStringValue; }
    }
}
