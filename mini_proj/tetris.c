#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/time.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <time.h>

/* Ÿ�̸�  */
#define CCHAR 0
#ifdef CTIME
#undef CTIME
#endif
#define CTIME 1

/* ����Ű, ȸ��Ű ����*/
#define LEFT 0
#define RIGHT 1
#define DOWN 2
#define ROTATE 3

/* ��Ʈ�� �̳� ���ϳѹ� ����*/
#define I_BLOCK 0
#define	T_BLOCK 1
#define S_BLOCK 2
#define Z_BLOCK 3
#define L_BLOCK 4
#define J_BLOCK 5
#define O_BLOCK 6

#define GAME_START 0
#define GAME_END 1

char i_block[4][4][4] = {
        1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0,
        0, 0 };

char t_block[4][4][4] = {
        1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0,
        0, 0 };

char s_block[4][4][4] = {
        1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0,
        0, 0 };

char z_block[4][4][4] = {
        0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0,
        0, 0 };

char l_block[4][4][4] = {
        1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0,
        0, 0 };

char j_block[4][4][4] = {
        0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
        0, 0 };

char o_block[4][4][4] = {
        1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, };

char tetris_table[21][10];

static struct result
{
	char name[30];
	long point;
	int year;
	int month;
	int day;
	int hour;
	int min;
	int rank;
} temp_result;

int block_number = 0;
int next_block_number = 0;
int block_state = 0;
int x = 3, y = 0;
int game = GAME_END;
int best_point = 0;
long point = 0;

int display_menu(void);
int init_tetris_table(void);
int display_tetris_table(void);
int game_start(void);
int refresh(int);
int move_block(int);
int drop(void);
int collision_test(int);
int check_one_line(void);
int print_result(void);
int search_result(void);
int getch(void);

int main(void)
{
	int menu = 1;

	while(menu) {
		menu = display_menu();

		if (menu == 1) {
			game = GAME_START;
			menu = game_start();
		} else if (menu == 2) {
			search_result();
		} else if (menu == 3) {
			print_result();
		} else if (menu == 4) {
			exit(0);
		}
	}

	return 0;
}

int display_menu(void)
{
	int menu = 0;

	while(1) {
		system("clear");
		printf("\n\n\t\t\t\tText Tetris");
		printf("\n\t\t\t============================");
		printf("\n\t\t\t\tGAME MENU\t\n");
		printf("\n\t\t\t============================");
		printf("\n\t\t\t   1) Game Start");
		printf("\n\t\t\t   2) Search history");
		printf("\n\t\t\t   3) Record Output");
		printf("\n\t\t\t   4) QUIT");
		printf("\n\t\t\t============================");
		printf("\n\t\t\t\t\t SELECT : ");
		scanf("%d", &menu);
		if (menu < 1 || menu > 4) {
			continue;
		} else {
			return menu;
		}
	}
	return 0;
}

int game_start(void)
{
	static struct sigaction sa;
	static struct itimerval timer;
	time_t ptime;
	struct tm *t;
	FILE *fp = NULL;

	if (game == GAME_START) {
		init_tetris_table();

		/* Install timer_handler as the signal handler for SIGVTALRM. */
		memset(&sa, 0, sizeof(sa));
		sa.sa_handler = &refresh;
		sigaction(SIGVTALRM, &sa, NULL);

		/* Configure the timer to expire after 250 msec... */
		timer.it_value.tv_sec = 0;
		timer.it_value.tv_usec = 1;

		/* ... and every 250 msec after that. */
		timer.it_interval.tv_sec = 0;
		timer.it_interval.tv_usec = 1;

		/* Start a virtual timer. It counts down whenever this process is executing. */
		setitimer(ITIMER_VIRTUAL, &timer, NULL);

		/* Do busy work.  */

		while(1) {
			if (game == GAME_END) {

				timer.it_value.tv_sec = 0;
				timer.it_value.tv_usec = 0;
				timer.it_interval.tv_sec = 0;
				timer.it_interval.tv_usec = 0;
				setitimer(ITIMER_VIRTUAL, &timer, NULL);

				printf("\n\n Final score : %ld ", point);
				printf("\n\n Please enter your name : ");
				scanf("%s%*c", temp_result.name);
				temp_result.point = point;

				if (temp_result.point >= best_point)
					best_point = temp_result.point;

				ptime = time(NULL);
				t = localtime(&ptime);

				temp_result.year = t->tm_year + 1900;
				temp_result.month = t->tm_mon + 1;
				temp_result.day = t->tm_mday;
				temp_result.hour = t->tm_hour;
				temp_result.min = t->tm_min;

				fp = fopen("result", "ab");
				fseek(fp, 1, SEEK_END);
				fwrite(&temp_result, sizeof(struct result), 1, fp);
				fclose(fp);

				x = 3, y = 0;
				point = 0;

				return 1;
			}
		}
	}

	return 0;
}

