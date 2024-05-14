#include "raylib.h"


int title()
{
    const int screenWidth = 736;
    const int screenHeight = 669;

InitWindow(screenWidth, screenHeight,"Pallet Town");



Texture  bg_menu;



bg_menu = LoadTexture("./pokemonMenu.png");


while (!WindowShouldClose())
{



    BeginDrawing();
    ClearBackground(WHITE);
    DrawTexture(bg_menu,-600,-100,RAYWHITE);
    DrawText("Pressione Enter para entrar no mundo",50,600,30,BLACK);

    EndDrawing();


if(IsKeyPressed(KEY_ENTER)) break;
}




CloseWindow();
}