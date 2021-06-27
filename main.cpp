#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <Windows.h>

using namespace std;
int ancho = 800, alto = 600;

int myX = 0, myY = 0;

void crecer() {
	myX++;
	myY++;
}

int main() {
	
	//Todo esto ira dentro de un init(), recordar adaptar todo a clases para poder manejar nuestros objetos
	al_init();
	al_init_font_addon();
	al_init_ttf_addon();
	ALLEGRO_DISPLAY* ventana = al_create_display(ancho, alto);
	ALLEGRO_FONT* GoticFont = al_load_font("sources/fonts/Gotic.otf",40,0);
	al_set_window_title(ventana, "Pandemic Hero");
	int ancho_W = GetSystemMetrics(SM_CXSCREEN);
	int alto_W = GetSystemMetrics(SM_CYSCREEN);
	al_set_window_position(ventana, ancho_W / 2 - ancho / 2, alto_W / 2 - alto / 2);

	while (true)
	{
		al_draw_text(GoticFont, al_map_rgb(255, 255, 255),myX,myY, NULL, "Hello World");
		crecer();
		al_flip_display();
	}

	return 0;
}

