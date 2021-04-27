//very basic console snake game
//no gameover states are added
//no scoring system
//just the basic structure 

#include<iostream>
#include<windows.h>
#include<winuser.h>
#include<time.h>
#include<conio.h>
#define MAXSIZE 100

using namespace std;

void gotoxy(int , int);
void SetConsoleColor(WORD );
int type = 0;
	//different types for different parts
	//	1 -> head of the snake
	//	2 -> body of the snake
	//	3 -> apple :-D

// the point class
class Point{
private:
	int x,y;

public:
	Point()
	{
		x = 10;
		y = 10;
	}
	Point(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	void setPoint(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	void transferPosition(Point *p)
	{
		p->x = x;
		p->y = y;
	}
	void Draw()
	{
		gotoxy(x, y);
		if(type == 1)	//head
			cout<<"@";
		else if(type == 2)	//body
			cout<<"#";
		else if(type == 3)	//apple
			cout<<"O";
	}

	int GetX() { return x; }
	int GetY() { return y; }
	void MoveUP() { y--; }
	void MoveDown() { y++; }
	void MoveRight() { x++; }
	void MoveLeft() { x--; }	
};

class Snake{
private:
	Point *snake[MAXSIZE];	//array of Point
	int size;	//current size of the snake
	char direction;	// direction
	Point apple;	// food for snake
public:
	Snake()
	{
		//initialize snake
		size = 1;
		snake[0] = new Point(20, 20);
		for(int i=1;i<MAXSIZE;i++)
			snake[i] = NULL;

		//initialize food at random position
		apple.setPoint(rand()%50, rand()%28);
	}
	void AddSnakePart(int x, int y)
	{
		snake[size++] = new Point(x,y);
	}

	void TurnUp() { direction = 'w'; }
	void TurnDown() { direction = 's'; }
	void TurnRight() { direction = 'd'; }
	void TurnLeft() { direction = 'a'; }

	void Move()
	{
		system("cls");

		// this part makes the snake body follow the head movement
		for(int i=size-1;i>0;i--)
			snake[i-1]->transferPosition(snake[i]);
		
		// controlling head direction
		switch (direction)
		{
		case 'w':
			snake[0]->MoveUP();
			break;
		case 's':
			snake[0]->MoveDown();
			break;
		case 'd':
			snake[0]->MoveRight();
			break;
		case 'a':
			snake[0]->MoveLeft();
			break;
		}

		//checking the collision between snake head and food
		if(apple.GetX() == snake[0]->GetX() && apple.GetY() == snake[0]->GetY() )
		{
			//if collision then add a snake part and reposition the food
			AddSnakePart(0,0);
			apple.setPoint(rand()%50, rand()%28);
		}
			
		//drawing the snake
		for(int i=0;i<size;i++)
		{
			SetConsoleColor(11);
			type = 2;
			if(i == 0)
			{
				SetConsoleColor(6);
				type = 1;
			}
			snake[i]->Draw();
		}

		//drawing the food (apple)
		type = 3;
		SetConsoleColor(5);
		apple.Draw();
		
		if(direction == 'a' || direction == 'd')
			Sleep(80);
		else
			Sleep(100);
	}


};


int main()
{
	srand(time(NULL));
	Snake snake;
	char c = 'l';	//random initialize

	while(1)
	{
		if(kbhit())
			c = getch();
		
		switch (c)
		{
		case 'w':
			snake.TurnUp();
			break;
		case 's':
			snake.TurnDown();
			break;
		case 'd':
			snake.TurnRight();
			break;
		case 'a':
			snake.TurnLeft();
			break;
		}
		snake.Move();	//snake updates
	}
}

void gotoxy(int x, int y)
{
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;

	coord.X = x;
	coord.Y = y;

	SetConsoleCursorPosition(output, coord);
}

void SetConsoleColor(WORD color)
{
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(output, color);
}


