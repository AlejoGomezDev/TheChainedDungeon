#include "Personaje.h"
#include <iostream>
#include <sstream>
Personaje::Personaje()
{
    /// VIDA
    _barraVidaFondo.setSize(sf::Vector2f(150, 20));
    _barraVidaFondo.setFillColor(sf::Color::Red);
    _barraVidaFrente.setSize(sf::Vector2f(150, 20));
    _barraVidaFrente.setFillColor(sf::Color::Green);
    _bordeBarraVida.setSize(sf::Vector2f(156, 29));
    _bordeBarraVida.setFillColor(sf::Color::Black);
    /// TEXTO VIDA
    font_vida.loadFromFile("Roboto-Regular.ttf");
    text_vida.setFont(font_vida);
    text_vida.setFillColor(sf::Color::White);
    text_vida.setCharacterSize(20);
    std::ostringstream txtvd;
    txtvd << _vida << "/" << _vida_maxima;
    text_vida.setString(txtvd.str());

    /// XP
    _barraXpFondo.setSize(sf::Vector2f(150, 10));
    _barraXpFondo.setFillColor(sf::Color::Black);
    _barraXpFrente.setSize(sf::Vector2f(150, 10));
    _barraXpFrente.setFillColor(sf::Color::Magenta);
    _bordeBarraXp.setSize(sf::Vector2f(153, 13));
    _bordeBarraXp.setFillColor(sf::Color::Black);
    /// TEXTO XP
    font_xp.loadFromFile("Roboto-Regular.ttf");
    text_xp.setFont(font_xp);
    text_xp.setFillColor(sf::Color::White);
    text_xp.setCharacterSize(10);
    std::ostringstream txtxp;
    txtxp << "XP: " << _xp;
    text_xp.setString(txtxp.str());

    _vida_maxima = 100;
    _vida = _vida_maxima;
    _danio=25;
    _xp=0;
    _xp_maximo=3;
    _velocity = {1.5, 1.5};
    _walk_frame=0;
    _attack_frame=0;
    _dead_frame=0;
    _texture.loadFromFile("imagenes/Sprites/Caballero/Caballero_1-4/Caminar/Caballero_1_Caminar.png");
    if (!_buffer.loadFromFile("Sound/Concrete_Footsteps.wav"))
    {
        std::cout << "Error cargando el sonido" << std::endl;
    }
    _sound.setBuffer(_buffer);
    _sound.setLoop(true);
    _sound.setVolume(8);
    _sprite.setTexture(_texture);
    _isMoving=false;
    _muerto=false;
    _isAttacking=false;
    _sprite.setPosition(1580, 515);
    _sprite.setTextureRect({83, 207, 26, 48});
    //_sprite.setOrigin(_sprite.getGlobalBounds().width/2, 48);
    _sprite.setOrigin(_sprite.getGlobalBounds().width/2, 0);
    _height_pixel=142;
    configurar_Tam_Pos_Hitbox();
}
void Personaje::aumentarXp(int kills)
{
    _xp=0;
    _xp+=kills;
}
void Personaje::aumentar_stats()
{
    _vida_maxima+=10;
    _vida+=5;
    _danio+=5;
}
void Personaje::aumentarVida(int vida)
{
    _vida+=vida;
    if(_vida>_vida_maxima)
    {
        _vida=_vida_maxima;
    }
}
int Personaje::getDanio()
{
    return _danio;
}
void Personaje::actualizarBarraVida()
{
    float porcentajeVida = static_cast<float>(_vida) / _vida_maxima;
    _barraVidaFrente.setSize(sf::Vector2f(150 * porcentajeVida, 20));
}
void Personaje::actualizarBarraXp()
{
    float porcentajeXp = static_cast<float>(_xp) / _xp_maximo;
    _barraXpFrente.setSize(sf::Vector2f(150 * porcentajeXp, 10));
}
void Personaje::actualizarTextoVida()
{
    std::ostringstream txtvd;
    txtvd << _vida << "/" << _vida_maxima;
    text_vida.setString(txtvd.str());
}
void Personaje::actualizarTextoXp()
{
    std::ostringstream txtxp;
    txtxp << "XP: " << _xp;
    text_xp.setString(txtxp.str());
}
void Personaje::disminuirVida(int _danio)
{
    _vida-=_danio;
    if(_vida<0)
    {
        _vida=0;
    }
    actualizarBarraVida();
}

