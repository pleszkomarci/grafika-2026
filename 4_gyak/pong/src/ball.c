#include "ball.h"
#include <GL/gl.h>
#include <math.h>

void init_ball(Ball* ball, float x, float y) {
    ball->x = x; ball->y = y;
    ball->radius = 30;
    ball->speed_x = 300; ball->speed_y = 300;
    ball->rotation_angle = 0;
    ball->rotation_speed = 100;
}

void update_ball(Ball* ball, double time) {
    ball->x += ball->speed_x * time;
    ball->y += ball->speed_y * time;
    ball->rotation_angle += ball->rotation_speed * time;
}

void render_ball(Ball* ball) {
    glPushMatrix();
    glTranslatef(ball->x, ball->y, 0.0);
    glRotatef(ball->rotation_angle, 0, 0, 1);

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0, 0);
    for (double a = 0; a <= 2.0 * M_PI + 0.2; a += 0.4) {
        if ((int)(a * 3) % 2 == 0) glColor3f(1.0, 0.5, 0.0); // rotation with random color
        else glColor3f(1.0, 0.9, 0.8);
        glVertex2f(cos(a) * ball->radius, sin(a) * ball->radius);
    }
    glEnd();
    glPopMatrix();
}

void change_ball_radius(Ball* ball, float amount) {
    ball->radius += amount;
    if (ball->radius < 5) ball->radius = 5;
    if (ball->radius > 100) ball->radius = 100;
}

void update_rotation_on_bounce(Ball* ball) {
    ball->rotation_speed *= -1.3;
    if (ball->rotation_speed > 1000) ball->rotation_speed = 1000;
}