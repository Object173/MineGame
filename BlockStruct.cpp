#include "BlockStruct.h"
#include<stdlib.h>

//конструктор
Block::Block(int x, int y, int s, int id, Block *UP)
{
	x0 = x;
	y0 = y;
	size = s;
	idBlock = id;

	for (int i = 0; i < 4; i++)
		down[i] = NULL;

	up = UP;
}

//деструктор
Block::~Block()
{
	for (int i = 0; i < 4; i++)
	if (down[i] != NULL) delete down[i];
}