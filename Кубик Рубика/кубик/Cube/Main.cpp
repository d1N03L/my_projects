#include <cstdio>
#include <windows.h>
#include <GL/freeglut.h>
#include <iostream>
#include <cstdlib>
#include <TCHAR.h>


void disp();
float deg = 0.0, degy = 0.0;
unsigned int c[9] = { 0xFFFFFF, 0xFFFF00, 0x0000FF, 0x00FF00, 0xFF0000, 0xCD853F };




class SmallCube
{
	unsigned int color[6];
public:
	void setColor(int i, int color)
	{
		this->color[i] = color;
	}
	unsigned char* transform_to_color(int i)
	{
		_color[0] = color[i] >> 16;
		_color[1] = color[i] >> 8;
		_color[2] = color[i];
		return _color;
	}
	void rotateZ()
	{
		unsigned int temp = color[5];
		color[5] = color[2];
		color[2] = color[4];
		color[4] = color[3];
		color[3] = temp;
	}
	void rotateX()
	{
		unsigned int temp = color[0];
		color[0] = color[5];
		color[5] = color[1];
		color[1] = color[4];
		color[4] = temp;
	}
	void Draw(int x, int y, int z)
	{
		glPushMatrix();
		glRotatef(deg, 0, 1, 0);
		glRotatef(degy, 1, 0, 0);
		glTranslated(x, y, z);
		glBegin(GL_QUADS);

		//задн€€
		glColor3ubv(transform_to_color(3));
		glVertex3f(-50, 50, -50);
		glVertex3f(50, 50, -50);
		glVertex3f(50, -50, -50);
		glVertex3f(-50, -50, -50);
		//верхн€€
		glColor3ubv(transform_to_color(0));
		glVertex3f(-50, 50, -50);
		glVertex3f(50, 50, -50);
		glVertex3f(50, 50, 50);
		glVertex3f(-50, 50, 50);
		//передн€€
		glColor3ubv(transform_to_color(2));
		glVertex3f(-50, 50, 50);
		glVertex3f(50, 50, 50);
		glVertex3f(50, -50, 50);
		glVertex3f(-50, -50, 50);
		//нижн€€
		glColor3ubv(transform_to_color(1));
		glVertex3f(-50, -50, -50);
		glVertex3f(50, -50, -50);
		glVertex3f(50, -50, 50);
		glVertex3f(-50, -50, 50);
		//лева€
		glColor3ubv(transform_to_color(4));
		glVertex3f(-50, 50, -50);
		glVertex3f(-50, -50, -50);
		glVertex3f(-50, -50, 50);
		glVertex3f(-50, 50, 50);
		//права€
		glColor3ubv(transform_to_color(5));
		glVertex3f(50, 50, -50);
		glVertex3f(50, 50, 50);
		glVertex3f(50, -50, 50);
		glVertex3f(50, -50, -50);

		glEnd();
		glPopMatrix();
	}
	int getcolor(int i)
	{
		return this->color[i];
	}
private:
	unsigned char _color[4];
};
class Cubik
{
	SmallCube a[3][3][3];
public:
	void drawAllCubiks()
	{
		for (int x_d = -105, i = 0; x_d < 106, i < 3; x_d = x_d + 105, i++)
		{
			for (int y_d = -105, j = 0; y_d < 106, j < 3; y_d = y_d + 105, j++)
			{
				for (int z_d = -105, k = 0; z_d < 106, k < 3; z_d = z_d + 105, k++)
				{
					a[i][j][k].Draw(x_d, y_d, z_d);
					if (z_d == 105)
					{
						break;
					}
				}
				if (y_d == 105)
				{
					break;
				}
			}
			if (x_d == 105)
			{
				break;
			}
		}
	}
	void color_to_cube(unsigned int* color)
	{
		// верх
		int i = 0, j = 0, k = 0;
		for (i = 0; i < 3; i++)
			for (j = 0; j < 3; j++)
				a[i][2][j].setColor(0, color[0]);
		// низ
		for (i = 0; i < 3; i++)
			for (j = 0; j < 3; j++)
				a[i][0][j].setColor(1, color[1]);
		// спереди
		for (k = 0; k < 3; k++)
			for (j = 0; j < 3; j++)
				a[j][k][2].setColor(2, color[2]);
		// сзади
		for (k = 0; k < 3; k++)
			for (j = 0; j < 3; j++)
				a[j][k][0].setColor(3, color[3]);
		// слева
		for (i = 0; i < 3; i++)
			for (k = 0; k < 3; k++)
				a[0][k][i].setColor(4, color[4]);
		// справа
		for (i = 0; i < 3; i++)
			for (k = 0; k < 3; k++)
				a[2][k][i].setColor(5, color[5]);
	}

