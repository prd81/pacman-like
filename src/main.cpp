#include "main.h"
#include "timer.h"
#include "ball.h"
#include "enemy.h"
#include "ground.h"
#include "water.h"
#include "window.h"
#include "trampo.h"
#include "porc.h"
#include "magnet.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

const int bnum = 16;

Ball ball;
Enemy enemy[bnum];
Ground ground;
Water water;
Window wind;
Trampo trampo;
Porc porc[3];
Magnet magnet[2];

int last[2];
char buff[100], buffgo[100];

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;

Timer t60(1.0 / 250);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    // glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    // glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    // glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    // Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render

    for(int i=0; i<bnum; ++i)
        enemy[i].draw(VP);

    for(int i=0; i<3; ++i)
        porc[i].draw(VP);

    for(int i=0; i<2; ++i)
        magnet[i].draw(VP);

    trampo.draw(VP);
    ground.draw(VP);
    water.draw(VP);
    ball.draw(VP);
    wind.draw(VP);

    ground.show(VP, ball.score, ball.health);

}

void tick_input(GLFWwindow *window) {

    sprintf(buff,"PACMAN SCORE : %d HEALTH : %.2f",ball.score,ball.health);
    glfwSetWindowTitle(window, buff);

    double move = 0.05;

    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    int A = glfwGetKey(window, GLFW_KEY_A);
    int D = glfwGetKey(window, GLFW_KEY_D);

    if (A) {
        ball.position.x -= move;
    }
    else if (D) {
        ball.position.x += move;
    }
    else if (space && ball.velocity.y == 0) {
        ball.velocity.y = ball.speed;
        ball.acceleration.y = ball.gravity;
    }
    else if (down){
        ball.velocity.x = 0;
    }
    else if (left){
        ball.velocity.x -= move/10.0;
    }
    else if (right){
        ball.velocity.x += move/10.0;
    }
}

void tick_elements() {
    for(int i=0; i<2; ++i)
        magnet[i].tick();

    ball.tick();

    for(int i=0; i<3; ++i)
        porc[i].tick();

    ball.acceleration.x = (magnet[0].act * magnet[0].pull) + (magnet[1].act * magnet[1].pull);

    int f = 1, i, aqua = 0;
    bounding_box_t b = ball.bounding_box(), t = trampo.bounding_box(), w = water.bounding_box();

    for(i=0; i<bnum && f; ++i)
    {
        enemy[i].tick();

        if (detect_collision(b, enemy[i].bounding_box()) &&
            ball.velocity.y < 0)
        {
            if(enemy[i].tramp)
            {
                float theta = enemy[i].rotation;
                glm::vec3 normal = glm::vec3(cos((float)M_PI*theta/180),sin((float)M_PI*theta/180),0.0f);
                ball.velocity = glm::reflect(ball.velocity, normal);
            }
            else
            {
                ball.velocity.y = min(-2*ball.velocity.y,(float)ball.speed);
            }
            enemy[i].position.x = -5.0;
            f = 0;
            ball.score += (int)(enemy[i].radius * 100.0 * (1 + enemy[i].rotation/180.0));
        }
        float x = enemy[i].position.x;
        if (x <= -5.0)
        {
            x += max((int)enemy[last[i&1]].position.x - (int)x + 2, 6);
            enemy[i].position.x = x;
            last[i&1] = i;
        }
    }
    if (f && hypot(b.x - t.x, b.y - t.y) <= (t.r - b.r) && t.y > b.y &&
        ball.velocity.y < 0)
    {
            ball.velocity.y = 1.3*min(-2*ball.velocity.y,(float)ball.speed);
    }
    else if(f && hypot(b.x - w.x, b.y - w.y) <= (w.r - b.r)){
        ball.position.y = -2.0;
        aqua = 1;
        ball.resist = -0.02;
    }
    if (aqua){
        ball.position.y += water.speed * water.inc;
        water.frame += water.inc;
        if (abs(water.frame) == water.freq)
            water.inc *= -1;
    }
    else
    {
        water.frame = 0;
        ball.resist = -0.01;
        for (int i=0; i<3 && f; ++i)
        {
            bounding_box_t p = porc[i].bounding_box();
            if (hypot(p.x - b.x, p.y - b.y) <= (p.r + b.r)){
                ball.health = max(0.00, ball.health - 5.00 * p.r * porc[i].speed);
                //std::cout<<ball.health<<std::endl;
            }
        }
    }
}

color_t rgen(int l,int h){
    int c[3];
    for(int i=0; i<3; ++i)
        c[i] = rand()%(h-l+1) + l;
    return {c[0], c[1], c[2]};
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models


    //Enemy block generation

    srand(time(NULL));

    for(int i=0; i<bnum; i+=2)
    {
        for(int j=0; j<2; ++j)
        {
            int k = i + j;
            float ry = (float)rand()/RAND_MAX * 0.25 + j * 1.5;
            float rx = (float)rand()/RAND_MAX + i - 2;
            float rad = (float)rand()/RAND_MAX * 0.1 + 0.2;

            enemy[k] = Enemy(rx, ry, rgen(50,150), rad, rand());
            enemy[k].rotation = enemy[k].tramp * ((double)120 * rand() / RAND_MAX + 30);
        }
    }
    last[1] = bnum - 1, last[0] = bnum -2;

    // Initialized elements : Ball

    ball = Ball(-3, -2, {250, 0, 0}, 0.2);

    // Initialized elements : Porcupines

    porc[0] = Porc(-1, -3, rgen(0,255), 0.3, 0.01);

    porc[1] = Porc(-1.5, -3, rgen(0,255), 0.25, 0.015);
    porc[1].entry *= 2, porc[1].stay /= 2, porc[1].freq /= 2;

    porc[2] = Porc(-1, -3, rgen(0,255), 0.35, 0.02);
    porc[2].entry *= 3, porc[2].stay /= 3, porc[2].freq /= 2;

    // Initialized elements : trampoline

    trampo = Trampo({50, 50, 50});

    // Initialized elements : Magnets

    magnet[0] = Magnet(-5, 3, 0.2, 0.5);

    magnet[1] = Magnet(5, 3, 0.2, 0.5);
    magnet[1].pull *= -1, magnet[1].rotation *= -1, magnet[1].speed *= -1;
    magnet[1].time = -1.5 * magnet[1].entry, magnet[1].entry *= 1.2;

    // Initialized elements : Ground

    ground = Ground({20, 250, 20});

    // Initialized elements : Water

    water = Water({50, 50, 250});

    // Initialized elements : Frame

    wind = Window({0, 0, 0});



    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 800;
    int height = 800;

    int go = 0;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);
            if (ball.health)
            {
                tick_elements();
                tick_input(window);
            }
            else if(!go)
            {
                sprintf(buffgo,"PACMAN SCORE : %d GAME-OVER",ball.score);
                glfwSetWindowTitle(window, buffgo);
                go = 1;
            }
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return hypot(a.x - b.x, a.y - b.y) <= (a.r + b.r) && a.y > b.y;
    //return abs(hypot(a.x - b.x, a.y - b.y) - (a.r + b.r)) <= 0.001 ;
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
