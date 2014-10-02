using System;

namespace QmlObjectPropertiesCodeGenerator
{
    public static class CamelHelper
    {
        public static String ToFirstLower(this String s)
        {
            if (s.Length < 2) return s.ToLower();
            return s.Substring(0, 1).ToLower() + s.Substring(1);
        }

        public static String ToFirstUpper(this String s)
        {
            if (s.Length < 2) return s.ToUpper();
            return s.Substring(0, 1).ToUpper() + s.Substring(1);
        }
    }
}
