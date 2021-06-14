#include "main.h"
#include "water.h"

Water::Water(color_t color) {

    radius = 0.7;
    speed = 0.02;
    frame = 0;
    inc = 1;
    freq = 4;
    position = glm::vec3(0.5,-2,0);

    int n = 32, i = 0, j = 0;
    float pi = M_PI/n, ang = M_PI, r = radius;
    GLfloat verbuff[9*n] = {};
    
    for(; i<n; ++i, j += 9){
        verbuff[j+0] = 0.0f;
        verbuff[j+1] = 0.0f;
        verbuff[j+2] = 0.0f;
        verbuff[j+3] = r*cos(ang);
        verbuff[j+4] = r*sin(ang);
        verbuff[j+5] = 0.0f;
        ang += pi;
        verbuff[j+6] = r*cos(ang);
        verbuff[j+7] = r*sin(ang);
        verbuff[j+8] = 0.0f;
    }

    this->object = create3DObject(GL_TRIANGLES, 3*n, verbuff, color, GL_FILL);
}

void Water::draw(glm::mat4 VP) {
    glm::mat4 MVP = VP * glm::translate (position);      //glm::mat4(1.0f);;
    
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

bounding_box_t Water::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, radius };
    return bbox;
}
