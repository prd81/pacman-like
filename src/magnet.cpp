#include "main.h"
#include "magnet.h"

Magnet::Magnet(float x, float y, float r, float R) {
    radius_int = r;
    radius_ext = R;

    position = glm::vec3 (x, y, 0);
    rotation = -135.0f;

    entry = 4000;
    speed = 0.05;
    stay = 400;
    time = 0;

    act = 0;
    pull = -0.001;

    int n = 32, i, j, k;
    float pi = M_PI/n, ang;
    float rad[2] = {radius_int, radius_ext};
    color_t col[] = {COLOR_BACKGROUND, {250, 50, 50}};

    GLfloat verbuff[9*n] = {};

    for(k = 0; k<2; ++k)
    {
        for(i = 0, j = 0, ang = M_PI; i<n; ++i, j += 9){
            verbuff[j+0] = 0.0f;
            verbuff[j+1] = 0.0f;
            verbuff[j+2] = 0.0f;
            verbuff[j+3] = rad[k]*cos(ang);
            verbuff[j+4] = rad[k]*sin(ang);
            verbuff[j+5] = 0.0f;
            ang += pi;
            verbuff[j+6] = rad[k]*cos(ang);
            verbuff[j+7] = rad[k]*sin(ang);
            verbuff[j+8] = 0.0f;
        }
        this->object[k] = create3DObject(GL_TRIANGLES, 3*n, verbuff, col[k], GL_FILL);
    }
    GLfloat sidebuff[36] = {
        r, 0.0f, 0.0f,
        r, R - r, 0.0f,
        R, R - r, 0.0f,
        r, 0.0f, 0.0f,
        R, 0.0f, 0.0f,
        R, R - r, 0.0f,
        -r, 0.0f, 0.0f,
        -r, R - r, 0.0f,
        -R, R - r, 0.0f,
        -r, 0.0f, 0.0f,
        -R, 0.0f, 0.0f,
        -R, R - r, 0.0f,
    };
    this->object[k] = create3DObject(GL_TRIANGLES, 12, sidebuff, {200,200,200}, GL_FILL);
}

void Magnet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    for(int i = 2; i>=0; --i){
        draw3DObject(this->object[i]);
    }
}

void Magnet::tick() {
    if (time == entry){
        position.x += speed;
        if (abs(position.x) <= 3.0) time++;
    }
    else if (time > entry)
    {
        if (time == entry + stay)
        {
            position.x -= speed;
            if (abs(position.x) >= 5.0)
            {
                act = 0;
                time = 0;
            }
        }
        else
        {
            act = 1;
            time++;
        }
    }
    else time++;
}
