#ifndef _BlockStruct_H
#define _BlockStruct_H

struct Block
{
private:

public:
	int x0, y0;	//���������� ������
	int size;	//������ �����
	int idBlock;	//������ ��������� �����

	Block *up;	//��������
	Block *down[4];	//����

	Block(int x, int y, int s, int id, Block *UP);
	~Block();
};


#endif