#include <raylib.h>
#include <vector>
#include <cmath>
#include "atoms.h"

const float k = 5000.0f;
float G = 3.7e-17;

void setOrbit(Particle& orbiter, Particle& center)
{
    // Calculate distance components
    float dx = orbiter.position.x - center.position.x;
    float dy = orbiter.position.y - center.position.y;

    // Calculate distance
    float r = sqrt(dx*dx + dy*dy);

    // Calculate orbital velocity magnitude
    float v = sqrt(k * fabs(orbiter.charge * center.charge) / (orbiter.mass * r));


    // Calculate velocity components (perpendicular to radius vector)
    
    float vx = -dy / r * v;
    float vy = dx / r * v;
    
    // Set the orbiter's velocity
    orbiter.velocity = {vx, vy};
};


int main()
{
    // Main variables
    const int screenWidth = 1200;
    const int screenHeight = 900;

    // Sub atomic particles
    Proton proton({screenWidth/2.0f, screenHeight/2.0f}, 10.0f, {0.0f, 0.0f});
    Electron electron({screenWidth/2.0f + 500.0f, screenHeight/2.0f}, 5.0f, {0.0f,0.0f});
    
    setOrbit(electron, proton);

    std::vector<Particle> particles;
    particles.push_back(proton);
    particles.push_back(electron);
    
    // Initialize window
    InitWindow(screenWidth, screenHeight, "Atomic Sim");
    SetTargetFPS(60);

    // gameloop
    while (!WindowShouldClose())
    {
        // Time step
        float dt = GetFrameTime();

        // Reset acceleration
        for (auto &p : particles)
        {
            p.acceleration.x = 0;
            p.acceleration.y = 0;
        }

        // Physics
        for (int i = 0; i < particles.size(); i++)
        {
            for (int j = 0; j < particles.size(); j++)
            {
                // Skip if both i and j are same
                if (i == j)
                    continue;

                auto &p = particles[i];
                auto &q = particles[j];

                // Distance between particles
                float dx = p.position.x - q.position.x;
                float dy = p.position.y - q.position.y;

                // squared distance
                float distSq = dx * dx + dy * dy;

                // Distance
                float dist = sqrt(distSq);

                // Normalized direction vector
                float dirX = dx / dist;
                float dirY = dy / dist;

                // Calculate forces
                float elforce = k * p.charge * q.charge / distSq;
                float gravforce = G * p.mass * q.mass / distSq;

                // Main force
                float force = elforce + gravforce;

                // Convert to x and y components
                float forceX = force * dirX;
                float forceY = force * dirY;

                // Update acceleration
                p.acceleration.x += forceX / p.mass;
                p.acceleration.y += forceY / p.mass;

                q.acceleration.x -= forceX / q.mass;
                q.acceleration.y -= forceY / q.mass;
            }
        }

        // Update velocity and position
        for (auto &p : particles)
        {
            p.velocity.x += p.acceleration.x * dt;
            p.velocity.y += p.acceleration.y * dt;

            p.position.x += p.velocity.x * dt;
            p.position.y += p.velocity.y * dt;
        }
        // Collision
        for (int i = 0; i < particles.size(); i++)
        {
            for (int j = i + 1; j < particles.size(); j++)
            {
                // Skip if both i and j are same
                if (i == j)
                    continue;

                // refrence of particles
                auto &p = particles[i];
                auto &q = particles[j];

                if (CheckCollisionCircles(p.position, p.radius, q.position, q.radius))
                {
                    // Compute normal vector (collision direction)
                    Vector2 normal;
                    normal.x = p.position.x - q.position.x;
                    normal.y = p.position.y - q.position.y;

                    float distSq = normal.x * normal.x + normal.y * normal.y;
                    if (distSq == 0.0f)
                        continue; // prevent divide by zero

                    float dist = sqrt(distSq);

                    // Normalize normal vector
                    normal.x /= dist;
                    normal.y /= dist;

                    // Relative velocity
                    Vector2 relVel;
                    relVel.x = p.velocity.x - q.velocity.x;
                    relVel.y = p.velocity.y - q.velocity.y;

                    // Velocity along normal
                    float velAlongNormal = relVel.x * normal.x + relVel.y * normal.y;

                    // Do not resolve if moving apart
                    if (velAlongNormal > 0)
                        continue;

                    // Compute impulse scalar
                    float impulse = (2.0f * velAlongNormal) / (p.mass + q.mass);

                    // Apply impulse
                    p.velocity.x -= impulse * q.mass * normal.x;
                    p.velocity.y -= impulse * q.mass * normal.y;

                    q.velocity.x += impulse * p.mass * normal.x;
                    q.velocity.y += impulse * p.mass * normal.y;

                    // --- Position correction to prevent sinking ---
                    float overlap = (p.radius + q.radius) - dist;
                    if (overlap > 0)
                    {
                        float correction = overlap / (p.mass + q.mass);

                        p.position.x += correction * q.mass * normal.x;
                        p.position.y += correction * q.mass * normal.y;

                        q.position.x -= correction * p.mass * normal.x;
                        q.position.y -= correction * p.mass * normal.y;
                    }
                }
            }
        }    
        // Display
        BeginDrawing();
        ClearBackground(BLACK);

        // Display all objects with Trails
        for (int i = 0; i < particles.size(); i++)
        {
            particles[i].getTrails();
            particles[i].Display();
        }

        EndDrawing();
    }

    CloseWindow();
}