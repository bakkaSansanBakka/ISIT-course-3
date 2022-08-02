using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace IterCode
{
    public partial class Form2 : Form
    {
        public int colEr;
        public int[] posEr;
        public Form2()
        {

            InitializeComponent();

        }

        private void Form2_Load(object sender, EventArgs e)
        {
            try
            {
                textBox2.Hide();
                button2.Hide();
                textBox1.Show();
                button1.Show();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }

        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                colEr = Convert.ToInt32(textBox1.Text);

                if (colEr > 0)
                {
                    textBox2.Show();
                    button2.Show();
                    textBox1.Hide();
                    button1.Hide();
                    label1.Text = "position of errors";
                }
                else
                {
                    this.Close();
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }


        }

        private void button2_Click(object sender, EventArgs e)
        {
            try
            {
                posEr = new int[colEr];
                string sub = textBox2.Text;
                for (int i = 0; i < colEr; i++)
                {
                    posEr[i] = Convert.ToInt32(sub.Split(' ')[i]);
                }

                this.Close();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }

        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
