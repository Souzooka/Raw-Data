using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;
using System.Threading.Tasks;

namespace Raw_Data
{
	public class Extractor
	{
        // Prepended to directories created with Extract, e.g. "ROOT.DAT" -> "@ROOT.DAT"
        private static char folderSymbol = '@';

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

			// Determine if the .DAT header is contained within the file, or an external file
			if (IsFAT(bodyReader))
			{
				long temp = bodyReader.BaseStream.Position;

				// If internal, read the file data offset from the header and offset all file reads by that later.
				bodyReader.BaseStream.Position = 0xFC;
				fileDataOffset = bodyReader.ReadInt32();
				headerReader = bodyReader;

				bodyReader.BaseStream.Position = temp;
			}
			else
			{
                // If not a header, Open .FAT in same folder
                if (File.Exists(FindFAT(path)))
                {
                    headerReader = new BinaryReader(File.Open(FindFAT(path), FileMode.Open));
                    fileDataOffset = 0;
                }
                else
                {
                    // If we cannot find header, abort
                    // Console.WriteLine($"Warning: Could not find header for {path}!");
                    return;
                }
			}

			// Gather all necessary file information
			fileCount = GetFileCount(headerReader);

            // If .DAT file is empty, abort
            if (fileCount == 0)
            {
                HandleEmptyDAT(path);
                return;
            }

            // Raw Danger has padding in its headers, so the amount to seek is different between the two variants
            step = ((IsRDFAT(headerReader)) ? 0x8 : 0xC);

            fileNames = GetFullPaths(GetFileNames(headerReader, fileCount), path);
			fileLengths = GetFileLengths(headerReader, fileCount, step);
			fileLocations = GetFileLocations(headerReader, fileCount, step);

			// Iterate over each file in the archive
			for (int i = 0; i < fileCount; ++i)
			{

				byte[] buffer = new Byte[1024];
				int bytesRead;

				// Variable which holds how much data is left to read for one file
				int targetBytes = fileLengths[i];

				// Create directory for the file
				if (!Directory.Exists(Path.GetDirectoryName(fileNames[i])))
				{
					Directory.CreateDirectory(Path.GetDirectoryName(fileNames[i]));
				}

				// Create a new file in the directory with the data in the .DAT file
				BinaryWriter writer = new BinaryWriter(File.Open(fileNames[i], FileMode.Create));
				bodyReader.BaseStream.Position = fileLocations[i] + fileDataOffset;

				// Extraction loop for 1 file
				while (true)
				{
					// If we're about to read the rest of our data for our file, only read that. Otherwise read 1024 bytes.
					// Store the results in byte[] buffer
					int bytesToRead = Math.Min(1024, targetBytes);
					bytesRead = bodyReader.Read(buffer, 0, bytesToRead);

					// If we're at the end of the file data, break the extraction loop
					if (bytesRead == 0) { break; }

					// Decrement our target by the amount of data we read
					targetBytes -= bytesRead;
                    

					// Write our read data to the new file
					writer.Write(buffer, 0, bytesRead);
				}
				// Close new file stream
				writer.Close();
			}

            // Close the header stream
            headerReader.Close();

            // Close .DAT stream and clean up
            bodyReader.Close();
		}

		public static string FindFAT(string path)
		{
			// Returns a path with the file extension changed to .FAT
			// TODO: Check if file exists and if not handle error, operation cannot resume at this point
			return Path.ChangeExtension(path, ".FAT");
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

		public static List<int> GetFileLengths(BinaryReader reader, int count, int step)
		{
			// Retain current reader's position
			long temp = reader.BaseStream.Position;

			// Change reader's position to the pointer data pointer, and then increment by 4 bytes to align with file lengths
			reader.BaseStream.Position = 0xF4;
			reader.BaseStream.Position = reader.ReadInt32() + 0x4;

			List<int> result = new List<int>();

			// Read each length and push into result
			for (int i = 0; i < count; ++i)
			{
				result.Add(reader.ReadInt32());
				reader.BaseStream.Position += step;
			}

			// Restore reader's position
			reader.BaseStream.Position = temp;
			return result;
		}

		public static List<int> GetFileLocations(BinaryReader reader, int count, int step)
		{
			// Retain current reader's position
			long temp = reader.BaseStream.Position;

			reader.BaseStream.Position = 0xF4;
			reader.BaseStream.Position = reader.ReadInt32();

			List<int> result = new List<int>();

			for (int i = 0; i < count; ++i)
			{
				result.Add(reader.ReadInt32());
				reader.BaseStream.Position += step;
			}

			// Restore reader's position
			reader.BaseStream.Position = temp;

			return result;
		}

		public static List<string> GetFileNames(BinaryReader reader, int count)
		{
			// Retain current reader's position
			long temp = reader.BaseStream.Position;

			// Move reader to the file names pointer and then move to that location
			reader.BaseStream.Position = 0xF8;
			reader.BaseStream.Position = reader.ReadInt32();

			List<string> result = new List<string>();

			// Iterate over each file
			for (int i = 0; i < count; ++i)
			{
				List<char> charArr = new List<char>();

				// while making sure we haven't hit the end of the file
				while (reader.BaseStream.Position != reader.BaseStream.Length)
				{
					// read each null terminated file name
					char letter = reader.ReadChar();
					if (letter == (char)0) { break; }
					charArr.Add(letter);
				}

				result.Add(String.Concat(charArr));
			}

			// Restore reader's position
			reader.BaseStream.Position = temp;

			return result;
		}

		// Changes paths found in a header file to a full relative path from the program, for easier file creation
		public static List<string> GetFullPaths(List<string> fileNames, string path)
		{
			

			// Prepend a character to our archive so that we can create a folder with its name
			path = Path.Combine(Path.GetDirectoryName(path), folderSymbol + Path.GetFileName(path));

			return fileNames.Select(v =>
			{
					// Filter out '\' or '/' and replace with the correct DirectorySeparatorChar for the system
					v = v.Replace('\\', Path.DirectorySeparatorChar).Replace('/', Path.DirectorySeparatorChar);

					// Combine our directory path with the file path contained inside the archive header file
					return Path.Combine(path, v);

			}).ToList();
		}

        public static void HandleEmptyDAT(string path)
        {
            if (!Directory.Exists(Path.Combine(Path.GetDirectoryName(path), folderSymbol + Path.GetFileName(path))))
            {
                Directory.CreateDirectory(Path.Combine(Path.GetDirectoryName(path), folderSymbol + Path.GetFileName(path)));
            }
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

			// All headers start with "FAT ", so if this file does it is (probably) a header
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
			reader.BaseStream.Position = temp;

			// In a RD FAT, fnStart should equal fn1
			return fnStart == fn1;
		}

        public static void RecursiveExtract(string path)
        {
            Extractor.Extract(path);

            // Move to the folder we extracted to
            string extractedFolder = Path.Combine(Path.GetDirectoryName(path), folderSymbol + Path.GetFileName(path));

            if (Directory.Exists(extractedFolder))
            {
                Directory.SetCurrentDirectory(Path.Combine(Path.GetDirectoryName(path), folderSymbol + Path.GetFileName(path)));
            }
            else
            {
                // Console.WriteLine($"Warning! Attempted to recursively extract {extractedFolder} when folder does not exist!");
                return;
            }
            

            // Iterate over the .DAT files in this folder
            foreach (var file in new DirectoryInfo(Directory.GetCurrentDirectory()).EnumerateFiles("*.DAT", SearchOption.AllDirectories))
            {
                Task.Factory.StartNew(() => RecursiveExtract(file.FullName));
            }

        }
	}
}
