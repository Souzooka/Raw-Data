using System;
using System.IO;
using System.Windows.Forms;

namespace Raw_Data
{
	class MainClass
	{
        [STAThread]
        public static void Main(string[] args)
		{

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            string path = "";

            OpenFileDialog ofd = new OpenFileDialog();
            DialogResult dr = ofd.ShowDialog();

            if (dr == DialogResult.OK)
            {
                path = ofd.FileName;
            }

            // Extractor.Extract(path);
            Extractor.RecursiveExtract(path);
        }
	}
}
