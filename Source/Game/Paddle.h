#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <math.h>
#include <random>

#include "../GDCore/Entity.h"
#include "Arkanoid.h"
#include "Ball.h"
#include "ButtonState.h"
#include "Paddle.h"

class Paddle : public GDES::Entity {

  public:
    Paddle(Ball* ball);
    ~Paddle();

    virtual void LoadContent() override;
    virtual void Update(sf::Time elapsedTime) override;
    virtual void Draw(sf::RenderWindow* window) override;

  private:
    // movimiento
    const float TAU = 0.3f;
    const float LIMIT_SPEED = 500;
    float speed;
    float moveTime;
    float initialSpeed;

    // limites en pantalla
    float limitLeft = 20;
    float limitRight = 0;

    // tamaño raqueta
    unsigned width = 120;
    unsigned height = 20;

    sf::RectangleShape rectangle;
    sf::Vector2f position;

    // objetos para controlar la duración de las pulsaciones
    ButtonState* sLeft;
    ButtonState* sRight;

    // cosas raras
    Ball* ball;
    std::default_random_engine generator;

    // metodos privados
    void Speed(float speedlimit, float tau);
};
