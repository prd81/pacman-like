#include "main.h"
#include "window.h"

Window::Window(color_t color) {

    width = 0.05;

    float w = width;

    GLfloat verbuff[18] = {
        -4.0f, 4.0f, 0.0f,
        4.0f - w, 4.0f, 0.0f,
        -4.0f, 4.0f - w, 0.0f,
        -4.0f, 4.0f - w, 0.0f,
        4.0f - w, 4.0f, 0.0f,
        4.0f - w, 4.0f - w, 0.0f
    };

    this->object = create3DObject(GL_TRIANGLES, 6, verbuff, color, GL_FILL);
}

void Window::draw(glm::mat4 VP) {
    for(int i=0; i<4; ++i){
        glm::mat4 MVP = VP * glm::rotate ((float)M_PI*i/2,glm::vec3(0,0,1));
        glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
        draw3DObject(this->object);
    }
}
