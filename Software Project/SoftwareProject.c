#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
//#include <windows.h>
#include "rs232.h"
#include "serial.h"

//#define bdrate 115200               /* 115200 baud */


struct shape_def //Struct of shape name and no. of sides w/ nested side data struct
    {
        char shape[25];
        int sides;
        struct draw *strokes;
    };

struct draw //Struct of shape sides data for main struct
    {
        int x;
        int y;
        int pen;
    };


/*Finds and returns number of shapes in file*/
int num_of_shapes(FILE *fInput);

/*Populates structure with shape data*/
int load_shape(FILE *fInput, struct shape_def *Shapes);

/*Prompts player to select shape - Returns 1 if valid input, 0 otherwise*/
int select_shapes(int *pIndex, struct shape_def *Shapes, int n, int Pn);

/*Scale shapes to fit in the selected grid sizes*/
float ScaleShapes(float board_size);

/*Sends G-code commands to robot*/
void SendCommands (char *buffer );

/*Draws board of selected size*/
int DrawBoard(float size);

/*Prompts player to select square for move - returns coordinates into pointers*/
int PlayerMove(int Pn, int *x, int *y);

/*Draws chosenn shape into player's chosen grid square*/
int DrawShape(int p1Index, int x, int y, struct shape_def *Shapes, float board_size, float unit);

/*Checks game grid for wins or draws*/
unsigned int GameState(int board[3][3], int Pn, int moves);

/*Draws line through winning 3-in-a-row*/
void WinLine(unsigned int game, float size);

int main()
{
    FILE *fInput;
    fInput = fopen("ShapeStrokeData.txt", "r"); //Open Shape File
    if (fInput == NULL) // Check if file has been opened. If not, display error & terminate code
        {
            printf("Unable to open file");
            return -1;
        }

    int n = num_of_shapes(fInput); //Read number of shapes for structure size def

    struct shape_def ShapeRead[n]; //Create Shape data struct
    int i;
    for (i = 0; i < n; i++) //Populate Shape Struct
    {
        load_shape(fInput, &ShapeRead[i]);   
    }

    fclose(fInput); //Close file

    for (i = 0; i < n; i++)
        {
            printf("%s %d\n", ShapeRead[i].shape, ShapeRead[i].sides);
        }

    int p1Index = -1, p2Index = -1; //Players shape locations in structure for future access
    int check1 = 0, check2 = 0;
    int Pn; //Player number
    
    while (check1 == 0 || check2 == 0) // Runs while either player has invalid inputs
    {
        while (check1 == 0) // Runs while Player 1 has an invalid input
        {
            Pn = 1;
            check1 = select_shapes(&p1Index, ShapeRead, n, Pn); //Player 1 selects shape
        }
        while (check2 == 0) // Runs while Player 1 has an invalid input
        {
            Pn = 2;
            check2 = select_shapes(&p2Index, ShapeRead, n, Pn); //Player 2 selects shape
        }
        if (p1Index == p2Index) // Check to see if chosen symbols are the same
        {
           printf("\nPlease choose 2 different symbols\n");
           check1 = 0; check2 = 0; //Variables reset to 0 to stay in while loop
        }
    }

    float board_size, unit;
    

    do
    {
        printf("\nEnter board size (30 <= x <= 100): "); //Player inputs board size
        scanf("%f", &board_size);
    } while (board_size <= 30 || board_size >= 100);

    unit = ScaleShapes(board_size);
    DrawBoard(board_size); // Generates and sends G-Code to draw board

    unsigned int game = 0; /*Game state
                    0 = in progress
                    wins:
                        1 = row 1; 2 = row 2; 3 = row 3;
                        4 = collumn 1; 5 = collumn 2; 6 = collumn 3;
                        7 = -ve diagonal; 8 = +ve diagonal;
                    9 = draw*/
    int x, y; //grid coordinates selection
    int board[3][3] = {{0, 0, 0},{0, 0, 0},{0, 0, 0}}; //Shows placed & free squares
    int moves = 0;

    Pn = 1;
    while (game == 0)
    {
        while (Pn == 1) //Player 1 moves
        {
            PlayerMove(Pn, &x, &y);
            if (board[x-1][3-y] != 0)
            {
                printf("\nSpace already taken"); //Stays in loop until valid move is made
            }
            else
            {
                board[x-1][3-y] = Pn; //Populates array for win-draw checker
                DrawShape(p1Index, x, y, ShapeRead, board_size, unit); 
                moves++; //Increases move count
                game = GameState(board, Pn, moves); //Check for win-draw
                if (game != 0)
                {
                    break; //Break out of move loop to initiate final result sequence
                }
                Pn = 2; //Change player number to initiate next player's move sequence
            }
            
        }
        

        while (Pn == 2)
        {
            PlayerMove(Pn, &x, &y);
            if (board[x-1][3-y] != 0)
            {
                printf("\nSpace already taken"); //Stays in loop until valid move is made
            }
            else
            {
                board[x-1][3-y] = Pn; //Populates array for win-draw checker
                DrawShape(p2Index, x, y, ShapeRead, board_size, unit);
                moves++; //Increases move count
                game = GameState(board, Pn, moves); //Check for win-draw
                if (game != 0)
                {
                    break; //Break out of move loop to initiate final result sequence
                }
                Pn = 1; //Change player number to initiate next player's move sequence
            }
            
        }

    }
    if (game != 9) //Game won
    {
        printf("Player %d wins!!", Pn); // Display winning message
        printf("Game = %d", game); // Game state test - comment out
        WinLine(game, board_size); // Draw win line through winning move
    }
    else
    {
        printf("Game drawn");
    }

    // Before we exit the program we need to close the COM port
    Sleep(5000);
    scanf("%d", &x);
    CloseRS232Port();
    printf("Com port now closed\n");


    return 0;
}


