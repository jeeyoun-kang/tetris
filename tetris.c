//���α׷��ַ� ��������Ʈ
//1971365,������
//1�ο� ��Ʈ���� ����
#define _CRT_SECURE_NO_WARNINGS


#include<stdio.h>
#include<Windows.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>
#include<stdbool.h>

// ���� ����
#define BLACK	0
#define BLUE1	1
#define GREEN1	2
#define CYAN1	3
#define RED1	4
#define MAGENTA1 5
#define YELLOW1	6
#define GRAY1	7
#define GRAY2	8
#define BLUE2	9
#define GREEN2	10
#define CYAN2	11
#define RED2	12
#define MAGENTA2 13
#define YELLOW2	14
#define WHITE	15

void textcolor(int fg_color, int bg_color)//���������Լ�
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fg_color | bg_color << 4);
}

#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ESCAPE 27
#define SPACE 32
#define UP 72
#define MAPWIDTH 13//�ְܼ���
#define MAPHEIGHT 25//�ּܼ���

clock_t CurTime, OldTime;
clock_t WaitCurTime, WaitOldTime;

typedef struct ShadowLocation//�׸����Լ�����
{
	int ShadowY;
	int ShadowX;

}ShadowLocation;

typedef struct Tetris//��Ʈ���� �Լ� ����
{
	int x;        //��� ��ǥ
	int y;        //��� ��ǥ 

	int rotation;
	int randBlocks;

	bool Right;
	bool Left;

	bool save;
	int score;

}Tetris;

Tetris T;
ShadowLocation S;



void gotoxy(int x, int y);
void CursorView(char show);


void Map();
void RandOutput();
void Delete();
void Move();

void Save();
void TimeDown();
void LineCheck();

void LineRemove(int vertical);
void LineDown(int vertical);
void Rotation();
void QuickDown();
void GameOver();
void Output();


