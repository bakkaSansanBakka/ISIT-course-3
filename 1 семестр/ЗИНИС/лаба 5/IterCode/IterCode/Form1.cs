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
    public partial class Form1 : Form
    {
        //инф слово
        public string mes;
        public int colMes; //кол-во символов инф слова
        public string code; //проверочные символы
        public int colCode; //кол-во проверочных символов  
        public string mesCode; //кодовое слово
        List<int> mesCodeListX = new List<int>();
        List<int> mesCodeListNew = new List<int>();
        List<int> codeListYNew = new List<int>();
        string codeYNew;
        public int[,] verMatrix;
        public bool IsAddInfByte = false;
       
        Tuple<int, int> minV; //наименьшая пара множителей
        int[,] mesMatrixX; //инф слово в виде матрицы
        int[] verSymbolColumnX;
        int[] verSymbolRowX;
        int VerSymbolKX;
        int colEr;
        int[] posEr;

        public string mesY;
        public int colMesY; //кол-во символов инф слова
        public string codeY= string.Empty; //проверочные символы
        public int colCodeY; //кол-во проверочных символов  
        public string mesCodeY; //кодовое слово
        List<int> mesCodeListY = new List<int>();
        int[,] mesMatrixY; //инф слово в виде матрицы
        int[] verSymbolColumnY;
        int[] verSymbolRowY;
        int VerSymbolKY;
        string sindrom = string.Empty;
        List<int> sindromList;
        Form2 f2;
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            mes = textBox1.Text;
            colMes = mes.Count();
            if (colMes % 2 != 0) //если кол-во символов нечетное, то
            {
                mes += "0";
                colMes += 1;
                IsAddInfByte = true;
            }
            List<Tuple<int, int>> varMn = new List<Tuple<int, int>>(); //хранит пары множителей
            List<int> simple = new List<int>();
            simple.Add(2);
            simple.Add(3);
            simple.Add(5);
            simple.Add(7);
            simple.Add(9);
            int k = colMes;
            int prev = 1;
            var simpleMn = 1;
            while (simpleMn != 0)
            {
                varMn.Add(new Tuple<int, int>(k / simpleMn, simpleMn * prev));
                k /= simpleMn;
                prev *= simpleMn;
                simpleMn = simple.FirstOrDefault(p => k % p == 0);

            }

        
            List<int> sumVar = new List<int>();
            foreach (var item in varMn)
            {
                sumVar.Add(item.Item1 + item.Item2);
            }

            int index = sumVar.IndexOf(sumVar.Min());
            minV = varMn[index];              
            mesMatrixX = new int[minV.Item1, minV.Item2];
            mesMatrixY = new int[minV.Item1, minV.Item2];
            GetInfMatrixByInfMes(mesMatrixX, minV.Item1, minV.Item2, mesCodeListX, true, mes);
           
            colCode = sumVar.Min() + 1;
            verMatrix = new int[sumVar.Min() + 1, mes.Count() + colCode];
            listBox1.Items.Add("Message " + mes);
            listBox1.Items.Add("Information symbols " + colMes);
            listBox1.Items.Add("Check symbols " + colCode);
            code = this.GetCodeByInfMatrix(mesMatrixX, mesCodeListX, true, minV.Item1, minV.Item2);
            mesCode = mes + code;
            GenerateVerMatrix();
            listBox1.Items.Add("Check Code " + code);
            listBox1.Items.Add("Sended " + mesCode);
        }
        public string GetCodeByInfMatrix(int[,] matrix, List<int> mesList , bool mode, int row, int column)
        {
            string code = String.Empty;
            verSymbolColumnX = new int[row];
            verSymbolRowX = new int[column];
            int sumRow = 0; 
            if (mode)
                dataGridView1.Columns.Add(dataGridView1.Columns.Count.ToString(),
                                              dataGridView1.Columns.Count.ToString());
            for (int i = 0; i < row; i++)
            {

                sumRow = 0;
                for (int j = 0; j < column; j++)
                {
                    sumRow += matrix[i, j];
                   

                }
                if (mode)
                    dataGridView1.Rows[i].Cells[dataGridView1.Columns.Count - 1].Value = (sumRow % 2);
                dataGridView1.Rows[i].Cells[dataGridView1.Columns.Count - 1].Style.BackColor = Color.LightGray;
                verSymbolColumnX[i] = (sumRow % 2);
                mesList.Add(sumRow % 2);
                code += (sumRow % 2).ToString();
            }
            if (mode)
                dataGridView1.Rows.Add();
            for (int j = 0; j < column; j++)
            {
                sumRow = 0;

                for (int i = 0; i < row; i++)
                {
                    sumRow += matrix[i, j];
                }
                if (mode)
                    dataGridView1.Rows[dataGridView1.Rows.Count - 2].Cells[j].Value = (sumRow % 2);
                dataGridView1.Rows[dataGridView1.Rows.Count - 2].Cells[j].Style.BackColor = Color.LightGray;
                verSymbolRowX[j] = (sumRow % 2);
                mesList.Add(sumRow % 2);
                code += (sumRow % 2).ToString();
            }
            sumRow = 0;
            for (int i = 0; i < verSymbolColumnX.Count(); i++)
            {
                sumRow += verSymbolColumnX[i];
            }
            if (mode)
                dataGridView1.Rows[dataGridView1.Rows.Count - 2]
                    .Cells[dataGridView1.Columns.Count - 1].Value = (sumRow % 2);
            dataGridView1.Rows[dataGridView1.Rows.Count - 2]
                   .Cells[dataGridView1.Columns.Count - 1].Style.BackColor = Color.Gray;
            VerSymbolKX = (sumRow % 2);
            mesList.Add(sumRow % 2);
            code += (sumRow % 2).ToString();


            return code;
        }
        public void GetInfMatrixByInfMes(int [,] matrix, int row, int column, List<int> mesList, bool mode, string mes )
        {
            int startIndex = 0;
            dataGridView1.Columns.Clear();
            dataGridView1.Rows.Clear();
            for (int i = 0; i < column; i++)
            {
                if (mode)
                dataGridView1.Columns.Add(i.ToString(), i.ToString());
            }
            for (int i = 0; i < row; i++)
            {
              
                if (mode)
                dataGridView1.Rows.Add();
                for (int j = 0; j < column; j++)
                {
                    matrix[i, j] = Convert.ToInt32(mes.Substring(startIndex, 1));
                    mesList.Add(matrix[i, j]);
                    if(mode)
                    dataGridView1.Rows[i].Cells[j].Value = matrix[i, j];
                    startIndex++;
                }
            }
 
        }

        private void button5_Click(object sender, EventArgs e)
        {
            try
            {
                f2 = new Form2();
                f2.Show(this);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            try
            {        
                if (f2 != null)
                {
                    colEr = f2.colEr;
                    posEr = f2.posEr;

                }
                else
                {
                    colEr = 0;                    
                    posEr = new int[colEr];
                }               
                mesCodeY = String.Empty;
                    button4.Enabled = true;
                    mesCodeListY = new List<int>(mesCodeListX);
                    for (int i = 0; i < posEr.Count(); i++)
                    {
                        if (mesCodeListY[posEr[i] - 1] == 0)
                        {
                            mesCodeListY[posEr[i] - 1] = 1;

                        }
                        else
                        {
                            mesCodeListY[posEr[i] - 1] = 0;
                        }

                    }
                if (mesCodeListY.Count >0)
                {
                    foreach (var item in mesCodeListY)
                    {
                        mesCodeY += item.ToString();
                    }
                }
                else
                {
                    mesCodeY = mesCode;
                }
                   
                    listBox1.Items.Add("Received " + mesCodeY);              

            }
            catch (Exception ex)
            {

            }

        }

        private void button4_Click(object sender, EventArgs e)
        {
            
            codeY += mesCodeY.Substring(colMes);
            GetInfMatrixByInfMes(mesMatrixY, minV.Item1, minV.Item2, mesCodeListNew, true, mesCodeY);
            codeYNew = GetCodeByInfMatrix(mesMatrixY, mesCodeListNew, true, minV.Item1, minV.Item2);
            listBox1.Items.Add("Check code" + codeYNew);
            int i = 0;
            int colOne = 0;
            foreach (var codeSym in codeY)
            {
                if (codeSym.Equals(Convert.ToChar(codeYNew.Substring(i, 1))))
                {
                    sindrom += "0";
                }
                else
                {
                    sindrom += "1";
                    colOne++;
                }
                i++;
            }
            sindromList = new List<int>();
            foreach (var item in sindrom)
            {
                sindromList.Add(Convert.ToInt32(item.ToString()));
            }
            listBox1.Items.Add("Syndrom " + sindrom);
            if (colOne == 0)
            {
                listBox1.Items.Add("Syndrom=0 No errors");
            }
            else
            {
                

            if (colOne % 2 == 0 && colOne !=0)
            {
                listBox1.Items.Add("Syndrom/2=0");
                listBox1.Items.Add("2 or more errors");


            }
            else
            {
                 listBox1.Items.Add("Syndrom/2 =1");
                int numberCol = 0;
                for (int j = 0; j < colMes + colCode; j++)
                {
                    bool ident = true;

                    for (int k = 0; k < code.Count(); k++)
                    {
                        if (sindromList[k] != verMatrix[k, j])
                        {
                            ident = false;
                            break;
                        }
                    }
                    if (ident)
                    {
                        numberCol = j + 1;
                        break;
                    }
                }
                if (numberCol != 0)
                {
                    listBox1.Items.Add("Error " + numberCol + " bit");

                    string vectorEr = string.Empty;
                    for (int j = 0; j < colMes + colCode; j++)
                    {
                        if (j == numberCol - 1)
                        {
                            vectorEr += "1";

                            if (mesCodeY.Substring(numberCol-1, 1) == "1")
                                mesCodeY = mesCodeY.Substring(0, numberCol-1) + "0" +
                                    mesCodeY.Substring(numberCol);
                            else
                            {
                                mesCodeY = mesCodeY.Substring(0, numberCol-1) + "1" +
                                                               mesCodeY.Substring(numberCol);
                            }
                        }
                        else
                            vectorEr += "0";
                    }
                    listBox1.Items.Add("Error Vector " + vectorEr);
                    listBox1.Items.Add("Fixed " + mesCodeY);
                }           
                else
               
                    listBox1.Items.Add("3 or more errors ");
                }
            }
        }

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }
        public void GenerateVerMatrix()
        {
            int k = 0;
            for (int i = 0; i < minV.Item1; i++)
            {

                for (int j = 0 + k; j < minV.Item2 + k; j++)
                {
                    verMatrix[i, j] = 1;
                }
                k += minV.Item2;

            }
            k = 0;
            for (int i = minV.Item1; i < minV.Item1 + minV.Item2; i++)
            {

                for (int j = 0 + k; j < mes.Count(); j += minV.Item2)
                {
                    verMatrix[i, j] = 1;
                }
                k++;

            }
            for (int j = 0; j < colMes; j++)
            {
                verMatrix[(minV.Item1 + minV.Item2), j] = 1;
            }
            for (int i = 0; i < colCode; i++)
            {
                verMatrix[i, i +colMes] = 1;
            }

                dataGridView2.Columns.Clear();
            dataGridView2.Rows.Clear();
            for (int i = 0; i < colMes+colCode; i++)
            {
                dataGridView2.Columns.Add(i.ToString(), i.ToString());
            }

            for (int i = 0; i < colCode; i++)
            {
                dataGridView2.Rows.Add();
                for (int j = 0; j < colMes+colCode; j++)
                {
                    dataGridView2.Rows[i].Cells[j].Value = verMatrix[i, j];
                }
            }
        }

        private void dataGridView2_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }
    }
}