bool Personaje::getFrameAttack()
{
    return _isAttacking;
}
bool Personaje::isDead()
{
    return _muerto;
}
void Personaje::configurar_Tam_Pos_Hitbox()
{
    float hitboxWidth = 24.0f;
    float hitboxHeight = 13.0f;
    _hitbox.setSize(sf::Vector2f(hitboxWidth,hitboxHeight));
    updateHitboxPos();
}
void Personaje::updateHitboxPos()
{
    sf::FloatRect hitbox_bounds = _sprite.getGlobalBounds();
    _hitbox.setPosition(hitbox_bounds.left+3, hitbox_bounds.top + 35);
}

void Personaje::cmd()
{
    _movePosition = {0,0};
    _state=PersonajeState::Idle;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)||sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        _movePosition.y= -_velocity.y;
        _state=PersonajeState::Move_up;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)||sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        _movePosition.y=_velocity.y;
        _state=PersonajeState::Move_down;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)||sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        _movePosition.x=-_velocity.x;
        _state=PersonajeState::Move_x;
        _isMoving=true;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)||sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        _movePosition.x=_velocity.x;
        _state=PersonajeState::Move_x;
    }
    //velocidad alterada para tests
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::P))
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::U))
                {
                    _velocity= {10, 10}; //aumenta velocidad para testeos
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                {
                    _velocity= {1.5, 1.5}; //decrementa velocidad para testeos
                }
            }
        }
    }
}

