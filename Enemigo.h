#ifndef ENEMIGO_H
#define ENEMIGO_H
#include "Colisionable.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Enemigo : public sf::Drawable, public Colisionable
{
protected:
    int _health, _max_health, _damage;
    float _walk_frame, _attack_frame, _dead_frame;
    bool _attack=false;
    bool _isMoving = false;
    bool _soundPlaying = false;
    bool _dead=false;
    sf::Sprite _sprite;
    virtual void configurar_Tam_Pos_Hitbox()=0;
    virtual void updateHitboxPos()=0;
    sf::RectangleShape _hitbox;
    sf::Vector2f _movePosition = {0,0};
    sf::Vector2f _distancia;
    sf::Vector2f _velocity;
    sf::Texture _texture;
    sf::SoundBuffer _buffer;
    sf::Sound _sound;
    sf::RectangleShape _barraVidaFondo;
    sf::RectangleShape _barraVidaFrente;

public:
    Enemigo(const char* archivoTextura, sf::Vector2f vel, int h,int d);
    virtual void actualizarBarraVida()=0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    virtual void disminuir_vida(int danio)=0;
    virtual void update(sf::Vector2f posicion_caballero)=0;
    virtual int getDanio()=0;
    virtual bool isDead()=0;
    virtual bool getFrameAttack()=0;
    virtual sf::Vector2f returnPosition()=0;
    virtual sf::FloatRect getHitbox()=0;
    virtual void colision_mapa(sf::Vector2f vectorPosicionesEsqueletos[],int pos)=0;
    virtual sf::FloatRect getBounds() const override;
    //destructor
};

#endif // ENEMIGO_H
