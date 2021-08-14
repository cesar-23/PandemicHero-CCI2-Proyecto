#include "Dependency.h"
#include "Level.h"






int main(void) {

    // inicializamos las librerías utilizadas
    al_init();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_install_keyboard();
    al_install_mouse();


    ALLEGRO_DISPLAY* display = al_create_display(800, 600);
    ALLEGRO_TIMER* timer = NULL;


    al_set_window_title(display, "Pandemic Hero");
    sistema.img = al_load_bitmap("sources/image/fondo2.jpg");
    sistema.fondo = al_map_rgb(255, 255, 255);
    sistema.FPS = 240;


    timer = al_create_timer(1.0 / sistema.FPS);


    // creo lista de eventos

    sistema.Mis_eventos = al_create_event_queue();

    // asigno eventos a la lista de eventos

    al_register_event_source(sistema.Mis_eventos, al_get_keyboard_event_source());
    al_register_event_source(sistema.Mis_eventos, al_get_mouse_event_source());
    al_register_event_source(sistema.Mis_eventos, al_get_display_event_source(display));
    al_register_event_source(sistema.Mis_eventos, al_get_timer_event_source(timer));
    al_start_timer(timer);
    
    menu();

    al_destroy_display(display);
}