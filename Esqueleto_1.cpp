#include "Esqueleto_1.h"
#include <iostream>
#include <cmath>
sf::Texture Esqueleto_1::_texture;
Esqueleto_1::Esqueleto_1(float x, float y) : Enemigo("imagenes/Sprites/Esqueleto/Esqueleto_1-2/Caminar/Esqueleto_1_Caminar.png", {1.2,1.2}, 75, 10)
{
    _max_health=100;
    _health=_max_health;
    _attack=false;
    _dead=false;
    _sprite.setTexture(_texture);
    _sprite.setPosition(x, y);
    _sprite.setTextureRect({16, 142, 32, 49});
    _walk_frame=0;
    _attack_frame=0;
    _dead_frame=0;
    _barraVidaFondo.setSize(sf::Vector2f(50, 5));
    _barraVidaFondo.setFillColor(sf::Color::Red);
    _barraVidaFrente.setSize(sf::Vector2f(50, 5));
    _barraVidaFrente.setFillColor(sf::Color::Green);
    configurar_Tam_Pos_Hitbox();
}
void Esqueleto_1::configurar_Tam_Pos_Hitbox()
{
    float hitboxWidth = 24.0f;
    float hitboxHeight = 13.0f;
    _hitbox.setSize(sf::Vector2f(hitboxWidth,hitboxHeight));
    _hitbox.setFillColor(sf::Color::Red);
    updateHitboxPos();
}
void Esqueleto_1::updateHitboxPos()
{
    sf::FloatRect hitbox_bounds = _sprite.getGlobalBounds();
    _hitbox.setPosition(hitbox_bounds.left+3, hitbox_bounds.top + 35);
}
void Esqueleto_1::colision_mapa(sf::Vector2f vectorPosicionesEsqueletos[], int pos)
{
    _sprite.setPosition(vectorPosicionesEsqueletos[pos].x,vectorPosicionesEsqueletos[pos].y);
}
sf::Vector2f Esqueleto_1::returnPosition()
{
    return _sprite.getPosition();
}
sf::FloatRect Esqueleto_1::getHitbox()
{
    return _hitbox.getGlobalBounds();
}
int Esqueleto_1::getDanio()
{
    if(_attack)
    {
        return _damage;
    }
}
bool Esqueleto_1::getFrameAttack()
{
    return _attack;
}
void Esqueleto_1::actualizarBarraVida()
{
    float porcentajeVida = static_cast<float>(_health) / _max_health;
    _barraVidaFrente.setSize(sf::Vector2f(50 * porcentajeVida, 5));
}
void Esqueleto_1::disminuir_vida(int danio)
{
    _health -= danio;
    if(_health<0)
    {
        _health=0;
    }
    actualizarBarraVida();
}
bool Esqueleto_1::detectar_jugador(sf::Vector2f posicion_jugador)
{
    sf::Vector2f distancia = _sprite.getPosition() - posicion_jugador;
    float distancia_total = std::sqrt(distancia.x * distancia.x + distancia.y * distancia.y);
    float rango_deteccion = 200.0f;
    if (distancia_total <= rango_deteccion)
    {
        return true;
    }
    return false;
}
bool Esqueleto_1::isDead()
{
    return _dead;
}
void Esqueleto_1::update(sf::Vector2f posicion_caballero)
{
    if(_health>0)
    {
        sf::Vector2f posicion = _sprite.getPosition();
        _barraVidaFondo.setPosition(posicion.x - 10, posicion.y - 10);
        _barraVidaFrente.setPosition(posicion.x - 10, posicion.y - 10);
        _texture.loadFromFile("imagenes/Sprites/Esqueleto/Esqueleto_1-2/Caminar/Esqueleto_1_Caminar.png");
        _sprite.setTexture(_texture);
        _sprite.setTextureRect({16, 142, 32, 49});
        _attack=false;
        if (detectar_jugador(posicion_caballero))
        {
            _distancia = posicion_caballero - _sprite.getPosition();
            float magnitud = std::sqrt(_distancia.x * _distancia.x + _distancia.y * _distancia.y);

            // Distancia mínima antes de detener el esqueleto
            float distancia_minima = 40; // Ajusta esta distancia según sea necesario

            if (magnitud > distancia_minima)
            {
                _attack_frame = 0;
                if (magnitud != 0)
                {
                    _distancia /= magnitud;
                }
                _movePosition = sf::Vector2f(_distancia.x * _velocity.x, _distancia.y * _velocity.y);
                _texture.loadFromFile("imagenes/Sprites/Esqueleto/Esqueleto_1-2/Caminar/Esqueleto_1_Caminar.png");
                _sprite.setTexture(_texture);
                _walk_frame += 0.1;
                if (_walk_frame >= 8)
                {
                    _walk_frame = 0;
                }
                _sprite.setTextureRect({80 + int(_walk_frame) * (28 + 36), 207, 29, 48});
                if (_movePosition.x < 0)
                {
                    _sprite.setScale(-1, 1);
                }
                else if (_movePosition.x > 0)
                {
                    _sprite.setScale(1, 1);
                }
                _sprite.move(_movePosition);
            }
            else
            {
                _texture.loadFromFile("imagenes/Sprites/Esqueleto/Esqueleto_1-2/Ataque/Esqueleto_1_Ataque.png");
                _sprite.setTexture(_texture);
                _attack_frame += 0.1;
                if (_attack_frame >= 5)
                {
                    _attack=true;
                    _attack_frame = 0;
                }
                switch((int)_attack_frame)
                {
                case 0:
                    _sprite.setTextureRect({86, 207, 31, 47});
                    break;
                case 1:
                    _sprite.setTextureRect({148, 207, 24, 47});
                    break;
                case 2:
                    _sprite.setTextureRect({211, 207, 38, 47});
                    break;
                case 3:
                    _sprite.setTextureRect({276, 207, 45, 47});
                    break;
                case 4:
                    _sprite.setTextureRect({340, 207, 44, 47});
                    break;
                }
                if (_movePosition.x < 0)
                {
                    _sprite.setScale(-1, 1);
                }
                else if (_movePosition.x > 0)
                {
                    _sprite.setScale(1, 1);
                }
            }
        }
    }
    else
    {
        _attack=false;
        _texture.loadFromFile("imagenes/Sprites/Esqueleto/Esqueleto_1-2/Dañado/Esqueleto_1_Dañado.png");
        _sprite.setTexture(_texture);
        _dead_frame+=0.1;
        if(_dead_frame>=18)
        {
            _dead=true;
        }
        switch((int)_dead_frame)
        {
        case 0:
            _sprite.setTextureRect({16, 110, 31, 48});
            break;
        case 1:
            _sprite.setTextureRect({81, 110, 32, 48});
            break;
        case 2:
            _sprite.setTextureRect({146, 110, 32, 48});
            break;
        case 3:
            _sprite.setTextureRect({210, 110, 31, 48});
            break;
        case 4:
            _sprite.setTextureRect({274, 110, 32, 48});
            break;
        case 5:
            _sprite.setTextureRect({337, 110, 35, 50});
            break;
        }
    }
    updateHitboxPos();
}
void Esqueleto_1::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
    target.draw(_barraVidaFondo, states);
    target.draw(_barraVidaFrente, states);
}
