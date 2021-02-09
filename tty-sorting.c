#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <ddcPrint.h>

#define SCREEN_BOTTOM 30
#define SCREEN_WIDTH 40

typedef char bool;
#define true 1
#define false 0

const int colors[][3] = { { 0, 0, 0 }, { 255, 0, 0 }, { 0, 255, 0 }, { 0, 0, 255 }, { 255, 255, 0 }, { 0, 255, 255 }, { 255, 0, 255 }, 
                          { 255, 255, 255 }, { 100, 100, 100 }, { 150, 40, 200 }, { 100, 30, 220 }, { 255, 50, 50 }, { 100, 255, 30 }, 
			  { 20, 90, 20 },
			  { 150, 100, 30 }, { 200, 200, 0 }, { 150, 100, 200 }, { 255, 20, 20 }, { 20, 255, 20 }, { 0, 120, 0 } };

void cur_clear(void)
{
	 ddPrintf("\x1b[60;60H\x1b[1J\x1b[0;0H");
}
void cur_reset(void)
{
	 ddPrintf("\x1b[1;1H");
}
void cur_bgoto(int pos)
{
	pos++;
	ddPrintf("\x1b[%d;%dH", SCREEN_BOTTOM+1, pos+1);
}
void cur_goto(int x, int y)
{
	ddPrintf("\x1b[%d;%dH", y+1, x+1);
}

void draw_bottom(void)
{
	ddPrintf("\x1b[%d;%dH", SCREEN_BOTTOM+2, 0);
	for (int i = 0; i < SCREEN_WIDTH; i++)
		ddPrintf("=");
}

void draw_rod(int pos, int len, char chr)
{
	cur_goto(0, 30-pos);
	for (int i = 0; i < len; i++)
	{
		ddPrintf("%c", chr);
	}
}

void draw_bar(int pos, int height, char chr, int r, int g, int b)
{
	cur_bgoto(pos);
	for (int i = 0; i < height; i++)
	{
		ddPrintf("\x1b[38;2;%d;%d;%dm%c\x1b[A\x1b[D", r, g, b, chr);
	}
}

void draw_array(const int* array, int len, int s1, int s2)
{
	cur_clear();
	for (int i = 0; i < len; i++)
		draw_bar(i, array[i], '|', colors[array[i]][0], colors[array[i]][1], colors[array[i]][2]);
	draw_bar(s1, array[s1], '@', colors[array[s1]][0], colors[array[s1]][1], colors[array[s1]][2]);
	draw_bar(s2, array[s2], '@', colors[array[s2]][0], colors[array[s2]][1], colors[array[s2]][2]);
	cur_reset();
}

void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

long delay = 10000;

void spaghettisort(int* array, int len)
{
	int rodpos = 20;
	int rodlen = len;
	draw_rod(rodpos, rodlen, '=');
	while (rodlen > 0)
	{
		for (int i = rodlen-1; i >= 0; i--)
		{
			if (rodpos == array[i])
			{
				draw_rod(rodpos, rodlen, '=');
				usleep(delay);
				draw_array(array, len, i, rodlen-1);
				swap(&(array[i]), &(array[--rodlen]));
				usleep(delay);
				draw_array(array, len, i, rodlen);
			}
		}
		rodpos--;
	}
}

void combsort(int* array, int len)
{
	static const float shrink = 1.3;
	float fgap = len;
	int gap = (int)fgap;
	bool swaped = true;
	while (!(swaped && gap == 1))
	{
		swaped = false;
		fgap /= shrink;
		gap = (int)fgap;
		if (gap < 1) gap = 1;
		for (int i = 0; i < len - gap; i++)
		{
			int j = gap + i;
			usleep(delay);
			draw_array(array, len, i, j);
			if (array[i] > array[j])
			{
				swap(&(array[i]), &(array[j]));
				swaped = true;
			}
			usleep(delay);
			draw_array(array, len, i, j);
		}
		
	}
}

void gnomesort(int* array, int len)
{
	int pos = 0;
	while (pos < len)
	{
		usleep(delay);
		if (pos != 0) draw_array(array, len, pos, pos-1);
		else draw_array(array, len, pos, pos);
		if (pos == 0 || array[pos] >= array[pos-1])
		{
			pos++;
		}
		else
		{
			swap(&(array[pos-1]), &(array[pos]));
			pos--;
		}
		if (pos == len) return;
		usleep(delay);
		if (pos != 0) draw_array(array, len, pos, pos-1);
		else draw_array(array, len, pos, pos);
	}
}
void bdbublesort(int* array, int len)
{
	bool swaped = true;
	while (swaped == true)
	{
		for (int i = 1; i < len; i++)
		{
			usleep(delay);
			draw_array(array, len, i, i-1);
			if (array[i-1] > array[i])
			{
				swap(&(array[i-1]), &(array[i]));
				swaped = true;
			}
			usleep(delay);
			draw_array(array, len, i, i-1);
		}
		swaped = false;
		for (int i = len-1; i >= 1; i--)
		{
			usleep(delay);
			draw_array(array, len, i, i-1);
			if (array[i-1] > array[i])
			{
				swap(&(array[i-1]), &(array[i]));
				swaped = true;
			}
			usleep(delay);
			draw_array(array, len, i, i-1);
		}
	}
}
void bublesort(int* array, int len)
{
	bool swaped = true;
	while (swaped == true)
	{
		swaped = false;
		for (int i = 1; i < len; i++)
		{
			usleep(delay);
			draw_array(array, len, i, i-1);
			if (array[i-1] > array[i])
			{
				swap(&(array[i-1]), &(array[i]));
				swaped = true;
			}
			usleep(delay);
			draw_array(array, len, i, i-1);
		}
	}
}

int main(void)
{
	srand(time(null));
	cur_clear();
	int array[50];
	
	for (int i = 0; i < 50; i++)
	{
		array[i] = 1 + (rand() % 19);
	}
	bdbublesort(array, 50);

	for (int i = 0; i < 50; i++)
	{
		array[i] = 1 + (rand() % 19);
	}
	bublesort(array, 50);

	for (int i = 0; i < 50; i++)
	{
		array[i] = 1 + (rand() % 19);
	}
	combsort(array, 50);

	for (int i = 0; i < 50; i++)
	{
		array[i] = 1 + (rand() % 19);
	}
	gnomesort(array, 50);

	for (int i = 0; i < 50; i++)
	{
		array[i] = 1 + (rand() % 19);
	}
	spaghettisort(array, 50);

	cur_reset();
	return 0;
}
