#include "reglas.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include "freeglut.h"
#include "vector2D.h"
#include <vector>
#include "tablero.h"

Reglas::Reglas() {};

bool Reglas::moveChecker(int piece, vector2D origen, vector2D destino, std::array<std::array<int, 6>, 5>& board) {//comprueba que se puedan realizar los movimientos de todas las piezas con las propiedades de cada una y el rango de movimiento
    int kingValue = (piece > 0) ? 6 : -6; //x? a : b = if x ->a else-> b 
    if (static_cast<int>(destino.x) < 0 || static_cast<int>(destino.x) > 4 || static_cast<int>(destino.z) < 0 || static_cast<int>(destino.z) > 5 || board[destino.x][destino.z] == kingValue) {//no captura del rey accidentalemte
        return false;
    }
    int dx = static_cast<int>(destino.x - origen.x);//lo q se puede mover en x
    int dz = static_cast<int>(destino.z - origen.z);// movimiento max en z
    //std::cout << origen.x+1 << "," << origen.z+1 << " to " << destino.z+1 << "," << destino.x+1 << " = " << dx << "," << dz << std::endl;
    int abs_dx = abs(dx);// valor absoluto del movimiento en x
    int abs_dz = abs(dz);//valor absoluto del movimiento en z
    int val = abs(piece);// valor absoluto de pieza, determina categoria
    switch (val) {
    case 1: // Peon
        return (((piece > 0) && ((dx == 0 && dz == 1 && board[destino.x][destino.z] == 0) || (abs_dx == 1 && dz == 1 && board[destino.x][destino.z] != 0))) || ((piece < 0)&&((dx == 0 && dz == -1 && board[destino.x][destino.z] == 0) || (abs_dx == 1 && dz == -1 && board[destino.x][destino.z] != 0))));
    case 3: // Caballo
        return (abs_dx == 2 && abs_dz == 1) || (abs_dx == 1 && abs_dz == 2);
    case 6: // Rey
        return ((abs_dx <= 1 && abs_dz <= 1) && !(dx == 0 && dz == 0));
    }
    if (val == 2 || val == 4 || val == 5) { // Torre, Alfil, Reina
        bool valid = (val == 2 && (dx == 0 || dz == 0)) ||
            (val == 4 && (abs_dx == abs_dz)) ||
            (val == 5 && (dx == 0 || dz == 0 || abs_dx == abs_dz));
        if (!valid || !(dx || dz)) return false;
        int step_x = (dx > 0) - (dx < 0);
        int step_z = (dz > 0) - (dz < 0);
        for (int ox = origen.x + step_x, oz = origen.z + step_z;
            ox != destino.x || oz != destino.z;
            ox += step_x, oz += step_z)// comprueba que no hay ninguna pieza delante
            if (board[ox][oz] != 0)
                return false;
        return true;
    }
    return false;
}
void Reglas::displayValidMoves(int piece, vector2D origen, std::array<std::array<int, 6>, 5>& board, std::array<std::array<Losa, 6>, 5>& tiles) {//determina las casillas a las que es posible moverse cada pieza
    for (int j = 0; j < 6; ++j) {
        for (int i = 0; i < 5; ++i) {
            if (moveChecker(piece, origen, { static_cast<float>(i), static_cast<float>(j) }, board)) {
                //std::cout << i << ", " << j << " mov. valido\n";
                tiles[i][j].setColor({valid});//muestra con un color diferente, las casillas a las que se puede mover la pieza seleccionada
               
            }
        }
    }
}
void Reglas::displayDanger(vector2D posicion, std::array<std::array<Losa, 6>, 5>& tiles) {//muestra las casillas donde puede haber peligro moverse 
    tiles[static_cast<int>(posicion.x)][static_cast<int>(posicion.z)].setColor({ danger });
}
void Reglas::displayDangerous(vector2D posicion, std::array<std::array<Losa, 6>, 5>& tiles) { //muestra las casillas a las que una pieza atacante puede moverse con riesgo para el rey
    tiles[static_cast<int>(posicion.x)][static_cast<int>(posicion.z)].setColor({ dangerous });
}
vector2D Reglas::kingFinder(bool turnFlag, std::array<std::array<int, 6>, 5>& board) {//determina la posicion del rey en todo momento
    int kingValue = ((turnFlag == 0) ? -6 : 6);
    for (int j = 0; j < 6; ++j) {
        for (int i = 0; i < 5; ++i) {
            if (board[i][j] == kingValue) {
                return { static_cast<float>(i), static_cast<float>(j) };                
            }
        }
    }
    return { -1, -1 };//el rey no se encontro, puesto q devuelve una ccoordenada q no esta en el tablero
}
bool Reglas::jaque(bool turnFlag, std::array<std::array<int, 6>, 5>& board, std::array<std::array<Losa, 6>, 5>& tiles) {//determina cuando hay jaque en la partida
    vector2D enemyKingPos = kingFinder(turnFlag, board);
    if (enemyKingPos.x == -1) return true; // REY NO ENCONTRADO
    for (int j = 0; j < 6; ++j) {
        for (int i = 0; i < 5; ++i) {
            int attackingPiece = board[i][j];
            if (attackingPiece == 0) continue;
            if ((turnFlag == 0 && attackingPiece <= 0) || (turnFlag == 1 && attackingPiece >= 0))
                continue; 
            vector2D attackerPos = { static_cast<float>(i), static_cast<float>(j) };
            if (moveChecker(attackingPiece, attackerPos, enemyKingPos, board)) {
                displayDanger(enemyKingPos, tiles); // REY EN PELIGRO
                displayDangerous(attackerPos, tiles); // ATACANTE PELIGROSO
                
                return true; // JAQUE
            }
        }
    }
    return false;
}
bool Reglas::jaqueMate(bool turnFlag, std::array<std::array<int, 6>, 5>& board, std::array<std::array<Losa, 6>, 5>& tiles) //determina el jaque mate
{
    vector2D enemyKingPos = kingFinder(turnFlag, board);
    if (enemyKingPos.x == -1)
        return true;  // REY NO ENCONTRADO

    bool legalMoveFound = false;
    for (int i = 0; i < 5 && !legalMoveFound; i++) {
        for (int j = 0; j < 6 && !legalMoveFound; j++) {

            int enemyPiece = board[i][j];
            if (turnFlag == 0) {
                if (enemyPiece >= 0)
                    continue;
            }
            else {
                if (enemyPiece <= 0)
                    continue;
            }
            vector2D piecePos((float)i, (float)j);

            // PROBAMOS CADA POSIBLE MOVIMIENTO
            for (int k = 0; k < 5 && !legalMoveFound; k++) {
                for (int l = 0; l < 6 && !legalMoveFound; l++) {
                    
                    if (i == k && j == l)
                        continue; // SALTAMOS LA PROPIA POSICION ACTUAL DE LA PIEZA 
                    vector2D dest((float)k, (float)l);

                    if (!moveChecker(enemyPiece, piecePos, dest, board))
                        continue; // SALTAMOS LOS MOVIMIENTOS INVALIDOS O ILEGALES

                    std::array<std::array<int, 6>, 5> boardCopy = board;
                    boardCopy[k][l] = enemyPiece;
                    boardCopy[i][j] = 0;

                    vector2D newKingPos;
                    if ((turnFlag == 0 && enemyPiece == 6) || (turnFlag == 1 && abs(enemyPiece) == 6))
                        newKingPos = dest;
                    else
                        newKingPos = kingFinder(turnFlag, boardCopy);
                    if (newKingPos.x == -1)
                        continue;  

                    bool kingStillInCheck = false;
                    for (int x = 0; x < 5 && !kingStillInCheck; x++) {
                        for (int z = 0; z < 6 && !kingStillInCheck; z++) {
                            int attacker = boardCopy[x][z];
                            if (attacker == 0)
                                continue;
                            if (turnFlag == 0 && attacker <= 0)
                                continue;
                            if (turnFlag == 1 && attacker >= 0)
                                continue;
                            vector2D attackerPos((float)x, (float)z);
                            if (moveChecker(attacker, attackerPos, newKingPos, boardCopy))
                                kingStillInCheck = true;
                        }
                    }
                    if (!kingStillInCheck) {
                        legalMoveFound = true;

                    }
                }
            }
        }
    }

    return !legalMoveFound;
}