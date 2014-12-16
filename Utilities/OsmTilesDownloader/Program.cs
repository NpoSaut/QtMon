using System;
using System.Globalization;
using System.IO;
using System.Net;

namespace OsmTilesDownloader
{
    internal class Program
    {
        private static void DownloadTiles(String OutDirectory, IndexRect r)
        {
            Directory.CreateDirectory(OutDirectory);
            var c = new WebClient();
            Console.WriteLine("Идёт загрузка:");
            for (int x = r.Left; x <= r.Right; x++)
            {
                for (int y = r.Top; y <= r.Bottom; y++)
                {
                    String from = String.Format("http://c.tile.openstreetmap.org/13/{0}/{1}.png", x, y);
                    String to = Path.Combine(OutDirectory, String.Format("{0}-{1}.png", x, y));
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

        private static void Main(string[] args)
        {
            if (args.Length > 1 && !args[0].Contains("?"))
            {
                string OutDirecory = args[0];
                string key = args[1].Trim().ToLower();
                if (key == "fromcenterbyindex" || key == "ci")
                {
                    int centralHorizontalIndex = Int32.Parse(args[2]);
                    int centralVerticalIndex = Int32.Parse(args[3]);
                    int radius = Int32.Parse(args[4]);
                    DownloadTiles(OutDirecory, new IndexRect
                                               {
                                                   Left = centralHorizontalIndex - radius,
                                                   Right = centralHorizontalIndex + radius,
                                                   Top = centralVerticalIndex - radius,
                                                   Bottom = centralVerticalIndex + radius
                                               });
                }
                if (key == "fromcenterbylatlon" || key == "cll")
                {
                    var centerLatitude = Double.Parse(args[2], CultureInfo.InvariantCulture);
                    var centerLongitude = Double.Parse(args[3], CultureInfo.InvariantCulture);
                    int radius = Int32.Parse(args[4]);
                    var centralHorizontalIndex = OsmIndexes.GetHorizontalIndex(centerLongitude, 13);
                    var centralVerticalIndex = OsmIndexes.GetVerticalIndex(centerLatitude, 13);
                    DownloadTiles(OutDirecory, new IndexRect
                    {
                        Left = centralHorizontalIndex - radius,
                        Right = centralHorizontalIndex + radius,
                        Top = centralVerticalIndex - radius,
                        Bottom = centralVerticalIndex + radius
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
                Console.WriteLine("      FromCenterByLatLon широта долгота радиус");
                Console.WriteLine("        (сокр. cll)");
                Console.WriteLine("        Загрузка области карты путём задания индекса центральной ячейки и радиуса");
            }
        }

        private class IndexRect
        {
            public int Left { get; set; }
            public int Right { get; set; }
            public int Top { get; set; }
            public int Bottom { get; set; }
        }
    }
}
