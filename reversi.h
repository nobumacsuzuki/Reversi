#pragma once

#define NUM_OF_COLUMN 8
#define NUM_OF_ROW 8
#define NUM_DIRECTIONS 8
#define ASCII_CODE_START_OF_ZERO 48

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

extern int* gpMasterBoard;
extern Piece initialBlack0;
extern Piece initialBlack1;
extern Piece initialWhite0;
extern Piece initialWhite1;
extern Direction gDirections[];
extern char CharPiece[];
