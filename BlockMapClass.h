#ifndef BlockMapClass_h__
#define BlockMapClass_h__

#include "BlockStruct.h"

//минимальный размер блока
const int minSize=2;

class BlockMap
{
private:
	
public:
	int x0, y0;
	Block *mainBlock;
	void addBlock(int x, int y, int size, int id);	//добаление блока
	BlockMap(int x, int y); //конструктор
	~BlockMap(); //деструктор
	Block *setBlock(int x, int y); //
	int getBlock(int x, int y); //значение блока
	void delBlock(int x, int y); //удаление блока
	void groupBlock(Block *block);	//группировка блоков
	int openMap(char *filename); //загрузка мира из файла
};
#endif