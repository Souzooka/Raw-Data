using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Raw_Data
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();

            // File dialog setup
            openFileDialogFileExtract.InitialDirectory = Directory.GetCurrentDirectory();
            openFileDialogFileExtract.Filter = "IREM Data Archive (*.DAT)|*.DAT";
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void extractBtn_Click(object sender, EventArgs e)
        {

        }
    }
}
