using System;
using System.IO;

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

			// TODO: Handle the file not existing better
			if (!File.Exists(path))
			{
				Console.WriteLine("File does not exist!");
				Main(args); // FIXME: This causes a potential memory leak dummy, how can you cause a memory leak in C#
				return;
			}

			// TODO: Recursive extract?
			Extractor.Extract(path);
		}
	}
}
