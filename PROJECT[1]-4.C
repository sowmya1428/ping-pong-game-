/* Basic 2D pong with OpenGL & GLUT */



#include<windows.h>
#include<GL/glut.h>
#include<stdio.h>
#include<winuser.h>

GLfloat cpuPaddle = 175.0f;		// CPU's paddle Y position
GLfloat playerPaddle = 175.0f;     //player1 paddle Y position
GLfloat pplayerPaddle = 175.0f;		// pplayer paddle Y position
GLfloat	ballX = 200.0f;		// Ball X
GLfloat ballY = 200.0f;		// Ball Y

							// How many spaces to move each frame
GLfloat step = 4.0f;
GLfloat ballStepX = -4.0f;
GLfloat ballStepY = -4.0f;
void *font = GLUT_BITMAP_TIMES_ROMAN_24;

// keep track of the window height and width
GLfloat windowWidth;
GLfloat windowHeight;
int dcond = 1, tcond = 1;
char cpuScore = 0, playerScore = 0;
int gameover = 0;	// used to tell if the game has ended

void output(int x, int y, char *string)
{
	int len, i;
	glRasterPos2f(x, y);
	len = (int)strlen(string);
	for (i = 0; i<len; i++)
		glutBitmapCharacter(font, string[i]);
}
void keyboard(unsigned char key, int x, int y)

{
	switch (key)
	{

	case '4': dcond = 6; tcond = 5; exit(0); break;
	case '1':dcond = 2; tcond = 2; break;
	case '2':dcond = 3; tcond = 3; break;
	case '3':dcond = 4; tcond = 4; break;
	}
}
void menu()
{
	switch (dcond)
	{
	case 1:
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1.0f, 1.0f, 1.0f);
		output(200, 375, "WELCOME TO PING PONG BALL GAME");
		glColor3f(1.0f, 0.0f, 0.0f);
		output(220, 330, "1.Single player easy");
		glColor3f(0.0f, 0.0f, 1.0f);
		output(220, 300, "2.Single player hard");
		glColor3f(0.0f, 1.0f, 0.0f);
		output(220, 270, "3.Two player");
output(160,250,"player two (left side)");
output(400,250,"player one ( right side) ");
		glColor3f(1.0f, 1.0f, 0.0f);
		output(220, 230, "4.Exit");
		glColor3f(1.0f, 0.0f, 1.0f);
		output(160, 95, "INSTRUCTIONS:");
		output(160, 75, ">Single player: Use up and down arrow keys to control the paddle.");
output(160,55,">Double player: ");
output(160,45,">Payer one: Use "A" and "Z" keys to control the paddle.");
output(160,35,">Player two : Use up and down arrow  to control the paddle.");
		output(160, 15, "> Save the ball from going off the window");
		glutSwapBuffers();
		break;
	case 2:
		glClear(GL_COLOR_BUFFER_BIT);

		glColor3f(0.0f, 0.5f, 1.0f);

		// CPU paddle
		glRectf(10, cpuPaddle, 20, cpuPaddle + 50);

		// Player paddle
		glRectf(windowWidth - 20, playerPaddle, windowWidth - 10, playerPaddle + 50);

		glColor3f(1.0f, 0.0f, 0.0f);

		// Ball
		glRectf(ballX, ballY, ballX + 5, ballY + 5);
		output(250, 350, "PIN BALL");


		glutSwapBuffers();
		break;
	case 3:

		glClear(GL_COLOR_BUFFER_BIT);

		glColor3f(0.0f, 0.5f, 1.0f);

		// CPU paddle
		glRectf(10, cpuPaddle, 20, cpuPaddle + 50);

		// Player paddle
		glRectf(windowWidth - 20, playerPaddle, windowWidth - 10, playerPaddle + 25);

		glColor3f(1.0f, 0.0f, 0.0f);

		// Ball
		glRectf(ballX, ballY, ballX + 5, ballY + 5);
		output(250, 350, "PIN BALL");


		glutSwapBuffers();
		break;

	case 4:
		glClear(GL_COLOR_BUFFER_BIT);

		glColor3f(0.0f, 0.5f, 1.0f);

		// CPU paddle
		glRectf(10, pplayerPaddle, 20, pplayerPaddle + 50);

		// Player paddle
		glRectf(windowWidth - 20, playerPaddle, windowWidth - 10, playerPaddle + 50);

		glColor3f(1.0f, 0.0f, 0.0f);

		// Ball
		glRectf(ballX, ballY, ballX + 5, ballY + 5);
		output(250, 350, "PIN BALL");


		glutSwapBuffers();
		break;

	case 6: exit(0);
		break;


	}
}
void credit()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0f, 1.0f, 1.0f);
	output(160, 250, "THANKYOU FOR PLAYING!!");
	glColor3f(1.0f, 0.0f, 0.0f);
	output(250, 100, "DESIGNED BY:");
	glColor3f(1.0f, 0.5f, 0.0f);
	output(250, 80, "SOWMYA K (1SG14CS110)");
	glutSwapBuffers();
}

