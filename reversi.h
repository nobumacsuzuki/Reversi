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

typedef enum _PLACE_MODE
{
    INITIAL = 0,
    NORMAL
} PlaceMode;

typedef enum _FLIP_MODE
{
    CHECK_ONLY = 0,
    CHECK_AND_FLIP
} FlipMode;


typedef struct _POSITION
{
    int X;
    int Y;
} Position;

typedef struct _DIRECTION
{
    int dX;
    int dY;
} Direction;

typedef struct _PIECE
{
    Position position;
    PieceType color;
} Piece;

char CharPiece[] = {'.', 'X', 'O'};

int* gpMasterBoard;

void InitializeBoard(int* pBoard);
void PutInitialPieces();
void PrintBoard(int* pBorard);
void PrintCount(int* pBoard);
void SetPiece(int* pBoard, Piece piece);
bool PlacePiece(int* pBoard, Piece piece, PlaceMode placeMode);
PieceType GetBoardPieceInformation(int* pBoard, Position position);
int CheckAndFlip(int *pBoard, Piece piece, FlipMode flipMode);
void GetUserTurnPiece(int* pBoard, Piece* pPiece);
int FlipPiece(int* pBoard, Piece piece, Direction* pDirectionToFlip);
int CountPiece(int* pBoard, PieceType color);


Piece initialBlack0 = {{3,3}, BLACK};
Piece initialBlack1 = {{4,4}, BLACK};
Piece initialWhite0 = {{3,4}, WHITE};
Piece initialWhite1 = {{4,3}, WHITE};
Direction gDirections[] =
{
    {-1, -1},
    {0, -1},
    {1, -1},
    {-1, 0},
    {1, 0},
    {-1,1},
    {0, 1},
    {1, 1}
};
#define NUM_DIRECTIONS 8
#define ASCII_CODE_START_OF_ZERO 48