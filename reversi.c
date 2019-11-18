
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
    while (true)
    {
        GetUserTurnPiece(gpMasterBoard, &turnPiece);
        printf("color %d, X position %d, Y position %d\n", turnPiece.color, turnPiece.position.X, turnPiece.position.Y);
        PlacePiece(gpMasterBoard, turnPiece, NORMAL);
        PrintBoard(gpMasterBoard);
    }

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

void SetPiece(int* pBoard, Piece piece)
{
        pBoard[piece.position.X + piece.position.Y * NUM_OF_COLUMN] = piece.color;
}

bool PlacePiece(int* pBoard, Piece piece, PlaceMode placeMode)
{
    if (GetBoardPieceInformation(pBoard, piece.position) != EMPTY)
    {
        printf("the place is not empty\n");        
        return false;
    }
    if (placeMode == INITIAL)
    {
        SetPiece(pBoard, piece);
        return true;
    }
    else
    {
        if (CheckAndFlip(pBoard, piece, CHECK_AND_FLIP))
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

bool CheckAndFlip(int *pBoard, Piece piece, FlipMode flipMode)
{
    printf("ChekAndFliop called\n");
    int indexDirection;
    bool isCheckCompleted = false;
    bool isPieceToBeFlipped = false;
    bool isOpponentColorBetween = false;
    bool ifFlip = false;
    Position positionToCheck;
    PieceType opponentColor = (piece.color == BLACK)? WHITE: BLACK;
    PieceType colorPositionToCheck;
    Direction* pDirectionToFlip;
    for (indexDirection = 0; indexDirection < NUM_DIRECTIONS; indexDirection++)
    {
        isCheckCompleted = false;
        ifFlip = false;
        isOpponentColorBetween = false;
        positionToCheck = piece.position;
        while(!isCheckCompleted)
        {
            positionToCheck.X += gDirections[indexDirection].dX;
            positionToCheck.Y += gDirections[indexDirection].dY;
            printf("check position X: %d, position Y: %d\n", 
                positionToCheck.X, 
                positionToCheck.Y);
            if (positionToCheck.X < 0 || positionToCheck.X > (NUM_OF_COLUMN - 1) || positionToCheck.Y < 0 || positionToCheck.Y > (NUM_OF_ROW - 1))
            {
                printf("out of board, stop\n");
                isCheckCompleted = true;
            }
            else
            {
                colorPositionToCheck = GetBoardPieceInformation(pBoard, positionToCheck);
                printf("check position X: %d, position Y: %d. color:%d\n", 
                        positionToCheck.X, 
                        positionToCheck.Y, 
                        colorPositionToCheck);
                // stop the check if the position is out of the board
                // stop the check if the position is empty
                if (colorPositionToCheck == EMPTY)
                {
                    printf("empty, stop\n");
                    isCheckCompleted = true;
                }
                // stop the check if the position color is same as the piece to be placed
                else if (colorPositionToCheck == piece.color)
                {
                    printf("same color, stop\n");
                    if (isOpponentColorBetween)
                    {
                        isPieceToBeFlipped = true;
                        ifFlip = true;
                    }
                    isCheckCompleted = true;
                }
                // flag isOpponentColorBetween if there is the opponent color piece
                else
                {
                    printf("opponent color, continue\n");
                    isOpponentColorBetween = true;
                }
            }
            if (flipMode == CHECK_AND_FLIP)
            {
                if (ifFlip)
                {
                    pDirectionToFlip = &gDirections[indexDirection];
                    FlipPiece(pBoard, piece, pDirectionToFlip);
                    ifFlip = false;
                }
            }
        }
    }
    return isPieceToBeFlipped;
}

void FlipPiece(int* pBoard, Piece piece, Direction* pDirectionToFlip)
{
    Piece flippedPiece;
    flippedPiece.position.X = piece.position.X + pDirectionToFlip->dX;
    flippedPiece.position.Y = piece.position.Y + pDirectionToFlip->dY;
    flippedPiece.color = piece.color;
    while(GetBoardPieceInformation(pBoard, flippedPiece.position) != piece.color)
    {
        SetPiece(pBoard, flippedPiece);
        flippedPiece.position.X += pDirectionToFlip->dX;
        flippedPiece.position.Y += pDirectionToFlip->dY;
    }
}
