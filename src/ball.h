#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, color_t color, double rad);
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 acceleration;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    double gravity;
    double resist;
    double radius;
    int sides;
    int score;
    float health;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BALL_H
