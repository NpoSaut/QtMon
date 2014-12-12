using System;
using System.Collections.Generic;

namespace QmlObjectPropertiesCodeGenerator
{
    public class CodeReplacement
    {
        public CodeReplacement(CodeLocation Location, List<string> ReplaceContent)
        {
            this.ReplaceContent = ReplaceContent;
            this.Location = Location;
        }

        public CodeLocation Location { get; private set; }
        public List<string> ReplaceContent { get; private set; }

        public IEnumerable<String> ApplyTo(IEnumerable<string> FileContent)
        {
            IEnumerator<string> enr = FileContent.GetEnumerator();

            int offset;
            do
            {
                if (!enr.MoveNext()) yield break;
                yield return enr.Current;
            } while ((offset = enr.Current.IndexOf(Location.StartLabel, StringComparison.Ordinal)) == -1);

            foreach (string contentLine in ReplaceContent)
                yield return new string(' ', offset) + contentLine;

            while (!enr.Current.Contains(Location.EndLabel))
                if (!enr.MoveNext()) yield break;

            do
            {
                yield return enr.Current;
            } while (enr.MoveNext());
        }
    }
}