void Score();
void Shadow();
void ShadowOutput();
void howtogame();
void startgame(void);
void Waiting();
// box �׸��� �Լ�, ch ���ڿ��� (x1,y1) ~ (x2,y2) box�� �׸���.
void draw_box2(int x1, int y1, int x2, int y2, char *ch)
{
	int x, y;
	for (x = x1; x <= x2; x += 2) {
		gotoxy(x, y1);
		printf("%s", ch);
		gotoxy(x, y2);
		printf("%s", ch);
	}
	for (y = y1; y <= y2; y++) {
		gotoxy(x1, y);
		printf("%s", ch);
		gotoxy(x2, y);
		printf("%s", ch);
	}
}
void startgame(void) {//���� ùȭ��
	textcolor(BLUE2, WHITE);
	draw_box2(0, 0, 50, 25, "��");
	textcolor(GREEN2, WHITE);
	gotoxy(7, 5);printf("���� ���� ���� ����  �� ����");
	gotoxy(7, 6);printf("  ��   ��       ��   ��  ��  �� ��    ");
	gotoxy(7, 7);printf("  ��   ����   ��   ���    �� ����");
	gotoxy(7, 8);printf("  ��   ��       ��   �� ��   ��     �� ");
	gotoxy(7, 9);printf("  ��   ����   ��   ��  ��  �� ����");
	gotoxy(15, 13);printf("Enter Any Key To Start!");
	gotoxy(17, 19);printf("��:Rotation");
	gotoxy(17, 20);printf("��:Fast drop");
	gotoxy(17, 21);printf("����:Left/Right");
	gotoxy(17, 22);printf("Space:Hard drop");
	gotoxy(17, 23);printf("ESC:Quit");
	textcolor(MAGENTA2, WHITE);
	gotoxy(45, 24);printf("KJY");


	if (_getch())return 1;
}
void howtogame() {//���ӹ��ȭ��
	textcolor(GREEN2, WHITE);
	gotoxy(33, 9);printf("��:Rotation");
	gotoxy(33, 10);printf("��:Fast drop");
	gotoxy(33, 11);printf("����:Left/Right");
	gotoxy(33, 12);printf("Space:Hard drop");
	gotoxy(33, 13);printf("ESC:Quit");


}
int map[MAPHEIGHT][MAPWIDTH] = {//��Ʈ���� �� ǥ��


	{1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int Blocks[7][4][4][4] =//��ϵ� ����
{
	{
		{
			{0,0,0,0},
			{0,1,1,1},
			{0,0,1,0},
			{0,0,0,0}
		},

		{
			{0,1,0,0},
			{0,1,1,0},
			{0,1,0,0},
			{0,0,0,0}
		},

		{
			{0,0,1,0},
			{0,1,1,1},
			{0,0,0,0},
			{0,0,0,0}
		},

		{
			{0,0,1,0},
			{0,1,1,0},
			{0,0,1,0},
			{0,0,0,0}
		},
	},//��

	{
		{
			{0,0,0,0},
			{0,1,1,1},
			{0,0,0,1},
			{0,0,0,0}
		},

		{
			{0,0,0,0},
			{0,1,1,0},
			{0,1,0,0},
			{0,1,0,0}
		},

		{
			{0,0,0,0},
			{0,1,0,0},
			{0,1,1,1},
			{0,0,0,0}
		},

		{
			{0,0,1,0},
			{0,0,1,0},
			{0,1,1,0},
			{0,0,0,0}
		},
	},//��

	{
		{
			{0,0,0,0},
			{1,1,0,0},
			{0,1,1,0},
			{0,0,0,0}
		},

		{
			{0,0,0,0},
			{0,0,1,0},
			{0,1,1,0},
			{0,1,0,0}
		},

		{
			{0,0,0,0},
			{1,1,0,0},
			{0,1,1,0},
			{0,0,0,0}
		},

		{
			{0,0,0,0},
			{0,0,1,0},
			{0,1,1,0},
			{0,1,0,0}
		},
	},//��

	{
		{
			{0,0,0,0},
			{0,1,1,0},
			{0,1,1,0},
			{0,0,0,0}
		},

		{
			{0,0,0,0},
			{0,1,1,0},
			{0,1,1,0},
			{0,0,0,0}
		},

		{
			{0,0,0,0},
			{0,1,1,0},
			{0,1,1,0},
			{0,0,0,0}
		},

		{
			{0,0,0,0},
			{0,1,1,0},
			{0,1,1,0},
			{0,0,0,0}
		},
	},//��

	{
		{
			{0,0,0,0},
			{0,1,1,1},
			{0,1,0,0},
			{0,0,0,0}
		},

		{
			{0,0,0,0},
			{0,1,0,0},
			{0,1,0,0},
			{0,1,1,0}
		},

		{
			{0,0,0,0},
			{0,0,0,1},
			{0,1,1,1},
			{0,0,0,0}
		},

		{
			{0,0,0,0},
			{0,1,1,0},
			{0,0,1,0},
			{0,0,1,0}
		},
	},//��

	{
		{
			{0,0,0,0},
			{0,0,0,0},
			{1,1,1,1},
			{0,0,0,0}
		},

		{
			{0,1,0,0},
			{0,1,0,0},
			{0,1,0,0},
			{0,1,0,0}
		},

		{
			{0,0,0,0},
			{0,0,0,0},
			{1,1,1,1},
			{0,0,0,0}
		},

		{
			{0,1,0,0},
			{0,1,0,0},
			{0,1,0,0},
			{0,1,0,0}
		},
	},//��

	{
		{
			{0,0,0,0},
			{0,0,1,1},
			{0,1,1,0},
			{0,0,0,0}
		},

		{
			{0,0,0,0},
			{0,1,0,0},
			{0,1,1,0},
			{0,0,1,0}
		},

		{
			{0,0,0,0},
			{0,0,1,1},
			{0,1,1,0},
			{0,0,0,0}
		},

		{
			{0,0,0,0},
			{0,1,0,0},
			{0,1,1,0},
			{0,0,1,0}
		},
	}//���ݴ�
};


void Map()//��Ʈ����Ʋȭ��
{
	textcolor(CYAN1, WHITE);
	int i = 0;
	int j = 0;

	for (i = 0; i < MAPHEIGHT; i++)
	{
		for (j = 0; j < MAPWIDTH; j++)
		{
			if (map[i][j] == 1)
			{
				gotoxy(j * 2, i);
				printf("��");
			}
		}
		printf("\n");
	}
}


void RandOutput()//�������
{
	int i = 0;
	int j = 0;

	T.x = 6;
	T.y = 0;

	gotoxy(T.x, T.y);

	srand(time(NULL));
	T.randBlocks = rand() % 7;


	for (i = 0; i < 4; i++)
	{
		gotoxy(T.x, T.y + i);
		for (j = 0; j < 4; j++)
		{
			if (Blocks[T.randBlocks][T.rotation][i][j] == 1)
				printf("��");
			else
				printf("  ");
		}
		printf("\n");
	}
}

void Delete()//��� �����
{
	int i = 0;
	int j = 0;

	gotoxy(T.x, T.y);

	for (i = 0; i < 4; i++)
	{
		gotoxy(T.x, T.y + i);
		for (j = 0; j < 4; j++)
			printf("  ");
		printf("\n");
	}


	for (i = 0; i < 4; i++)
	{
		gotoxy(S.ShadowX, S.ShadowY + i);
		for (j = 0; j < 4; j++)
			printf("  ");
		printf("\n");
	}
}

void Move()//��� �� ������ 
{
	bool exitOuterLoop = false;

	int i = 0;
	int j = 0;

	for (i = 0; i < 4; i++)        //������ �� �������
	{
		for (j = 0; j < 4; j++)
		{
			if (Blocks[T.randBlocks][T.rotation][i][j] == 1)
			{
				if (T.Right == true && map[T.y + i][T.x / 2 + j] == 1)
				{
					T.x = T.x - 2;
					T.Right = false;
					exitOuterLoop = true;
					break;
				}
			}
		}
		if (exitOuterLoop == true)
		{
			exitOuterLoop = false;
			break;
		}
	}

	for (i = 0; i < 4; i++)        ////���� �� �������
	{
		for (j = 0; j < 4; j++)
		{
			if (Blocks[T.randBlocks][T.rotation][i][j] == 1)
			{
				if (T.Left == true && map[T.y + i][T.x / 2 + j] == 1)
				{
					T.x = T.x + 2;
					T.Left = false;
					exitOuterLoop = true;
					break;
				}
			}
		}
		if (exitOuterLoop == true)
		{
			exitOuterLoop = false;
			break;
		}
	}

	for (i = 0; i < 4; i++)        //�Ʒ��� �� �������
	{
		for (j = 0; j < 4; j++)
		{
			if (Blocks[T.randBlocks][T.rotation][i][j] == 1)
			{
				if (map[T.y + i + 1][T.x / 2 + j] == 1)
				{
					T.save = true;
					Save();
					break;
				}
			}
		}

		if (exitOuterLoop == true)
		{
			exitOuterLoop = false;
			break;
		}
	}

	T.Left = 0;
	T.Right = 0;

	Waiting();
	Shadow();

	Output();
	Map();
}

void Save()//����
{
	int i = 0;
	int j = 0;

	if (T.save == true)
	{
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				map[T.y + i][T.x / 2 + j] += Blocks[T.randBlocks][T.rotation][i][j];
			}
		}
		LineCheck();
		system("cls");
		RandOutput();
		Score();
		T.save = false;
	}

	GameOver();
}

