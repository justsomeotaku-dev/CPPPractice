#include "raylib.h"
#include <cmath>
#include <vector>

struct Ship{
    Vector2 position;
    Vector2 velocity;
    float rotation;
};

struct Bullet{
    Vector2 position;
    Vector2 velocity;
    float rotation;
    float lifeTime;
};

std::vector<Bullet> bullets;
float elapsedTime = 0.0f;

// rotation formula
Vector2 rotatePoint(Vector2 vector, float rotation){
    return {
        vector.x * cosf(rotation) - vector.y * sinf(rotation),
        vector.x * sinf(rotation) + vector.y * cosf(rotation)
    };
}

int main(int argc, char const *argv[])
{
    SetConfigFlags(FLAG_MSAA_4X_HINT);

    Ship ship{
        {200,200},
        {0,0},
        0.0f
    };

    // local coordiantes of the 3 points
    Vector2 localFront = {0,-40};
    Vector2 localLeft = {-20,20};
    Vector2 localRight = {20,20};

    const int screenWidth = 800;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Asteroids");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // calculates the position of the 3 points using the rotation formula, ship rotation and adds the norm of the ship position
        Vector2 front = {
        rotatePoint(localFront, ship.rotation).x + ship.position.x,
        rotatePoint(localFront, ship.rotation).y + ship.position.y,
        };
        Vector2 left = {
            rotatePoint(localLeft, ship.rotation).x + ship.position.x,
            rotatePoint(localLeft, ship.rotation).y + ship.position.y,
        };
        Vector2 right = {
            rotatePoint(localRight, ship.rotation).x + ship.position.x,
            rotatePoint(localRight, ship.rotation).y + ship.position.y,
        };

        // checks input

        if (IsKeyDown(KEY_RIGHT)) ship.rotation += 0.1f;
        if (IsKeyDown(KEY_LEFT)) ship.rotation -= 0.1f;

        // takes a new vector: cos 0 sin 1, which points up, then rotates it so value 0-1
        Vector2 forward = rotatePoint({0,-1},ship.rotation);
        if (IsKeyDown(KEY_UP)){
            ship.velocity.x += forward.x * 0.1f;
            ship.velocity.y += forward.y * 0.1f;
        } 

        if (IsKeyPressed(KEY_SPACE) && bullets.size() < 4){
            bullets.push_back(Bullet{
                {front.x,front.y},
                {0,0},
                {ship.rotation}
            });
        }

        // adds the velocity to the position, but 0.98 to avoid infinite velocity
        ship.velocity.x *= 0.98f;
        ship.velocity.y *= 0.98f;
        ship.position.x += ship.velocity.x;
        ship.position.y += ship.velocity.y;

        // basic screen wraparound logic
        if (ship.position.x < 0) ship.position.x = screenWidth;
        if (ship.position.y < 0) ship.position.y = screenHeight;
        if (ship.position.x > screenWidth) ship.position.x = 0;
        if (ship.position.y > screenHeight) ship.position.y = 0;

        for (Bullet& b : bullets){
                Vector2 forwardB = rotatePoint({0,-1},b.rotation);
                b.velocity.x = forwardB.x * 5.0f;
                b.velocity.y = forwardB.y * 5.0f;
                b.position.x += b.velocity.x;
                b.position.y += b.velocity.y;

                if(b.lifeTime >= 1.0f){
                    bullets.erase(bullets.begin());
                }
        }

        BeginDrawing();
            ClearBackground(WHITE);
            // drawing the ship manually, since DrawTriangleLines doesn't have a thickness
            DrawLineEx(front, left, 4, BLACK); 
            DrawLineEx(left, right, 4, BLACK);
            DrawLineEx(right, front, 4, BLACK);

            // bullets
            for (Bullet& b : bullets){
                DrawCircleV(b.position,3.0f, BLACK);
                b.lifeTime += GetFrameTime();
            }
            elapsedTime += GetFrameTime();
            DrawText(TextFormat("Time Elapsed: %0.2f",elapsedTime),20,20,20,LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
