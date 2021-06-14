#include "main.h"
#include "ground.h"

Ground::Ground(color_t color) {
    color_t col[2] = {color, {153, 76, 0}};
    for(int i=0; i<2; ++i){
    GLfloat verbuff[18] = {
        -4.0f, -2.0f - i, 0.0f,
        4.0f, -2.0f - i, 0.0f,
        -4.0f, -3.0f - i, 0.0f,
        -4.0f, -3.0f - i, 0.0f,
        4.0f, -3.0f - i, 0.0f,
        4.0f, -2.0f - i, 0.0f,
    };
    this->object[i] = create3DObject(GL_TRIANGLES, 6, verbuff, col[i], GL_FILL);
    }
}

void Ground::draw(glm::mat4 VP) {
    glm::mat4 MVP = VP * glm::mat4(1.0f);
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    for(int i=0; i<2; ++i)
        draw3DObject(this->object[i]);
}

void Ground::show(glm::mat4 VP, int sc, float hl) {
    glm::mat4 MVP = VP * glm::mat4(1.0f);
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

    color_t BLACK = {0, 0, 0};
    float w = 0.05, x1 = -3, x2 = -1, y1 = -3.25, y2 = -3.75;
    GLfloat verbuff[18] = {
        x1 - w, y1 + w, 0.0f,
        x2 + w, y1 + w, 0.0f,
        x1 - w, y2 - w, 0.0f,
        x1 - w, y2 - w, 0.0f,
        x2 + w, y1 + w, 0.0f,
        x2 + w, y2 - w, 0.0f,
    };
    draw3DObject(create3DObject(GL_TRIANGLES, 6, verbuff, BLACK, GL_FILL));

    float g = std::max(hl/100.0, 0.0);
    float x0 = x1 + (x2 - x1) * g;
    color_t POWER = {(int)(255 * (1 - g)),(int)(255 * g), 0};
    GLfloat sidebuff[18] = {
        x1, y1, 0.0f,
        x0, y1, 0.0f,
        x1, y2, 0.0f,
        x1, y2, 0.0f,
        x0, y1, 0.0f,
        x0, y2, 0.0f,
    };
    draw3DObject(create3DObject(GL_TRIANGLES, 6, sidebuff, POWER, GL_FILL));

}
