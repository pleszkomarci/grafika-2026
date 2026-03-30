#ifndef BALL_H
#define BALL_H

/**
 * Ball position, speed, size and rotation
 */
typedef struct Ball
{
    float x;
    float y;
    float radius;
    float speed_x;
    float speed_y;
    float rotation_angle;
    float rotation_speed;
} Ball;

/**
 * Move the ball to the given position.
 */
void init_ball(Ball* ball, float x, float y);

/**
 * Update the ball position and rotation.
 * @param time elapsed time in seconds.
 */
void update_ball(Ball* ball, double time);

/**
 * Render the ball with rotation effect.
 */
void render_ball(Ball* ball);

/**
 * Change the radius of the ball within limits.
 */
void change_ball_radius(Ball* ball, float amount); // ÚJ

/**
 * Modify rotation speed on collision.
 */
void update_rotation_on_bounce(Ball* ball); // ÚJ

#endif /* BALL_H */