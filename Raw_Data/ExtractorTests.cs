#if DEBUG
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NUnit
{
    using NUnit.Framework;
    using Raw_Data;

    [TestFixture]
    class ExtractorTests
    {
        // TODO: Setup path and payload for file I/O tests
        // Extractor may have to change slightly to rebuild files and we don't want to just break everything
        public const string path = "TODO";

        //Placeholder
        [Test]
        public void Test() => Assert.AreEqual(4, 2 + 2);
    }
}
#endif