void TimeDown()//�ð��� ���������� Down
{
	int Millisecond = 500;

	if (T.score > 500)
		Millisecond = 400;

	else if (T.score > 1000)
		Millisecond = 300;

	else if (T.score > 2000)
		Millisecond = 200;

	CurTime = clock();
	if (CurTime - OldTime > Millisecond)
	{
		Delete();
		T.y++;
		Move();
		OldTime = CurTime;
	}
}


void LineCheck()//��� �� üũ
{
	int i = 0;
	int j = 0;

	int Line = 0;
	int Vertical = 0;

	for (i = 0; i < 24; i++)
	{
		for (j = 1; j <= 11; j++)
		{
			if (map[i][j] == 1)
				Line += 1;

			if (Line == 11)
			{
				Vertical = i;
				LineRemove(Vertical);
				LineDown(Vertical);
				T.score += 100;
			}
		}
		Line = 0;
	}
}

void LineRemove(int vertical)//��� �� ���ֱ�
{
	int Remove;
	for (Remove = 1; Remove <= 8; Remove++)
		map[vertical][Remove] = 0;
}

void LineDown(int vertical)//��� �ٿ�
{
	int LinePlus;
	while (vertical > 0)
	{
		for (LinePlus = 1; LinePlus <= 8; LinePlus++)
		{
			map[vertical][LinePlus] += map[vertical - 1][LinePlus];
			map[vertical - 1][LinePlus] = 0;
		}
		vertical--;
	}
}

void Rotation()//��� ȸ��
{
	bool exitOuterLoop = false;

	int i = 0;
	int j = 0;
	int X = T.x;

	T.rotation = T.rotation + 1;

	if (T.rotation == 4)
		T.rotation = 0;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (Blocks[T.randBlocks][T.rotation][i][j] == 1)
			{
				if (j > 1 && map[T.y + i][T.x / 2 + j] == 1)
					T.x = T.x - 2;
				else if (j <= 1 && map[T.y + i][T.x / 2 + j] == 1)
					T.x = T.x + 2;
				else {}
			}
		}
	}

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (Blocks[T.randBlocks][T.rotation][i][j] == 1)
			{
				if (map[T.y + i][T.x / 2 + j] == 1)
				{
					T.x = X;
					if (T.rotation > 0)
					{
						T.rotation = T.rotation - 1;
						exitOuterLoop = true;
						break;
					}
					if (T.rotation == 0)
					{
						T.rotation = 3;
						exitOuterLoop = true;
						break;
					}
				}
			}
		}
		if (exitOuterLoop == true)
		{
			exitOuterLoop = false;
			break;
		}
	}
}

