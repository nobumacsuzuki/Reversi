
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "reversi.h"

int main(int argc, char* argv[])
{
    // initialize
    gpMasterBoard = (int*) malloc(sizeof(int) * NUM_OF_COLUMN * NUM_OF_ROW);
    InitializeBoard(gpMasterBoard);
    PrintBoard(gpMasterBoard);
    Piece turnPiece;
    GetUserTurnPiece(gpMasterBoard, &turnPiece);
    printf("color %d, X position %d, Y position %d\n", turnPiece.color, turnPiece.position.X, turnPiece.position.Y);
    PlacePiece(gpMasterBoard, turnPiece, NORMAL);
    PrintBoard(gpMasterBoard);

    // end
    free(gpMasterBoard);
    return 0;
}

void GetUserTurnPiece(int* pBoard, Piece* pPiece)
{
    int color, positionX, positionY;
    bool IsUserOperationSuccessful = false;
    while (!IsUserOperationSuccessful)
    {
        printf("color (black = 1, whilte = 2): ");
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
        else if (positionX < 0 || positionY < 0 || positionX > NUM_OF_COLUMN || positionY > NUM_OF_ROW)
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
    PutInitialPieces();
}

void PutInitialPieces()
{
    PlacePiece(gpMasterBoard, initialBlack0, INITIAL);
    PlacePiece(gpMasterBoard, initialBlack1, INITIAL);
    PlacePiece(gpMasterBoard, initialWhite0, INITIAL);
    PlacePiece(gpMasterBoard, initialWhite1, INITIAL);
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

bool PlacePiece(int* pBoard, Piece piece, PlaceMode placeMode)
{
    if (GetBoardPieceInformation(pBoard, piece.position) != EMPTY)
        return false;
    if (placeMode == INITIAL)
    {
        pBoard[piece.position.X + piece.position.Y * NUM_OF_COLUMN] = piece.color;
        return true;
    }
    else
    {
        if (IsPieceToBeFlipped(pBoard, piece))
        {
            pBoard[piece.position.X + piece.position.Y * NUM_OF_COLUMN] = piece.color;
            return true;
        }
        else 
            return false;
    }
}

PieceType GetBoardPieceInformation(int* pBoard, Position position)
{
    return pBoard[position.Y * NUM_OF_COLUMN + position.X];
}

bool IsPieceToBeFlipped(int *pBoard, Piece piece)
{
    int indexDirection;
    bool isCheckCompleted;
    bool isPieceToBeFlipped = false;
    Position positionToCheck;
    PieceType colorToCheck = (piece.color == BLACK)? WHITE: BLACK;
    for (indexDirection = 0; indexDirection < NUM_DIRECTIONS; indexDirection++)
    {
        isCheckCompleted = true;
        positionToCheck = piece.position;
        while(!isCheckCompleted)
        {
            positionToCheck.X += gDirections[indexDirection].dX;
            positionToCheck.Y += gDirections[indexDirection].dY;
            if (positionToCheck.X < 0 || positionToCheck.X > NUM_OF_COLUMN || positionToCheck.Y < 0 || positionToCheck.Y > NUM_OF_ROW)
                    isCheckCompleted = true;
            else
            {
                if (pBoard[positionToCheck.X + positionToCheck.Y * NUM_OF_COLUMN] == colorToCheck)
                {
                    isPieceToBeFlipped = true;
                    isCheckCompleted = true;
                }
            }
        }
    }
    return isPieceFlipped;
}
