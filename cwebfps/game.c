#include "raylib.h"

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>
#endif

static const int width = 800;
static const int height = 450;
static Camera camera = {0};
static int camera_mode = CAMERA_FIRST_PERSON;

typedef struct Col {
    float h;
    Vector3 pos;
    Color c;
} Col;

#define NCOLS 20
static Col cols[NCOLS] = {0};

static void gen_cols(void) {
    for (int i = 0; i < NCOLS; i++) {
        float h = GetRandomValue(1, 12);
        Vector3 pos = {GetRandomValue(-15, 15), h/2.0f, GetRandomValue(-15, 15)};
        Color c = {GetRandomValue(20, 255), GetRandomValue(10, 55), 30, 255};
        cols[i] = (Col){h, pos, c};
    }
}

static void draw_frame(void);

int main(void) {
    InitWindow(width, height, "cwebfps");

    camera.position = (Vector3){0, 2, 4};
    camera.target = (Vector3){0, 2, 0};
    camera.up = (Vector3){0, 1, 0};
    camera.fovy = 60;
    camera.projection = CAMERA_PERSPECTIVE;

    gen_cols();

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

static void handle_input(void) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        DisableCursor();
    }
    if (IsKeyPressed(KEY_ENTER) &&  /* M-Enter */
        (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT))) {
#ifdef PLATFORM_WEB
        emscripten_request_fullscreen("#canvas", 0);
#else
        ToggleFullscreen();
#endif
    }
    if (IsKeyPressed(KEY_F4)) {
        camera_mode = camera_mode == CAMERA_FREE ?
            CAMERA_FIRST_PERSON : CAMERA_FREE;
    }
}

static void draw_env(void) {
    DrawPlane((Vector3){0, 0, 0}, (Vector2){32, 32}, BLACK);
    DrawCube((Vector3){-16, 2.5f, 0}, 1, 5, 32, BLUE);
    DrawCube((Vector3){16, 2.5f, 0}, 1, 5, 32, LIME);
    DrawCube((Vector3){0, 2.5f, 16}, 32, 5, 1, GOLD);
    for (int i = 0; i < NCOLS; i++) {
        DrawCube     (cols[i].pos, 2, cols[i].h, 2, cols[i].c);
        DrawCubeWires(cols[i].pos, 2, cols[i].h, 2, MAROON);
    }
}

static void draw_frame(void) {
    handle_input();
    UpdateCamera(&camera, camera_mode);
    BeginDrawing();
    ClearBackground(DARKGREEN);
    BeginMode3D(camera);
    draw_env();
    EndMode3D();
    DrawText(camera_mode == CAMERA_FREE ? "CAMERA_FREE" : "",
             300, 420, 20, LIGHTGRAY);
    EndDrawing();
}