/* ������ ��Ʈ�������� �����ش�. ������ ���̰� ���� ���� ���¸� ������*/
int display_tetris_table(void)
{
	int i, j;
	char (*block_pointer)[4][4][4] = NULL;

	switch(next_block_number)
	{
		case I_BLOCK:
			block_pointer = &i_block;
			break;
		case T_BLOCK:
			block_pointer = &t_block;
			break;
		case S_BLOCK:
			block_pointer = &s_block;
			break;
		case Z_BLOCK:
			block_pointer = &z_block;
			break;
		case L_BLOCK:
			block_pointer = &l_block;
			break;
		case J_BLOCK:
			block_pointer = &j_block;
			break;
		case O_BLOCK:
			block_pointer = &o_block;
			break;
	}

	system("clear");

	printf("\n\n Next Block\n");

	for (i = 0; i < 4; i++) {
		printf("\n ");
		for (j = 0; j < 4; j++) {
			if ((*block_pointer)[0][i][j] == 1)
				printf("#");
			else if ((*block_pointer)[0][i][j] == 0)
				printf(" ");
		}
	}

	for (i = 2; i < 21; i++) {
		printf("\t");
		for (j = 0; j < 10; j++) {
			if (j == 0 || j == 9 || (i == 20 && (j > 1 || j < 9))) {
				printf("@");
			} else if (tetris_table[i][j] == 1)
				printf("#");
			else if (tetris_table[i][j] == 0)
				printf(" ");
		}
		printf("\n");
	}

	return 0;
}

int init_tetris_table(void)
{
	int i = 0, j = 0;

	for (i = 0; i < 20; i++)
//		전체 타일을 0으로
		for (j = 1; j < 9; j++)
			tetris_table[i][j] = 0;
//양쪽 기둥 타일만 1
	for (i = 0; i < 21; i++) {
		tetris_table[i][0] = 1;
		tetris_table[i][9] = 1;
	}
//바닥 타일만 1
	for (j = 1; j < 9; j++)
		tetris_table[20][j] = 1;

	return 0;
}

int getch(void)
{
	char ch;
	int error;
	static struct termios Otty, Ntty;

	fflush(stdout);
	tcgetattr(0, &Otty);
	Ntty = Otty;
	Ntty.c_iflag = 0;
	Ntty.c_oflag = 0;
	Ntty.c_lflag &= ~ICANON;
#if 1
	Ntty.c_lflag &= ~ECHO;
#else
            Ntty.c_lflag |=  ECHO;
#endif
	Ntty.c_cc[VMIN] = CCHAR;
	Ntty.c_cc[VTIME] = CTIME;

#if 1
#define FLAG TCSAFLUSH
#else
#define FLAG TCSANOW
#endif

	if (0 == (error = tcsetattr(0, FLAG, &Ntty))) {
		error = read(0, &ch, 1);
		error += tcsetattr(0, FLAG, &Otty);
	}

	return (error == 1 ? (int) ch : -1);
}

