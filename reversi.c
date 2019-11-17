
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUM_OF_COLUMN 8
#define NUM_OF_ROW 8

typedef enum _PIECE_TYPE
{
    EMPTY = 0,
    WHITE,
    BLACK
} PieceType;

typedef struct _POSITION
{
    int X;
    int Y;
} Position;

typedef struct _PIECE
{
    Position position;
    PieceType color;
} Piece;

static char CharPiece[] = {'.', 'X', 'O'};

int* gpMasterBoard;

void InitializeBoard(int* pBoard);
void PutInitialPieces();
void PrintBoard(int* pBorard);
bool PlacePiece(int* pBoard, Piece piece);
PieceType GetBoardPieceInformation(int* pBoard, Position position);

static Piece initialBlack0 = {{3,3}, BLACK};
static Piece initialBlack1 = {{4,4}, BLACK};
static Piece initialWhite0 = {{3,4}, WHITE};
static Piece initialWhite1 = {{4,3}, WHITE};

int main(int argc, char* argv[])
{
    // initialize
    gpMasterBoard = (int*) malloc(sizeof(int) * NUM_OF_COLUMN * NUM_OF_ROW);
    InitializeBoard(gpMasterBoard);
    PrintBoard(gpMasterBoard);
    PutInitialPieces();

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
            *(pBoard + indexYPosition * NUM_OF_COLUMN + indexXPosition) = EMPTY;
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

bool PlacePiece(int* pBoard, Piece piece)
{
    if (GetBoardPieceInformation(pBoard, piece.position) != EMPTY)
        return false;
    else
    {
        *(pBoard + piece.position.Y * NUM_OF_COLUMN + piece.position.X) = piece.color;
        return true;
    }
}

PieceType GetBoardPieceInformation(int* pBoard, Position position)
{
    return *(pBoard + position.Y * NUM_OF_COLUMN + position.X );
}

void PutInitialPieces()
{
    PlacePiece(gpMasterBoard, initialBlack0);
    PlacePiece(gpMasterBoard, initialBlack1);
    PlacePiece(gpMasterBoard, initialWhite0);
    PlacePiece(gpMasterBoard, initialWhite1);
}
