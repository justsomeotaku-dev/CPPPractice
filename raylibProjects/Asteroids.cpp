#include "raylib.h"
#include <cmath>
#include <vector>
#include <cstdlib>
#include <ctime>

struct Ship
{
    Vector2 position;
    Vector2 velocity;
    float rotation;
};

struct Bullet
{
    Vector2 position;
    Vector2 velocity;
    float lifeTime;
    float radius;
};

struct Asteroid
{
    Vector2 position;
    Vector2 velocity;
    float radius;
};

// local coordiantes of the 3 points
const Vector2 localFront = {0, -40};
const Vector2 localLeft = {-20, 20};
const Vector2 localRight = {20, 20};

std::vector<Asteroid> asteroids;
std::vector<Bullet> bullets;
float elapsedTime = 0.0f;
float asteroidTimer = 0.0f;
bool gameOver;

// rotation formula
Vector2 rotatePoint(Vector2 vector, float rotation)
{
    return {
        vector.x * cosf(rotation) - vector.y * sinf(rotation),
        vector.x * sinf(rotation) + vector.y * cosf(rotation)};
}

void CheckWraparound(Vector2 &position, int screenWidth, int screenHeight)
{
    if (position.x < 0)
        position.x = screenWidth;
    if (position.y < 0)
        position.y = screenHeight;
    if (position.x > screenWidth)
        position.x = 0;
    if (position.y > screenHeight)
        position.y = 0;
}

bool CircleCollision(Vector2 p1, float r1, Vector2 p2, float r2)
{
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;

    return dx * dx + dy * dy <= (r1 + r2) * (r1 + r2);
}

Asteroid SpawnAsteroid(int screenWidth, int screenHeight)
{
    Asteroid a;
    int side = rand() % 4; // 0-3
    float angle = 0.0f;
    switch (side)
    {
    case 0: // Top
        a.position = {(float)(rand() % screenWidth), 0.0f};
        angle = (float)PI / 2.0f;
        break;
    case 1: // Right
        a.position = {(float)(screenWidth), (float)(rand() % screenHeight)};
        angle = (float)PI;
        break;
    case 2: // Bottom
        a.position = {(float)(rand() % screenWidth), (float)screenHeight};
        angle = ((float)PI * 3.0f) / 2.0f;
        break;
    case 3: // Left
        a.position = {0.0f, (float)(rand() % screenHeight)};
        angle = 0.0f;
        break;
    }

    float spread = (((float)rand() / (float)RAND_MAX) - 0.5) * (PI / 3); // 0.5 centered around 0, pi/3 = 60% = +-30%
    angle += spread;
    float speed = 2.0f;

    a.velocity = {
        cosf(angle) * speed,
        sinf(angle) * speed};

    a.radius = 50.0f;

    return a;
}

void HandleInput(Ship &ship, Vector2 front, Vector2 left, Vector2 right)
{

    if (IsKeyDown(KEY_RIGHT))
        ship.rotation += 0.1f;
    if (IsKeyDown(KEY_LEFT))
        ship.rotation -= 0.1f;

    // takes a new vector: cos 0 sin 1, which points up, then rotates it so value 0-1
    Vector2 forward = rotatePoint({0, -1}, ship.rotation);
    if (IsKeyDown(KEY_UP))
    {
        ship.velocity.x += forward.x * 0.1f;
        ship.velocity.y += forward.y * 0.1f;
    }

    if (IsKeyPressed(KEY_SPACE) && bullets.size() < 4)
    {
        Vector2 forwardB = rotatePoint({0, -1}, ship.rotation);
        bullets.push_back(Bullet{
            {front.x, front.y},
            {forwardB.x * 5.0f, forwardB.y * 5.0f},
            0.0f,
            4.0f});
    }
}

