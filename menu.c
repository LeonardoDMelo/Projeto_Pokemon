#include "raylib.h"
#include "gameplay.c"


typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, ENDING } GameScreen;


int main()
{

    const int screenWidth = 736;
    const int screenHeight = 669;

    InitWindow(screenWidth, screenHeight, "Pokemon");

    InitAudioDevice();

    Texture bg_menu;
    bg_menu = LoadTexture("./pokemonMenu.png");
    GameScreen currentScreen = LOGO;


    int framesCounter = 0;
    Sound soundMenu = LoadSound("./abertura.wav");
    //Sound soundPallet = LoadSound("./cenario.wav");
    //Sound sound1 = LoadSound("./abertura.wav");


    SetTargetFPS(60);



    while (!WindowShouldClose())
    {

        switch(currentScreen)
        {
        case LOGO:
        {
            framesCounter++;    // Count frames

            if (framesCounter > 60)
            {
                currentScreen = TITLE;
                PlaySound(soundMenu);
            }
        }
        break;
        case TITLE:
        {

            if (IsKeyPressed(KEY_ENTER))
            {
                currentScreen = GAMEPLAY;
                UnloadSound(soundMenu);

            }
            //PlaySound(soundPallet);
        }
        break;

        case GAMEPLAY:
        {


            if (IsKeyPressed(KEY_ENTER))
            {
                currentScreen = ENDING;
            }
        }
        break;
        case ENDING:
            //UnloadSound(soundPallet);
        {

            if (IsKeyPressed(KEY_ENTER))
            {
                DrawText("Encerrando... \n\n\n\n Até a proxima...", 20, 20, 40, LIGHTGRAY);
                framesCounter++;

                if (framesCounter > 120)
                {

                    CloseWindow();
                }
                break;
            }
        }
        break;
        default:
            break;
        }

        BeginDrawing();

        ClearBackground(WHITE);

        switch(currentScreen)
        {
        case LOGO:
        {

            DrawText("POKEMON", 20, 20, 40, LIGHTGRAY);
            DrawText("Aguarde o carregamento...", 290, 220, 20, GRAY);

        }
        break;
        case TITLE:
        {
            DrawTexture(bg_menu,-600,-100,RAYWHITE);
            DrawText("Pressione Enter para entrar no mundo",50,600,30,BLACK);

        }
        break;
        case GAMEPLAY:
        {
            CloseWindow();
            gameplay();

        }
        break;
        case ENDING:
        {

            DrawRectangle(0, 0, screenWidth, screenHeight, BLUE);
            DrawText("ENDING SCREEN", 20, 20, 40, DARKBLUE);
            DrawText("PRESS ENTER or TAP to RETURN to TITLE SCREEN", 120, 220, 20, DARKBLUE);

        }
        break;
        default:
            break;
        }

        EndDrawing();

    }



    CloseAudioDevice();
    CloseWindow();

    return 0;
}


