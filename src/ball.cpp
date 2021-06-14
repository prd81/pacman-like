#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y, color_t color, double rad) {
    this->position = glm::vec3(x, y, 0);
    this->velocity = glm::vec3(0, 0, 0);
    this->acceleration = glm::vec3(0, 0, 0);
    this->rotation = 0;
    speed = 0.24;
    gravity = -0.01;
    resist = -0.01;
    radius = rad;
    sides = 64;

    score = 0;
    health = 100.0;

    int n = sides, i = 0, j = 0;
    double pi = (double)M_PI*2/n, ang = 0.00, r = radius;
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

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    //rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tick() {
    float r = this->radius, k = this->resist;

    float posx = this->position.x, posy = this->position.y;

    float velx = this->velocity.x, vely = this->velocity.y;

    float accx = this->acceleration.x + k*velx;
    float accy = this->acceleration.y + k*vely;

    this->position.x += velx + 0.5*accx;
    this->velocity.x += accx;

    this->position.y += vely + 0.5*accy;
    this->velocity.y += accy;

    if(posy <= -2.0 + r)
    {
        this->acceleration.y = 0;
        this->velocity.y = 0;
        this->position.y = -2.0 + r;
    }
    else if(posy >= 4.0 - r)
    {
        this->position.y = 4.0 - r;
        this->velocity.y *= -0.8;
        this->health = std::max(0.00, this->health - 2.00 * vely);
    }
    if(posx <= -4.0 + r)
    {
        this->position.x = -4.0 + r;
        this->velocity.x *= -0.5;
        this->health = std::max(0.00, this->health + 5.00 * velx);
    }
    else if(posx >= 4.0 - r)
    {
        this->position.x = 4.0 - r;
        this->velocity.x *= -0.5;
        this->health = std::max(0.00, this->health - 5.00 * velx);
    }
}

bounding_box_t Ball::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, radius };
    return bbox;
}
