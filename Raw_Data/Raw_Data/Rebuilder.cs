using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

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
    }
}
