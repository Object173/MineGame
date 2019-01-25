#include "Graphics.h"

BlockMap *mainMap;

void loadMap(BlockMap *map)
{
	mainMap = map;
}

void DrawPoly(int x, int y, int size)
{
	x *= BlockSize;
	y *= BlockSize;
	size *= BlockSize;

	glColor3f(1, 0, 0);
	glBegin(GL_QUADS);                      // Draw A Quad
	glVertex3f(x - size / 2, y + size / 2, 0.0f);              // Top Left
	glVertex3f(x + size / 2, y + size / 2, 0.0f);              // Top Right
	glVertex3f(x + size / 2, y - size / 2, 0.0f);              // Bottom Right
	glVertex3f(x - size / 2, y - size / 2, 0.0f);              // Bottom Left
	glEnd();
}

void Initialize()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);      // Будем очищать экран, заполняя его цветом тумана. ( Изменено )
	glFogf(GL_FOG_DENSITY, 0.35f);          // Насколько густым будет туман

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glOrtho(-Width / 2, Width / 2, -Height / 2, Height / 2, -200.0, 200.0);
	glMatrixMode(GL_MODELVIEW);
}

void Update()
{

}

void Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	DrawMap(mainMap);

	glutSwapBuffers();
	glFlush();
}

void DrawBlock(Block *b)
{
	if (b->idBlock != 0)
	{
		DrawPoly(b->x0, b->y0, b->size);
		glColor3f(0.0f, 1.0f, 0.0f);
		glBegin(GL_LINES);
		glVertex3f(b->x0 - b->size / 2, b->y0 + b->size / 2, 0.0f);
		glVertex3f(b->x0 + b->size / 2, b->y0 + b->size / 2, 0.0f);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(b->x0 + b->size / 2, b->y0 + b->size / 2, 0.0f);
		glVertex3f(b->x0 + b->size / 2, b->y0 - b->size / 2, 0.0f);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(b->x0 + b->size / 2, b->y0 - b->size / 2, 0.0f);
		glVertex3f(b->x0 - b->size / 2, b->y0 - b->size / 2, 0.0f);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(b->x0 - b->size / 2, b->y0 - b->size / 2, 0.0f);
		glVertex3f(b->x0 - b->size / 2, b->y0 + b->size / 2, 0.0f);
		glEnd();
		return;
	}

	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(b->x0 - b->size / 2, b->y0 + b->size / 2, 0.0f);
	glVertex3f(b->x0 + b->size / 2, b->y0 + b->size / 2, 0.0f);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(b->x0 + b->size / 2, b->y0 + b->size / 2, 0.0f);
	glVertex3f(b->x0 + b->size / 2, b->y0 - b->size / 2, 0.0f);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(b->x0 + b->size / 2, b->y0 - b->size / 2, 0.0f);
	glVertex3f(b->x0 - b->size / 2, b->y0 - b->size / 2, 0.0f);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(b->x0 - b->size / 2, b->y0 - b->size / 2, 0.0f);
	glVertex3f(b->x0 - b->size / 2, b->y0 + b->size / 2, 0.0f);
	glEnd();

	for (int i = 0; i < 4;i++)
	if (b->down[i] != NULL) DrawBlock(b->down[i]);
}

void DrawMap(BlockMap *map)
{
	glPushMatrix();
	
	DrawBlock(map->mainBlock);

	glPopMatrix();

}