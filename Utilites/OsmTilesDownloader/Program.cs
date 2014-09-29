using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;

namespace OsmTilesDownloader
{
    class Program
    {
        private class IndexRect
        {
            public int Left { get; set; }
            public int Right { get; set; }
            public int Top { get; set; }
            public int Bottom { get; set; }
        }

        private static void DownloadTiles(String OutDirectory, IndexRect r)
        {
            WebClient c = new WebClient();
            Console.WriteLine("Идёт загрузка:");
            for (int x = r.Left; x <= r.Right; x++)
            {
                for (int y = r.Top; y <= r.Bottom; y++)
                {
                    String from = String.Format("http://c.tile.openstreetmap.org/13/{0}/{1}.png", x, y);
                    String to = System.IO.Path.Combine(OutDirectory, String.Format("{0}-{1}.png", x, y));
                    int AttemptsCount = 3;
                    while (AttemptsCount > 0)
                    {
                        try
                        {
                            c.DownloadFile(from, to);
                            Console.Write('.');
                            break;
                        }
                        catch (WebException wexc)
                        {
                            AttemptsCount--;
                            if (AttemptsCount < 0) throw new Exception(String.Format("Не удалось загрузить тайл [{0} {1}]", x, y), wexc);
                        }
                    }
                }
                Console.WriteLine();
            }
        }

        static void Main(string[] args)
        {
            if (args.Length > 1 && !args[0].Contains("?"))
            {
                var OutDirecory = args[0];
                var key = args[1].Trim().ToLower();
                if (key == "fromcenterbyindex" || key == "ci")
                {
                    int CentralHorizontalIndex = Int32.Parse(args[2]);
                    int CentralVerticalIndex = Int32.Parse(args[3]);
                    int radius = Int32.Parse(args[4]);
                    DownloadTiles(OutDirecory, new IndexRect()
                    {
                        Left = CentralHorizontalIndex - radius,
                        Right = CentralHorizontalIndex + radius,
                        Top = CentralVerticalIndex - radius,
                        Bottom = CentralVerticalIndex + radius
                    });
                }

                Console.WriteLine("Готово");
                Console.ReadLine();
            }
            else
            {
                Console.WriteLine("Программа для загрузки тайлов карт OSM");
                Console.WriteLine("  Параметры запуска:");
                Console.WriteLine("  OutDirectory Key [parameters]");
                Console.WriteLine("    Ключи:");
                Console.WriteLine("      FromCenterByIndex гориз_индекс_центра вертик_индекс_центра радиус");
                Console.WriteLine("        (сокр. ci)");
                Console.WriteLine("        Загрузка области карты путём задания индекса центральной ячейки и радиуса");
            }
        }
    }
}
