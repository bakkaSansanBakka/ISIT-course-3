using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ZINISCourseProject
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void blowfish_Click(object sender, EventArgs e)
        {
            Blowfish blowfish = new Blowfish("04B915BA43FEB5B6");
            Form2 form2 = new Form2(blowfish);
            form2.Show();
        }

        private void twofish_Click(object sender, EventArgs e)
        {
            Twofish twofish = new Twofish();
            twofish.Mode = CipherMode.ECB;
            Form2 form2 = new Form2(twofish);
            form2.Show();
        }

        private void threefish_Click(object sender, EventArgs e)
        {
            byte[] key = {
                0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
                2, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0,
                4, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0,
                6, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0,
                8, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0,
                10, 0, 0, 0, 0, 0, 0, 0, 11, 0, 0, 0, 0, 0, 0, 0,
                12, 0, 0, 0, 0, 0, 0, 0, 13, 0, 0, 0, 0, 0, 0, 0,
                14, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0
            };

            var threefish = new Threefish
            {
                BlockSize = 1024,
                Key = key,
                IV = key,
                Mode = CipherMode.ECB,
                Padding = PaddingMode.ANSIX923
            };

            Form2 form2 = new Form2(threefish);
            form2.Show();
        }
    }
}