	void rotate_around_Z(int ind)
	{
		SmallCube temp;
		int i;
		for (i = 0; i < 6; i++)
		{
			temp.setColor(i, a[0][ind][0].getcolor(i));
		}
		a[2][ind][0].rotateZ();
		for (i = 0; i < 6; i++)
		{
			a[0][ind][0].setColor(i, a[2][ind][0].getcolor(i));
		}
		a[2][ind][2].rotateZ();
		for (i = 0; i < 6; i++)
		{
			a[2][ind][0].setColor(i, a[2][ind][2].getcolor(i));
		}
		a[0][ind][2].rotateZ();
		for (i = 0; i < 6; i++)
		{
			a[2][ind][2].setColor(i, a[0][ind][2].getcolor(i));
		}
		temp.rotateZ();
		for (i = 0; i < 6; i++)
		{
			a[0][ind][2].setColor(i, temp.getcolor(i));
		}
		for (i = 0; i < 6; i++)
		{
			temp.setColor(i, a[0][ind][1].getcolor(i));
		}
		a[1][ind][0].rotateZ();
		for (i = 0; i < 6; i++)
		{
			a[0][ind][1].setColor(i, a[1][ind][0].getcolor(i));
		}
		a[2][ind][1].rotateZ();
		for (i = 0; i < 6; i++)
		{
			a[1][ind][0].setColor(i, a[2][ind][1].getcolor(i));
		}
		a[1][ind][2].rotateZ();
		for (i = 0; i < 6; i++)
		{
			a[2][ind][1].setColor(i, a[1][ind][2].getcolor(i));
		}
		temp.rotateZ();
		for (i = 0; i < 6; i++)
		{
			a[1][ind][2].setColor(i, temp.getcolor(i));
		}
	}
	void rotate_around_X(int ind)
	{
		SmallCube temp;
		int i;
		for (i = 0; i < 6; i++)
		{
			temp.setColor(i, a[0][0][ind].getcolor(i));
		}
		a[0][2][ind].rotateX();
		for (i = 0; i < 6; i++)
		{
			a[0][0][ind].setColor(i, a[0][2][ind].getcolor(i));
		}
		a[2][2][ind].rotateX();
		for (i = 0; i < 6; i++)
		{
			a[0][2][ind].setColor(i, a[2][2][ind].getcolor(i));
		}
		a[2][0][ind].rotateX();
		for (i = 0; i < 6; i++)
		{
			a[2][2][ind].setColor(i, a[2][0][ind].getcolor(i));
		}
		temp.rotateX();
		for (i = 0; i < 6; i++)
		{
			a[2][0][ind].setColor(i, temp.getcolor(i));
		}
		for (i = 0; i < 6; i++)
		{
			temp.setColor(i, a[1][0][ind].getcolor(i));
		}
		a[0][1][ind].rotateX();
		for (i = 0; i < 6; i++)
		{
			a[1][0][ind].setColor(i, a[0][1][ind].getcolor(i));
		}
		a[1][2][ind].rotateX();
		for (i = 0; i < 6; i++)
		{
			a[0][1][ind].setColor(i, a[1][2][ind].getcolor(i));
		}
		a[2][1][ind].rotateX();
		for (i = 0; i < 6; i++)
		{
			a[1][2][ind].setColor(i, a[2][1][ind].getcolor(i));
		}
		temp.rotateX();
		for (i = 0; i < 6; i++)
		{
			a[2][1][ind].setColor(i, temp.getcolor(i));
		}

	}

};

Cubik cube;
void disp()
{
	glPushMatrix();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	cube.drawAllCubiks();
	glPopMatrix();
	glutSwapBuffers();
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a': deg = deg - 3;
		break;
	case 'd': deg = deg + 3;
		break;
	case 's': degy = degy + 3;
		break;
	case 'w': degy = degy - 3;
		break;
	case '1': cube.rotate_around_Z(0);
		break;
	case '2': cube.rotate_around_Z(1);
		break;
	case '3': cube.rotate_around_Z(2);
		break;
	case '4': cube.rotate_around_X(0);
		break;
	case '5': cube.rotate_around_X(1);
		break;
	case '6': cube.rotate_around_X(2);
		break;
	}

}
void Timer(int)
{
	glutTimerFunc(30, Timer, 0);
	glutPostRedisplay();
}


int main(int argc, char** argv)
{
	int x = 100;
	int y = 100;
	int width = 800;
	int height = 800;
	glutInit(&argc, argv);
	glutInitWindowPosition(x, y);
	glutInitWindowSize(width, height);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("Cube");
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	cube.color_to_cube(c);
	glOrtho(-width / 2, width / 2, -height / 2, height / 2, -400, 400);
	glutDisplayFunc(disp);
	glutTimerFunc(20, Timer, 0);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();
	return 0;
}

