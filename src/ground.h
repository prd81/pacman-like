#include "main.h"

#ifndef GROUND_H
#define GROUND_H


class Ground {
public:
    Ground() {}
    Ground(color_t color);
    void draw(glm::mat4 VP);
    void show(glm::mat4 VP, int sc, float hl);
    //bounding_box_t bounding_box();
private:
    VAO *object[2];
};

#endif // GROUND_H



/*bounding_box_t Ground::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, radius };
    return bbox;
}*/