int num_of_shapes(FILE *fInput)
{
    int num;
    
    fscanf(fInput, "NumShapes %d\n", &num); // Scan first line for items number
    return num;
}

int load_shape(FILE *fInput, struct shape_def *Shapes)
{
    fscanf(fInput, "%s %d\n", Shapes->shape, &Shapes->sides); // scan shape name and num of sides
    Shapes->strokes = calloc(Shapes->sides, sizeof(struct draw)); // shape data nested structure

    int i;
    for (i = 0; i < Shapes->sides; i++)
    {
        fscanf(fInput, "%d %d %d\n", &Shapes->strokes[i].x, &Shapes->strokes[i].y, &Shapes->strokes[i].pen); // read shape side data into struct
    }
    return 0;
}

int select_shapes(int *pIndex, struct shape_def *Shapes, int n, int Pn)
{
    char p[25];
    int i;
    
    printf("\nPlayer %d choose shape: ", Pn);
    scanf("%s", p); // Player shape input
    printf("\np%d = %s", Pn, p);
        for (i = 0; i < n; i++) // Search struct for shape name and location
        {
            if (strcmp(Shapes[i].shape, p) == 0)
            {
                *pIndex = i;
                return 1;
            }
        }
        if (*pIndex == -1)
        {
            printf("\nInvalid Input"); //Test for invalid input
            return 0;
        }
        return 0;
}

float ScaleShapes(float board_size)
{
    float unit_size;
    unit_size = ((board_size/3)-4)/16;
    return unit_size;
}

void SendCommands(char *buffer )
{
    // printf ("Buffer to send: %s", buffer); // For diagnostic purposes only, normally comment out
    PrintBuffer (&buffer[0]);
    WaitForReply();
    Sleep(100); // Can omit this when using the writing robot but has minimal effect
}

int DrawBoard(float size)
{
    char buffer[100];
 
    // If we cannot open the port then give up immediatly
    if ( CanRS232PortBeOpened() == -1 )
    {
        printf ("\nUnable to open the COM port (specified in serial.h) ");
        exit (0);
    }

    // Time to wake up the robot
    printf ("\nAbout to wake up the robot\n");

    // We do this by sending a new-line
    sprintf (buffer, "\n");
    // printf ("Buffer to send: %s", buffer); // For diagnostic purposes only, normally comment out
    PrintBuffer (&buffer[0]);
    Sleep(100);

    // This is a special case - we wait  until we see a dollar ($)
    WaitForDollar();

    printf ("\nThe robot is now ready to draw\n");

    //These commands get the robot into 'ready to draw mode' and need to be sent before any writing commands
    sprintf (buffer, "G1 X0 Y0 F1000\n");
    SendCommands(buffer);
    sprintf (buffer, "M3\n");
    SendCommands(buffer);
    sprintf (buffer, "S0\n");
    SendCommands(buffer);

    
    sprintf (buffer, "G0 X%f Y0\n", size/3);
    SendCommands(buffer);
    sprintf (buffer, "S1000\n");
    SendCommands(buffer);
    sprintf (buffer, "G1 X%f Y%f\n", size/3, -size);
    SendCommands(buffer);
    sprintf (buffer, "S0\n");
    SendCommands(buffer);
    sprintf (buffer, "G0 X%f Y%f\n", 2*size/3, -size);
    SendCommands(buffer);
    sprintf (buffer, "S1000\n");
    SendCommands(buffer);
    sprintf (buffer, "G1 X%f Y%d\n", 2*size/3, 0);
    SendCommands(buffer);
    sprintf (buffer, "S0\n");
    SendCommands(buffer);
    sprintf (buffer, "G0 X%d Y%f\n", 0, -size/3);
    SendCommands(buffer);
    sprintf (buffer, "S1000\n");
    SendCommands(buffer);
    sprintf (buffer, "G1 X%f Y%f\n", size, -size/3);
    SendCommands(buffer);
    sprintf (buffer, "S0\n");
    SendCommands(buffer);
    sprintf (buffer, "G0 X%f Y%f\n", size, -2*size/3);
    SendCommands(buffer);
    sprintf (buffer, "S1000\n");
    SendCommands(buffer);
    sprintf (buffer, "G1 X%d Y%f\n", 0, -2*size/3);
    SendCommands(buffer);
    printf (buffer, "S0\n");
    SendCommands(buffer);

    
    return 0;
}

