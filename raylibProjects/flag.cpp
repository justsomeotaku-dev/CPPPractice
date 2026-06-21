#include "raylib.h"

// Converts a point from the original 1000x1000 SVG coordinate space into
// screen coordinates, given the inner content box's top-left corner and
// a uniform scale factor.
static Vector2 SvgToScreen(float x, float y, float originX, float originY, float scale)
{
    return (Vector2){
        originX + (x - 500.0f) * scale,
        originY + (y - 500.0f) * scale
    };
}

int main(void)
{
    const int screenWidth = 400;
    const int screenHeight = 400;

    InitWindow(screenWidth, screenHeight, "Flag Icon - raylib");
    SetTargetFPS(60);

    // Page background (#e9e9e9)
    Color pageBg = (Color){ 233, 233, 233, 255 };

    // Icon panel dimensions, matching the original CSS
    const float iconSize    = 320.0f;
    const float borderWidth = 36.0f;

    Color panelBg     = (Color){ 189, 189, 189, 255 }; // #bdbdbd
    Color borderLight = (Color){ 250, 250, 250, 255 }; // #fafafa (top/left bevel)
    Color borderDark  = (Color){ 112, 112, 112, 255 }; // #707070 (bottom/right bevel)
    Color flagRed     = (Color){ 255, 0, 0, 255 };
    Color flagBlack   = BLACK;

    // Center the icon panel in the window
    Vector2 iconOrigin = {
        (screenWidth  - iconSize) / 2.0f,
        (screenHeight - iconSize) / 2.0f
    };

    // Inner content box (where the SVG graphic is drawn), inset by the border
    Vector2 contentOrigin = { iconOrigin.x + borderWidth, iconOrigin.y + borderWidth };
    float contentSize = iconSize - 2.0f * borderWidth;
    Vector2 contentCenter = {
        contentOrigin.x + contentSize * 0.5f,
        contentOrigin.y + contentSize * 0.5f
    };

    float svgScale = contentSize / 1000.0f; // original SVG viewBox is 1000x1000

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(pageBg);

        // ---- Beveled "sunken panel" background ----
        // The CSS border trick mitres each side into a trapezoid at 45 degrees;
        // we reproduce that with two triangles per side.
        Vector2 outerTL = { iconOrigin.x,             iconOrigin.y             };
        Vector2 outerTR = { iconOrigin.x + iconSize,   iconOrigin.y             };
        Vector2 outerBL = { iconOrigin.x,              iconOrigin.y + iconSize };
        Vector2 outerBR = { iconOrigin.x + iconSize,   iconOrigin.y + iconSize };

        Vector2 innerTL = { contentOrigin.x,                contentOrigin.y                };
        Vector2 innerTR = { contentOrigin.x + contentSize,  contentOrigin.y                };
        Vector2 innerBL = { contentOrigin.x,                contentOrigin.y + contentSize  };
        Vector2 innerBR = { contentOrigin.x + contentSize,  contentOrigin.y + contentSize  };
        // ---- SVG flag graphic, scaled into the content box ----
        float ox = contentCenter.x;
        float oy = contentCenter.y;

        // Pole
        Vector2 poleTL = SvgToScreen(470, 510, ox, oy, svgScale);
        Vector2 poleBR = SvgToScreen(540, 720, ox, oy, svgScale);
        DrawRectangleV(poleTL, (Vector2){ poleBR.x - poleTL.x, poleBR.y - poleTL.y }, flagBlack);

        // Pedestal, upper tier
        Vector2 pedUpperTL = SvgToScreen(380, 720, ox, oy, svgScale);
        Vector2 pedUpperBR = SvgToScreen(630, 820, ox, oy, svgScale);
        DrawRectangleV(pedUpperTL, (Vector2){ pedUpperBR.x - pedUpperTL.x, pedUpperBR.y - pedUpperTL.y }, flagBlack);

        // Pedestal, lower tier
        Vector2 pedLowerTL = SvgToScreen(265, 820, ox, oy, svgScale);
        Vector2 pedLowerBR = SvgToScreen(745, 930, ox, oy, svgScale);
        DrawRectangleV(pedLowerTL, (Vector2){ pedLowerBR.x - pedLowerTL.x, pedLowerBR.y - pedLowerTL.y }, flagBlack);

        // Flag (red triangle)
        Vector2 flagP1 = SvgToScreen(170, 330, ox, oy, svgScale);
        Vector2 flagP2 = SvgToScreen(540, 110,  ox, oy, svgScale);
        Vector2 flagP3 = SvgToScreen(540, 560, ox, oy, svgScale);
        DrawTriangle(flagP1, flagP3, flagP2, RED);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}