#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include<stdlib.h>
#include<GL\glut.h>
#include<GL\glaux.h>
#include "BlockMapClass.h"

#define Width 800
#define Height 600
#define BlockSize 1

void loadMap(BlockMap *map);
void Initialize();
void Update();
void Render();
void DrawPoly(int x, int y, int size);
void DrawMap(BlockMap *map);

#endif