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
				throw new ArgumentException("File does not exist!");
			}

			// TODO: Recursive extract?
			Extractor.Extract(path);
		}
	}

	public class Extractor
	{
		public static void Extract(string path)
		{
			BinaryReader headerReader = new BinaryReader(File.Open(path, FileMode.Open));
			Console.WriteLine(isFAT(headerReader));
		}

		public static bool isFAT(BinaryReader reader)
		{
			long temp = reader.BaseStream.Position;
			reader.BaseStream.Position = 0;
			string result = String.Concat(reader.ReadChars(4));
			reader.BaseStream.Position = temp;
			return result == "FAT ";
		}

	}
}
