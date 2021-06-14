#include "main.h"

#ifndef ENEMY_H
#define ENEMY_H


class Enemy {
public:
    Enemy() {}
    Enemy(float x, float y, color_t color, double rad,int t);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    double radius;
    int sides;
    int tramp;
    double tramp_width;
    double tramp_height;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // ENEMY_H
