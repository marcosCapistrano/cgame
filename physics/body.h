#ifndef BODY_H
#define BODY_H

#include "raymath.h"

typedef struct CircleBody
{
    float radius;

    /* linear */
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;

    Vector2 forces;
    float invMass;

    /* angular */
    float rotation;
    float angularVelocity;
    float angularAcceleration;

    float torques;
    float invI;
} CircleBody;

typedef struct BoxBody
{
    int width;
    int height;

    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;

    Vector2 forces;
    float invMass;
} BoxBody;

void Physics_NewCircleBody(CircleBody *body, float posX, float posY, float radius, float mass);

void Physics_IntegrateLinearCircle(CircleBody *body, float deltaTime);
void Physics_IntegrateAngularCircle(CircleBody *body, float deltaTime);
void Physics_UpdateCircle(CircleBody *body, float deltaTime);

#endif