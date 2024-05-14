#include "raylib.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


typedef struct Pokemon
{
    char nome[1][30] ;
    int hp;
    int MaxHp;
    int speed;
    char ataques[2][20];
    int power[2];
    
}Pokemon;

int gameplay()
{
    srand(time(NULL));


    //Inicializando variaveis 
    Pokemon Pokemon[3];

    strcpy (Pokemon[0].nome, "Charmander");
    Pokemon[0].hp = 80;
    Pokemon[0].MaxHp = 80;
    Pokemon[0].speed = 65;
    strcpy (Pokemon[0].ataques[0], "Cabecada");
    strcpy (Pokemon[0].ataques[1], "lanca-chamas");
    Pokemon[0].power[0] = 20;
    Pokemon[0].power[1] = 40;

    strcpy (Pokemon[1].nome, "Squirtle");
    Pokemon[1].hp = 100;
    Pokemon[1].MaxHp = 100;
    Pokemon[1].speed = 43;
    strcpy (Pokemon[1].ataques[0], "Cabecada"); 
    strcpy (Pokemon[1].ataques[1], "Jato de agua"); 
    Pokemon[1].power[0] = 20;
    Pokemon[1].power[1] = 40;

    strcpy (Pokemon[2].nome, "Bulbassaur");
    Pokemon[2].hp = 110;
    Pokemon[2].MaxHp = 110;    
    Pokemon[2].speed = 45;
    strcpy (Pokemon[2].ataques[0], "Cabecada"); 
    strcpy (Pokemon[2].ataques[1], "Folha-Navalha"); 
    Pokemon[2].power[0] = 20;
    Pokemon[2].power[1] = 40;







    SetTargetFPS(60);

    InitAudioDevice();
    const int screenWidth = 736;
    const int screenHeight = 669;

InitWindow(screenWidth, screenHeight,"Pallet Town");
//Rectangle player = { 200, 200, PLAYER_SIZE, PLAYER_SIZE };


Texture sprite,sprite_up,sprite_down,sprite_left,sprite_right ;
Texture bg;

Texture squirtle_F,squirtle_B,charmander_F,charmander_B,bulbassaur_F,bulbassaur_B;
Texture Enemy_pokemon,Player_Pokemon;
Texture red_battle,blue_batlle;
Texture charmander_opc,squirtle_opc,bulbassaur_opc;

Sound soundPallet = LoadSound("./cenario.wav");
Sound soundBattle = LoadSound("./batalha.wav");

sprite = LoadTexture("./red_up.png");
sprite_up = LoadTexture("./red_up.png");
sprite_down = LoadTexture("./red_down.png");
sprite_left = LoadTexture("./red_left.png");
sprite_right = LoadTexture("./red_right.png");


red_battle = LoadTexture("./battle_red.png");
blue_batlle = LoadTexture("./blue_battle.png");

squirtle_B = LoadTexture("./squirtle_back.png");
squirtle_F = LoadTexture("./squirtle_front.png");

charmander_B = LoadTexture("./charmander_back.png");
charmander_F = LoadTexture("./charmander_front.png");

bulbassaur_B = LoadTexture("./Bulbassaur_back.png");
bulbassaur_F = LoadTexture("./Bulbassaur_front.png");

charmander_opc = LoadTexture("./charmander_chose.png");
squirtle_opc = LoadTexture("squirtle_chose.png");
bulbassaur_opc = LoadTexture("bulbassaur_chose.png");

bg = LoadTexture("./pallet.png");



int pk_player = -1;
int pk_enemy = -1;
int framesCount = 0;
float posx = 300;
float posy = 300;
float screen_Top = -736;
float screen_Down = 736;
float player = 30;
float enemy = 480;
float pokemon_oponente = 0;
float pokemon_player = 0;
float lifeBar_Player = 736;
float lifeBar_Enemy = -736;
int CurrentHp_Enemy = Pokemon[2].hp;
float CurrentLifeBar = 300.0;
float dmg_Enemy_lifebar = 0.0;
int dmg_Player_lifebar = 0;
int dmg = 0;
int dificuldade = 0;
int resultado = 0;



SetTargetFPS(60);
int framesCounter = 0;

while (!WindowShouldClose())
{

    //Sistema de colisão com limites do mapa
    if(posx > 680) posx -= 10.0f;

    else if(posx < 30) posx += 10.0f;

    if(posy < 40) posy += 10.0f;

    else if(posy > 630) posy -= 10.0f;

    else
    {
        if(IsKeyDown(KEY_D))
         {
             posx += 3.0f;
            sprite = sprite_right;
         }
        else if(IsKeyDown(KEY_A)) 
        {
            posx -= 3.0f;
            sprite = sprite_left;
        }
        if (IsKeyDown(KEY_S)) 
        {
            posy += 3.0f;
            sprite = sprite_down;
        }
        else if(IsKeyDown(KEY_W))
        {
            posy -= 3.0f;
            sprite = sprite_up;
        }
    }
//-----------------------------------------
        
    BeginDrawing();
    ClearBackground(WHITE);

    //Escolhendo a dificuldade
    DrawText("Escolha a dificuldade: ",30,30,30,RED);
    DrawText("Normal  -  [F5]",30,60,30,RED);
    DrawText("Dificil -  [F10]",30,90,30,RED);

    //Hard
    if(IsKeyPressed(KEY_F10))
    {
    dificuldade += 2;
    }
    if(IsKeyPressed(KEY_F5))
    {
    dificuldade += 1;
    }

    if(dificuldade == 2)
    {
        
        ClearBackground(WHITE);
        //Escolhendo seu Pokemon 

        DrawTexture(charmander_F,-20,400,WHITE);
        DrawTexture(squirtle_F,220,420,WHITE);
        DrawTexture(bulbassaur_F,450,420,WHITE);

        DrawText("Escolha seu Pokemon",190,200,35,BLACK);
        DrawText("Charmander [F1]",10,400,20,RED);
        DrawText("Squirtle   [F2]",270,400,20,BLUE);
        DrawText("Bulbassaur [F3]",500,400,20,GREEN);



        if(IsKeyPressed(KEY_F1) || IsKeyPressed(KEY_F2) || IsKeyPressed(KEY_F3))
        {
            ClearBackground(WHITE);

            
            if(IsKeyPressed(KEY_F1))
            {
                //PlaySound(soundPallet);
                pk_player = 0;
                pk_enemy = 1;   

                Player_Pokemon = charmander_B;
                Enemy_pokemon = squirtle_F;   

            }
            if(IsKeyPressed(KEY_F2))
            {
                //PlaySound(soundPallet);
                pk_player = 1;
                pk_enemy = 2;    

                Player_Pokemon = squirtle_B;
                Enemy_pokemon = bulbassaur_F;

            }
            if(IsKeyPressed(KEY_F3))
            {
                //PlaySound(soundPallet);
                pk_player = 2;
                pk_enemy = 0;
                
                Player_Pokemon = bulbassaur_B; 
                Enemy_pokemon = charmander_F;
            
            }   

                
        }     
    }

    if(dificuldade == 1)
    {
        ClearBackground(WHITE);
        //Escolhendo seu Pokemon 
        DrawTexture(charmander_F,-20,400,WHITE);
        DrawTexture(squirtle_F,220,420,WHITE);
        DrawTexture(bulbassaur_F,450,420,WHITE);

        DrawText("Escolha seu Pokemon",190,200,35,BLACK);
        DrawText("Charmander [F1]",10,400,20,RED);
        DrawText("Squirtle   [F2]",270,400,20,BLUE);
        DrawText("Bulbassaur [F3]",500,400,20,GREEN);


            if(IsKeyPressed(KEY_F1) || IsKeyPressed(KEY_F2) || IsKeyPressed(KEY_F3))
            {
                if(IsKeyPressed(KEY_F1))
                {
                    //PlaySound(soundPallet);
                    pk_player = 0;
                    pk_enemy = 2;

                Player_Pokemon = charmander_B;  
                Enemy_pokemon = bulbassaur_F;
                }
                if(IsKeyPressed(KEY_F2))
                {
                    //PlaySound(soundPallet);
                    pk_player = 1;
                    pk_enemy = 0;
                    
                    Player_Pokemon = squirtle_B;
                    Enemy_pokemon = charmander_F;
                }
                if(IsKeyPressed(KEY_F3))
                {
                    //PlaySound(soundPallet);
                    pk_player = 2;
                    pk_enemy = 1;
                    
                    Player_Pokemon = bulbassaur_B;
                    Enemy_pokemon = squirtle_F;
                }     
            }
    }   
    
            if(pk_player >= 0)
            {

                ClearBackground(WHITE);
                DrawTexture(bg,0,0,RAYWHITE);
                DrawTexture(sprite, posx,posy - sprite.height, WHITE);
                //DrawText("PalletTown",50,100,30,BLACK);
                //DrawRectangle(390, 30, 30, 30, RED);
                //DrawText(TextFormat("Voce escolheu: %s",Pokemon[pk_player].nome),50,100,30,RED);
                DrawText("PalletTown",100,100,30,BLACK);
                DrawText("^",400,100,30,BLACK);
                DrawText("^",400,120,30,BLACK);
                DrawText("^",400,140,30,BLACK);
                DrawText("W ",110,360,20,BLACK);
                DrawText("A ",80,400,20,BLACK);
                DrawText("S ",110,400,20,BLACK);
                DrawText("D ",140,400,20,BLACK);
            }

    ClearBackground(WHITE);
    
    
/*
    DrawTexture(sprite, posx,posy - sprite.height, WHITE);
    //DrawText("PalletTown",50,100,30,BLACK);
    DrawRectangle(390, 30, 30, 30, RED);
    DrawText(TextFormat("Voce escolheu: %s",Pokemon[pk].nome),50,100,30,RED);
*/



    //Escolhendo seu pokemon


//Interação para iniciar a batalha---------------------
if(posx <= 400 && posx >= 360  && posy <= 60 && posy >= 30)
{   
    //UnloadSound(soundPallet);
    posx = 380;
    posy = 45;

        //Formando a tela de batalha      
        if(screen_Down >= 0 && screen_Top <= 736) 
        {
            
         
           
            PlaySound(soundBattle);

            DrawRectangle(screen_Down, 340, 800, 340, WHITE);
            DrawRectangle(screen_Top, 0, 800, 340, WHITE);
            screen_Down -= 6.0f;
            screen_Top += 6.0f;


            posx = 380;
            posy = 45;
            
            
        }
    
        //Sair da batalha
        else if(IsKeyPressed(KEY_B))
        {
            DrawRectangle(736, 340, 800, 340, WHITE);
            DrawRectangle(-736, 0, 800, 340, WHITE);
            posx = 300;
            posy = 300;
            UnloadSound(soundBattle);
            
        }

        //Finalizando a tela
        else
        {

            DrawRectangle(screen_Down, 340, 800, 340, WHITE);
            DrawRectangle(screen_Top - 5 , 0, 800, 340, WHITE);

            //Oponente
            DrawTexture(blue_batlle,enemy,80,RAYWHITE);
            //DrawRectangle(enemy,80,200,200,RED);

            //Treinador
            DrawTexture(red_battle,player,400,RAYWHITE);
            //DrawRectangle(player,500,200,200,BLUE);

            //Aparecendo os Pokemons e treinadores
            
            framesCounter++;

            if (framesCounter > 120)
                {
                    
                    pokemon_oponente = 480;
                    pokemon_player = 150;

                    //Pokemon oponente

                    DrawTexture(Enemy_pokemon,pokemon_oponente,80,RAYWHITE);
                    //DrawRectangle(pokemon_oponente,80,100,100,YELLOW);
                    DrawText(TextFormat("%s",Pokemon[pk_enemy].nome),60,80,20,BLACK);

                    //Pokemon player
                    DrawTexture(Player_Pokemon,100,300,RAYWHITE);
                    //DrawRectangle(pokemon_player,400,100,100,ORANGE);
                    DrawText(TextFormat("%s",Pokemon[pk_player].nome),400,380,20,BLACK);

                    //Definindo Status

                    //--------------------Vida----------------------
                                       
                    //DrawRectangle(lifeBar_Enemy,100,300,20,GREEN);

                    //Player

                    switch (dificuldade)
                    {
                    case 1:
                    if(Pokemon[pk_player].hp > 0 && Pokemon[pk_enemy].hp > 0)
                    {
                        if(IsKeyPressed(KEY_J))
                        {

                        dmg = (rand() %20) +3; 
                        Pokemon[pk_enemy].hp -= dmg;
                        
                        dmg_Enemy_lifebar += (CurrentLifeBar*dmg) / Pokemon[pk_enemy].MaxHp ;
                        


                        DrawRectangle(lifeBar_Enemy,100,CurrentLifeBar-dmg_Enemy_lifebar,20,GREEN);
                        DrawText(TextFormat("%d/%d",Pokemon[pk_enemy].hp,Pokemon[pk_enemy].MaxHp),-736,100,20,BLACK); 
                        

                        //Inimigo atacando 

                        dmg = (rand() %20) +1;
                        Pokemon[pk_player].hp -= dmg;
                        DrawRectangle(lifeBar_Player,400,CurrentLifeBar-dmg_Player_lifebar,20,GREEN);

                        dmg_Player_lifebar += (CurrentLifeBar*dmg) / Pokemon[pk_player].MaxHp ;

                       

                        }
     
                    

                    if(IsKeyPressed(KEY_K))
                    {

                        dmg = rand() %30;
                        Pokemon[pk_enemy].hp -= dmg;
                        
                        dmg_Enemy_lifebar += (CurrentLifeBar*dmg) / Pokemon[pk_enemy].MaxHp ;

                        DrawRectangle(lifeBar_Enemy,100,CurrentLifeBar-dmg_Enemy_lifebar,20,GREEN);    
                        DrawText(TextFormat("%d/%d",Pokemon[pk_enemy].hp,Pokemon[pk_enemy].MaxHp),-736,100,20,BLACK); 


                        //Inimigo atacando 

                        dmg = rand() % 30;
                        Pokemon[pk_player].hp -= dmg;
                        DrawText(TextFormat("%d/%d",Pokemon[pk_player].hp,Pokemon[pk_player].MaxHp),638,420,20,BLACK);                    
                        dmg_Player_lifebar += (CurrentLifeBar*dmg) / Pokemon[pk_player].MaxHp ;


                        
                    }
                    DrawRectangle(lifeBar_Enemy,100,CurrentLifeBar-dmg_Enemy_lifebar,20,GREEN);
                    DrawText(TextFormat("%d/%d",Pokemon[pk_enemy].hp,Pokemon[pk_enemy].MaxHp), 100,100,20,BLACK); 


                    DrawRectangle(lifeBar_Player,400,CurrentLifeBar-dmg_Player_lifebar,20,GREEN);
                    DrawText(TextFormat("%d/%d",Pokemon[pk_player].hp,Pokemon[pk_player].MaxHp),638,420,20,BLACK); ;


                        break;
                    }



                    case 2:
                    if(Pokemon[pk_player].hp > 0 && Pokemon[pk_enemy].hp > 0)
                    {
                        if(IsKeyPressed(KEY_J))
                        {

                            dmg = (rand() %20) +1;
                            Pokemon[pk_enemy].hp -= dmg;
                            
                            dmg_Enemy_lifebar += (CurrentLifeBar*dmg) / Pokemon[pk_player].MaxHp ;


                            DrawRectangle(lifeBar_Enemy,100,CurrentLifeBar-dmg_Enemy_lifebar,20,GREEN);
                            DrawText(TextFormat("%d/%d",Pokemon[pk_enemy].hp,Pokemon[pk_enemy].MaxHp),-736,100,20,BLACK); 
                            

                            //Inimigo atacando 

                            dmg = rand() %30;
                            Pokemon[pk_player].hp -= dmg;
                            dmg_Player_lifebar += (CurrentLifeBar*dmg) / Pokemon[pk_player].MaxHp ;

                            DrawRectangle(lifeBar_Player,400,CurrentLifeBar-dmg_Player_lifebar,20,GREEN);


                            
        
                        }
                        if(IsKeyPressed(KEY_K))
                        {

                            dmg = rand() %30;
                            Pokemon[pk_enemy].hp -= dmg;
                            
                            dmg_Enemy_lifebar += (CurrentLifeBar*dmg) / Pokemon[pk_enemy].MaxHp ;

                            DrawRectangle(lifeBar_Enemy,100,CurrentLifeBar-dmg_Enemy_lifebar,20,GREEN);    
                            DrawText(TextFormat("%d/%d",Pokemon[pk_enemy].hp,Pokemon[pk_enemy].MaxHp),-736,100,20,BLACK); 


                            //Inimigo atacando 

                            dmg = rand() % 40;
                            Pokemon[pk_player].hp -= dmg;
                            DrawText(TextFormat("%d/%d",Pokemon[pk_player].hp,Pokemon[pk_player].MaxHp),638,420,20,BLACK);                    
                            dmg_Player_lifebar += (CurrentLifeBar*dmg) / Pokemon[pk_player].MaxHp ;
                            

                        }
                        DrawRectangle(lifeBar_Enemy,100,CurrentLifeBar-dmg_Enemy_lifebar,20,GREEN);
                        DrawText(TextFormat("%d/%d",Pokemon[pk_enemy].hp,Pokemon[pk_enemy].MaxHp), 100,100,20,BLACK); 


                        DrawRectangle(lifeBar_Player,400,CurrentLifeBar-dmg_Player_lifebar,20,GREEN);
                        DrawText(TextFormat("%d/%d",Pokemon[pk_player].hp,Pokemon[pk_player].MaxHp),638,420,20,BLACK); ;


                }
                        else 
                        {
                            if(Pokemon[pk_player].hp <= 0) resultado = 0;
                            
                            if(Pokemon[pk_enemy].hp <= 0 && Pokemon[pk_player].hp) resultado = 1;
                        }
                        break;
                    }


                    //oponente

                    //----------------------------------------------
                    
                    //------------------Ataques---------------------

                    //1° - Ataque
                    if(Pokemon[pk_player].hp > 0 && Pokemon[pk_enemy].hp > 0)
                    {
                
                    DrawRectangle(50,580,295,55,BLACK);
                    DrawRectangle(52,582,290,50,WHITE);
                    DrawText(TextFormat("%s  [J]",Pokemon[pk_player].ataques[0]),130,600,20,BLACK);

                    //2° - Ataque

                    DrawRectangle(400,580,295,55,BLACK);
                    DrawRectangle(402,582,290,50,WHITE);
                    DrawText(TextFormat("%s  [K]",Pokemon[pk_player].ataques[1]),480,600,20,BLACK);

                    //----------------------------------------------

                    player = 900;
                    enemy = 900;
                    lifeBar_Enemy = 50;
                    lifeBar_Player = 400;
                    }
                    else
                    {
                        DrawRectangle(0,0,900,900,YELLOW);

                        if(resultado == 1)
                        {
                            DrawText("Parabens pela Vitoria!!!",30,220,50,RED);
                            DrawText("Pressione Enter para sair...",30,320,30,RED);
                        }
                        else if(resultado == 2)
                        {
                            DrawText("Empatou a batalha :o",30,220,50,RED);
                            DrawText("Pressione Enter para sair...",30,320,30,RED);                       
                        }
                        else
                        {
                            DrawText("Infelizmente você não conseguiu...",30,220,40,RED);
                            DrawText("Pressione Enter para sair...",30,320,30,RED);
                        }

                    }

                    
                }
            posx = 380;
            posy = 45;
        }
}

    
EndMode2D();

//Interação para iniciar a batalha---------------------

    EndDrawing();

if(IsKeyPressed(KEY_ENTER)) break;

}

CloseAudioDevice();
CloseWindow();


return 0;
}
