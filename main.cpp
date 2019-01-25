#include<stdio.h>
#include "BlockMapClass.h"
#include "Graphics.h"

void main(int argc, char** argv)
{
	BlockMap *map = new BlockMap(0, 0);
	//map->addBlock(0, 0, 2, 5);
	loadMap(map);
	map->openMap("in.txt");
	map->addBlock(32, 32, 64, 5);
	map->addBlock(64, 64, 32, 5);
	map->delBlock(10, 10);
	map->delBlock(0, 0);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(Width, Height);
	glutInitWindowPosition(100, 50);
	glutCreateWindow("window");
	glutDisplayFunc(Render);
	glutIdleFunc(Update);
	//glutMouseFunc(MousePressed);
	Initialize();
	glutMainLoop();

	delete map;
}