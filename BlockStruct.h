#ifndef _BlockStruct_H
#define _BlockStruct_H

struct Block
{
private:

public:
	int x0, y0;	//координаты центра
	int size;	//размер блока
	int idBlock;	//индекс материала блока

	Block *up;	//родитель
	Block *down[4];	//дети

	Block(int x, int y, int s, int id, Block *UP);
	~Block();
};


#endif