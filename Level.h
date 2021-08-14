
#include "Dependency.h"
#include "Player.h"
#include "Box.h"
#include "Virus.h"

Virus virulin;
Player* jugador = Player::getInstance();
Box cajita(200, 400, 400, 50);


int state = 0;

int menu();

bool choca(Virus virus) {
    int R_inf = jugador->getY() + tam;
    int R_sup = jugador->getY();
    int R_der = jugador->getX() + tam;
    int R_izq = jugador->getX();
    
    int sesgoY = 5;
    int sesgoX = 10;
    //coordenadas de la caja y medidas
    int cordX = virus.GetX();
    int cordY = virus.GetY();
    int ancho = 50;
    int largo = 50;

    if (R_sup <= cordY + largo && R_inf >= cordY && R_der >= cordX /*+ sesgoX*/ && R_izq <= cordX + ancho/*- sesgoX*/) {
        if (R_izq == cordX + ancho /*- sesgoX*/) {
            return true;
        }
        else if (R_der >= cordX /*+ sesgoX*/) {
            return true;
        }
        else if (R_inf >= cordY && R_inf <= cordY + 20) {
            return true;
        }
        else if (R_sup <= cordY + largo && R_sup >= cordY + largo - 20) {
            return true;
        }
    }
    return false;
}


ALLEGRO_FONT* font;

void dibuja(void) {
    al_clear_to_color(sistema.fondo);
    al_draw_bitmap(sistema.img, 0, 0, 0);
    al_draw_text(font, al_map_rgb(254, 65, 100), 250, 20, 0, "Pandemic Hero");
    //al_draw_text(font, al_map_rgb(254, 65, 100), 20, 20, 0, "score: ");
    //al_draw_text(font, al_map_rgb(254, 65, 100), 40, 20, 0, jscore);

    jugador->pinta();
    cajita.Draw();
    virulin.Draw();

    //muestra por pantalla
    al_flip_display();

}

int gameOver() {

    int x = -1, y = -1;
    ALLEGRO_BITMAP* over = al_load_bitmap("sources/image/over_null.jpg");
    ALLEGRO_BITMAP* over1 = al_load_bitmap("sources/image/over_1.jpg");
    ALLEGRO_BITMAP* over2 = al_load_bitmap("sources/image/over_2.jpg");
    //menu
    int botones[] = { 0 };

    while (true)
    {
        ALLEGRO_EVENT Evento;
        al_wait_for_event(sistema.Mis_eventos, &Evento);


        if (botones[0] == 0)
            al_draw_bitmap(over, 0, 0, 0);
        else if (botones[0] == 1)
            al_draw_bitmap(over1, 0, 0, 0);
        else
            al_draw_bitmap(over2, 0, 0, 0);

        if (Evento.type == ALLEGRO_EVENT_MOUSE_AXES || Evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {

            x = Evento.mouse.x;
            y = Evento.mouse.y;

            if (x >= 271 && x <= 527 && y >= 304 && y <= 372) {
                botones[0] = 1;
                if (Evento.mouse.button & 1) {
                    jugador->teleport(380, 500);
                    virulin.Teleport(0, 500);
                    return 1;
                }

            }
            else {
                if (x >= 271 && x <= 527 && y >= 405 && y <= 472) {
                    botones[0] = 2;
                    if (Evento.mouse.button & 1) {
                        jugador->teleport(380, 500);
                        menu();
                    }
                }
                else {
                    botones[0] = 0;
                }
            }

        }

        al_flip_display();
    }
}


void juego() {

    
    font = al_load_ttf_font("sources/fonts/Gotic.otf", 54, 0);
    ALLEGRO_EVENT evento;
    bool ejecutar = true;
    bool dibujar = true;

    jugador->setPlayer1();
    cajita.initImg();
    virulin.IniImg();


    while (ejecutar) {
        // Pinta si es dibuja y esta vacia la lista de eventos

        if (dibujar && al_event_queue_is_empty(sistema.Mis_eventos)) {
            dibuja();
            dibujar = false;
        }

        // esperamos a que ocurra un evento
        al_wait_for_event(sistema.Mis_eventos, &evento);

        // se ha cerrado la ventana
        if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            ejecutar = false;
        }

        // se ha pulsado ESC
        if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                ejecutar = false;
            }
        }

        //perder el juego
        if (choca(virulin)) {
            gameOver();
        }

        // pasa un tiempo determinado
        if (evento.type == ALLEGRO_EVENT_TIMER) {
            dibujar = true;
            jugador->teclas(evento);
            jugador->mover();
            jugador->caer();
            virulin.Update();
            choca(virulin);
            if (jugador->getY() >= 488) {
                jugador->setNotFalling();
            }
        }

    }
    al_destroy_font(font);
}

int menu() {
    int x = -1, y = -1;
    ALLEGRO_COLOR blanco = al_map_rgb(255, 255, 255);
    ALLEGRO_COLOR azar = al_map_rgb(255, 50, 65);

    
    ALLEGRO_BITMAP* menu_null = al_load_bitmap("sources/image/menu.png");
    ALLEGRO_BITMAP* menu_jugar = al_load_bitmap("sources/image/menu_jugar.png");
    ALLEGRO_BITMAP* menu_salir = al_load_bitmap("sources/image/menu_salir.png");
    //menu
    int botones[] = { 0 };

    while (true)
    {
            ALLEGRO_EVENT Evento;
            al_wait_for_event(sistema.Mis_eventos, &Evento);


            if (botones[0] == 0)
                al_draw_bitmap(menu_null, 0, 0, 0);
            else if (botones[0] == 1)
                al_draw_bitmap(menu_jugar, 0, 0, 0);
            else
                al_draw_bitmap(menu_salir, 0, 0, 0);

            if (Evento.type == ALLEGRO_EVENT_MOUSE_AXES || Evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){

                x = Evento.mouse.x;
                y = Evento.mouse.y;

                if (x >= 284 && x <= 515 && y >= 400 && y <= 462) {
                    botones[0] = 1;
                    if (Evento.mouse.button & 1)
                        juego();

                }
                else {
                    if (x >= 284 && x <= 515 && y >= 485 && y <= 548) {
                        botones[0] = 2;
                        if (Evento.mouse.button & 1)
                            return 1;
                    }
                    else {
                        botones[0] = 0;
                    }
                }

            }

            al_flip_display();
        }
}

