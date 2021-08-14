#include "Dependency.h"

class Box {
private:
	int cordX;
	int cordY;
	int largo;
	int ancho;
	ALLEGRO_BITMAP* img;
public:
	Box(int, int, int, int);
	void initImg();
	void Draw();
	//getter and setter
	int getCordX()const;
	int getCordY()const;
	int getLength()const;
	int getWidth()const;

};

Box::Box(int X, int Y, int lenght, int width) {
	this->cordX = X;
	this->cordY = Y;
	this->largo = lenght;
	this->ancho = width;
}

void Box::initImg() {
	img = al_load_bitmap("sources/image/obsidian.png");
}

void Box::Draw() {
	al_draw_bitmap_region(img, 0, 0, largo, ancho, cordX, cordY, 4);
}

int Box::getCordX()const {
	return cordX;
}
int Box::getCordY()const {
	return cordY;
}
int Box::getLength()const {
	return largo;
}
int Box::getWidth()const {
	return ancho;
}