using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace Raw_Data
{
    public class Header
    {

        private string fileName;
        private FileInfo fat;
        public int FileCount;
        public int FileDataOffset;
        private string[] fullFileNames;
        public string[] FullFileNames
        {
            get
            {
                if (fullFileNames == null)
                {
                    // Prepend a character to our archive so that we can create a folder with its name
                    string path = Path.Combine(fat.DirectoryName, Extractor.FolderSymbol + fileName);

                    fullFileNames = FileNames.Select(v =>
                    {
                        // Filter out '\' or '/' and replace with the correct DirectorySeparatorChar for the system
                        v = v.Replace('\\', Path.DirectorySeparatorChar).Replace('/', Path.DirectorySeparatorChar);

                        // Combine our directory path with the file path contained inside the archive header file
                        return Path.Combine(path, v);

                    }).ToArray();
                }

                return fullFileNames;
            }
        }
        public bool IsEmpty
        {
            get
            {
                return FileCount == 0;
            }
        }
        public string[] FileNames;
        public int[] FileLengths;
        public int[] FileLocations;

        public Header(FileInfo pFat)
        {
            fileName = pFat.Name;
            if (!IsHeader(pFat))
            {
                pFat = FindHeader(pFat);
                if (!pFat.Exists)
                {
                    throw new ArgumentException("Invalid file type or header file not found.");
                }
            }
            fat = pFat;

            int step;
            if (this.IsEmpty) { step = 0; }
            else { step = (IsRDFat(pFat) ? 0xC : 0x10); }

            BinaryReader pFatBR = new BinaryReader(pFat.Open(FileMode.Open));

            // FileCount
            pFatBR.BaseStream.Position = 0x4;
            FileCount = pFatBR.ReadInt32();

            // FileDataOffset
            pFatBR.BaseStream.Position = 0xFC;
            FileDataOffset = pFatBR.ReadInt32();

            // FileNames, FileLengths, FileLocations
            FileNames = new string[FileCount];
            FileLengths = new int[FileCount];
            FileLocations = new int[FileCount];

            pFatBR.BaseStream.Position = 0xF4;
            int ptr = pFatBR.ReadInt32();

            for (int i = 0; i < FileCount; ++i)
            {
                pFatBR.BaseStream.Position = ptr + (step * i);

                // Locations
                FileLocations[i] = pFatBR.ReadInt32() + FileDataOffset;

                // Lengths
                FileLengths[i] = pFatBR.ReadInt32();

                // Names
                pFatBR.BaseStream.Position = pFatBR.ReadInt32();

                // Read null-terminated string at this location
                StringBuilder sb = new StringBuilder();
                byte c = pFatBR.ReadByte();

                while (c != 0)
                {
                    sb.Append((char)c);
                    c = pFatBR.ReadByte();
                }
                FileNames[i] = sb.ToString();

            }

            pFatBR.Close();
        }

        public static bool IsRDFat(FileInfo pFat)
        {
            BinaryReader pFatBR = new BinaryReader(pFat.Open(FileMode.Open));

            pFatBR.BaseStream.Position = 0x4;
            if (pFatBR.ReadInt32() == 0)
            {
                // empty DAT
                return false;
            }

            // Set reader's position to the position which points to the start of filenames
            pFatBR.BaseStream.Position = 0xF8;
            int fnStart = pFatBR.ReadInt32();

            // Set reader's position to the (expected) position for the first filename's pointer
            pFatBR.BaseStream.Position = 0x108;
            int fn1 = pFatBR.ReadInt32();

            // Cleanup
            pFatBR.Close();

            // In a RD FAT, fnStart should equal fn1
            return fnStart == fn1;
        }

        public static bool IsHeader(FileInfo pFat)
        {
            FileStream pFatFS = pFat.OpenRead();
            StreamReader pFatSR = new StreamReader(pFatFS, System.Text.Encoding.UTF8);
            string identifier;

            char[] buffer = new char[4];
            pFatSR.Read(buffer, 0, 4);
            identifier = String.Concat(buffer);
            pFatSR.Close();
            pFatFS.Close();

            return identifier == "FAT ";
        }

        public static FileInfo FindHeader(FileInfo pFat)
        {
            return new FileInfo(Path.ChangeExtension(pFat.FullName, ".FAT"));
        }
    }
}
