namespace ZINISCourseProject
{
    partial class Form2
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
            this.backButton = new System.Windows.Forms.Button();
            this.plaintextTextBox = new System.Windows.Forms.RichTextBox();
            this.plaintext = new System.Windows.Forms.Label();
            this.chooseFileButton = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.encryptedTextBox = new System.Windows.Forms.RichTextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.decryptedTextBox = new System.Windows.Forms.RichTextBox();
            this.encryptionTimeTextBox = new System.Windows.Forms.RichTextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.decryptionTimeTextBox = new System.Windows.Forms.RichTextBox();
            this.encryptTextButton = new System.Windows.Forms.Button();
            this.decryptTextButton = new System.Windows.Forms.Button();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.SuspendLayout();
            // 
            // backButton
            // 
            this.backButton.Location = new System.Drawing.Point(13, 13);
            this.backButton.Name = "backButton";
            this.backButton.Size = new System.Drawing.Size(75, 33);
            this.backButton.TabIndex = 0;
            this.backButton.Text = "Назад";
            this.backButton.UseVisualStyleBackColor = true;
            this.backButton.Click += new System.EventHandler(this.backButton_Click);
            // 
            // plaintextTextBox
            // 
            this.plaintextTextBox.Location = new System.Drawing.Point(274, 67);
            this.plaintextTextBox.Name = "plaintextTextBox";
            this.plaintextTextBox.ScrollBars = System.Windows.Forms.RichTextBoxScrollBars.Vertical;
            this.plaintextTextBox.Size = new System.Drawing.Size(576, 124);
            this.plaintextTextBox.TabIndex = 1;
            this.plaintextTextBox.Text = "";
            this.plaintextTextBox.TextChanged += new System.EventHandler(this.plaintextTextBox_TextChanged);
            // 
            // plaintext
            // 
            this.plaintext.AutoSize = true;
            this.plaintext.Font = new System.Drawing.Font("Microsoft Sans Serif", 14F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.plaintext.Location = new System.Drawing.Point(12, 115);
            this.plaintext.Name = "plaintext";
            this.plaintext.Size = new System.Drawing.Size(249, 29);
            this.plaintext.TabIndex = 2;
            this.plaintext.Text = "Введите сообщение";
            // 
            // chooseFileButton
            // 
            this.chooseFileButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.chooseFileButton.Location = new System.Drawing.Point(882, 92);
            this.chooseFileButton.Name = "chooseFileButton";
            this.chooseFileButton.Size = new System.Drawing.Size(143, 52);
            this.chooseFileButton.TabIndex = 3;
            this.chooseFileButton.Text = "Выберите\r\nфайл";
            this.chooseFileButton.UseVisualStyleBackColor = true;
            this.chooseFileButton.Click += new System.EventHandler(this.chooseFileButton_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 14F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label1.Location = new System.Drawing.Point(12, 404);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(206, 58);
            this.label1.TabIndex = 5;
            this.label1.Text = "Зашифрованное\r\nсообщение";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // encryptedTextBox
            // 
            this.encryptedTextBox.Location = new System.Drawing.Point(274, 356);
            this.encryptedTextBox.Name = "encryptedTextBox";
            this.encryptedTextBox.ReadOnly = true;
            this.encryptedTextBox.ScrollBars = System.Windows.Forms.RichTextBoxScrollBars.Vertical;
            this.encryptedTextBox.Size = new System.Drawing.Size(576, 124);
            this.encryptedTextBox.TabIndex = 4;
            this.encryptedTextBox.Text = "";
            this.encryptedTextBox.TextChanged += new System.EventHandler(this.encryptedTextBox_TextChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 14F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label2.Location = new System.Drawing.Point(12, 561);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(219, 58);
            this.label2.TabIndex = 7;
            this.label2.Text = "Расшифрованное\r\nсообщение";
            this.label2.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // decryptedTextBox
            // 
            this.decryptedTextBox.Location = new System.Drawing.Point(274, 513);
            this.decryptedTextBox.Name = "decryptedTextBox";
            this.decryptedTextBox.ReadOnly = true;
            this.decryptedTextBox.ScrollBars = System.Windows.Forms.RichTextBoxScrollBars.Vertical;
            this.decryptedTextBox.Size = new System.Drawing.Size(576, 124);
            this.decryptedTextBox.TabIndex = 6;
            this.decryptedTextBox.Text = "";
            this.decryptedTextBox.TextChanged += new System.EventHandler(this.decryptedTextBox_TextChanged);
            // 
            // encryptionTimeTextBox
            // 
            this.encryptionTimeTextBox.Location = new System.Drawing.Point(882, 429);
            this.encryptionTimeTextBox.Name = "encryptionTimeTextBox";
            this.encryptionTimeTextBox.ReadOnly = true;
            this.encryptionTimeTextBox.ScrollBars = System.Windows.Forms.RichTextBoxScrollBars.None;
            this.encryptionTimeTextBox.Size = new System.Drawing.Size(143, 51);
            this.encryptionTimeTextBox.TabIndex = 8;
            this.encryptionTimeTextBox.Text = "";
            this.encryptionTimeTextBox.TextChanged += new System.EventHandler(this.encryptionTimeTextBox_TextChanged);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label3.Location = new System.Drawing.Point(897, 373);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(113, 36);
            this.label3.TabIndex = 9;
            this.label3.Text = "Время\r\nзашифрования";
            this.label3.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label4.Location = new System.Drawing.Point(897, 527);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(121, 36);
            this.label4.TabIndex = 11;
            this.label4.Text = "Время\r\nрасшифрования";
            this.label4.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // decryptionTimeTextBox
            // 
            this.decryptionTimeTextBox.Location = new System.Drawing.Point(882, 586);
            this.decryptionTimeTextBox.Name = "decryptionTimeTextBox";
            this.decryptionTimeTextBox.ReadOnly = true;
            this.decryptionTimeTextBox.ScrollBars = System.Windows.Forms.RichTextBoxScrollBars.None;
            this.decryptionTimeTextBox.Size = new System.Drawing.Size(143, 51);
            this.decryptionTimeTextBox.TabIndex = 10;
            this.decryptionTimeTextBox.Text = "";
            this.decryptionTimeTextBox.TextChanged += new System.EventHandler(this.decryptionTimeTextBox_TextChanged);
            // 
            // encryptTextButton
            // 
            this.encryptTextButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.encryptTextButton.Location = new System.Drawing.Point(338, 244);
            this.encryptTextButton.Name = "encryptTextButton";
            this.encryptTextButton.Size = new System.Drawing.Size(151, 52);
            this.encryptTextButton.TabIndex = 12;
            this.encryptTextButton.Text = "Зашифровать";
            this.encryptTextButton.UseVisualStyleBackColor = true;
            this.encryptTextButton.Click += new System.EventHandler(this.encryptTextButton_Click);
            // 
            // decryptTextButton
            // 
            this.decryptTextButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.decryptTextButton.Location = new System.Drawing.Point(645, 244);
            this.decryptTextButton.Name = "decryptTextButton";
            this.decryptTextButton.Size = new System.Drawing.Size(154, 52);
            this.decryptTextButton.TabIndex = 13;
            this.decryptTextButton.Text = "Расшифровать";
            this.decryptTextButton.UseVisualStyleBackColor = true;
            this.decryptTextButton.Click += new System.EventHandler(this.decryptTextButton_Click);
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.FileName = "openFileDialog1";
            // 
            // Form2
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1068, 732);
            this.Controls.Add(this.decryptTextButton);
            this.Controls.Add(this.encryptTextButton);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.decryptionTimeTextBox);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.encryptionTimeTextBox);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.decryptedTextBox);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.encryptedTextBox);
            this.Controls.Add(this.chooseFileButton);
            this.Controls.Add(this.plaintext);
            this.Controls.Add(this.plaintextTextBox);
            this.Controls.Add(this.backButton);
            this.Name = "Form2";
            this.Text = "Form2";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button backButton;
        private System.Windows.Forms.RichTextBox plaintextTextBox;
        private System.Windows.Forms.Label plaintext;
        private System.Windows.Forms.Button chooseFileButton;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.RichTextBox encryptedTextBox;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.RichTextBox decryptedTextBox;
        private System.Windows.Forms.RichTextBox encryptionTimeTextBox;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.RichTextBox decryptionTimeTextBox;
        private System.Windows.Forms.Button encryptTextButton;
        private System.Windows.Forms.Button decryptTextButton;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
    }
}