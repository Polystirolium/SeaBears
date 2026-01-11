#include "raylib.h"
#include "raymath.h"
#include "SinkSub.h"

const int maxFrame = 60;

int main()
{

  const char *appName{"SeaBears"};
  const int windowDimensioms[2] = {1280, 720};
  InitWindow(windowDimensioms[0], windowDimensioms[1], appName);

  Image icon = LoadImage("Icon/SeaBears_32x32.png"); // Путь файлу иконки
  ImageFormat(&icon, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
  SetWindowIcon(icon);
  UnloadImage(icon);

  SinkSub sinkSubEngine(windowDimensioms[0], windowDimensioms[1]);

  SetTargetFPS(maxFrame);

  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground({233, 227, 193, 255});

    sinkSubEngine.Tick(GetFrameTime());

    // Медиана
    //DrawLine(1280 / 2, 0, 1280 / 2, 720, RED);

    EndDrawing();
    if (sinkSubEngine.GetGameStatus() == STATUS::EXIT)
    {
      CloseWindow();
      return 0;
    }
  }

  CloseWindow();
  return 0;
}