void TimerFunction(int value)
{
	switch (tcond)
	{
	case 1:glutTimerFunc(33, TimerFunction, 1);
		break;
	case 2:
		if (playerPaddle < 375)
		{
			if (GetAsyncKeyState(VK_UP))
				playerPaddle += step;
		}

		if (playerPaddle > 0)
		{
			if (GetAsyncKeyState(VK_DOWN))
				playerPaddle -= step;
		}


		// ball physics

		// reverse direction when the ball hits playerPaddle
		if (ballX >= windowWidth - 20)	// IF the ball is matching Xpos with playerPaddle
		{
			if (ballY >= playerPaddle && ballY <= playerPaddle + 50) // ball within paddle's pos
			{
				playerScore++;
				ballStepX = -ballStepX;
				MessageBeep(0);
				ballStepX = ballStepX - 0.5f;	// add some speed each time the player hits the ball

			}
		}


		if (ballX <= 20 && ballX > 10)  // CPU paddle
		{
			if (ballY >= cpuPaddle && ballY <= cpuPaddle + 50)
			{
				cpuScore++;
				ballStepX = -ballStepX;

			}
			MessageBeep(0);
		}


		// Bounce the ball off the top and bottom
		if (ballY > windowHeight || ballY - 5 < 0)
			ballStepY = -ballStepY;

		// move the CPUs paddle
		if (ballY < cpuPaddle + 25)
		{
			cpuPaddle -= step;
		}
		else
		{
			cpuPaddle += step;
		}

		// lets see if the player won or lost
		if (ballX > windowWidth)
		{
			MessageBox(NULL, L"YOU LOSE!", L"LOSER", MB_OK);
			printf("Game Over, you lost!\n");
			gameover = 1;
		}

		if (ballX < 0 && (ballY<cpuPaddle || ballY>cpuPaddle + 50))
		{
			MessageBox(NULL, L"YOU WIN!", L"WINNER", MB_OK);
			printf("Game Over, you won!\n");
			gameover = 1;
		}


		ballX += ballStepX;
		ballY += ballStepY;

		glutPostRedisplay();

		if (!gameover)
			glutTimerFunc(33, TimerFunction, 1);
		if (gameover)
			glutDisplayFunc(credit);
		break;

	case 4:
		// Get keyboard input
		if (playerPaddle < 350)
		{
			if (GetAsyncKeyState(VK_UP))
				playerPaddle += step;
		}

		if (playerPaddle > 0)
		{
			if (GetAsyncKeyState(VK_DOWN))
				playerPaddle -= step;
		}
		// move the pplayer paddle
		if (pplayerPaddle < 350)
		{
			if (GetAsyncKeyState(65))
				pplayerPaddle += step;
		}

		if (pplayerPaddle > 0)
		{
			if (GetAsyncKeyState(90))
				pplayerPaddle -= step;
		}


		// ball physics

		// reverse direction when the ball hits playerPaddle
		if (ballX >= windowWidth - 20 && ballX < windowWidth - 10)	// IF the ball is matching Xpos with playerPaddle
		{
			if (ballY >= playerPaddle && ballY <= playerPaddle + 50) // ball within paddle's pos
			{
				playerScore++;
				ballStepX = -ballStepX;
				MessageBeep(0);
				ballStepX = ballStepX - 0.1f;	// add some speed each time the player hits the ball
				if (ballStepY < 0)
				{
					ballStepY -= 0.01f;
				}
				else
				{
					ballStepY += 0.01f;
				}
			}
		}


		if (ballX <= 20 && ballX > 10)  // player 2 paddle
		{
			if (ballY >= pplayerPaddle && ballY <= pplayerPaddle + 50)
			{
				ballStepX = -ballStepX;

			}
			MessageBeep(0);
		}


		// Bounce the ball off the top and bottom
		if (ballY > windowHeight || ballY - 5 < 0)
			ballStepY = -ballStepY;


		// lets see if the player won or lost
		if (ballX > windowWidth)
		{
			MessageBox(NULL, L"player 1 win", L"WINNER", MB_OK);
			printf("Game Over, you won!\n");
			gameover = 1;
		}

		if (ballX < 0)
		{
			MessageBox(NULL, L"player 2 win", L"WINNER", MB_OK);
			printf("Game Over, you won!\n");
			gameover = 1;
		}


		ballX += ballStepX;
		ballY += ballStepY;

		glutPostRedisplay();

		if (!gameover)
			glutTimerFunc(33, TimerFunction, 1);
		if (gameover)
			glutDisplayFunc(credit);
		break;
	case 3:
		// Get keyboard input
		if (playerPaddle < 375)
		{
			if (GetAsyncKeyState(VK_UP))
				playerPaddle += step;
		}

		if (playerPaddle > 0)
		{
			if (GetAsyncKeyState(VK_DOWN))
				playerPaddle -= step;
		}


		// ball physics

		// reverse direction when the ball hits playerPaddle
		if (ballX >= windowWidth - 20 && ballX < windowWidth - 10)	// IF the ball is matching Xpos with playerPaddle
		{
			if (ballY >= playerPaddle && ballY <= playerPaddle + 25) // ball within paddle's pos
			{
				playerScore++;
				ballStepX = -ballStepX;
				MessageBeep(0);
				ballStepX = ballStepX - 0.1f;	// add some speed each time the player hits the ball
				if (ballStepY < 0)
				{
					ballStepY -= 0.01f;
				}
				else
				{
					ballStepY += 0.01f;
				}
			}
		}


		if (ballX <= 20 && ballX > 10)  // CPU paddle
		{
			if (ballY >= cpuPaddle && ballY <= cpuPaddle + 50)
			{
				cpuScore++;
				ballStepX = -ballStepX;

			}
			MessageBeep(0);
		}


		// Bounce the ball off the top and bottom
		if (ballY > windowHeight || ballY - 5 < 0)
			ballStepY = -ballStepY;

		// move the CPUs paddle
		if (ballY < cpuPaddle + 25)
		{
			cpuPaddle -= step;
		}
		else
		{
			cpuPaddle += step;
		}

		// lets see if the player won or lost
		if (ballX > windowWidth)
		{
			MessageBox(NULL, L"YOU LOSE!", L"LOSER", MB_OK);
			printf("Game Over, you lost!\n");
			gameover = 1;
		}

		if (ballX < 0)
		{
			MessageBox(NULL, L"YOU WIN!", L"WINNER", MB_OK);
			printf("Game Over, you won!\n");
			gameover = 1;
		}


		ballX += ballStepX;
		ballY += ballStepY;

		glutPostRedisplay();

		if (!gameover)
			glutTimerFunc(33, TimerFunction, 1);
		if (gameover)
			glutDisplayFunc(credit);
		break;
	case 5:exit(0);
		break;

	}
}


void SetupRC()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}



void ChangeSize(GLsizei w, GLsizei h)
{
	if (h == 0)
		h = 1;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h)
	{
		windowHeight = 400.0f*h / w;
		windowWidth = 400.0f;
	}
	else
	{
		windowHeight = 400.0f;
		windowWidth = 400.0f*w / h;
	}

	glOrtho(0.0f, windowWidth, 0.0f, windowHeight, 1.0f, -1.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc,char**argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutCreateWindow("Pong");
	glutDisplayFunc(menu);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(33, TimerFunction, 1);
	glutKeyboardFunc(keyboard);
	if (dcond == 6)
		return 0;
	SetupRC();

	glutMainLoop();

}