void QuickDown() //�ѹ��� �ٿ� 
{
	int i = 0;
	int j = 0;

	int VerticalLine = 0;
	int VerticalLine2 = 20;
	int distance = 0;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (Blocks[T.randBlocks][T.rotation][i][j] == 1)
			{
				for (VerticalLine = 0; VerticalLine <= 19; VerticalLine++)
				{
					if (map[T.y + VerticalLine + i][T.x / 2 + j] == 1)
					{
						if (VerticalLine2 >= VerticalLine)
							VerticalLine2 = VerticalLine;
						distance = VerticalLine2 - 1;
					}
				}
			}
		}
	}

	T.y = T.y + distance;
}

void GameOver()//��������
{
	int i = 0;
	int j = 0;

	for (i = 0; i < 4; i++)
	{
		for (j = 3; j < 7; j++)
		{
			if (map[i][j] == 1)
			{

				system("cls");
				textcolor(RED2, WHITE);
				gotoxy(20, 15);
				
				Score();
				system("pause>null");
				system("pause");
				
			}
		}
	}

}

void Output()//������ϻ���
{
	int i = 0;
	int j = 0;

	gotoxy(T.x, T.y);

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			gotoxy(T.x + j * 2, T.y + i);
			if (Blocks[T.randBlocks][T.rotation][i][j] == 1)
				printf("��");
		}
		printf("\n");
	}
}


void Score()//����ǥ��
{

	gotoxy(33, 15);
	printf("SCORE: %d", T.score);
}

void Shadow()//��� �׸���
{

	bool ShadowExitOuterLoop = false;

	int i = 0;
	int j = 0;

	S.ShadowX = T.x;

	int VerticalLine = 0;
	int VerticalLine2 = 20;
	int distance = 0;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (Blocks[T.randBlocks][T.rotation][i][j] == 1)
			{
				for (VerticalLine = 0; VerticalLine <= 19; VerticalLine++)
				{
					if (map[T.y + VerticalLine + i][T.x / 2 + j] == 1)
					{
						if (VerticalLine2 >= VerticalLine)
							VerticalLine2 = VerticalLine;
						distance = VerticalLine2 - 1;
					}
				}
			}
		}
	}

	S.ShadowY = T.y + distance;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (Blocks[T.randBlocks][T.rotation][i][j] == 1)
			{
				if (T.Right == 1 && map[T.y + i][T.x / 2 + j] == 1)
				{
					S.ShadowX = T.x - 2;
					T.Right = 0;
					S.ShadowY = T.y + distance;
					ShadowExitOuterLoop = true;
					break;
				}
			}
		}
		if (ShadowExitOuterLoop == true)
		{
			ShadowExitOuterLoop = false;
			break;
		}
	}
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (Blocks[T.randBlocks][T.rotation][i][j] == 1)
			{
				if (T.Left == 1 && map[T.y + i][T.x / 2 + j] == 1)
				{
					S.ShadowX = T.x + 2;
					T.Left = 0;
					S.ShadowY = T.y + distance;
					ShadowExitOuterLoop = true;
					break;
				}
			}
		}
		if (ShadowExitOuterLoop == true)
		{
			ShadowExitOuterLoop = false;
			break;
		}
	}
	ShadowOutput();
}

void ShadowOutput()//��� �׸��� ����
{
	textcolor(CYAN1, WHITE);
	int i = 0;
	int j = 0;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			gotoxy(S.ShadowX + j * 2, S.ShadowY + i);
			if (Blocks[T.randBlocks][T.rotation][i][j] == 1)
				printf("��");
		}
		printf("\n");
	}
	Map();
}




void Waiting()    //�����Ÿ��°� ����
{
	while (1)
	{
		WaitCurTime = clock();
		if (WaitCurTime - WaitOldTime > 33)
		{
			WaitOldTime = WaitCurTime;
			break;
		}
	}
}

int main()
{
	system("mode con: cols=52 lines=26");
	int key;
	CursorView(0);
	startgame();
	system("cls");


	OldTime = clock();

	Map();
	RandOutput();

	while (1)
	{

		Score();
		howtogame();
		TimeDown();


		if (_kbhit())
		{
			key = _getch();
			switch (key)
			{
			case DOWN:
				Delete();
				T.y++;
				Move();
				break;
			case LEFT:
				T.Left = true;
				Delete();
				T.x = T.x - 2;
				Move();
				break;
			case RIGHT:
				T.Right = true;
				Delete();
				T.x = T.x + 2;
				Move();
				break;
			case ESCAPE:
				textcolor(RED2, WHITE);
				gotoxy(34, 5);
				printf("GAMEOVER");
				system("pause>null");
				exit(0);
				break;
			case SPACE:
				Delete();
				QuickDown();
				Move();
				break;
			case UP:
				Delete();
				Rotation();
				Move();
				break;
			default:
				break;
			}
		}
	}
	return 0;
}
void gotoxy(int x, int y)
{
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void CursorView(char show)//Ŀ�������
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}


