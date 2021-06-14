#include "main.h"

#ifndef WATER_H
#define WATER_H


class Water {
public:
    Water() {}
    Water(color_t color);
    float radius;
    float speed;
    int frame;
    int inc;
    int freq;
    glm::vec3 position;
    void draw(glm::mat4 VP);
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // WATER_H

