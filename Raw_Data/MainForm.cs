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
            openFolderDialogRebuild = new FolderBrowserDialog();
        }

        private void textBoxFileExtract_TextChanged(object sender, EventArgs e)
        {
            btnExtract.Enabled = true;
            btnRecursiveExtract.Enabled = true;
        }

        private void textBoxFileRebuild_TextChanged(object sender, EventArgs e)
        {
            btnRebuild.Enabled = true;
        }

        private void btnExtract_Click(object sender, EventArgs e)
        {
            btnExtract.Enabled = false;
            btnRecursiveExtract.Enabled = false;

            Extractor.Extract(textBoxFileExtract.Text);

            btnExtract.Enabled = true;
            btnRecursiveExtract.Enabled = true;
        }

        private void btnRebuild_Click(object sender, EventArgs e)
        {
            btnRebuild.Enabled = false;
            DatType archiveType = (DatType)(Convert.ToInt32(checkBoxRDHeader.Checked) + (Convert.ToInt32(checkBoxLargeDAT.Checked) << 1));

            Rebuilder.Rebuild(textBoxFileRebuild.Text, archiveType);

            btnRebuild.Enabled = true;
        }

        private void btnOfdExtract_Click(object sender, EventArgs e)
        {
            DialogResult dr = openFileDialogFileExtract.ShowDialog();

            if (dr == DialogResult.OK)
            {
                textBoxFileExtract.Text = openFileDialogFileExtract.FileName;
            }
        }

        private void btnOfdRebuild_Click(object sender, EventArgs e)
        {
            openFolderDialogRebuild.SelectedPath = Directory.GetCurrentDirectory();
            DialogResult dr = openFolderDialogRebuild.ShowDialog();

            if (dr == DialogResult.OK)
            {
                textBoxFileRebuild.Text = openFolderDialogRebuild.SelectedPath;
            }
        }

        private void btnRecursiveExtract_Click(object sender, EventArgs e)
        {
            btnExtract.Enabled = false;
            btnRecursiveExtract.Enabled = false;

            // Recursive extract w/ perserved working directory
            string current = Directory.GetCurrentDirectory();
            Extractor.RecursiveExtract(textBoxFileExtract.Text);
            Directory.SetCurrentDirectory(current);

            btnExtract.Enabled = true;
            btnRecursiveExtract.Enabled = true;
        }

        private void linkLabel1_Click(object sender, EventArgs e)
        {
            linkLabel1.LinkVisited = true;
            System.Diagnostics.Process.Start("https://github.com/Souzooka/Raw-Data/");
        }

    }
}
