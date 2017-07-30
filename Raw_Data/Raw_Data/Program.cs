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
			Console.WriteLine(GetFileCount(headerReader));
		}

		public static bool IsFAT(BinaryReader reader)
		{
			// Retain current reader's position
			long temp = reader.BaseStream.Position;

			// Set reader's position to the start of file
			reader.BaseStream.Position = 0;

			// Concatenate the first four bytes into a string
			string result = String.Concat(reader.ReadChars(4));

			// Restore reader's position
			reader.BaseStream.Position = temp;

			return result == "FAT ";
		}

		public static int GetFileCount(BinaryReader reader)
		{
			// Retain current reader's position
			long temp = reader.BaseStream.Position;

			// Set reader's position to the correct position
			reader.BaseStream.Position = 0x4;

			int result = reader.ReadInt32();

			// Restore reader's position
			reader.BaseStream.Position = temp;

			return result;
		}
	}
}
