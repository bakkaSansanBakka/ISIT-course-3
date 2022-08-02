namespace ZINISCourseProject
{
    partial class Form1
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.blowfish = new System.Windows.Forms.Button();
            this.twofish = new System.Windows.Forms.Button();
            this.threefish = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // blowfish
            // 
            this.blowfish.Font = new System.Drawing.Font("Microsoft Sans Serif", 20F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.blowfish.Location = new System.Drawing.Point(442, 90);
            this.blowfish.Name = "blowfish";
            this.blowfish.Size = new System.Drawing.Size(327, 77);
            this.blowfish.TabIndex = 0;
            this.blowfish.Text = "Blowfish";
            this.blowfish.UseVisualStyleBackColor = true;
            this.blowfish.Click += new System.EventHandler(this.blowfish_Click);
            // 
            // twofish
            // 
            this.twofish.Font = new System.Drawing.Font("Microsoft Sans Serif", 20F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.twofish.Location = new System.Drawing.Point(442, 250);
            this.twofish.Name = "twofish";
            this.twofish.Size = new System.Drawing.Size(327, 77);
            this.twofish.TabIndex = 1;
            this.twofish.Text = "Twofish";
            this.twofish.UseVisualStyleBackColor = true;
            this.twofish.Click += new System.EventHandler(this.twofish_Click);
            // 
            // threefish
            // 
            this.threefish.Font = new System.Drawing.Font("Microsoft Sans Serif", 20F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.threefish.Location = new System.Drawing.Point(442, 413);
            this.threefish.Name = "threefish";
            this.threefish.Size = new System.Drawing.Size(327, 77);
            this.threefish.TabIndex = 2;
            this.threefish.Text = "Threefish";
            this.threefish.UseVisualStyleBackColor = true;
            this.threefish.Click += new System.EventHandler(this.threefish_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1216, 722);
            this.Controls.Add(this.threefish);
            this.Controls.Add(this.twofish);
            this.Controls.Add(this.blowfish);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button blowfish;
        private System.Windows.Forms.Button twofish;
        private System.Windows.Forms.Button threefish;
    }
}