int refresh(int signum)
{
	static int downcount = 0;
	static int setcount = 0;
	static long speedcount = 0;
	static int countrange = 5;
	static int firststart = 0;

	char ch;

	srand((unsigned) time(NULL));

	if (firststart == 0) {
		block_number = rand() % 7;
		if (firststart == 0)
			firststart++;
	}

	printf("\n Score: %ld | Speed: %d | hihgest score: %d", point, countrange, best_point);

	display_tetris_table();
	check_one_line();

	printf("\n GAME STOP : P");

	if (downcount == countrange - 1) {
		point += 1;
		move_block(DOWN);
	}

	if (speedcount == 499) {
		if (countrange != 1)
			countrange--;
	}

	downcount++;
	downcount %= countrange;
	speedcount++;
	speedcount %= 500;

	if (x == 3 && y == 0) {
		if (collision_test(LEFT) || collision_test(RIGHT) || collision_test(DOWN)
		            || collision_test(ROTATE)) {
			printf("\n Game End! \n");
			downcount = 0;
			setcount = 0;
			speedcount = 0;
			countrange = 5;
			firststart = 0;
			game = GAME_END;
		}
	}

	if (collision_test(DOWN)) {
		if (setcount == 9) {
			block_number = next_block_number;
			next_block_number = rand() % 7;
			block_state = 0;
			x = 3;
			y = 0;
		}
		setcount++;
		setcount %= 10;
	}

	ch = getch();

	switch(ch)
	{
		case 74:
		case 106:
			move_block(LEFT);
			break;
		case 76:
		case 108:
			move_block(RIGHT);
			break;
		case 75:
		case 107:
			move_block(DOWN);
			break;
		case 73:
		case 105:
			move_block(ROTATE);
			break;
		case 65:
		case 97:
			drop();
			break;
		case 80:
		case 112:
			downcount = 0;
			setcount = 0;
			speedcount = 0;
			countrange = 5;
			firststart = 0;
			game = GAME_END;
			break;
		default:
			break;
	}
	return 0;
}

int move_block(int command)
{
	int i, j;
	int newx, newy;
	int oldx, oldy;
	int old_block_state;
	char (*block_pointer)[4][4][4] = NULL;

	newx = x;
	newy = y;

	old_block_state = block_state;

	if (collision_test(command) == 0) {
		switch(command)
		{
			case LEFT:
				newx--;
				break;
			case RIGHT:
				newx++;
				break;
			case DOWN:
				newy++;
				break;
			case ROTATE:
				block_state++;
				block_state %= 4;
				break;
		}
	} else {
		return 1;
	}

	switch(block_number)
	{
		case I_BLOCK:
			block_pointer = &i_block;
			break;
		case T_BLOCK:
			block_pointer = &t_block;
			break;
		case S_BLOCK:
			block_pointer = &s_block;
			break;
		case Z_BLOCK:
			block_pointer = &z_block;
			break;
		case L_BLOCK:
			block_pointer = &l_block;
			break;
		case J_BLOCK:
			block_pointer = &j_block;
			break;
		case O_BLOCK:
			block_pointer = &o_block;
			break;
	}

	for (i = 0, oldy = y; i < 4; i++, oldy++) {
		for (j = 0, oldx = x; j < 4; j++, oldx++) {
			if (oldx > 0 && oldx < 9 && oldy < 20 && oldy > 0)
				if ((*block_pointer)[old_block_state][i][j] == 1)
					tetris_table[oldy][oldx] = 0;

		}
	}

	x = newx;
	y = newy;

	for (i = 0, newy = y; i < 4; i++, newy++) {
		for (j = 0, newx = x; j < 4; j++, newx++) {
			if (newx > 0 && newx < 9 && newy < 20 && newy > 0)
				if ((*block_pointer)[block_state][i][j] == 1)
					tetris_table[newy][newx] = (*block_pointer)[block_state][i][j];
		}
	}

	return 0;
}

