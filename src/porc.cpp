#include "main.h"
#include "porc.h"

Porc::Porc(float x, float y,color_t color,float h, float v) {
    position = glm::vec3(x, y, 0);
    height = h;
    speed = v;
    frame = 0;
    inc = 1;
    freq = 20;
    entry = 3000;
    stay = 1500;
    time = 0;

    GLfloat verbuff[27] = {
        -h, 0.0f, 0.0f,
        -h/2, 2*h, 0.0f,
        0.0f, 0.0f, 0.0f,
        h, 0.0f, 0.0f,
        h/2, 2*h, 0.0f,
        0.0f, 0.0f, 0.0f,
        -h/2, 0.0f, 0.0f,
        h/2, 0.0f, 0.0f,
        0.0f, 2.5f*h, 0.0f
    };

    this->object = create3DObject(GL_TRIANGLES, 9, verbuff, color, GL_FILL);
}

void Porc::draw(glm::mat4 VP) {
    glm::mat4 MVP = VP * glm::translate(position);

    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Porc::tick() {
    if (time == entry){
        position.y += speed;
        if (position.y >= -2.0) time++;
    }
    else if (time > entry)
    {
        if (time == entry + stay)
        {
            position.y -= speed;
            if (position.y <= -3.0) time = 0;
        }
        else
        {
            position.x += speed*inc;
            frame += inc;
            if (abs(frame) == freq)
                inc *= -1;
            time++;
        }
    }
    else time++;
}

bounding_box_t Porc::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, height };
    return bbox;
}
