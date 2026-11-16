#pragma once

class Creature
{
public:
    int health;
    int energy;
    int age;

    int x;
    int y;

    Creature();

    void Move();
    void Sleep();
    void Update();
};