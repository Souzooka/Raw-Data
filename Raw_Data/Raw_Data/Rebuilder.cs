using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace Raw_Data
{
    public static class Rebuilder
    {
        public enum DatType
        {
            LargeGeneric,
            SmallGeneric,
            LargeRD,
            SmallRD
        }

        public static void Rebuild(string path, DatType archiveType = DatType.LargeRD)
        {
            // Gather all relevant directory information
            FileInfo[] files = Directory.EnumerateFiles(path, "*", SearchOption.AllDirectories).Select(v => new FileInfo(v)).ToArray();
            byte[][] fileNames = files.Select(
                v => Encoding.UTF8.GetBytes(v.FullName.Substring(path.Length + 1).Replace(Path.DirectorySeparatorChar, '\\') + '\u0000')
                ).ToArray();
            int[] fileSizes = files.Select(v => (int)v.Length).ToArray();
            int[] fileLocations = new int[files.Length+1];
            fileLocations[0] = 0;

            int flush = (archiveType == DatType.LargeRD || archiveType == DatType.LargeGeneric ? 0x800 : 0x10);
            for (int i = 1; i < fileLocations.Length; ++i)
            {
                fileLocations[i] = fileLocations[i - 1] + fileSizes[i - 1] + (fileSizes[i - 1] % flush == 0 ? 0 : (flush - fileSizes[i - 1] % flush));
            }

            int fileCount = files.Length;
            int dataOffset = 0;
            string datName = new DirectoryInfo(Path.GetFileNameWithoutExtension(path)).Name + ".DAT";
            if (datName.StartsWith(Extractor.FolderSymbol.ToString())) { datName = datName.Substring(1); }
            string datLocation = Path.GetDirectoryName(path);

            // rebuild header
            BinaryWriter bw = new BinaryWriter(File.Open(Path.Combine(datLocation, datName), FileMode.Create));
            bw.Write(Encoding.UTF8.GetBytes("FAT "));
            bw.Write(fileCount);
            bw.Write(0);
            bw.Write(0);
            bw.Write(0);
            bw.Write((archiveType == DatType.LargeRD || archiveType == DatType.LargeGeneric ? 0x0 : 0x2));
            for (; bw.BaseStream.Position < 0xF4; bw.Write(0)) { }
            bw.Write(0x0100);
            bw.Write(0x0100 + fileCount * (archiveType == DatType.LargeRD || archiveType == DatType.SmallRD ? 12 : 16));
            bw.Write(0); // location to start of file data, 0xFC, will be written later

            int stringPtr = 0x0100 + fileCount * (archiveType == DatType.LargeRD || archiveType == DatType.SmallRD ? 12 : 16);
            for (int i = 0; i < fileCount; ++i)
            {
                bw.Write(fileLocations[i]);
                bw.Write(fileSizes[i]);
                bw.Write(stringPtr);
                if (archiveType == DatType.LargeGeneric || archiveType == DatType.SmallGeneric)
                {
                    bw.Write(0);
                }

                stringPtr += fileNames[i].Length;
            }

            foreach (byte[] str in fileNames)
            {
                foreach (byte chr in str)
                {
                    bw.Write(chr);
                }
            }
            while (bw.BaseStream.Length % 0x10 != 0)
            {
                bw.Write((byte)0);
            }

            // Write body
            if (archiveType == DatType.SmallGeneric || archiveType == DatType.SmallRD)
            {
                dataOffset = (int)bw.BaseStream.Length;
                bw.BaseStream.Position = 0xFC;
                bw.Write(dataOffset);
                bw.BaseStream.Position = bw.BaseStream.Length;
            }
            else
            {
                bw.Dispose();
                
                if (File.Exists(Path.Combine(datLocation, Path.GetFileNameWithoutExtension(datName) + ".FAT")))
                {
                    File.Delete(Path.Combine(datLocation, Path.GetFileNameWithoutExtension(datName) + ".FAT"));
                }

                File.Move(Path.Combine(datLocation, datName), Path.Combine(datLocation, Path.GetFileNameWithoutExtension(datName) + ".FAT"));

                bw = new BinaryWriter(File.Open(Path.Combine(datLocation, datName), FileMode.Create));
            }

            for (int i = 0; i < files.Length; ++i)
            {
                byte[] buffer = new Byte[4096];
                int bytesRead;
                BinaryReader br = new BinaryReader(File.OpenRead(files[i].FullName));

                // Variable which holds how much data is left to read for one file
                int targetBytes = (int)br.BaseStream.Length;

                // Extraction loop for 1 file
                do
                {
                    // If we're about to read the rest of our data for our file, only read that. Otherwise read 1024 bytes.
                    // Store the results in byte[] buffer
                    int bytesToRead = Math.Min(4096, targetBytes);
                    bytesRead = br.Read(buffer, 0, bytesToRead);

                    // Decrement our target by the amount of data we read
                    targetBytes -= bytesRead;

                    // Write our read data to the new file
                    bw.Write(buffer, 0, bytesRead);

                    // If we're at the end of the file data, break the extraction loop
                } while (bytesRead != 0);

                while (bw.BaseStream.Length < fileLocations[i + 1] - dataOffset)
                {
                    bw.Write((byte)0);
                }
            }

            bw.Dispose();
        }

        public static void RecursiveRebuild(string path)
        {
            // TODO -- how to do this?
            // Some issues:
            // Extracted archives likely contain the smaller extracted archives, along with the smaller files to be extracted
            // If possible we want to avoid mutatating those smaller files.
            // Additionally, we don't want to rebundle the extracted archives when rebuilding. That would just lend to a bunch of duplicate junk data.

            // We may have to scout through the file to be rebuilt and, if there any files that end with .DAT (VIBDATA.DAT excluded), ignore them.
            // Although checking if they have a corresponding folder (currently Extractor.folderSymbol + filename) would likely be better practice

            // After getting relevant filedata, we may just have to rebuild any smaller archives (keeping track of their path/name), and put it into a temporary directory
            // to be rebuilt into the master file later

            // Before even building any master file, we'll *have to* build up smaller levels first to get accurate filesizes, plus we have to know if a smaller level is a
            // *major* .DAT or a *minor* .DAT, that is to say minor .DATs have headers built into the files.

            // Practically, if possible we could treat everything but the master level as a minor .DAT
        }

        // Seperates .DAT into .DAT + .FAT
        // Probably going to be hardcoded for ROOT.DAT/STR.DAT,
        // all .DATs have headers included in them except for these
        // and game fails to boot if they are
        public static void SeparateHeader(FileInfo dataFile)
        {
            if (!Header.IsHeader(dataFile)) { throw new ArgumentException("File is not a header/does not contain a header."); }
            FileInfo headerFile = new FileInfo(Path.Combine(dataFile.DirectoryName, Path.GetFileNameWithoutExtension(dataFile.Name) + ".FAT"));
            
            // get position of data
            BinaryReader datBr = new BinaryReader(File.Open(dataFile.FullName, FileMode.Open));
            datBr.BaseStream.Position = 0xFC;
            int truncatePos = datBr.ReadInt32();
            datBr.BaseStream.Position = 0x0;
            
            // Copy data over to new header file
            BinaryWriter headerBw = new BinaryWriter(File.Open(headerFile.FullName, FileMode.Create));

            byte[] buffer = new Byte[4096];
            int bytesRead;

            int targetBytes = truncatePos;
            do
            {
                // Store the results in byte[] buffer
                int bytesToRead = Math.Min(4096, targetBytes);
                bytesRead = datBr.Read(buffer, 0, bytesToRead);

                // Decrement our target by the amount of data we read
                targetBytes -= bytesRead;

                // Write our read data to the new file
                headerBw.Write(buffer, 0, bytesRead);

                // If we're at the end of the file data, break the extraction loop
            } while (bytesRead != 0);
            datBr.Dispose();
            
            // Header cleanup
            headerBw.BaseStream.Position = 0x14;
            headerBw.Write(0);
            headerBw.Dispose();
        }
    }
}
