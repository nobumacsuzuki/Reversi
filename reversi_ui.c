#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "reversi.h"

char CharPiece[] = {'.', 'X', 'O'};

void GetUserTurnPiece(int* pBoard, Piece* pPiece)
{
    int color, positionX, positionY;
    bool IsUserOperationSuccessful = false;
    while (!IsUserOperationSuccessful)
    {
        printf("color (%c = %d, %c = %d): ", CharPiece[BLACK], BLACK, CharPiece[WHITE], WHITE);
        color = getchar();
        getchar();
        printf("X position: ");
        positionX = getchar();
        getchar();
        printf("Y position: ");
        positionY = getchar();
        getchar();
        color -= ASCII_CODE_START_OF_ZERO;
        positionX -= ASCII_CODE_START_OF_ZERO;
        positionY -= ASCII_CODE_START_OF_ZERO;
        // the entry validity check
        if (color != BLACK && color != WHITE)
        {
            IsUserOperationSuccessful = false;
        }
        else if (positionX < 0 || positionY < 0 || positionX > (NUM_OF_COLUMN  - 1) || positionY > (NUM_OF_ROW - 1))
        {
            IsUserOperationSuccessful = false;
        }
        else
        {
            IsUserOperationSuccessful = true;
        }
    }
    pPiece->position.X = positionX;
    pPiece->position.Y = positionY;
    pPiece->color = color;
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
            CharPiece[pBoard[indexYPosition * NUM_OF_COLUMN + indexXPosition]]);
        }
        printf("\n");
    }
}

void PrintCount(int* pBoard)
{
    int countWhite = CountPiece(pBoard, WHITE);
    int countBlack = CountPiece(pBoard, BLACK);
    printf("%c: %d vs %c: %d\n", CharPiece[BLACK], countBlack, CharPiece[WHITE], countWhite);
}
