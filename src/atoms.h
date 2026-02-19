#pragma once
#include <iostream>
#include <vector>
#include <raylib.h>

class Particle 
{
    public:
        Vector2 position;
        Vector2 velocity;
        Vector2 acceleration;
        float mass;
        float charge;
        float radius;
        // trail points stored as vector of positions
        std::vector<Vector2> trails;
        Color color;
        void Display();
        void getTrails();
};

class Proton : public Particle
{
    public:
        Proton(Vector2 pos, float r, Vector2 vel);
        void Display(); 
};

class Neutron : public Particle
{
    public:
        Neutron(Vector2 pos, float r, Vector2 vel);
        void Display();
};

class Electron : public Particle
{
    public:
        Electron(Vector2 pos, float r, Vector2 vel);
        void Display();
};