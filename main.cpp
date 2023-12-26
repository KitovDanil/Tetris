/*************************
* Author: Kitov D.A.     *
* Date: 18.12.2023       *
* Name: Tetris           *
*************************/

#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <cstdlib>
#include "windows.h"
#include <Windows.h>
#include <time.h>
#include <vector>

using namespace std;

vector<string> mainField = {
  "#                    #",
  "#                    #",
  "#                    #",
  "#                    #",
  "#                    #",
  "#                    #",
  "#                    #",
  "#                    #",
  "#                    #",
  "#                    #",
  "#                    #",
  "#                    #",
  "#                    #",
  "#                    #",
  "#                    #",
  "#                    #",
  "#                    #",
  "#                    #",
  "#                    #",
  "#                    #",
  "######################"
};

struct block {
  vector<string> rotations[4];
  int currentRotationCode = 0;
  int coordX = 10;
  int coordY = 0;
} I, J, L, O, S, T, Z;

void setRotations() {
  I.rotations[0] = {"*", "*", "*", "*"}; I.rotations[1] = {"****"}; I.rotations[2] = {"*", "*", "*", "*"}; I.rotations[3] = {"****"};
  J.rotations[0] = {" *", " *", "**"}; J.rotations[1] = {"*", "***"}; J.rotations[2] = {"**", "*", "*"}; J.rotations[3] =  {"***", "  *"};
  L.rotations[0] = {"*", "*", "**"}; L.rotations[1] = {"***", "*"}; L.rotations[2] = {"**", " *", " *"}; L.rotations[3] = {"  *", "***"};
  O.rotations[0] = {"**", "**"}; O.rotations[1] = {"**", "**"}; O.rotations[2] = {"**", "**"}; O.rotations[3] = {"**", "**"};
  S.rotations[0] = {" **", "**"}; S.rotations[1] = {"*", "**", " *"}; S.rotations[2] = {" **", "**"}; S.rotations[3] = {"*", "**", " *"};
  T.rotations[0] = {"***", " *"}; T.rotations[1] = {" *", "**", " *"}; T.rotations[2] = {" * ", "***"}; T.rotations[3] = {"*", "**", "*"};
  Z.rotations[0] = {"**", " **"}; Z.rotations[1] = {" *", "**", "*"}; Z.rotations[2] = {"**", " **"}; Z.rotations[3] = {" *", "**", "*"};
}
/*
I
rot1: |*|   rot2: |****| rot3: |*|  rot4: |****|
      |*|                      |*|
      |*|                      |*|
      |*|                      |*|

J
rot1: | *|  rot2: |*|    rot3: |**|  rot4: |***|
      | *|        |***|        |*|         |  *|
      |**|                     |*|

L
rot1: |*|   rot2: |***|  rot3: |**|  rot4: |  *|
      |*|         |*|          | *|        |***|
      |**|                     | *|

O
rot1: |**|  rot2: |**|   rot3: |**|  rot4: |**|
      |**|        |**|         |**|        |**|

S
rot1: | **| rot2: |*|    rot3: | **| rot4: |*|
      |**|        |**|         |**|        |**|
                  | *|                     | *|

T
rot1: |***| rot2: | *|   rot3: | *|  rot4: |*|
      | *|        |**|         |***|       |**|
                  | *|                     |*|

Z
rot1: |**|  rot2: | *|   rot3: |**|  rot4: | *|
      | **|       |**|         | **|       |**|
                  |*|                      |*|
*/
void refreshField(vector<string> &currentField, block &currentBlock) {
  vector<string> fieldToPrint;

  for(int fieldRowIndex = 0; fieldRowIndex < currentField.size(); ++fieldRowIndex) {
        fieldToPrint.push_back(currentField[fieldRowIndex]);
  }

  for(int currentBlockRowCoordIndex = currentBlock.coordY; currentBlockRowCoordIndex < currentBlock.coordY + currentBlock.rotations[currentBlock.currentRotationCode].size(); ++currentBlockRowCoordIndex) {
    for(int currentBlockColumnCoordIndex = currentBlock.coordX;
        currentBlockColumnCoordIndex < currentBlock.coordX + currentBlock.rotations[currentBlock.currentRotationCode][currentBlockRowCoordIndex - currentBlock.coordY].size();
        ++currentBlockColumnCoordIndex) {
      if(fieldToPrint[currentBlockRowCoordIndex][currentBlockColumnCoordIndex] != '*') {
        fieldToPrint[currentBlockRowCoordIndex][currentBlockColumnCoordIndex] = currentBlock.rotations[currentBlock.currentRotationCode][currentBlockRowCoordIndex - currentBlock.coordY][currentBlockColumnCoordIndex - currentBlock.coordX];
      }
    }
  }

  system("cls");
  for(int fieldRowIndex = 0; fieldRowIndex < fieldToPrint.size(); ++fieldRowIndex) {
    cout << fieldToPrint[fieldRowIndex] << endl;
  }
}

