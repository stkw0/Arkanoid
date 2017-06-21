#pragma once

#include "../GDCore/Scene.h"
#include "Ball.h"
#include "Brick.h"
#include "ButtonState.h"
#include "Paddle.h"

class TestScene : public GDES::Scene {
  public:
    TestScene();
    ~TestScene();

    void Initialize();

  private:
    void CreateBricks();

  private:
    std::vector<Brick*> brickList;
};