void Personaje::update()
{
    sf::Vector2f posicion = returnPosition();
    _barraVidaFondo.setPosition(posicion.x - 450, posicion.y - 250);
    _barraVidaFrente.setPosition(posicion.x - 450, posicion.y - 250);
    _bordeBarraVida.setPosition(posicion.x - 453, posicion.y - 253);
    text_vida.setPosition(posicion.x - 445, posicion.y - 253);
    actualizarBarraVida();
    actualizarTextoVida();
    _barraXpFondo.setPosition(posicion.x - 450, posicion.y-210);
    _barraXpFrente.setPosition(posicion.x - 450, posicion.y-210);
    _bordeBarraXp.setPosition(posicion.x - 453, posicion.y-211);
    text_xp.setPosition(posicion.x - 440, posicion.y-210);
    actualizarBarraXp();
    actualizarTextoXp();
    _isMoving=false;
    _isAttacking=false;
    if(_vida>0)
    {
        _texture.loadFromFile("imagenes/Sprites/Caballero/Caballero_1-4/Caminar/Caballero_1_Caminar.png");
        _sprite.setTexture(_texture);
        switch(_state)
        {
        case PersonajeState::Idle:
            _sprite.setTextureRect({17, _height_pixel, 30, 48});
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                _texture.loadFromFile("imagenes/Sprites/Caballero/Caballero_1-4/Lanza/Caballero_1_Lanza.png");
                _sprite.setTexture(_texture);
                _movePosition = {0,0};
                _attack_frame+=0.2;
                if(_attack_frame>=5)
                {
                    _attack_frame=0;
                    _isAttacking=true;
                }
                switch(_height_pixel)
                {
                case 142:
                    switch((int)_attack_frame)
                    {
                    case 0:
                        _sprite.setTextureRect({210, 130, 27, 61});
                        break;
                    case 1:
                        _sprite.setTextureRect({274, 130, 27, 61});
                        break;
                    case 2:
                        _sprite.setTextureRect({338, 130, 27, 61});
                        break;
                    case 3:
                        _sprite.setTextureRect({402, 130, 27, 61});
                        break;
                    case 4:
                        _sprite.setTextureRect({466, 130, 27, 61});
                        break;
                    }
                    break;
                case 14:
                    switch((int)_attack_frame)
                    {
                    case 0:
                        _sprite.setTextureRect({212, 0, 24, 64});
                        break;
                    case 1:
                        _sprite.setTextureRect({277, 0, 24, 64});
                        break;
                    case 2:
                        _sprite.setTextureRect({341, 0, 24, 64});
                        break;
                    case 3:
                        _sprite.setTextureRect({405, 0, 24, 64});
                        break;
                    case 4:
                        _sprite.setTextureRect({468, 0, 24, 64});
                        break;
                    }
                    break;
                case 207:
                    switch((int)_attack_frame)
                    {
                    case 0:
                        _sprite.setTextureRect({194, 207, 55, 47});
                        break;
                    case 1:
                        _sprite.setTextureRect({256, 207, 62, 47});
                        break;
                    case 2:
                        _sprite.setTextureRect({319, 207, 67, 47});
                        break;
                    case 3:
                        _sprite.setTextureRect({386, 207, 61, 47});
                        break;
                    case 4:
                        _sprite.setTextureRect({451, 207, 57, 47});
                        break;
                    }
                    break;
                }
            }
            break;
        case PersonajeState::Move_up:
            _isMoving=true;
            _walk_frame+=0.1;
            _height_pixel=14;
            if(_walk_frame>=8)
            {
                _walk_frame=0;
            }
            _sprite.setTextureRect({81 + int(_walk_frame)*(28+36), 14, 30, 49});
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                _isMoving=false;
                _texture.loadFromFile("imagenes/Sprites/Caballero/Caballero_1-4/Lanza/Caballero_1_Lanza.png");
                _sprite.setTexture(_texture);
                _movePosition= {0,0};
                _attack_frame+=0.2;
                if(_attack_frame>=5)
                {
                    _attack_frame=0;
                }
                switch((int)_attack_frame)
                {
                case 0:
                    _sprite.setTextureRect({212, 0, 24, 64});
                    break;
                case 1:
                    _sprite.setTextureRect({277, 0, 24, 64});
                    break;
                case 2:
                    _sprite.setTextureRect({341, 0, 24, 64});
                    break;
                case 3:
                    _sprite.setTextureRect({405, 0, 24, 64});
                    break;
                case 4:
                    _sprite.setTextureRect({468, 0, 24, 64});
                    break;
                }
            }
            _sprite.move(_movePosition);
            break;
        case PersonajeState::Move_down:
            _isMoving=true;
            _height_pixel=142;
            _walk_frame+=0.1;
            if(_walk_frame>=8)
            {
                _walk_frame=0;
            }
            _sprite.setTextureRect({81 + int(_walk_frame)*(28+36), 142, 30, 49});
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                _isMoving=false;
                _texture.loadFromFile("imagenes/Sprites/Caballero/Caballero_1-4/Lanza/Caballero_1_Lanza.png");
                _sprite.setTexture(_texture);
                _movePosition= {0,0};
                _attack_frame+=0.2;
                if(_attack_frame>=5)
                {
                    _attack_frame=0;
                }
                switch((int)_attack_frame)
                {
                case 0:
                    _sprite.setTextureRect({210, 130, 27, 61});
                    break;
                case 1:
                    _sprite.setTextureRect({274, 130, 27, 61});
                    break;
                case 2:
                    _sprite.setTextureRect({338, 130, 27, 61});
                    break;
                case 3:
                    _sprite.setTextureRect({402, 130, 27, 61});
                    break;
                case 4:
                    _sprite.setTextureRect({466, 130, 27, 61});
                    break;
                }
            }
            _sprite.move(_movePosition);
            break;
        case PersonajeState::Move_x:
            _isMoving=true;
            _height_pixel=207;
            _walk_frame+=0.1;
            if(_walk_frame>=8)
            {
                _walk_frame=0;
            }
            _sprite.setTextureRect({80 + int(_walk_frame)*(28+36), 207, 29, 48});
            if(_movePosition.x<0)
            {
                _sprite.setScale(-1, 1);
            }
            else if(_movePosition.x>0)
            {
                _sprite.setScale(1, 1);

            }
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                _isMoving=false;
                _texture.loadFromFile("imagenes/Sprites/Caballero/Caballero_1-4/Lanza/Caballero_1_Lanza.png");
                _sprite.setTexture(_texture);
                _movePosition= {0,0};
                _attack_frame+=0.2;
                if(_attack_frame>=5)
                {
                    _attack_frame=0;
                }
                switch((int)_attack_frame)
                {
                case 0:
                    _sprite.setTextureRect({194, 207, 55, 47});
                    break;
                case 1:
                    _sprite.setTextureRect({256, 207, 62, 47});
                    break;
                case 2:
                    _sprite.setTextureRect({319, 207, 67, 47});
                    break;
                case 3:
                    _sprite.setTextureRect({386, 207, 61, 47});
                    break;
                case 4:
                    _sprite.setTextureRect({451, 207, 57, 47});
                    break;
                }
            }
            _sprite.move(_movePosition);
            break;
        }
        if (_isMoving)
        {
            if (!_soundPlaying)
            {
                _sound.play();
                _soundPlaying = true;
            }
        }
        else
        {
            if (_soundPlaying)
            {
                _sound.stop();
                _soundPlaying = false;
            }
        }

        position = {_sprite.getPosition()};
        updateHitboxPos();
    }
    else
    {
        _texture.loadFromFile("imagenes/Sprites/Caballero/Caballero_1-4/Dañado/Caballero_1_Dañado.png");
        _sprite.setTexture(_texture);
        _dead_frame+=0.1;
        if(_dead_frame>=12)
        {
            _muerto=true;
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
}

void Personaje::colision_mapa(sf::Vector2f posicion_valida)
{
    _sprite.setPosition(posicion_valida.x,posicion_valida.y);
}

void Personaje::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
//    target.draw(_bordeBarraVida, states);
//    target.draw(_barraVidaFondo, states);
//    target.draw(_barraVidaFrente, states);
}
sf::RectangleShape Personaje::getBarraVidaFondo()
{
    return _barraVidaFondo;
}
sf::RectangleShape Personaje::getBarraVidaFrente()
{
    return _barraVidaFrente;
}
sf::RectangleShape Personaje::getBarraVidaBorde()
{
    return _bordeBarraVida;
}
sf::RectangleShape Personaje::getBarraXpFondo()
{
    return _barraXpFondo;
}
sf::RectangleShape Personaje::getBarraXpFrente()
{
    return _barraXpFrente;
}
sf::RectangleShape Personaje::getBarraXpBorde()
{
    return _bordeBarraXp;
}
sf::Text Personaje::getTextVida()
{
    return text_vida;
}
sf::Text Personaje::getTextXp()
{
    return text_xp;
}

