using System;
using System.Diagnostics;
using System.Security.Cryptography;
using System.Windows.Forms;

namespace ZINISCourseProject
{
    public partial class Form2 : Form
    {
        Blowfish blowfishInstance;
        Twofish twofishInstance;
        Threefish threefishInstance;
       
        byte[] Key = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
        byte[] dummy = { };
        byte[] plain;
        byte[] bytOut;
        byte[] cipher;

        string plainText = "";
        string encryptedText;
        string decryptedText;

        Stopwatch stopWatch;
        long elapsedTicks;
        string file;

        public Form2()
        {
            InitializeComponent();
        }

        public Form2(Blowfish blowfish)
        {
            InitializeComponent();

            blowfishInstance = blowfish;
            stopWatch = new Stopwatch();

            backButton.Click += backButton_Click;
            plaintextTextBox.TextChanged += plaintextTextBox_TextChanged;
            encryptTextButton.Click += encryptTextButton_Click;
            decryptTextButton.Click += decryptTextButton_Click;
            chooseFileButton.Click += chooseFileButton_Click;

            openFileDialog1.Filter = "Text files(*.txt)|*.txt|All files(*.*)|*.*";
        }

        public Form2(Twofish twofish)
        {
            InitializeComponent();

            twofishInstance = twofish;
            stopWatch = new Stopwatch();

            backButton.Click += backButton_Click;
            plaintextTextBox.TextChanged += plaintextTextBox_TextChanged;
            encryptTextButton.Click += encryptTextButton_Click;
            decryptTextButton.Click += decryptTextButton_Click;
            chooseFileButton.Click += chooseFileButton_Click;

            openFileDialog1.Filter = "Text files(*.txt)|*.txt|All files(*.*)|*.*";
        }

        public Form2(Threefish threefish)
        {
            InitializeComponent();

            threefishInstance = threefish;

            stopWatch = new Stopwatch();

            backButton.Click += backButton_Click;
            plaintextTextBox.TextChanged += plaintextTextBox_TextChanged;
            encryptTextButton.Click += encryptTextButton_Click;
            decryptTextButton.Click += decryptTextButton_Click;
            chooseFileButton.Click += chooseFileButton_Click;

            openFileDialog1.Filter = "Text files(*.txt)|*.txt|All files(*.*)|*.*";
        }

        private void backButton_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void plaintextTextBox_TextChanged(object sender, EventArgs e)
        {
            plainText = plaintextTextBox.Text;
        }

        private void encryptTextButton_Click(object sender, EventArgs e)
        {
            if (String.IsNullOrEmpty(plaintextTextBox.Text))
            {
                MessageBox.Show("Поле текста для зашифрования не должно быть пустым. Введите текст в поле или выберите текстовый файл для зашифрования", "Ошибка");
            }
            else
            {
                if (blowfishInstance != null)
                {
                    blowfishInstance.SetRandomIV();

                    stopWatch.Restart();
                    encryptedText = blowfishInstance.Encrypt_CBC(plainText);
                    stopWatch.Stop();

                    elapsedTicks = stopWatch.ElapsedTicks;

                    encryptedTextBox.Text = encryptedText;
                    encryptionTimeTextBox.Text = elapsedTicks.ToString();
                }
                else if (twofishInstance != null)
                {
                    System.IO.MemoryStream ms = new System.IO.MemoryStream();

                    stopWatch.Restart();
                    ICryptoTransform encrypt = twofishInstance.CreateEncryptor(Key, dummy);

                    //Create Crypto Stream that transforms file stream using twofish encryption
                    CryptoStream cryptostream = new CryptoStream(ms, encrypt, CryptoStreamMode.Write);

                    plain = Util.GetBytes(plainText);

                    //write out Twofish encrypted stream
                    cryptostream.Write(plain, 0, plain.Length);

                    cryptostream.Close();

                    stopWatch.Stop();

                    bytOut = ms.ToArray();
                    elapsedTicks = stopWatch.ElapsedTicks;

                    encryptedTextBox.Text = Util.GetString(bytOut);
                    encryptionTimeTextBox.Text = elapsedTicks.ToString();
                }
                else
                {
                    byte[] plain = Util.GetBytes(plainText);

                    var enc = threefishInstance.CreateEncryptor();

                    stopWatch.Restart();
                    cipher = enc.TransformFinalBlock(plain, 0, plain.Length);
                    stopWatch.Stop();

                    elapsedTicks = stopWatch.ElapsedTicks;

                    encryptedTextBox.Text = Util.GetString(cipher);
                    encryptionTimeTextBox.Text = elapsedTicks.ToString();
                }
            }
        }

        private void encryptedTextBox_TextChanged(object sender, EventArgs e)
        {

        }

        private void encryptionTimeTextBox_TextChanged(object sender, EventArgs e)
        {

        }

        private void decryptTextButton_Click(object sender, EventArgs e)
        {
            if (String.IsNullOrEmpty(encryptedTextBox.Text))
            {
                MessageBox.Show("Поле зашифрованного текста не должно быть пустым. " +
                    "Введите текст в поле для зашифрования или выберите текстовый файл для зашифрования и нажмите кнопку \"Зашифровать\", а затем нажмите кнопку \"Расшифровать\"", "Ошибка");
            }
            else
            {
                if (blowfishInstance != null)
                {
                    stopWatch.Restart();
                    decryptedText = blowfishInstance.Decrypt_CBC(encryptedText);
                    stopWatch.Stop();

                    elapsedTicks = stopWatch.ElapsedTicks;

                    decryptedTextBox.Text = decryptedText;
                    decryptionTimeTextBox.Text = elapsedTicks.ToString();
                }
                else if (twofishInstance != null)
                {
                    byte[] Key = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
                    byte[] plain = Util.GetBytes(plainText);

                    ICryptoTransform decrypt = twofishInstance.CreateDecryptor(Key, plain);

                    System.IO.MemoryStream msD = new System.IO.MemoryStream();

                    stopWatch.Restart();
                    //create crypto stream set to read and do a Twofish decryption transform on incoming bytes
                    CryptoStream cryptostreamDecr = new CryptoStream(msD, decrypt, CryptoStreamMode.Write);

                    //write out Twofish encrypted stream
                    cryptostreamDecr.Write(bytOut, 0, bytOut.Length);

                    cryptostreamDecr.Close();

                    stopWatch.Stop();

                    elapsedTicks = stopWatch.ElapsedTicks;

                    byte[] bytOutD = msD.GetBuffer();

                    decryptedTextBox.Text = Util.GetString(bytOutD);
                    decryptionTimeTextBox.Text = elapsedTicks.ToString();
                }
                else
                {
                    var dec = threefishInstance.CreateDecryptor();

                    stopWatch.Restart();
                    var decipher = dec.TransformFinalBlock(cipher, 0, cipher.Length);
                    stopWatch.Stop();

                    elapsedTicks = stopWatch.ElapsedTicks;

                    decryptedTextBox.Text = Util.GetString(decipher);
                    decryptionTimeTextBox.Text = elapsedTicks.ToString();
                }
            }
        }

        private void decryptedTextBox_TextChanged(object sender, EventArgs e)
        {

        }

        private void decryptionTimeTextBox_TextChanged(object sender, EventArgs e)
        {

        }

        private void chooseFileButton_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog() == DialogResult.Cancel)
                return;
            else 
                file = openFileDialog1.FileName;
            plainText = System.IO.File.ReadAllText(file);
            plaintextTextBox.Text = plainText;
        }
    }
}
