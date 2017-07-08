using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        private string itemSelected;

        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string[] data = { "1", "2", "3", "4", "5" };
            // 각 콤보박스에 데이타를 초기화
            comboSimple.Items.AddRange(data);
            comboDropDown.Items.AddRange(data);
            //string str ="dldfl";
            comboDropDownList.Items.Add("data");

            comboSimple_SelectedIndexChanged(sender, e);

           // DrawVerticalText();




        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void comboSimple_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (comboSimple.SelectedIndex >= 0)
            {
                this.itemSelected = comboSimple.SelectedItem as string;
                DrawVerticalText();
            }
        }

        private void DrawVerticalText()
        { 
            Graphics formGraphics = this.CreateGraphics();
            string txt2;
            //string txt = "Sample 한글..Text";

            txt2 = itemSelected;
            Font drawFont = new Font("Arial", 22); 
            SolidBrush drawBrush = new SolidBrush(Color.Black); 
            float x = 150.0f; float y = 50.0f; 
            // 출력방향 설정 
            StringFormat drawFormat = new StringFormat(StringFormatFlags.DirectionVertical); 
            formGraphics.DrawString(txt2, drawFont, drawBrush, x, y, drawFormat); 
            drawFont.Dispose(); 
            drawBrush.Dispose(); 
            formGraphics.Dispose(); 
        }

 

    }
}
