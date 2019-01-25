#include "BlockMapClass.h"
#include "Graphics.h"
#include<stdio.h>

//конструктор класса
BlockMap::BlockMap(int x, int y)
{
	x0 = x;
	y0 = y;
	mainBlock = new Block(0, 0, 0, 0, NULL);
}

//дуструктор класса
BlockMap::~BlockMap()
{
	delete mainBlock;
}

//добавление блока
void BlockMap::addBlock(int x, int y, int size, int id)
{
	Block *nb = mainBlock;

	if (size == minSize)
	{
		x = (minSize)*x;
		y = (minSize)*y;
	}

	if (nb->size==0)
	{
		nb->x0 = x;
		nb->y0 = y;
		nb->size = size;
		nb->idBlock = id;
		return;
	}

	while (x<nb->x0 - nb->size / 2 || x>nb->x0 + nb->size / 2 || y<nb->y0 - nb->size / 2 || y>nb->y0 + nb->size / 2)
	{
		if (nb->up == NULL)
		{
			if (x<nb->x0 + nb->size / 2 && y>nb->y0 + nb->size / 2)
			{
				Block *nUP = new Block(nb->x0 - nb->size / 2, nb->y0 + nb->size / 2, nb->size * 2, 0, NULL);
				nb->up = nUP;
				nUP->down[2] = nb;
				mainBlock = nUP;
			}
			else
			if (x>nb->x0 + nb->size / 2 && y>nb->y0 - nb->size / 2)
			{
				Block *nUP = new Block(nb->x0 + nb->size / 2, nb->y0 + nb->size / 2, nb->size * 2, 0, NULL);
				nb->up = nUP;
				nUP->down[3] = nb;
				mainBlock = nUP;
			}
			else
			if (x>nb->x0 - nb->size / 2 && y<nb->y0 - nb->size / 2)
			{
				Block *nUP = new Block(nb->x0 + nb->size / 2, nb->y0 - nb->size / 2, nb->size * 2, 0, NULL);
				nb->up = nUP;
				nUP->down[0] = nb;
				mainBlock = nUP;
			}
			else
			if (x<nb->x0 - nb->size / 2 && y<nb->y0 + nb->size / 2)
			{
				Block *nUP = new Block(nb->x0 - nb->size / 2, nb->y0 - nb->size / 2, nb->size * 2, 0, NULL);
				nb->up = nUP;
				nUP->down[1] = nb;
				mainBlock = nUP;
			}
		}
		nb = nb->up;
	}

	while (nb->size > size)
	{
		if (x<=nb->x0 && y>=nb->y0)
		{
			if (nb->down[0] == NULL) 
				nb->down[0] = new Block(nb->x0 - nb->size / 4, nb->y0 + nb->size / 4, nb->size / 2, 0, nb);
			nb = nb->down[0];
		}
		else
		if (x>=nb->x0 && y>=nb->y0)
		{
			if (nb->down[1] == NULL) 
				nb->down[1] = new Block(nb->x0 + nb->size / 4, nb->y0 + nb->size / 4, nb->size / 2, 0, nb);
			nb = nb->down[1];
		}
		else
		if (x>=nb->x0 && y<=nb->y0)
		{
			if (nb->down[2] == NULL) 
				nb->down[2] = new Block(nb->x0 + nb->size / 4, nb->y0 - nb->size / 4, nb->size / 2, 0, nb);
			nb = nb->down[2];
		}
		else
		if (x<=nb->x0 && y<=nb->y0)
		{
			if (nb->down[3] == NULL) 
				nb->down[3] = new Block(nb->x0 - nb->size / 4, nb->y0 - nb->size / 4, nb->size / 2, 0, nb);
			nb = nb->down[3];
		}
	}
	nb->size = size;
	nb->idBlock = id;

	if (nb->up!=NULL) groupBlock(nb->up);
}

