#include <iostream>
#include <vector>
#include <raylib.h>
#include "atoms.h"

Proton::Proton(Vector2 pos, float r, Vector2 vel)
{
    this->position = pos;
    this->mass = 1.0f;
    this->charge = 1.0f;
    this->radius = r;
    this->velocity = vel;
    this->color = RED;
};

Neutron::Neutron(Vector2 pos, float r, Vector2 vel)
{
    this->position = pos;
    this->mass = 1.0014f;
    this->charge = 0.0f;
    this->radius = r;
    this->velocity = vel;
    this->color = GREEN;
};

Electron::Electron(Vector2 pos, float r, Vector2 vel)
{
    this->position = pos;
    this->mass = 1.0f / 1837.0f;
    this->charge = -1.0f;
    this->radius = r;
    this->velocity = vel;
    this->color = BLUE;
};

void Particle::Display()
{
    DrawCircleV(this->position, this->radius, this->color);
}

void Proton::Display()
{
    DrawCircle((int)this->position.x, 
    (int)this->position.y, this->radius, color);
}

void Neutron::Display()
{
    DrawCircle((int)this->position.x, 
    (int)this->position.y, this->radius, color);
}

void Electron::Display()
{
    DrawCircle((int)this->position.x, 
    (int)this->position.y, this->radius, color);
}

void Particle::getTrails()
{

    this->trails.push_back(this->position);

   
    if (this->trails.size() > 450)
    {
        this->trails.erase(this->trails.begin());
    }

    for (size_t i = 0; i < this->trails.size(); ++i)
    {
        float alpha = (float)i / (float)this->trails.size();
        Color c = Fade(this->color, alpha);
        DrawPixelV(this->trails[i], c);
    }
}