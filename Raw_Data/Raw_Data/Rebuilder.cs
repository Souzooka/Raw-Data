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
        public static void Rebuild(string path)
        {
            // TODO -- normal rebuild of folder
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
            File.Move(dataFile.FullName, headerFile.FullName);
            
            // get position of data
            BinaryReader headerBr = new BinaryReader(File.Open(headerFile.FullName, FileMode.Open));
            headerBr.BaseStream.Position = 0xFC;
            int truncatePos = headerBr.ReadInt32();
            headerBr.BaseStream.Position = truncatePos;
            
            // Copy data over to new .DAT file
            BinaryWriter datBw = new BinaryWriter(File.Open(dataFile.FullName, FileMode.Create));

            byte[] buffer = new Byte[4096];
            int bytesRead;

            int targetBytes = (int)headerFile.Length - truncatePos;
            do
            {
                // Store the results in byte[] buffer
                int bytesToRead = Math.Min(4096, targetBytes);
                bytesRead = headerBr.Read(buffer, 0, bytesToRead);

                // Decrement our target by the amount of data we read
                targetBytes -= bytesRead;

                // Write our read data to the new file
                datBw.Write(buffer, 0, bytesRead);

                // If we're at the end of the file data, break the extraction loop
            } while (bytesRead != 0);
            datBw.Dispose();
            headerBr.Dispose();

            // Header cleanup
            BinaryWriter headerBw = new BinaryWriter(File.Open(headerFile.FullName, FileMode.Open));
            headerBw.BaseStream.SetLength(truncatePos);
            headerBw.BaseStream.Position = 0x14;
            headerBw.Write(0);
            headerBw.BaseStream.Position = 0xFC;
            headerBw.Write(0);
            headerBw.Dispose();
        }
    }
}
