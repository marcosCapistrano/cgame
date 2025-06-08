#include <stdio.h>
#include "body.h"
#include "raymath.h"

void Physics_NewCircleBody(CircleBody *body, float posX, float posY, float radius, float mass)
{
    *body = (CircleBody){0}; 

    body->radius = radius;

    body->position.x = posX;
    body->position.y = posY; 

    body->velocity = (Vector2){0};
    body->acceleration = (Vector2){0};
    body->forces = (Vector2){0};
    body->invMass = 1.0f / mass;

    body->rotation = 0;
    body->angularVelocity = 0;
    body->angularAcceleration = 0;
    body->torques = 0;

    float I = (1.0f / 2.0f) * radius * radius * mass;
    body->invI = 1.0f/I;
}

void Physics_IntegrateLinearCircle(CircleBody *body, float deltaTime)
{
    body->acceleration = Vector2Scale(body->forces, body->invMass); 
    body->velocity = Vector2Add(body->velocity, Vector2Scale(body->acceleration, deltaTime)); 
    body->position = Vector2Add(body->position, Vector2Scale(body->velocity, deltaTime)); 

    body->forces = Vector2Zero();
}

void Physics_IntegrateAngularCircle(CircleBody *body, float deltaTime)
{
    body->angularAcceleration = body->torques * body->invI; 
    body->angularVelocity += body->angularAcceleration * deltaTime;
    body->rotation += body->angularVelocity * deltaTime;

    printf("frontwheel physics: %f %f %f %f\n", body->torques, body->angularAcceleration, body->angularVelocity, body->rotation);

    body->torques = 0;
}

void Physics_UpdateCircle(CircleBody *body, float deltaTime)
{
    Physics_IntegrateLinearCircle(body, deltaTime);
    Physics_IntegrateAngularCircle(body, deltaTime);
}