int main(int argc, char const *argv[])
{
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    srand(time(nullptr));

    Ship ship{
        {200, 200},
        {0, 0},
        0.0f};

    const int screenWidth = 800;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Asteroids");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // calculates the position of the 3 points using the rotation formula, ship rotation and adds the norm of the ship position
        Vector2 rotatedLocalFront = rotatePoint(localFront, ship.rotation);
        Vector2 front = {
            rotatedLocalFront.x + ship.position.x,
            rotatedLocalFront.y + ship.position.y,
        };

        Vector2 rotatedLocalLeft = rotatePoint(localLeft, ship.rotation);
        Vector2 left = {
            rotatedLocalLeft.x + ship.position.x,
            rotatedLocalLeft.y + ship.position.y,
        };

        Vector2 rotatedLocalRight = rotatePoint(localRight, ship.rotation);
        Vector2 right = {
            rotatedLocalRight.x + ship.position.x,
            rotatedLocalRight.y + ship.position.y,
        };

        // adds the velocity to the position, but 0.98 to avoid infinite velocity
        if (!gameOver)
        {
            HandleInput(ship, front, left, right);

            asteroidTimer += GetFrameTime();
            if (asteroidTimer >= 2.0f)
            {
                asteroids.push_back(SpawnAsteroid(screenWidth, screenHeight));
                asteroidTimer = 0.0f;
            }

            ship.velocity.x *= 0.985f;
            ship.velocity.y *= 0.985f;
            ship.position.x += ship.velocity.x;
            ship.position.y += ship.velocity.y;

            // basic screen wraparound logic
            CheckWraparound(ship.position, screenWidth, screenHeight);

            // when you need to add, modify, or remove elements during iteration, iterate in reverse, or skip elements,
            // you should use iterators
            for (auto it = bullets.begin(); it != bullets.end();)
            {
                it->position.x += it->velocity.x;
                it->position.y += it->velocity.y;

                CheckWraparound(it->position, screenWidth, screenHeight);

                it->lifeTime += GetFrameTime();
                if (it->lifeTime >= 1.0f)
                    it = bullets.erase(it);
                else
                    ++it;
            }

            for (auto it = asteroids.begin(); it != asteroids.end();)
            {
                bool destroyed = false;
                it->position.x += it->velocity.x;
                it->position.y += it->velocity.y;
                if (CheckCollisionCircleLine(it->position, it->radius, front, right) || CheckCollisionCircleLine(it->position, it->radius, right, left) || CheckCollisionCircleLine(it->position, it->radius, left, front))
                {
                    it = asteroids.erase(it);
                    destroyed = true;
                    gameOver = true;
                }
                else
                {
                    for (auto itB = bullets.begin(); itB != bullets.end();)
                    {
                        if (CircleCollision(it->position, it->radius, itB->position, itB->radius))
                        {
                            it = asteroids.erase(it);
                            itB = bullets.erase(itB);
                            destroyed = true;
                            break;
                        }
                        else
                        {
                            itB++;
                        }
                    }
                }

                if (!destroyed)
                {
                    it++;
                }
            }
        }

        BeginDrawing();
            ClearBackground(WHITE);
            // drawing the ship manually, since DrawTriangleLines doesn't have a thickness
            DrawLineEx(front, left, 4, BLACK);
            DrawLineEx(left, right, 4, BLACK);
            DrawLineEx(right, front, 4, BLACK);

            // bullets
            for (Bullet &b : bullets)
            {
                DrawCircleV(b.position, b.radius, BLACK);
            }
            // asteroids
            for (Asteroid &a : asteroids)
            {
                DrawCircleV(a.position, a.radius, BLACK);
            }
            elapsedTime += GetFrameTime();
            DrawText(TextFormat("Time Elapsed: %0.2f", elapsedTime), 20, 20, 20, LIGHTGRAY);

            int fontSize = 50;
            int fontWidth = MeasureText("GAME OVER!",fontSize);
            if (gameOver) DrawText("GAME OVER!",screenWidth/2.0f-fontWidth/2.0f,screenHeight/2.0f-fontSize/2.0f,fontSize,BLACK);
            

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