int collision_test(int command)
{
	int i, j;
	int tempx, tempy;
	int oldx, oldy;
	int temp_block_state;
	char (*block_pointer)[4][4][4];
	char temp_tetris_table[21][10];

	oldx = tempx = x;
	oldy = tempy = y;
	temp_block_state = block_state;

	switch(command)
	{
		case LEFT:
			tempx--;
			break;
		case RIGHT:
			tempx++;
			break;
		case DOWN:
			tempy++;
			break;
		case ROTATE:
			temp_block_state++;
			temp_block_state %= 4;
			break;
	}

	switch(block_number)
	{
		case I_BLOCK:
			block_pointer = &i_block;
			break;
		case T_BLOCK:
			block_pointer = &t_block;
			break;
		case S_BLOCK:
			block_pointer = &s_block;
			break;
		case Z_BLOCK:
			block_pointer = &z_block;
			break;
		case L_BLOCK:
			block_pointer = &l_block;
			break;
		case J_BLOCK:
			block_pointer = &j_block;
			break;
		case O_BLOCK:
			block_pointer = &o_block;
			break;
	}

	for (i = 0; i < 21; i++) {
		for (j = 0; j < 10; j++) {
			temp_tetris_table[i][j] = tetris_table[i][j];
		}
	}

	for (i = 0, oldy = y; i < 4; i++, oldy++) {
		for (j = 0, oldx = x; j < 4; j++, oldx++) {
			if (oldx > 0 && oldx < 9 && oldy < 20 && oldy > 0) {
				if ((*block_pointer)[block_state][i][j] == 1)
					temp_tetris_table[oldy][oldx] = 0;
			}
		}
	}

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {

			if (temp_tetris_table[tempy + i][tempx + j] == 1
			            && (*block_pointer)[temp_block_state][i][j] == 1)
				return 1;
		}
	}

	return 0;
}

int drop(void)
{
	while(!collision_test(DOWN))
		move_block(DOWN);

	return 0;
}

int check_one_line(void)
{
	int i, j;
	int ti, tj;
	int line_hole;

	for (i = 19; i > 0; i--) {
		line_hole = 0;
		for (j = 1; j < 9; j++) {
			if (tetris_table[i][j] == 0) {
				line_hole = 1;
			}
		}

		if (line_hole == 0) {
			point += 1000;
			for (ti = i; ti > 0; ti--) {
				for (tj = 0; tj < 9; tj++) {
					tetris_table[ti][tj] = tetris_table[ti - 1][tj];
				}
			}
		}
	}

	return 0;
}

int search_result(void)
{
	FILE *fp = NULL;
	char name[30];
	char ch;
	int find = 0;

	fp = fopen("result", "rb");

	if (fp == NULL)
		return 0;

	system("clear");

	printf("\n\n\t\tEnter the name your to search.  : ");
	scanf("%s%*c", name);

	printf("\n\t\t\t\tText Tetris");
	printf("\n\t\t\t\t Game Stats\n\n");
	printf("\n\t\tName\t\tScore\t   Date\t\t Time");

	while(1) {
		fread(&temp_result, sizeof(struct result), 1, fp);
		if (!feof(fp)) {
			if (!strcmp(temp_result.name, name)) {
				find = 1;
				printf("\n\t========================================================");
				printf("\n\t\t%s\n\t\t\t\t%ld\t%d.%d.%d.  |  %d:%d\n", temp_result.name,
				            temp_result.point, temp_result.year, temp_result.month, temp_result.day,
				            temp_result.hour, temp_result.min);
			}
		} else {
			break;
		}
	}

	if (find == 0)
		printf("\n\n\n\t\tThis name is not found.");

	printf("\n\n\n\t\tBack to the game menu : M");
	while(1) {
		ch = getch();
		if (ch == 77 || ch == 109)
			break;
	}

	return 0;
}

/* �޴����� �����½� ȣ��Ǿ� ����� ����ϴ� �Լ�*/
int print_result(void)
{
	FILE *fp = NULL;
	char ch = 1;

	fp = fopen("result", "rb");

	if (fp == NULL)
		return 0;

	system("clear");

	printf("\n\t\t\t\tText Tetris");
	printf("\n\t\t\t\t Game Stats\n\n");
	printf("\n\t\tName\t\tScore\t   Date\t\t Time");

	while(1) {
		fread(&temp_result, sizeof(struct result), 1, fp);
		if (!feof(fp)) {
			printf("\n\t========================================================");
			printf("\n\t\t%s\n\t\t\t\t%ld\t %d.%d.%d.  |  %d:%d\n", temp_result.name,
			            temp_result.point, temp_result.year, temp_result.month, temp_result.day,
			            temp_result.hour, temp_result.min);
		} else {
			break;
		}
	}

	fclose(fp);

	printf("\n\n\tBack to the game menu : M");
	while(1) {
		ch = getch();
		if (ch == 77 || ch == 109)
			break;
	}
	return 0;

}
