#ifndef PERSONAJE_H_INCLUDED
#define PERSONAJE_H_INCLUDED
#include "Colisionable.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
enum class PersonajeState
{
    Idle=0,
    Move_up,
    Move_down,
    Move_x,
};
class Personaje: public sf::Drawable, public Colisionable
{
    int _height_pixel;
    int _vida;
    int _vida_maxima;
    int _danio;
    int _xp;
    int _xp_maximo;
    bool _isMoving = false;
    bool _isAttacking= false;
    bool _soundPlaying = false;
    bool _muerto=false;
    float posy=0, posx=0;
    float _walk_frame, _attack_frame, _dead_frame;
    void configurar_Tam_Pos_Hitbox();
    void updateHitboxPos();
    sf::Sprite _sprite;
    sf::Texture _texture;
    sf::Vector2f _velocity;
    sf::Vector2f _movePosition = {0,0};
    sf::SoundBuffer _buffer;
    sf::Sound _sound;
    sf::Vector2f position;
    sf::RectangleShape _hitbox;
    sf::RectangleShape _barraVidaFondo;
    sf::RectangleShape _barraVidaFrente;
    sf::RectangleShape _bordeBarraVida;
    sf::RectangleShape _barraXpFondo;
    sf::RectangleShape _barraXpFrente;
    sf::RectangleShape _bordeBarraXp;
    sf::Font font_vida;
    sf::Text text_vida;
    sf::Font font_xp;
    sf::Text text_xp;
    PersonajeState _state = PersonajeState::Idle;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void actualizarBarraVida();
    void actualizarBarraXp();
    void actualizarTextoVida();
    void actualizarTextoXp();
public:
    Personaje();
    int getDanio();
    bool getFrameAttack();
    bool isDead();
    void disminuirVida(int _danio);
    void aumentarVida(int vida);
    void aumentarXp(int kills);
    void aumentar_stats();
    void cmd();
    void update();
    void colision_mapa(sf::Vector2f posicion_caballero);
    sf::RectangleShape getBarraVidaFondo();
    sf::RectangleShape getBarraVidaFrente();
    sf::RectangleShape getBarraVidaBorde();
    sf::RectangleShape getBarraXpFondo();
    sf::RectangleShape getBarraXpFrente();
    sf::RectangleShape getBarraXpBorde();
    sf::Text getTextVida();
    sf::Text getTextXp();
    sf::Vector2f returnPosition();
    sf::FloatRect getBounds()const override;
    sf::FloatRect getHitbox()const;
};


#endif // PERSONAJE_H_INCLUDED
