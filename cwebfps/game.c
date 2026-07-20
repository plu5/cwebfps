#include "raylib.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

static void draw_frame(void);

int main(void) {
    InitWindow(800, 450, "cwebfps");

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(draw_frame, 60, 1);
#else
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        draw_frame();
    }
#endif

    CloseWindow();
    return 0;
}

static void draw_frame(void) {
    BeginDrawing();
    ClearBackground(DARKGREEN);
    EndDrawing();
}
