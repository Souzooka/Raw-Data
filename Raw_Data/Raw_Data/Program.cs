using System;
using System.IO;
using System.Windows.Forms;

namespace Raw_Data
{
	class MainClass
	{
		public static string GetPathFromUser()
		{
			Console.WriteLine("Please enter the path of the .DAT file to extract:");
			return Console.ReadLine();
		}

		public static void Main(string[] args)
		{
			// TODO: Get path from arguments instead
			string path = GetPathFromUser();

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            // TODO: Handle the file not existing better
            if (!File.Exists(path))
			{
				Console.WriteLine("File does not exist!");
                path = GetPathFromUser();
			}

            // TODO: Recursive extract?
            // Extractor.Extract(path);
            Extractor.RecursiveExtract(path);
        }
	}
}
