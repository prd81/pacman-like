#include "main.h"

#ifndef WINDOW_H
#define WINDOW_H


class Window {
public:
    Window() {}
    Window(color_t color);
    void draw(glm::mat4 VP);
    float width;
    //bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // WINDOW_H



/*bounding_box_t Window::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, radius };
    return bbox;
}*/
