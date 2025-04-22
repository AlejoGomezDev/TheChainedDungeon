#ifndef JEFE_FINAL_H
#define JEFE_FINAL_H
#include "Colisionable.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Enemigo.h"

class Jefe_Final : public Enemigo
{
protected:
    sf::Vector2f _vel = {1.8,1.8};
    static sf::Texture _texture;
    bool _primera_deteccion;
public:
    Jefe_Final(float x, float y);
    int getDanio();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void disminuir_vida(int danio);
    void update(sf::Vector2f posicion_jugador) override;  // Actualización con posición del jugador
    void actualizarBarraVida();
    bool detectar_jugador(sf::Vector2f posicion_jugador);
    bool getFrameAttack();
    bool isDead();
    void configurar_Tam_Pos_Hitbox()override;
    void updateHitboxPos()override;
    void colision_mapa(sf::Vector2f vectorPosicionesEsqueletos[],int pos);
    sf::FloatRect getHitbox();
    sf::Vector2f returnPosition();
};

#endif // JEFE_FINAL_H
