using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

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

	public class Extractor
	{
		public static void Extract(string path)
		{
			BinaryReader headerReader;
			BinaryReader bodyReader = new BinaryReader(File.Open(path, FileMode.Open));
			int fileDataOffset;
			int fileCount;
			int step;
			List<string> fileNames;
			List<int> fileLengths;
			List<int> fileLocations;

			if (IsFAT(bodyReader))
			{
				long temp = bodyReader.BaseStream.Position;
				bodyReader.BaseStream.Position = 0xFC;
				fileDataOffset = bodyReader.ReadInt32();
				headerReader = bodyReader;

				bodyReader.BaseStream.Position = temp;
			}
			else
			{
				// Open .FAT in same folder
				headerReader = new BinaryReader(File.Open(FindFAT(path), FileMode.Open));
				fileDataOffset = 0;
			}

			fileCount = GetFileCount(headerReader);
			step = ((IsRDFAT(headerReader)) ? 0x8 : 0xC);
			fileNames = GetFullPaths(GetFileNames(headerReader, fileCount), path);
			fileLengths = GetFileLengths(headerReader, fileCount, step);
			fileLocations = GetFileLocations(headerReader, fileCount, step);
			fileLengths.ForEach(v => Console.WriteLine(v.ToString("X8")));

			for (int i = 0; i < fileCount; ++i)
			{
				Directory.CreateDirectory(Path.GetDirectoryName(fileNames[i]));
				BinaryWriter writer = new BinaryWriter(File.Open(fileNames[i], FileMode.Create));
				bodyReader.BaseStream.Position = fileLocations[i] + fileDataOffset;

				byte[] buffer = new Byte[1024];
				int bytesRead;
				int targetBytes = fileLengths[i];

				while (true)
				{
					int bytesToRead = Math.Min(1024, targetBytes);
					bytesRead = bodyReader.Read(buffer, 0, bytesToRead);
					if (bytesRead == 0) { break; }
					targetBytes -= bytesToRead;
					writer.Write(buffer, 0, bytesRead);
				}
				writer.Close();
			}

			headerReader.Close();
			bodyReader.Close();

 			Console.WriteLine("butts");
		}

		public static string FindFAT(string path)
		{
			return ((Path.GetDirectoryName(path) == "") ? "" : Path.GetDirectoryName(path) + Path.DirectorySeparatorChar) + Path.GetFileNameWithoutExtension(path) + ".FAT";
		}

		public static List<int> GetFileLengths(BinaryReader reader, int count, int step)
		{
			long temp = reader.BaseStream.Position;

			reader.BaseStream.Position = 0xF4;
			reader.BaseStream.Position = reader.ReadInt32() + 0x4;

			List<int> result = new List<int>();

			for (int i = 0; i < count; ++i)
			{
				result.Add(reader.ReadInt32());
				reader.BaseStream.Position += step;
			}

			reader.BaseStream.Position = temp;
			return result;
		}

		public static List<int> GetFileLocations(BinaryReader reader, int count, int step)
		{
			long temp = reader.BaseStream.Position;

			reader.BaseStream.Position = 0xF4;
			reader.BaseStream.Position = reader.ReadInt32();

			List<int> result = new List<int>();

			for (int i = 0; i < count; ++i)
			{
				result.Add(reader.ReadInt32());
				reader.BaseStream.Position += step;
			}

			reader.BaseStream.Position = temp;
			return result;
		}

		public static List<string> GetFullPaths(List<string> fileNames, string path)
		{ 
			return fileNames.Select(v => ((Path.GetDirectoryName(path) == "") ? "" : Path.GetDirectoryName(path) + Path.DirectorySeparatorChar) + "@" + Path.GetFileName(path) + Path.DirectorySeparatorChar + v).ToList();
		}

		public static List<string> GetFileNames(BinaryReader reader, int count)
		{
			long temp = reader.BaseStream.Position;

			reader.BaseStream.Position = 0xF8;
			reader.BaseStream.Position = reader.ReadInt32();

			List<string> result = new List<string>();

			for (int i = 0; i < count; ++i)
			{
				List<char> charArr = new List<char>();
				while (true)
				{
					char letter = reader.ReadChar();
					if (letter == (char)0) { break; }
					charArr.Add(letter);
				}

				result.Add(String.Concat(charArr));
			}

			reader.BaseStream.Position = temp;

			return result;
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
