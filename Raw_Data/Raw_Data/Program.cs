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
            Application.Run(new MainForm());
            

            string path = "";

            OpenFileDialog ofd = new OpenFileDialog();
            ofd.InitialDirectory = Directory.GetCurrentDirectory();
            ofd.Filter = "IREM Data Archive (*.DAT)|*.DAT";
            DialogResult dr = ofd.ShowDialog();

            if (dr == DialogResult.OK)
            {
                path = ofd.FileName;
            }
            else
            {
                // Tentative: this will be replaced and better handled once Form1 is set up
                // this aborts the program if user doesn't select a file
                return;
            }

            // Extractor.Extract(path);
            Extractor.RecursiveExtract(path);
        }
	}
}
