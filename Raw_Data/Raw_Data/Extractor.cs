using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;
using System.Threading.Tasks;

namespace Raw_Data
{
	public static class Extractor
	{
        // Prepended to directories created with Extract, e.g. "ROOT.DAT" -> "@ROOT.DAT"
        public const char FolderSymbol = '@';

        public static void Extract(string path)
        {
            FileInfo pathInfo = new FileInfo(path);

            // If invalid file or header missing, abort
            if (!Header.IsHeader(pathInfo) && !Header.FindHeader(pathInfo).Exists)
            {
                return;
            }

            // Gather all necessary file information
            Header fat = new Header(pathInfo);

            // If .DAT file is empty, abort
            if (fat.IsEmpty)
            {
                HandleEmptyDAT(path);
                return;
            }

            using (BinaryReader bodyReader = new BinaryReader(File.Open(path, FileMode.Open)))
            {
                // Iterate over each file in the archive
                for (int i = 0; i < fat.FileCount; ++i)
                {

                    byte[] buffer = new Byte[4096];
                    int bytesRead;

                    // Variable which holds how much data is left to read for one file
                    int targetBytes = fat.FileLengths[i];

                    // Create directory for the file
                    if (!Directory.Exists(Path.GetDirectoryName(fat.FullFileNames[i])))
                    {
                        Directory.CreateDirectory(Path.GetDirectoryName(fat.FullFileNames[i]));
                    }

                    // Create a new file in the directory with the data in the .DAT file
                    using (BinaryWriter writer = new BinaryWriter(File.Open(fat.FullFileNames[i], FileMode.Create)))
                    {
                        bodyReader.BaseStream.Position = fat.FileLocations[i];

                        // Extraction loop for 1 file
                        do
                        {
                            // If we're about to read the rest of our data for our file, only read that. Otherwise read 1024 bytes.
                            // Store the results in byte[] buffer
                            int bytesToRead = Math.Min(4096, targetBytes);
                            bytesRead = bodyReader.Read(buffer, 0, bytesToRead);

                            // Decrement our target by the amount of data we read
                            targetBytes -= bytesRead;

                            // Write our read data to the new file
                            writer.Write(buffer, 0, bytesRead);

                            // If we're at the end of the file data, break the extraction loop
                        } while (bytesRead != 0);
                    }
                }
            }
		}

        public static void HandleEmptyDAT(string path)
        {
            if (!Directory.Exists(Path.Combine(Path.GetDirectoryName(path), FolderSymbol + Path.GetFileName(path))))
            {
                Directory.CreateDirectory(Path.Combine(Path.GetDirectoryName(path), FolderSymbol + Path.GetFileName(path)));
            }
        }

        public static void RecursiveExtract(string path)
        {
            Extractor.Extract(path);

            // Move to the folder we extracted to
            string extractedFolder = Path.Combine(Path.GetDirectoryName(path), FolderSymbol + Path.GetFileName(path));

            if (Directory.Exists(extractedFolder))
            {
                Directory.SetCurrentDirectory(Path.Combine(Path.GetDirectoryName(path), FolderSymbol + Path.GetFileName(path)));
            }
            else
            {
                // Console.WriteLine($"Warning! Attempted to recursively extract {extractedFolder} when folder does not exist!");
                return;
            }

            List<string> fileNames = new List<string>();

            // Iterate over the .DAT files in this folder
            foreach (var file in new DirectoryInfo(Directory.GetCurrentDirectory()).EnumerateFiles("*.DAT", SearchOption.AllDirectories))
            {
                fileNames.Add(file.FullName);
            }

            Task.WaitAll(fileNames.Select(v => Task.Factory.StartNew(() => RecursiveExtract(v))).ToArray());
        }
	}
}