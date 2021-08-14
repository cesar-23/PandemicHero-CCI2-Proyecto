#include "Dependency.h"

int desplaza = 1;
int mueve = 70;
int gravedad = -3;
int tam = 96;

class Player {

    // posicion del personaje
    int x, y;
    int score;
    int dir;
    int paso;
    int tiempoPaso;
    int tiempoCont;
    bool falling;
    Player();
    static Player* instance;
    ALLEGRO_BITMAP* img;

public:
    static Player* getInstance();
    void setPlayer1();
    void teclas(ALLEGRO_EVENT);
    void pinta();
    void caer();
    int getX()const;
    int getY()const;
    int getScore()const;
    void setNotFalling();
    void setFalling();
    void teleport(int, int);
    bool mover();
    //void Collider();
};

Player* Player::instance = 0;

Player* Player::getInstance() {
    if (instance == 0) {
        instance = new Player;
    }
    return instance;
}

struct {
    int FPS;
    ALLEGRO_EVENT_QUEUE* Mis_eventos;
    ALLEGRO_COLOR fondo;
    ALLEGRO_BITMAP* img;

} sistema;

Player::Player() {
    this->tiempoPaso = int(sistema.FPS / mueve);
    this->tiempoCont = 0;
    this->x = 400;
    this->y = 500;
    this->score = 0;
    this->dir = 0;
    this->paso = 0;
    this->falling = true;
}

void Player::setPlayer1() {
    img = al_load_bitmap("sources/image/chica.png");
}

void Player::teclas(ALLEGRO_EVENT evento) {
    ALLEGRO_KEYBOARD_STATE teclado;
    al_get_keyboard_state(&teclado);
    if (al_key_down(&teclado, ALLEGRO_KEY_UP) && !falling) {
        falling = true;
        gravedad = 22;
        dir = 3;
        tiempoCont++;
    }
    else if (al_key_down(&teclado, ALLEGRO_KEY_LEFT) && mover()) {
        x -= desplaza;
        dir = 1;
        tiempoCont++;
    }
    else if (al_key_down(&teclado, ALLEGRO_KEY_RIGHT) && mover()) {
        x += desplaza;
        dir = 2;
        tiempoCont++;
    }
    else {
        dir = 0;
    }
    //primera colisión


    // animacion

    if (tiempoCont > tiempoPaso) {
        paso++;
        tiempoCont = 0;
    }
    if (paso > 2) paso = 0;

    if (y >= 600 - tam) {
        y = 600 - (tam + 1);
        setNotFalling();
    }

    int R_inf = y + tam;
    int R_sup = y;
    int R_der = x + tam;
    int R_izq = x;
    //recortando la hitbox
    int sesgoY = 5;
    int sesgoX = 10;
    //coordenadas de la caja y medidas
    int cordX = 200;
    int cordY = 400;
    int ancho = 400;
    int largo = 50;

    if ((R_sup <= cordY + largo) && (R_inf >= cordY) && (R_der >= cordX /*+ sesgoX*/) && (R_izq <= cordX + ancho/*- sesgoX*/)) {/**/
        if (R_izq == cordX + ancho /*- sesgoX*/) {
            x += desplaza;
        }
        else if (R_der == cordX /*+ sesgoX*/) {
            x -= desplaza;
        }
        else if (R_inf >= cordY && R_inf <= cordY + 20) {
            y = cordY - tam /*+ sesgoY*/;
            setNotFalling();
        }
        else if (R_sup <= cordY + largo && R_sup >= cordY + largo - 20) {
            gravedad = -3;
            setFalling();
        }
        //std::cout << x + tam << "\t";
        //std::cout << y << std::endl;
    }
    else {
        setFalling();
    }
}

void Player::caer() {
    y -= gravedad;
    if (gravedad >= -2) {
        gravedad -= 1;
    }
}

void Player::pinta() {
    al_draw_bitmap_region(img, paso * tam, dir * tam, tam, tam, x, y, 4);
}

int Player::getX()const {
    return x;
}

int Player::getY()const {
    return y;
}

void Player::setNotFalling() {
    falling = false;
}

void Player::setFalling() {
    falling = true;
}

int Player::getScore()const {
    return score;
}

void Player::teleport(int x, int y) {
    this->x = x;
    this->y = y;
}

bool Player::mover() {
    //Limites de pantalla
    if (x < 0) {
        x = 1;
        return false;
    }
    else if (x > 800 - tam) {
        x = 800 - (tam + 1);
        return false;
    }
    else if (y < 0) {
        y = 1;
        return false;
    }
    else {
        return true;
    }
}