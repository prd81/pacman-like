#include "main.h"

#ifndef TRAMPO_H
#define TRAMPO_H


class Trampo {
public:
    Trampo() {}
    Trampo(color_t color);
    void draw(glm::mat4 VP);
    float bounce;
    float radius;
    float height;
    float width;
    glm::vec3 position;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // TRAMPO_H

