#include "scene.h"

#include <SDL2/SDL.h>

#include <math.h>

#include <GL/gl.h>

void init_scene(Scene* scene)
{
    scene->rotation = 0.0;
}

void update_scene(Scene* scene)
{
    static double last_time = 0;
    double current_time = (double)SDL_GetTicks() / 1000.0;
    double elapsed = current_time - last_time;
    last_time = current_time;

    scene->rotation += 50.0 * elapsed;
}

void render_scene(const Scene* scene)
{
    draw_origin();
    draw_checkerboard();
    draw_triangle();
    draw_sphere(scene->rotation);
    draw_cylinder_and_cone();

}

void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();
}

void draw_checkerboard()
{
    int i, j;
    int size = 10; // 10x10 table
    float step = 0.1f; // to make sure there are 10 pieces

    glBegin(GL_QUADS);
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            if ((i + j) % 2 == 0) glColor3f(0.2f, 0.2f, 0.2f); //black piece
            else glColor3f(0.8f, 0.8f, 0.8f); //light piece

            glVertex3f(i * step, j * step, 0.0f);
            glVertex3f((i + 1) * step, j * step, 0.0f);
            glVertex3f((i + 1) * step, (j + 1) * step, 0.0f);
            glVertex3f(i * step, (j + 1) * step, 0.0f);
        }
    }
    glEnd();
}

void draw_triangle()
{
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(0.2f, 0.2f, 0.5f);
    
    glColor3f(0.0, 1.0, 1.0);
    glVertex3f(0.8f, 0.2f, 0.5f);
    
    glColor3f(1.0, 0.0, 1.0);
    glVertex3f(0.5f, 0.8f, 0.5f);
    glEnd();
}

void draw_sphere(float rotation)
{
    glPushMatrix();
    glTranslatef(0.5f, 0.5f, 0.8f); // Put inside the cube
    glRotatef(rotation, 0, 0, 1);  
    glColor3f(0.5f, 0.5f, 0.5f);

    int lats = 10; // Small tesselation
    int longs = 10;
    for (int i = 0; i <= lats; i++) {
        double lat0 = M_PI * (-0.5 + (double)(i - 1) / lats);
        double z0 = sin(lat0);
        double zr0 = cos(lat0);

        double lat1 = M_PI * (-0.5 + (double)i / lats);
        double z1 = sin(lat1);
        double zr1 = cos(lat1);

        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= longs; j++) {
            double lng = 2 * M_PI * (double)(j - 1) / longs;
            double x = cos(lng);
            double y = sin(lng);
            glVertex3f(x * zr0 * 0.1, y * zr0 * 0.1, z0 * 0.1);
            glVertex3f(x * zr1 * 0.1, y * zr1 * 0.1, z1 * 0.1);
        }
        glEnd();
    }
    glPopMatrix();
}

void draw_cylinder_and_cone()
{
    int segments = 12;
    float r = 0.1f, h = 0.2f;

    // cylinder
    glPushMatrix();
    glTranslatef(0.2f, 0.8f, 0.0f);
    glBegin(GL_TRIANGLE_STRIP);
    for(int i = 0; i <= segments; i++) {
        float angle = i * 2.0 * M_PI / segments;
        glVertex3f(r * cos(angle), r * sin(angle), 0);
        glVertex3f(r * cos(angle), r * sin(angle), h);
    }
    glEnd();
    glPopMatrix();

    // cone
    glPushMatrix();
    glTranslatef(0.8f, 0.8f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0, 0, h); // Kúp csúcsa
    for(int i = 0; i <= segments; i++) {
        float angle = i * 2.0 * M_PI / segments;
        glVertex3f(r * cos(angle), r * sin(angle), 0);
    }
    glEnd();
    glPopMatrix();
}
