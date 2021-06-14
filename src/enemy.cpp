#include "enemy.h"
#include "main.h"

Enemy::Enemy(float x, float y, color_t color, double rad, int t) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.01;
    radius = rad;
    sides = 64;
    tramp = t&1;

    int n = sides, i = 0, j = 0;
    double pi = (double)M_PI*2/n, ang = 0.00, r = radius;
    GLfloat verbuff[9*(n+2)] = {};
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

    int buff_size = 3*(n+2*tramp);

    if(tramp){
        float l = 3*r, w = r/2;

        GLfloat refbuff[18] = {
            r, l/2, 0.0f,
            r + w, l/2, 0.0f,
            r, -l/2, 0.0f,
            r, -l/2, 0.0f,
            r + w, l/2, 0.0f,
            r + w, -l/2, 0.0f
        };

        for(i=0;i<18;++i)
            verbuff[9*n+i] = refbuff[i];

        tramp_height = l/2;
        tramp_width = w;

    }

    this->object = create3DObject(GL_TRIANGLES, buff_size, verbuff, color, GL_FILL);
}

void Enemy::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    //rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Enemy::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Enemy::tick() {
    this->position.x -= speed;
}

bounding_box_t Enemy::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, radius };
    return bbox;
}
