#include "main.h"

#ifndef PORC_H
#define PORC_H


class Porc {
public:
    Porc() {}
    Porc(float x,float y,color_t color, float h, float v);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void tick();
    float speed;
    float height;
    int frame;
    int inc;
    int entry;
    int stay;
    int time;
    int freq;

    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // PORC_H


