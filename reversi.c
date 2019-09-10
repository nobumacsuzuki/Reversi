#include <stdio.h>
#include <stdlib.h>

#define NUM_OF_COLUMN 8
#define NUM_OF_ROW 8
#define NO_PIECE 0
#define BLACK_PIECE 1
#define WHITE_PIECE 2
#define TRUE 0
#define FALSE -1

typedef struct _POSITION
{
    int X;
    int Y;
} Position;

typedef struct _PIECE
{
    Position position;
    int color;
} Piece;

int* gpMasterBoard;

void InitializeBoard(int* pBoard);
void PrintBoard(int* pBorard);
int PlacePiece(int* pBoard, Piece piece);
int GetBoardPieceInformation(int* pBoard, Position position);

static Piece initialBlack0 = {{3,3}, BLACK_PIECE};
static Piece initialBlack1 = {{4,4}, BLACK_PIECE};
static Piece initialWhite0 = {{3,4}, WHITE_PIECE};
static Piece initialWhite1 = {{4,3}, WHITE_PIECE};

static char CharPiece[] = {'.', 'X', 'O'};

int main(int argc, char* argv[])
{
    // initialize
    gpMasterBoard = (int*) malloc(sizeof(int) * NUM_OF_COLUMN * NUM_OF_ROW);
    InitializeBoard(gpMasterBoard);
    PlacePiece(gpMasterBoard, initialBlack0);
    PlacePiece(gpMasterBoard, initialBlack1);
    PlacePiece(gpMasterBoard, initialWhite0);
    PlacePiece(gpMasterBoard, initialWhite1);
    PrintBoard(gpMasterBoard);

    // end
    free(gpMasterBoard);
    return 0;
}

void InitializeBoard(int* pBoard)
{
    int indexXPosition, indexYPosition;
    for(indexYPosition = 0; indexYPosition < NUM_OF_ROW; indexYPosition++)
    {
        for(indexXPosition = 0; indexXPosition < NUM_OF_COLUMN; indexXPosition++)
        {
            *(pBoard + indexYPosition * NUM_OF_COLUMN + indexXPosition) = NO_PIECE;
        }
    }
}

void PrintBoard(int* pBoard)
{
    int indexXPosition, indexYPosition;
    printf("  0 1 2 3 4 5 6 7\n");
    for(indexYPosition = 0; indexYPosition < NUM_OF_ROW; indexYPosition++)
    {
        printf("%d ", indexYPosition);
        for(indexXPosition = 0; indexXPosition < NUM_OF_COLUMN; indexXPosition++)
        {
            printf("%c ", 
            *(CharPiece + *(pBoard + indexYPosition * NUM_OF_COLUMN + indexXPosition)));
        }
        printf("\n");
    }

}

int PlacePiece(int* pBoard, Piece piece)
{
    if (GetBoardPieceInformation(pBoard, piece.position) != NO_PIECE)
        return FALSE;
    else
    {
        *(pBoard + piece.position.Y * NUM_OF_COLUMN + piece.position.X) = piece.color;
        return TRUE;
    }
    
}

int GetBoardPieceInformation(int* pBoard, Position position)
{
    return *(pBoard + position.Y * NUM_OF_COLUMN + position.X );
}
