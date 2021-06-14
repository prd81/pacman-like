#include "main.h"

#ifndef MAGNET_H
#define MAGNET_H


class Magnet {
public:
    Magnet() {}
    Magnet(float x,float y,float r,float R);
    void draw(glm::mat4 VP);
    void tick();
    float radius_int;
    float radius_ext;
    float rotation;
    int entry;
    int stay;
    float speed;
    float pull;
    int time;
    int act;
    glm::vec3 position;
    //bounding_box_t bounding_box();
private:
    VAO *object[3];
};

#endif // MAGNET_H



/*bounding_box_t Magnet::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, radius };
    return bbox;
}*/