sf::Vector2f Personaje::returnPosition()
{
    return position;
}
sf::FloatRect Personaje::getBounds()const
{
    return _sprite.getGlobalBounds();
}
sf::FloatRect Personaje::getHitbox()const
{
    return _hitbox.getGlobalBounds();
}


///Animacion golpe con espada
/*switch(_state)
    {
    case PersonajeState::Idle:
        _sprite.setTextureRect({17, 142, 30, 48});
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            _texture.loadFromFile("imagenes/Sprites/Caballero/Caballero_1-4/Ataque/Caballero_1_Ataque.png");
            _sprite.setTexture(_texture);
            _movePosition= {0,0};
            _frame+=0.1;
            if(_frame>=5)
            {
                _frame=0;
            }
            switch((int)_frame)
            {
            case 0:
                _sprite.setTextureRect({82, 142, 26, 48});
                break;
            case 1:
                _sprite.setTextureRect({145, 142, 27, 48});
                break;
            case 2:
                _sprite.setTextureRect({212, 142, 26, 48});
                break;
            case 3:
                _sprite.setTextureRect({276, 142, 34, 48});
                break;
            case 4:
                _sprite.setTextureRect({339, 142, 44, 48});
                break;
            }
        }
        break;
    case PersonajeState::Move_up:
        _frame+=0.1;
        if(_frame>=8)
        {
            _frame=0;
        }
        _sprite.setTextureRect({81 + int(_frame)*(28+36), 14, 30, 49});
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            _texture.loadFromFile("imagenes/Sprites/Caballero/Caballero_1-4/Ataque/Caballero_1_Ataque.png");
            _sprite.setTexture(_texture);
            _movePosition= {0,0};
            _frame+=0.1;
            if(_frame>=5)
            {
                _frame=0;
            }
            switch((int)_frame)
            {
            case 0:
                _sprite.setTextureRect({83, 15, 25, 48});
                break;
            case 1:
                _sprite.setTextureRect({146, 15, 26, 48});
                break;
            case 2:
                _sprite.setTextureRect({211, 15, 26, 48});
                break;
            case 3:
                _sprite.setTextureRect({274, 15, 35, 48});
                break;
            case 4:
                _sprite.setTextureRect({338, 15, 38, 48});
                break;
            }
        }
        _sprite.move(_movePosition);
        break;
    case PersonajeState::Move_down:
        _frame+=0.1;
        if(_frame>=8)
        {
            _frame=0;
        }
        _sprite.setTextureRect({81 + int(_frame)*(28+36), 142, 30, 49});
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            _texture.loadFromFile("imagenes/Sprites/Caballero/Caballero_1-4/Ataque/Caballero_1_Ataque.png");
            _sprite.setTexture(_texture);
            _movePosition= {0,0};
            _frame+=0.1;
            if(_frame>=5)
            {
                _frame=0;
            }
            switch((int)_frame)
            {
            case 0:
                _sprite.setTextureRect({82, 142, 26, 48});
                break;
            case 1:
                _sprite.setTextureRect({145, 142, 27, 48});
                break;
            case 2:
                _sprite.setTextureRect({212, 142, 26, 48});
                break;
            case 3:
                _sprite.setTextureRect({276, 142, 34, 48});
                break;
            case 4:
                _sprite.setTextureRect({339, 142, 44, 48});
                break;
            }
        }
        _sprite.move(_movePosition);
        break;
    case PersonajeState::Move_x:
        _frame+=0.1;
        if(_frame>=8)
        {
            _frame=0;
        }
        _sprite.setTextureRect({80 + int(_frame)*(28+36), 207, 29, 48});
        if(_movePosition.x<0)
        {
            _sprite.setScale(-1, 1);
        }
        else if(_movePosition.x>0)
        {
            _sprite.setScale(1, 1);

        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            _texture.loadFromFile("imagenes/Sprites/Caballero/Caballero_1-4/Ataque/Caballero_1_Ataque.png");
            _sprite.setTexture(_texture);
            _movePosition= {0,0};
            _frame+=0.1;
            if(_frame>=5)
            {
                _frame=0;
            }
            switch((int)_frame)
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
        }
        _sprite.move(_movePosition);
        break;
    case PersonajeState::Attack:
        _texture.loadFromFile("imagenes/Sprites/Caballero/Caballero_1-4/Ataque/Caballero_1_Ataque.png");
        _sprite.setTexture(_texture);
        _frame+=0.15;
        if(_frame>=5)
        {
            _frame=0;
        }
        switch((int)_frame)
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
        break;
    }
    position = {_sprite.getPosition()};
}*/