block getBlockByCode(int blockCode) {
  switch(blockCode) {
    case 1:
      return I;
    case 2:
      return J;
    case 3:
      return L;
    case 4:
      return O;
    case 5:
      return S;
    case 6:
      return T;
    case 7:
      return Z;
  }
  return I;
}

block getRandomBlock() {
  return getBlockByCode(rand() % 7 + 1);
}

enum CollisionCodes { WALL = 1, BLOCK = 2, NOCOLLISION = 0 };

int checkCollision(block currentBlock, vector<string> currentField) {
  for(int currentBlockRowIndex = 0; currentBlockRowIndex < currentBlock.rotations[currentBlock.currentRotationCode].size(); ++currentBlockRowIndex) {
    for(int currentBlockColumnIndex = 0; currentBlockColumnIndex < currentBlock.rotations[currentBlock.currentRotationCode][currentBlockRowIndex].size(); ++currentBlockColumnIndex) {
      if(currentBlock.rotations[currentBlock.currentRotationCode][currentBlockRowIndex][currentBlockColumnIndex] != ' ') {
        if(currentField[currentBlockRowIndex + currentBlock.coordY][currentBlockColumnIndex  + currentBlock.coordX] == '#') return WALL;
        if(currentField[currentBlockRowIndex + currentBlock.coordY][currentBlockColumnIndex  + currentBlock.coordX] == '*') return BLOCK;
      }
    }
  }
  return NOCOLLISION;
}

void putBlockOnField(block &currentBlock, vector<string> &currentField) {
  for(int currentBlockRowIndex = 0; currentBlockRowIndex < currentBlock.rotations[currentBlock.currentRotationCode].size(); ++currentBlockRowIndex) {
    for(int currentBlockColumnIndex = 0; currentBlockColumnIndex < currentBlock.rotations[currentBlock.currentRotationCode][currentBlockRowIndex].size(); ++currentBlockColumnIndex) {
      if(currentBlock.rotations[currentBlock.currentRotationCode][currentBlockRowIndex][currentBlockColumnIndex] == '*') {
        currentField[currentBlockRowIndex + currentBlock.coordY][currentBlockColumnIndex + currentBlock.coordX] = currentBlock.rotations[currentBlock.currentRotationCode][currentBlockRowIndex][currentBlockColumnIndex];
      }
    }
  }
}

void clearLineIfNeeded(vector<string> &currentField, int &score) {
  bool isFieldEnded = false;

  while(!isFieldEnded) {
    isFieldEnded = true;

    for(int currentFieldRowIndex = 1; currentFieldRowIndex < currentField.size() - 1; ++currentFieldRowIndex) {
      if(currentField[currentFieldRowIndex].compare("#********************#") == 0) {
        for(int currentFieldRowSecondIndex = currentFieldRowIndex; currentFieldRowSecondIndex > 0; --currentFieldRowSecondIndex) {
          currentField[currentFieldRowSecondIndex] = currentField[currentFieldRowSecondIndex - 1];
        }

        score += 10;
        isFieldEnded = false;
        break;
      }
    }
  }
}

