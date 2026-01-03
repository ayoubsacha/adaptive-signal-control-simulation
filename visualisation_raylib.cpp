#include "raylib.h"
#include "draw.h" 
#include <string>
#include <cmath> 


int currentScreenWidth = 800;
int currentScreenHeight = 600;

enum GameState {
    MENU = 0,
    GAME = 1
};

void runMenu(int& rows, int& cols, GameState& state, int screenW, int screenH);
void runGame(int rows, int cols, GameState& state, int screenW, int screenH);

int main()
{
    InitWindow(currentScreenWidth, currentScreenHeight, "Road Grid Generator");

    SetWindowState(FLAG_WINDOW_RESIZABLE);

    SetTargetFPS(60);

    int currentRows = 0;
    int currentColls = 0;
    GameState currentState = MENU;

    while (!WindowShouldClose())
    {
        currentScreenWidth = GetScreenWidth();
        currentScreenHeight = GetScreenHeight();

        if (currentState == MENU)
        {
            runMenu(currentRows, currentColls, currentState, currentScreenWidth, currentScreenHeight);
        }
        else 
        {
            
            runGame(currentRows, currentColls, currentState, currentScreenWidth, currentScreenHeight);
        }
    }

    CloseWindow();
    return 0;
}

void runMenu(int& rows, int& cols, GameState& state, int screenW, int screenH)
{
    
    static int inputRows = rows;
    static int inputCols = cols;
    static int activeInput = 0;

   
    Rectangle rowRec = { 450, 195, 100, 40 };
    Rectangle colRec = { 450, 255, 100, 40 };
    
    Rectangle playRec = { (float)screenW / 2 - 100, 350, 200, 50 };

    Rectangle rowUp = { 550, 195, 25, 20 };
    Rectangle rowDown = { 550, 215, 25, 20 };
    Rectangle colUp = { 550, 255, 25, 20 };
    Rectangle colDown = { 550, 275, 25, 20 };

    
    Vector2 mousePoint = GetMousePosition();
   

    if (CheckCollisionPointRec(mousePoint, rowRec) || CheckCollisionPointRec(mousePoint, rowUp) || CheckCollisionPointRec(mousePoint, rowDown)) {
        activeInput = 0;
    }
    else if (CheckCollisionPointRec(mousePoint, colRec) || CheckCollisionPointRec(mousePoint, colUp) || CheckCollisionPointRec(mousePoint, colDown)) {
        activeInput = 1;
    }
    else if (CheckCollisionPointRec(mousePoint, playRec)) {
        activeInput = 2;
    }
    else {
        activeInput = 3;
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
      
        if (CheckCollisionPointRec(mousePoint, rowUp)) {
            if (inputRows < 99) inputRows++;
        }
        else if (CheckCollisionPointRec(mousePoint, rowDown)) {
            if (inputRows > 0) inputRows--;
        }
        else if (CheckCollisionPointRec(mousePoint, colUp)) {
            if (inputCols < 99) inputCols++;
        }
        else if (CheckCollisionPointRec(mousePoint, colDown)) {
            if (inputCols > 0) inputCols--;
        }

        
        else if (CheckCollisionPointRec(mousePoint, playRec))
        {
            if (inputRows > 0 && inputCols > 0)
            {
                rows = inputRows;
                cols = inputCols;
                state = GAME;
            }
        }
    }

  
    if (IsKeyPressed(KEY_ENTER) && activeInput == 2)
    {
        if (inputRows > 0 && inputCols > 0)
        {
            rows = inputRows;
            cols = inputCols;
            state = GAME;
        }
    }


    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawText("--- ROAD GRID GENERATOR ---", screenW / 2 - MeasureText("--- ROAD GRID GENERATOR ---", 30) / 2, 80, 30, DARKGRAY);

    

    DrawText("ROWS (0-99):", 200, 200, 20, BLACK);
    DrawRectangleRec(rowRec, (activeInput == 0) ? LIGHTGRAY : WHITE);
    DrawText(TextFormat("%i", inputRows), 460, 200, 30, (activeInput == 0) ? RED : BLUE);

    DrawRectangleRec(rowUp, (activeInput == 0 && CheckCollisionPointRec(mousePoint, rowUp)) ? GREEN : GRAY);
    DrawText("^", 555, 195, 20, BLACK);    DrawRectangleRec(rowDown, (activeInput == 0 && CheckCollisionPointRec(mousePoint, rowDown)) ? GREEN : GRAY);
    DrawText("v", 555, 215, 20, BLACK);


    DrawText("COLUMNS (0-99):", 200, 260, 20, BLACK);
    DrawRectangleRec(colRec, (activeInput == 1) ? LIGHTGRAY : WHITE);
    DrawText(TextFormat("%i", inputCols), 460, 260, 30, (activeInput == 1) ? RED : BLUE);

    DrawRectangleRec(colUp, (activeInput == 1 && CheckCollisionPointRec(mousePoint, colUp)) ? GREEN : GRAY);
    DrawText("^", 555, 255, 20, BLACK);
    DrawRectangleRec(colDown, (activeInput == 1 && CheckCollisionPointRec(mousePoint, colDown)) ? GREEN : GRAY);
    DrawText("v", 555, 275, 20, BLACK);


  
    Color playColor = (inputRows > 0 && inputCols > 0) ? DARKGREEN : RED;
    if (activeInput == 2) playColor = (inputRows > 0 && inputCols > 0) ? GREEN : ORANGE;

    DrawRectangleRec(playRec, playColor);
    DrawText("START GAME", screenW / 2 - MeasureText("START GAME", 25) / 2, 360, 25, RAYWHITE); 

    if (inputRows == 0 || inputCols == 0)
    {
        DrawText("Grid must be at least 1x1!", screenW / 2 - MeasureText("Grid must be at least 1x1!", 20) / 2, 420, 20, RED);
    }
    else
    {
        DrawText("Click START GAME or press ENTER.", screenW / 2 - MeasureText("Click START GAME or press ENTER.", 15) / 2, 420, 15, GRAY);
    }

    EndDrawing();
}


void runGame(int rows, int cols, GameState& state, int screenW, int screenH)
{

    Road roadMap(rows, cols, screenH, screenW, 20.0f);

    BeginDrawing();
    ClearBackground(SKYBLUE);

    roadMap.createRoads();

    DrawText("Press M to return to Menu", 10, screenH - 30, 20, BLACK);

    EndDrawing();

    if (IsKeyPressed(KEY_M))
    {
        state = MENU;
    }
}