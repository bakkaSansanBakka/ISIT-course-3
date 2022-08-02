namespace Lab8
{
    partial class Form1
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
            this.textBoxInput = new System.Windows.Forms.TextBox();
            this.buttonGen = new System.Windows.Forms.Button();
            this.richTextBoxW1 = new System.Windows.Forms.RichTextBox();
            this.richTextBoxW2 = new System.Windows.Forms.RichTextBox();
            this.textBoxM = new System.Windows.Forms.TextBox();
            this.textBoxK = new System.Windows.Forms.TextBox();
            this.buttonBack = new System.Windows.Forms.Button();
            this.richTextBoxB1 = new System.Windows.Forms.RichTextBox();
            this.buttonLast = new System.Windows.Forms.Button();
            this.textBoxNow = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // textBoxInput
            // 
            this.textBoxInput.Location = new System.Drawing.Point(382, 72);
            this.textBoxInput.Name = "textBoxInput";
            this.textBoxInput.Size = new System.Drawing.Size(300, 22);
            this.textBoxInput.TabIndex = 0;
            // 
            // buttonGen
            // 
            this.buttonGen.Location = new System.Drawing.Point(447, 114);
            this.buttonGen.Name = "buttonGen";
            this.buttonGen.Size = new System.Drawing.Size(170, 165);
            this.buttonGen.TabIndex = 1;
            this.buttonGen.Text = "Получить матрицы";
            this.buttonGen.UseVisualStyleBackColor = true;
            this.buttonGen.Click += new System.EventHandler(this.buttonGen_Click);
            // 
            // richTextBoxW1
            // 
            this.richTextBoxW1.Location = new System.Drawing.Point(49, 70);
            this.richTextBoxW1.Name = "richTextBoxW1";
            this.richTextBoxW1.Size = new System.Drawing.Size(300, 300);
            this.richTextBoxW1.TabIndex = 2;
            this.richTextBoxW1.Text = "";
            // 
            // richTextBoxW2
            // 
            this.richTextBoxW2.Location = new System.Drawing.Point(708, 70);
            this.richTextBoxW2.Name = "richTextBoxW2";
            this.richTextBoxW2.Size = new System.Drawing.Size(300, 300);
            this.richTextBoxW2.TabIndex = 3;
            this.richTextBoxW2.Text = "";
            this.richTextBoxW2.TextChanged += new System.EventHandler(this.richTextBoxW2_TextChanged);
            // 
            // textBoxM
            // 
            this.textBoxM.Location = new System.Drawing.Point(112, 483);
            this.textBoxM.Name = "textBoxM";
            this.textBoxM.Size = new System.Drawing.Size(160, 22);
            this.textBoxM.TabIndex = 4;
            // 
            // textBoxK
            // 
            this.textBoxK.Location = new System.Drawing.Point(112, 523);
            this.textBoxK.Name = "textBoxK";
            this.textBoxK.Size = new System.Drawing.Size(160, 22);
            this.textBoxK.TabIndex = 5;
            // 
            // buttonBack
            // 
            this.buttonBack.Location = new System.Drawing.Point(814, 428);
            this.buttonBack.Name = "buttonBack";
            this.buttonBack.Size = new System.Drawing.Size(138, 77);
            this.buttonBack.TabIndex = 6;
            this.buttonBack.Text = "Следующее значение";
            this.buttonBack.UseVisualStyleBackColor = true;
            this.buttonBack.Click += new System.EventHandler(this.buttonBack_Click);
            // 
            // richTextBoxB1
            // 
            this.richTextBoxB1.Location = new System.Drawing.Point(382, 394);
            this.richTextBoxB1.Name = "richTextBoxB1";
            this.richTextBoxB1.Size = new System.Drawing.Size(300, 300);
            this.richTextBoxB1.TabIndex = 7;
            this.richTextBoxB1.Text = "";
            // 
            // buttonLast
            // 
            this.buttonLast.Location = new System.Drawing.Point(814, 554);
            this.buttonLast.Name = "buttonLast";
            this.buttonLast.Size = new System.Drawing.Size(138, 74);
            this.buttonLast.TabIndex = 8;
            this.buttonLast.Text = "Результат";
            this.buttonLast.UseVisualStyleBackColor = true;
            this.buttonLast.Click += new System.EventHandler(this.buttonLast_Click);
            // 
            // textBoxNow
            // 
            this.textBoxNow.Location = new System.Drawing.Point(868, 672);
            this.textBoxNow.Name = "textBoxNow";
            this.textBoxNow.Size = new System.Drawing.Size(42, 22);
            this.textBoxNow.TabIndex = 9;
            this.textBoxNow.TextChanged += new System.EventHandler(this.textBoxNow_TextChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(134, 34);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(120, 17);
            this.label1.TabIndex = 10;
            this.label1.Text = "Матрица сдвигов";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(765, 34);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(187, 17);
            this.label2.TabIndex = 11;
            this.label2.Text = "Отсортированная матрица";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(487, 34);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(84, 17);
            this.label3.TabIndex = 12;
            this.label3.Text = "Сообщение";
            this.label3.Click += new System.EventHandler(this.label3_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.HighlightText;
            this.ClientSize = new System.Drawing.Size(1093, 725);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.textBoxNow);
            this.Controls.Add(this.buttonLast);
            this.Controls.Add(this.richTextBoxB1);
            this.Controls.Add(this.buttonBack);
            this.Controls.Add(this.textBoxK);
            this.Controls.Add(this.textBoxM);
            this.Controls.Add(this.richTextBoxW2);
            this.Controls.Add(this.richTextBoxW1);
            this.Controls.Add(this.buttonGen);
            this.Controls.Add(this.textBoxInput);
            this.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.Name = "Form1";
            this.Text = "Lab8";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox textBoxInput;
        private System.Windows.Forms.Button buttonGen;
        private System.Windows.Forms.RichTextBox richTextBoxW1;
        private System.Windows.Forms.RichTextBox richTextBoxW2;
        private System.Windows.Forms.TextBox textBoxM;
        private System.Windows.Forms.TextBox textBoxK;
        private System.Windows.Forms.Button buttonBack;
        private System.Windows.Forms.RichTextBox richTextBoxB1;
        private System.Windows.Forms.Button buttonLast;
        private System.Windows.Forms.TextBox textBoxNow;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
    }
}