void clearFieldIfNeeded(block &currentBlock, vector<string> &currentField, int &score) {
  for(int currentFieldRowIndex = 1; currentFieldRowIndex < currentField[0].size() - 1; ++currentFieldRowIndex) {
    if(currentField[0][currentFieldRowIndex] == '*') {
      score = 0;
      currentField.clear();
      for(int mainFieldRowIndex = 0; mainFieldRowIndex < mainField.size(); ++mainFieldRowIndex) {
        currentField.push_back(mainField[mainFieldRowIndex]);
      }
      currentBlock = getRandomBlock();
      break;
    }
  }
}

enum Buttons { UP = 72, DOWN = 80, LEFT = 75, RIGHT = 77, NONE = 0 };

void controls(block &changedBlock, block &currentBlock, bool &isDownKeyPressed, vector<string> &currentField, int &collisionCode, int &score) {
  int pressedKey = NONE;

  while(_kbhit()) {
    pressedKey = _getch();
  }

  switch(pressedKey) {
    case UP:
      changedBlock.currentRotationCode = (changedBlock.currentRotationCode + 1) % 4;
      collisionCode = checkCollision(changedBlock, currentField);
      if(collisionCode == NOCOLLISION) {
        currentBlock.currentRotationCode = (currentBlock.currentRotationCode + 1) % 4;
        refreshField(currentField, currentBlock);
        cout << "Счет: " << score;
      }
      pressedKey = NONE;
      break;

    case DOWN:
      isDownKeyPressed = true;
      break;

    case LEFT:
      --changedBlock.coordX;
      collisionCode = checkCollision(changedBlock, currentField);
      if(collisionCode == NOCOLLISION) --currentBlock.coordX;
      pressedKey = NONE;
      break;

    case RIGHT:
      ++changedBlock.coordX;
      collisionCode = checkCollision(changedBlock, currentField);
      if(collisionCode == NOCOLLISION) {
        ++currentBlock.coordX;
      }
      pressedKey = NONE;
      break;

    default:
      break;
  }
}

int main() {
  void* handle = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO structCursorInfo;
  GetConsoleCursorInfo(handle,&structCursorInfo);
  structCursorInfo.bVisible = FALSE;
  SetConsoleCursorInfo( handle, &structCursorInfo );
  setlocale(LC_ALL, "RUS");
  setRotations();
  srand(time(NULL));

  vector<string> currentField;
  for(int mainFieldRowIndex = 0; mainFieldRowIndex < mainField.size(); ++mainFieldRowIndex) {
    currentField.push_back(mainField[mainFieldRowIndex]);
  }

  block currentBlock = getRandomBlock();

  int score = 0;
  int counter = 0;
  bool isDownKeyPressed = false;

  while(true) {
    isDownKeyPressed = false;

    block changedBlock = currentBlock;
    int collisionCode = NOCOLLISION;

    controls(changedBlock, currentBlock, isDownKeyPressed, currentField, collisionCode, score);

    if(counter == 4 || isDownKeyPressed) {
      changedBlock = currentBlock;
      ++changedBlock.coordY;
      collisionCode = checkCollision(changedBlock, currentField);

      if(collisionCode == NOCOLLISION) {
        ++currentBlock.coordY;
      } else {
        putBlockOnField(currentBlock, currentField);
        currentBlock = getRandomBlock();
        clearLineIfNeeded(currentField, score);
        clearFieldIfNeeded(currentBlock, currentField, score);
      }
      counter = 0;
    } else {
      ++counter;
    }

    Sleep(30);
    refreshField(currentField, currentBlock);
    cout << "Счет: " << score;
  }
  return 0;
}

