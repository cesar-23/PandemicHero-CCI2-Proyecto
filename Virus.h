#include "Dependency.h"

int Nrand(int num1) {
	int aux;
	srand(time(NULL));
	aux = 1 + rand() % (num1 - 1);
	return aux;
}


class Virus {
private:
	int cordX;
	int azar;
	int cordY;
	int desplazar;
	ALLEGRO_BITMAP* imagen;
public:
	Virus();
	void IniImg();
	void Draw();
	void Update();
	void Teleport(int,int);
	int GetX()const;
	int GetY()const;
	~Virus();
};

Virus::Virus() {
	this->cordX = -50;
	this->cordY = 500;
	this->desplazar = 0;
	this->azar = 0;
}

void Virus::IniImg() {
	imagen = al_load_bitmap("sources/image/virus.png");
}

void Virus::Draw() {
	al_draw_bitmap_region(imagen, 0, 0, 50, 50, cordX, cordY, 4);
}

void Virus::Teleport(int x,int y) {
	this->cordX = x;
	this->cordY = y;
}

void Virus::Update() {
	if (cordX == -50) {
		desplazar = 2;
		this->cordY = Nrand(11)*50;
	}
	else if (cordX == 850) {
		desplazar = -2;
		this->cordY = Nrand(11)*50;
	}
	this->cordX += desplazar;
}

int Virus::GetX()const {
	return cordX;
}

int Virus::GetY()const {
	return cordY;
}

Virus::~Virus() {}