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
			int fileCount = GetFileCount(headerReader);
			int step = ((IsRDFAT(headerReader)) ? 0x8 : 0xC);
			Console.WriteLine(step);
		}

		// Returns true if the current file is a header file
		public static bool IsFAT(BinaryReader reader)
		{
			// Retain current reader's position
			long temp = reader.BaseStream.Position;

			// Set reader's position to the start of file
			reader.BaseStream.Position = 0x0;

			// Concatenate the first four bytes into a string
			string result = String.Concat(reader.ReadChars(4));

			// Restore reader's position
			reader.BaseStream.Position = temp;

			return result == "FAT ";
		}

		// Returns true if the current file is a Raw Danger header
		public static bool IsRDFAT(BinaryReader reader)
		{ 
			// Retain current reader's position
			long temp = reader.BaseStream.Position;

			// Set reader's position to the position which points to the start of filenames
			reader.BaseStream.Position = 0xF8;

			int fnStart = reader.ReadInt32();

			// Set reader's position to the (expected) position for the first filename's pointer
			reader.BaseStream.Position = 0x108;

			int fn1 = reader.ReadInt32();

			// Restore reader's position
			reader.BaseStream.Position = 0;

			// In a RD FAT, fnStart should equal fn1
			return fnStart == fn1;
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