int PlayerMove(int PlayerNumber, int *x, int *y)
{
    *x = 0; *y = 0; //reset move variables
    while (*x > 3 || *x < 1)
    {
        printf("\nPlayer %d enter collumn: ", PlayerNumber);
        scanf("%d", x);
        if (*x > 3 || *x < 1)
        {
            printf("\nInvaid Square");
        }
    }
    
    while (*y > 3 || *y < 1)
    {
        printf("\nPlayer %d enter row: ", PlayerNumber);
        scanf("%d", y);
        if (*y > 3 || *y < 1)
        {
            printf("\nInvaid Square");
        }
    }
    printf("\nMove = (%d, %d)", *x, *y);
    return 0;
}

int DrawShape(int pIndex, int x, int y, struct shape_def *Shapes, float board_size, float unit)
{
    float xSquare = (x-1)*(board_size/3)+2, ySquare = (y-4)*(board_size/3)+2;
    
    //Make fn for robot setup??
    char buffer[100];

    // We do this by sending a new-line
    sprintf (buffer, "\n");
    // printf ("Buffer to send: %s", buffer); // For diagnostic purposes only, normally comment out
    PrintBuffer (&buffer[0]);
    Sleep(100);

    // This is a special case - we wait  until we see a dollar ($)
    WaitForDollar();

    printf ("\nThe robot is now ready to draw\n");

    sprintf (buffer, "G0 X0 Y0 F1000\n");
    SendCommands(buffer);
    sprintf (buffer, "M3\n");
    SendCommands(buffer);
    sprintf (buffer, "S0\n");
    SendCommands(buffer);

    sprintf (buffer, "G0 X%f Y%f F1000\n", xSquare, ySquare);
    SendCommands(buffer);
    
    int n, i;
    n = Shapes[pIndex].sides;
    for (i = 0; i < n; i++)
    {
        if (Shapes[pIndex].strokes[i].pen == 0)
        {
            sprintf (buffer, "S0\n");
            SendCommands(buffer);
        }
        else
        {
            sprintf (buffer, "S1000\n");
            SendCommands(buffer);
        }
        sprintf (buffer, "G%d X%f Y%f\n", Shapes[pIndex].strokes[i].pen, xSquare+(Shapes[pIndex].strokes[i].x*unit), ySquare+(Shapes[pIndex].strokes[i].y*unit));
        SendCommands(buffer);
    }
    sprintf (buffer, "S0\n");
    SendCommands(buffer);
    return 0;
}

unsigned int GameState(int board[3][3], int Pn, int moves)
{
    unsigned int i, game = 0;
    for (i = 0; i < 3; i++)
    {
        if  (board[0][i] == Pn && board[1][i] == Pn && board[2][i] == Pn)
        {
            game = i+1;
        }
        else if (board[i][0] == Pn && board[i][1] == Pn && board[i][2] == Pn)
        {
            game = i+4;
        }
    }
    if (game == 0)
    {
        if ((board[0][0] == Pn && board[1][1] == Pn && board[2][2] == Pn))
        {
            game = 7;
        }
        else if (board[0][2] == Pn && board[1][1] == Pn && board[2][0] == Pn)
        {
            game = 8;
        }
        else if (moves == 9)
        {
            game = 9;
        }
    }
    return game;
}

void WinLine(unsigned int game, float size)
{
    char buffer[100];
 
    // If we cannot open the port then give up immediatly

    // Time to wake up the robot
    

    sprintf (buffer, "G0 X0 Y0 F1000\n");
    SendCommands(buffer);
    sprintf (buffer, "M3\n");
    SendCommands(buffer);
    sprintf (buffer, "S0\n");
    SendCommands(buffer);

    if (game <= 3) //Horizontal win
    {
        sprintf (buffer, "G0 X0 Y%f\n", -(size/6+(((float) game-1)*size/3)));
        SendCommands(buffer);
        sprintf (buffer, "S1000\n");
        SendCommands(buffer);
        sprintf (buffer, "G1 X%f Y%f\n", size, -(size/6+(((float) game-1)*size/3)));
        SendCommands(buffer);
    }
    else if (game <= 6) //Vertical win
    {
        sprintf (buffer, "G0 X%f Y0\n", (size/6+(((float) game-4)*size/3)));
        SendCommands(buffer);
        sprintf (buffer, "S1000\n");
        SendCommands(buffer);
        sprintf (buffer, "G1 X%f Y%f\n", (size/6+(((float) game-4)*size/3)), -size);
        SendCommands(buffer);
    }
    else if (game == 7) //-ve Diagonal win
    {
        sprintf (buffer, "G0 X0 Y0\n");
        SendCommands(buffer);
        sprintf (buffer, "S1000\n");
        SendCommands(buffer);
        sprintf (buffer, "G1 X%f Y%f\n", size, -size);
        SendCommands(buffer);
    }
    else if (game == 8) //+ve Diagonal win
    {
        sprintf (buffer, "G0 X0 Y%f\n", -size);
        SendCommands(buffer);
        sprintf (buffer, "S1000\n");
        SendCommands(buffer);
        sprintf (buffer, "G1 X%f Y0\n", size);
        SendCommands(buffer);
    }

    return;
}
