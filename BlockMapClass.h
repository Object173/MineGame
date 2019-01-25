#ifndef BlockMapClass_h__
#define BlockMapClass_h__

#include "BlockStruct.h"

//����������� ������ �����
const int minSize=2;

class BlockMap
{
private:
	
public:
	int x0, y0;
	Block *mainBlock;
	void addBlock(int x, int y, int size, int id);	//��������� �����
	BlockMap(int x, int y); //�����������
	~BlockMap(); //����������
	Block *setBlock(int x, int y); //
	int getBlock(int x, int y); //�������� �����
	void delBlock(int x, int y); //�������� �����
	void groupBlock(Block *block);	//����������� ������
	int openMap(char *filename); //�������� ���� �� �����
};
#endif