//группировка блоков
void BlockMap::groupBlock(Block *block)
{

	if (block->down[0] == NULL)	return;
	if (block->down[0]->idBlock == 0) return;

	bool flag=true;
	for (int i = 1; i < 4;i++)
		if (block->down[i]==NULL || block->down[i]->idBlock != block->down[0]->idBlock)
			flag = false;

	if (flag)
	{
		block->idBlock = block->down[0]->idBlock;
		for (int i = 0; i < 4; i++)
		{
			delete block->down[i];
			block->down[i] = NULL;
		}

		if (block->up!=NULL)
			groupBlock(block->up);
	}	
}

//значение блока
int BlockMap::getBlock(int x, int y)
{
	Block *nb = mainBlock;

	x = (minSize)*x;
	y = (minSize)*y;

	while (nb->size > minSize)
	{
		if (nb->idBlock != 0) return nb->idBlock;

		if (x<nb->x0 && y>nb->y0)
		{
			if (nb->down[0] == NULL) return NULL;
			nb = nb->down[0];
		}
		else
		if (x>nb->x0 && y>nb->y0)
		{
			if (nb->down[1] == NULL) return NULL;
			nb = nb->down[1];
		}
		else
		if (x>nb->x0 && y<nb->y0)
		{
			if (nb->down[2] == NULL) return NULL;
			nb = nb->down[2];
		}
		else
		if (x<nb->x0 && y<nb->y0)
		{
			if (nb->down[3] == NULL) return NULL;
			nb = nb->down[3];
		}
	}
	if (nb->idBlock != 0) return nb->idBlock;
	return NULL;
}

//удаление блока
void BlockMap::delBlock(int x, int y)
{
	Block *nb = mainBlock;

	x = (minSize)*x;
	y = (minSize)*y;

	while (nb->size > minSize && nb->idBlock==0)
	{
		if (x<nb->x0 && y>nb->y0)
		{
			if (nb->down[0] == NULL) return;
			nb = nb->down[0];
		}
		else
		if (x>nb->x0 && y>nb->y0)
		{
			if (nb->down[1] == NULL) return;
			nb = nb->down[1];
		}
		else
		if (x>nb->x0 && y<nb->y0)
		{
			if (nb->down[2] == NULL) return;
			nb = nb->down[2];
		}
		else
		if (x<nb->x0 && y<nb->y0)
		{
			if (nb->down[3] == NULL) return;
			nb = nb->down[3];
		}
	}
	
	while (nb->size > minSize)
	{
		nb->down[0] = new Block(nb->x0 - nb->size / 4, nb->y0 + nb->size / 4, nb->size / 2, nb->idBlock, nb);
		nb->down[1] = new Block(nb->x0 + nb->size / 4, nb->y0 + nb->size / 4, nb->size / 2, nb->idBlock, nb);
		nb->down[2] = new Block(nb->x0 + nb->size / 4, nb->y0 - nb->size / 4, nb->size / 2, nb->idBlock, nb);
		nb->down[3] = new Block(nb->x0 - nb->size / 4, nb->y0 - nb->size / 4, nb->size / 2, nb->idBlock, nb);

		nb->idBlock = 0;
		
		if (x<nb->x0 && y>nb->y0) nb = nb->down[0];
		else
		if (x>nb->x0 && y>nb->y0) nb = nb->down[1];
		else
		if (x>nb->x0 && y<nb->y0) nb = nb->down[2];
		else
		if (x<nb->x0 && y<nb->y0) nb = nb->down[3];
	}
	
	if (x<nb->up->x0 && y>nb->up->y0) nb->up->down[0] = NULL;
	else
	if (x>nb->up->x0 && y>nb->up->y0) nb->up->down[1] = NULL;
	else
	if (x>nb->up->x0 && y<nb->up->y0) nb->up->down[2] = NULL;
	else
	if (x<nb->up->x0 && y<nb->up->y0) nb->up->down[3] = NULL;

	delete nb;
}

//загрузка мира из файла
int BlockMap::openMap(char *filename)
{
	FILE *f;
	fopen_s(&f, filename, "r");

	while (!feof(f))
	{
		int x, y, s, id;
		fscanf_s(f, "%d", &x);
		fscanf_s(f, "%d", &y);
		fscanf_s(f, "%d", &s);
		fscanf_s(f, "%d", &id);

		addBlock(x, y, s, id);
	}

	fclose(f);

	return 0;
}