using System;
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

        }
	}
}
