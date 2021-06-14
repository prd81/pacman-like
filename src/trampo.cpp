#include "main.h"
#include "trampo.h"

Trampo::Trampo(color_t color) {
    radius = 0.6;
    height = 0.75;
    width = 0.06;

    float h = height, w = width;
    
    position = glm::vec3(3, -2+h, 0);

    int n = 32, i = 0, j = 0;
    float pi = M_PI/n, ang = M_PI, r = radius;
    GLfloat verbuff[9*(n+4)] = {};
    
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

    GLfloat sidebuff[36] = {
        -r-w, 0.0f, 0.0f,
        -r-w, -h, 0.0f,
        -r, 0.0f, 0.0f,
        -r-w, -h, 0.0f,
        -r, 0.0f, 0.0f,
        -r, -h, 0.0f,
        r+w, 0.0f, 0.0f,
        r+w, -h, 0.0f,
        r, 0.0f, 0.0f,
        r+w, -h, 0.0f,
        r, 0.0f, 0.0f,
        r, -h, 0.0f,
    };

    for(i=0;i<36;++i)
        verbuff[9*n+i]=sidebuff[i];

    this->object = create3DObject(GL_TRIANGLES, 3*(n+4), verbuff, color, GL_FILL);
}

void Trampo::draw(glm::mat4 VP) {
    glm::mat4 MVP = VP * glm::translate (position);

    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

bounding_box_t Trampo::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, radius };
    return bbox;
}
