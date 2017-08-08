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
            this.button1 = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // textBoxFileExtract
            // 
            this.textBoxFileExtract.Location = new System.Drawing.Point(12, 82);
            this.textBoxFileExtract.Name = "textBoxFileExtract";
            this.textBoxFileExtract.ReadOnly = true;
            this.textBoxFileExtract.Size = new System.Drawing.Size(521, 20);
            this.textBoxFileExtract.TabIndex = 0;
            this.textBoxFileExtract.TextChanged += new System.EventHandler(this.textBox1_TextChanged);
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
            this.btnExtract.Click += new System.EventHandler(this.extractBtn_Click);
            // 
            // button1
            // 
            this.button1.Enabled = false;
            this.button1.Location = new System.Drawing.Point(510, 111);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(104, 23);
            this.button1.TabIndex = 3;
            this.button1.Text = "Recursive Extract";
            this.button1.UseVisualStyleBackColor = true;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(624, 322);
            this.Controls.Add(this.button1);
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
        private System.Windows.Forms.Button btnOfdExtract;
        private System.Windows.Forms.Button btnExtract;
        private System.Windows.Forms.Button button1;
    }
}