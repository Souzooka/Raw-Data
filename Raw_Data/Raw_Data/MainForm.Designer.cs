namespace Raw_Data
{
    partial class MainForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.textBoxFileExtract = new System.Windows.Forms.TextBox();
            this.openFileDialogFileExtract = new System.Windows.Forms.OpenFileDialog();
            this.btnOfdExtract = new System.Windows.Forms.Button();
            this.btnExtract = new System.Windows.Forms.Button();
            this.btnRecursiveExtract = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.linkLabel1 = new System.Windows.Forms.LinkLabel();
            this.textBoxFileRebuild = new System.Windows.Forms.TextBox();
            this.btnOfdRebuild = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            this.btnRebuild = new System.Windows.Forms.Button();
            this.checkBoxLargeDAT = new System.Windows.Forms.CheckBox();
            this.checkBoxRDHeader = new System.Windows.Forms.CheckBox();
            this.SuspendLayout();
            // 
            // textBoxFileExtract
            // 
            this.textBoxFileExtract.Location = new System.Drawing.Point(12, 82);
            this.textBoxFileExtract.Name = "textBoxFileExtract";
            this.textBoxFileExtract.ReadOnly = true;
            this.textBoxFileExtract.Size = new System.Drawing.Size(521, 20);
            this.textBoxFileExtract.TabIndex = 0;
            this.textBoxFileExtract.TextChanged += new System.EventHandler(this.textBoxFileExtract_TextChanged);
            // 
            // openFileDialogFileExtract
            // 
            this.openFileDialogFileExtract.FileName = "openFileDialogFileExtract";
            // 
            // btnOfdExtract
            // 
            this.btnOfdExtract.Location = new System.Drawing.Point(12, 111);
            this.btnOfdExtract.Name = "btnOfdExtract";
            this.btnOfdExtract.Size = new System.Drawing.Size(133, 23);
            this.btnOfdExtract.TabIndex = 1;
            this.btnOfdExtract.Text = "Open File in File Explorer";
            this.btnOfdExtract.UseVisualStyleBackColor = true;
            this.btnOfdExtract.Click += new System.EventHandler(this.btnOfdExtract_Click);
            // 
            // btnExtract
            // 
            this.btnExtract.Enabled = false;
            this.btnExtract.Location = new System.Drawing.Point(539, 82);
            this.btnExtract.Name = "btnExtract";
            this.btnExtract.Size = new System.Drawing.Size(75, 23);
            this.btnExtract.TabIndex = 2;
            this.btnExtract.Text = "Extract";
            this.btnExtract.UseVisualStyleBackColor = true;
            this.btnExtract.Click += new System.EventHandler(this.btnExtract_Click);
            // 
            // btnRecursiveExtract
            // 
            this.btnRecursiveExtract.Enabled = false;
            this.btnRecursiveExtract.Location = new System.Drawing.Point(510, 111);
            this.btnRecursiveExtract.Name = "btnRecursiveExtract";
            this.btnRecursiveExtract.Size = new System.Drawing.Size(104, 23);
            this.btnRecursiveExtract.TabIndex = 3;
            this.btnRecursiveExtract.Text = "Recursive Extract";
            this.btnRecursiveExtract.UseVisualStyleBackColor = true;
            this.btnRecursiveExtract.Click += new System.EventHandler(this.btnRecursiveExtract_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 66);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(43, 13);
            this.label1.TabIndex = 4;
            this.label1.Text = "Extract:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(23, 28);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(107, 13);
            this.label2.TabIndex = 5;
            this.label2.Text = "<Raw Data Graphic>";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(431, 8);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(183, 52);
            this.label3.TabIndex = 6;
            this.label3.Text = "Raw Data\r\nAn IREM .DAT file extractor/rebuilder\r\nCopyright 2017 Dakota Smith\r\nRel" +
    "eased under the GPL 3.0 License\r\n";
            this.label3.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // linkLabel1
            // 
            this.linkLabel1.AutoSize = true;
            this.linkLabel1.LinkArea = new System.Windows.Forms.LinkArea(0, 31);
            this.linkLabel1.Location = new System.Drawing.Point(441, 60);
            this.linkLabel1.Name = "linkLabel1";
            this.linkLabel1.Size = new System.Drawing.Size(162, 13);
            this.linkLabel1.TabIndex = 7;
            this.linkLabel1.TabStop = true;
            this.linkLabel1.Text = "View the source code on Github!";
            this.linkLabel1.Click += new System.EventHandler(this.linkLabel1_Click);
            // 
            // textBoxFileRebuild
            // 
            this.textBoxFileRebuild.Location = new System.Drawing.Point(12, 161);
            this.textBoxFileRebuild.Name = "textBoxFileRebuild";
            this.textBoxFileRebuild.ReadOnly = true;
            this.textBoxFileRebuild.Size = new System.Drawing.Size(521, 20);
            this.textBoxFileRebuild.TabIndex = 8;
            this.textBoxFileRebuild.TextChanged += new System.EventHandler(this.textBoxFileRebuild_TextChanged);
            // 
            // btnOfdRebuild
            // 
            this.btnOfdRebuild.Location = new System.Drawing.Point(12, 187);
            this.btnOfdRebuild.Name = "btnOfdRebuild";
            this.btnOfdRebuild.Size = new System.Drawing.Size(133, 23);
            this.btnOfdRebuild.TabIndex = 9;
            this.btnOfdRebuild.Text = "Open File in File Explorer";
            this.btnOfdRebuild.UseVisualStyleBackColor = true;
            this.btnOfdRebuild.Click += new System.EventHandler(this.btnOfdRebuild_Click);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(12, 145);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(46, 13);
            this.label4.TabIndex = 10;
            this.label4.Text = "Rebuild:";
            // 
            // btnRebuild
            // 
            this.btnRebuild.Enabled = false;
            this.btnRebuild.Location = new System.Drawing.Point(539, 158);
            this.btnRebuild.Name = "btnRebuild";
            this.btnRebuild.Size = new System.Drawing.Size(75, 23);
            this.btnRebuild.TabIndex = 11;
            this.btnRebuild.Text = "Rebuild";
            this.btnRebuild.UseVisualStyleBackColor = true;
            this.btnRebuild.Click += new System.EventHandler(this.btnRebuild_Click);
            // 
            // checkBoxLargeDAT
            // 
            this.checkBoxLargeDAT.AutoSize = true;
            this.checkBoxLargeDAT.Location = new System.Drawing.Point(499, 187);
            this.checkBoxLargeDAT.Name = "checkBoxLargeDAT";
            this.checkBoxLargeDAT.Size = new System.Drawing.Size(78, 17);
            this.checkBoxLargeDAT.TabIndex = 12;
            this.checkBoxLargeDAT.Text = "Large DAT";
            this.checkBoxLargeDAT.UseVisualStyleBackColor = true;
            // 
            // checkBoxRDHeader
            // 
            this.checkBoxRDHeader.AutoSize = true;
            this.checkBoxRDHeader.Location = new System.Drawing.Point(499, 201);
            this.checkBoxRDHeader.Name = "checkBoxRDHeader";
            this.checkBoxRDHeader.Size = new System.Drawing.Size(119, 17);
            this.checkBoxRDHeader.TabIndex = 13;
            this.checkBoxRDHeader.Text = "Use generic header";
            this.checkBoxRDHeader.UseVisualStyleBackColor = true;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(624, 230);
            this.Controls.Add(this.checkBoxRDHeader);
            this.Controls.Add(this.checkBoxLargeDAT);
            this.Controls.Add(this.btnRebuild);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.btnOfdRebuild);
            this.Controls.Add(this.textBoxFileRebuild);
            this.Controls.Add(this.linkLabel1);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.btnRecursiveExtract);
            this.Controls.Add(this.btnExtract);
            this.Controls.Add(this.btnOfdExtract);
            this.Controls.Add(this.textBoxFileExtract);
            this.Name = "MainForm";
            this.Text = "Raw Data";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox textBoxFileExtract;
        private System.Windows.Forms.OpenFileDialog openFileDialogFileExtract;
        private System.Windows.Forms.FolderBrowserDialog openFolderDialogRebuild;
        private System.Windows.Forms.Button btnOfdExtract;
        private System.Windows.Forms.Button btnExtract;
        private System.Windows.Forms.Button btnRecursiveExtract;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.LinkLabel linkLabel1;
        private System.Windows.Forms.TextBox textBoxFileRebuild;
        private System.Windows.Forms.Button btnOfdRebuild;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button btnRebuild;
        private System.Windows.Forms.CheckBox checkBoxLargeDAT;
        private System.Windows.Forms.CheckBox checkBoxRDHeader;
    }
}