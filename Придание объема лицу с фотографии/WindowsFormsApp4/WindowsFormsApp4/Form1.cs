using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using SharpGL;
using static System.Math;

namespace WindowsFormsApp4
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        
        float rtri = 0;
        bool check =false;
        float zoom=0;
        private void openGLControl1_Load(object sender, EventArgs e)
        {

        }
        double[,] Koor;
        Bitmap bmp;
        private void openGLControl1_OpenGLDraw(object sender, RenderEventArgs args)
        {
            OpenGL gl = this.openGLControl1.OpenGL;
            // Очистка экрана и буфера глубин
            gl.Clear(OpenGL.GL_COLOR_BUFFER_BIT | OpenGL.GL_DEPTH_BUFFER_BIT);

            // Пирамида /////////////////////////////
            // Сбрасываем модельно-видовую матрицу
            gl.LoadIdentity();
            // Сдвигаем перо влево от центра и вглубь экрана
            gl.Translate(0.0f, 0.0f, -5.0f);
            // Вращаем пирамиду вокруг ее оси Y
            gl.Rotate(rtri, 0.0f, 1.0f, 0.0f);
            // Рисуем треугольники - грани пирамиды
            gl.Begin(OpenGL.GL_POINTS);
            

            // Front
            float temp_zoom=0;
            int i = 0;
            int j = 0;
            if((-20 < zoom) && (zoom < 20))
            {
                if (zoom > 0)
                {
                    temp_zoom = 1 + Abs((zoom / 20));
                }
                else
                {
                    temp_zoom = 1 - Abs((zoom / 20));
                }
            }
            else
            {
                zoom = 0;
            }
            if (check == true)
            {
                for (double q = 0; q <= 2; q = q + ((1.0 / bmp.Width) * 2))
                {
                    for (double w = 0; w <= 2; w = w + ((1.0 / bmp.Height) * 2))
                    {
                        if (j == bmp.Height) break;
                        if (i == bmp.Width) break;
                        gl.Color(bmp.GetPixel(i, j).R, bmp.GetPixel(i, j).G, bmp.GetPixel(i, j).B);
                        gl.Vertex(((-q + 1)*temp_zoom),( (-w + 1)*temp_zoom), ((Koor[i, j])*temp_zoom));
                        j++;
                    }
                    i++;
                    j = 0;
                }

            }
            else
            {
                gl.Color(255.0, 255.0, 255.0);
                for (double q = 0; q <= 2; q = q + ((1.0 / bmp.Width) * 2))
                {
                    for (double w = 0; w <= 2; w = w + ((1.0 / bmp.Height) * 2))
                    {
                        if (j == bmp.Height) break;
                        if (i == bmp.Width) break;

                        gl.Vertex(((-q + 1) * temp_zoom), ((-w + 1) * temp_zoom), ((Koor[i, j]) * temp_zoom));
                        j++;
                    }
                    i++;
                    j = 0;
                }
            }
        
            gl.End();
            // Контроль полной отрисовки следующего изображения
            gl.Flush();
            // Меняем угол поворота 
        }

        private void button1_Click(object sender, EventArgs e)
        {


        }
        
        private void Form1_Load(object sender, EventArgs e)
        {
            OpenFileDialog dialog = new OpenFileDialog();
            dialog.Filter = "Image files (*.BMP, *.JPG, *.GIF, *.TIF, *.PNG, *.ICO, *.EMF, *.WMF)|*.bmp;*.jpg;*.gif; *.tif; *.png; *.ico; *.emf; *.wmf";
            if (dialog.ShowDialog() == DialogResult.OK)
            {
                Image image = Image.FromFile(dialog.FileName);
                bmp = new Bitmap(image, image.Width, image.Height);
                Koor = new double[image.Width, image.Height];                
                for (int i = 0; i < bmp.Width; i++)
                {
                    for (int j = 0; j < bmp.Height; j++)
                    {
                        if(i<=(bmp.Width/2))
                        {
                            Koor[i, j] = (bmp.GetPixel(i, j).GetBrightness() + ((Math.Log(i, 2)) / 8)); 
                        }
                        else
                        {
                            Koor[i, j] = (bmp.GetPixel(i, j).GetBrightness() + ((Math.Log(bmp.Width-i, 2)) / 8)); 
                        }
                    }
                }
            }
        }

        private void button1_Click_1(object sender, EventArgs e)
        {
            rtri -= 5.0f;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            rtri += 5.0f;
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            if(check==true)
            {
                check = false;
            }
            else
            {
                check = true;
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            zoom+=1;
        }

        private void button4_Click(object sender, EventArgs e)
        {
            zoom -= 1;
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void openFileDialog1_FileOk(object sender, CancelEventArgs e)
        {

        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            
           

        }
    }

}
