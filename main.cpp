#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const char JUGADOR = 'O';
const char IA = 'X';
const char VACIO = ' ';

const int MAX = std::numeric_limits<int>::max();
const int MIN = std::numeric_limits<int>::min();

void imprimirTablero(const std::vector<std::vector<char>>& tablero) {
    int num = 1;
    for(const auto& fila : tablero) {
        for(const auto& celda : fila) {
            if(celda == ' ') {
                std::cout << num++ << ' ';
            } else {
                std::cout << celda << ' ';
                ++num;
            }
        }
        std::cout << '\n';
    }
}

bool esGanador(const std::vector<std::vector<char>>& tablero, char jugador) {
    for(int i = 0; i < 3; ++i) {
        if(tablero[i][0] == jugador && tablero[i][1] == jugador && tablero[i][2] == jugador) return true;
        if(tablero[0][i] == jugador && tablero[1][i] == jugador && tablero[2][i] == jugador) return true;
    }
    if(tablero[0][0] == jugador && tablero[1][1] == jugador && tablero[2][2] == jugador) return true;
    if(tablero[0][2] == jugador && tablero[1][1] == jugador && tablero[2][0] == jugador) return true;
    return false;
}

bool esEmpate(const std::vector<std::vector<char>>& tablero) {
    for(const auto& fila : tablero) {
        for(const auto& celda : fila) {
            if(celda == VACIO) return false;
        }
    }
    return true;
}

int minimax(std::vector<std::vector<char>>& tablero, bool esJugadorMax, int alpha, int beta) {
    if(esGanador(tablero, IA)) return 1;
    if(esGanador(tablero, JUGADOR)) return -1;
    if(esEmpate(tablero)) return 0;

    if(esJugadorMax) {
        int mejorValor = MIN;
        for(int i = 0; i < 3; ++i) {
            for(int j = 0; j < 3; ++j) {
                if(tablero[i][j] == VACIO) {
                    tablero[i][j] = IA;
                    mejorValor = std::max(mejorValor, minimax(tablero, !esJugadorMax, alpha, beta));
                    tablero[i][j] = VACIO;

                    alpha = std::max(alpha, mejorValor);
                    if(beta <= alpha)
                        break;
                }
            }
        }
        return mejorValor;
    } else {
        int mejorValor = MAX;
        for(int i = 0; i < 3; ++i) {
            for(int j = 0; j < 3; ++j) {
                if(tablero[i][j] == VACIO) {
                    tablero[i][j] = JUGADOR;
                    mejorValor = std::min(mejorValor, minimax(tablero, !esJugadorMax, alpha, beta));
                    tablero[i][j] = VACIO;

                    beta = std::min(beta, mejorValor);
                    if(beta <= alpha)
                        break;
                }
            }
        }
        return mejorValor;
    }
}

std::pair<int, int> movimientoIA(std::vector<std::vector<char>>& tablero) {

    int mejorValor = MIN;
    int mejorMovimientoX = -1;
    int mejorMovimientoY = -1;

    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 3; ++j) {
            if(tablero[i][j] == VACIO) {
                tablero[i][j] = IA;
                int valor = minimax(tablero, false, MIN, MAX);
                tablero[i][j] = VACIO;

                if(valor > mejorValor) {
                    mejorValor = valor;
                    mejorMovimientoX = i;
                    mejorMovimientoY = j;
                }
            }
        }
    }

    return std::make_pair(mejorMovimientoX, mejorMovimientoY);
}

int main() {
    std::vector<std::vector<char>> tablero(3, std::vector<char>(3, VACIO));

    while(true) {
        imprimirTablero(tablero);
        int num;

        std::cout << "Turno del jugador: " << '\n';
        std::cin >> num;
        int x = (num - 1) / 3;
        int y = (num - 1) % 3;
        if(tablero[x][y] == VACIO) {
            tablero[x][y] = JUGADOR;
        } else {
            std::cout << "Celda invalida" << '\n';
            continue;
        }

        if(esGanador(tablero, JUGADOR)) {
            imprimirTablero(tablero);
            std::cout << "Gano el jugador" << '\n';
            break;
        }
        if(esEmpate(tablero)) {
            imprimirTablero(tablero);
            std::cout << "Empate" << '\n';
            break;
        }

        std::cout << "Turno de la IA: " << '\n';
        std::pair<int, int> movimiento = movimientoIA(tablero);
        tablero[movimiento.first][movimiento.second] = IA;

        if(esGanador(tablero, IA)) {
            imprimirTablero(tablero);
            std::cout << "Gano la IA" << '\n';
            break;
        }
        if(esEmpate(tablero)) {
            imprimirTablero(tablero);
            std::cout << "Empate" << '\n';
            break;
        }
    }

    return 0;
}
