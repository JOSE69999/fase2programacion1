#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>

using namespace std;

void gotoxy(int x, int y) {
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hCon, dwPos);
}

void limpiarLinea(int y, int length) {
    gotoxy(0, y);
    for (int i = 0; i < length; i++) {
        cout << " ";
    }
    gotoxy(0, y); // Restaurar el cursor al inicio de la línea
}

void ajustarCoordenadas(int& x, int& y, int maxX, int maxY) {
    x = (x % maxX + maxX) % maxX;
    y = (y % maxY + maxY) % maxY;
}

void dibujarTriangulo(int base, int x, int y, char caracter, int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    int maxX = csbi.dwSize.X;
    int maxY = csbi.dwSize.Y;

    SetConsoleTextAttribute(hConsole, color);
    for (int i = 0; i < base; i++) {
        for (int j = 0; j < 2 * i + 1; j++) {
            int newX = x - i + j;
            int newY = y + i;
            ajustarCoordenadas(newX, newY, maxX, maxY);
            gotoxy(newX, newY);
            if (i == base - 1 || j == 0 || j == 2 * i) {
                cout << caracter;
            } else {
                cout << " ";
            }
        }
    }
    SetConsoleTextAttribute(hConsole, 15); // Restaurar color predeterminado
}

void mostrarColores() {
    cout << "Seleccione un color para la figura:" << endl;
    cout << "1. Azul" << endl;
    cout << "2. Verde" << endl;
    cout << "3. Cyan" << endl;
    cout << "4. Rojo" << endl;
    cout << "5. Púrpura" << endl;
    cout << "6. Amarillo" << endl;
    cout << "7. Blanco" << endl;
}

int elegirColor() {
    char tecla = _getch();
    switch (tecla) {
        case '1': return 9;  // Azul
        case '2': return 10; // Verde
        case '3': return 11; // Cyan
        case '4': return 12; // Rojo
        case '5': return 13; // Púrpura
        case '6': return 14; // Amarillo
        case '7': return 15; // Blanco
        default: return 15;  // Blanco por defecto
    }
}

void dibujarCuadrado(int lado, int x, int y, char caracter, int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    int maxX = csbi.dwSize.X;
    int maxY = csbi.dwSize.Y;

    SetConsoleTextAttribute(hConsole, color);
    for (int i = 0; i < lado; i++) {
        for (int j = 0; j < lado; j++) {
            int newX = x + j * 2;
            int newY = y + i;
            ajustarCoordenadas(newX, newY, maxX, maxY);
            gotoxy(newX, newY);
            if (i == 0 || i == lado - 1 || j == 0 || j == lado - 1) {
                cout  << caracter<< ' ';
            } else {
                cout << ' ';
            }
        }
    }
    SetConsoleTextAttribute(hConsole, 15); // Restaurar color predeterminado
}

void dibujarRectangulo(int base, int altura, int x, int y, char caracter, int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    int maxX = csbi.dwSize.X;
    int maxY = csbi.dwSize.Y;

    SetConsoleTextAttribute(hConsole, color);
    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < base; j++) {
            int newX = x + j *2;
            int newY = y + i;
            ajustarCoordenadas(newX, newY, maxX, maxY);
            gotoxy(newX, newY);
            if (i == 0 || i == altura - 1 || j == 0 || j == base - 1) {
                cout << caracter << " ";
            } else {
                cout << "  ";
            }
        }
    }
    SetConsoleTextAttribute(hConsole, 15); // Restaurar color predeterminado
}

void dibujarCirculo(int diametro, int x, int y, char caracter, int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    int maxX = csbi.dwSize.X;
    int maxY = csbi.dwSize.Y;

    SetConsoleTextAttribute(hConsole, color);
    int radio = diametro / 2;
    for (int i = -radio; i <= radio; i++) {
        for (int j = -radio; j <= radio; j++) {
            if (i * i + j * j <= radio * radio) {
                int newX = x + j;
                int newY = y + i;
                ajustarCoordenadas(newX, newY, maxX, maxY);
                gotoxy(newX, newY);
                cout << caracter;
            }
        }
    }
    SetConsoleTextAttribute(hConsole, 15); // Restaurar color predeterminado
}

void dibujarRombo(int lado, int x, int y, char caracter, int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    int maxX = csbi.dwSize.X;
    int maxY = csbi.dwSize.Y;

    SetConsoleTextAttribute(hConsole, color);
    for (int i = 0; i < lado; i++) {
        int newX1 = x - i;
        int newY1 = y + i;
        ajustarCoordenadas(newX1, newY1, maxX, maxY);
        gotoxy(newX1, newY1);
        cout << caracter;

        int newX2 = x + i;
        int newY2 = y + i;
        ajustarCoordenadas(newX2, newY2, maxX, maxY);
        gotoxy(newX2, newY2);
        cout << caracter;
    }
    for (int i = lado - 2; i >= 0; i--) {
        int newX1 = x - i;
        int newY1 = y + 2 * (lado - 1) - i;
        ajustarCoordenadas(newX1, newY1, maxX, maxY);
        gotoxy(newX1, newY1);
        cout << caracter;

        int newX2 = x + i;
        int newY2 = y + 2 * (lado - 1) - i;
        ajustarCoordenadas(newX2, newY2, maxX, maxY);
        gotoxy(newX2, newY2);
        cout << caracter;
    }
    SetConsoleTextAttribute(hConsole, 15); // Restaurar color predeterminado
}

void dibujarLinea(int longitud, int x, int y, char direccion, char caracter, int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    int maxX = csbi.dwSize.X;
    int maxY = csbi.dwSize.Y;

    SetConsoleTextAttribute(hConsole, color);
    for (int i = 0; i < longitud; i++) {
        int newX = x, newY = y;
        switch (direccion) {
            case '1': // Arriba diagonal
                newX += i;
                newY -= i;
                break;
            case '2': // Abajo diagonal
                newX += i;
                newY += i;
                break;
            case '3': // Derecha horizontal
                newX += i;
                break;
            case '4': // Izquierda horizontal
                newX -= i;
                break;
        }
        ajustarCoordenadas(newX, newY, maxX, maxY);
        gotoxy(newX, newY);
        cout << caracter;
    }
    SetConsoleTextAttribute(hConsole, 15); // Restaurar color predeterminado
}

void dibujarHexagono(int lado, int x, int y, char caracter, int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    int maxX = csbi.dwSize.X;
    int maxY = csbi.dwSize.Y;

    int altura = 2 * lado;
    SetConsoleTextAttribute(hConsole, color);

    // Dibujar la parte superior del hexágono
    for (int i = 0; i < lado; i++) {
        int newX1 = x - i;
        int newY1 = y + i;
        ajustarCoordenadas(newX1, newY1, maxX, maxY);
        gotoxy(newX1, newY1);
        cout << caracter;

        int newX2 = x + lado + i;
        int newY2 = y + i;
        ajustarCoordenadas(newX2, newY2, maxX, maxY);
        gotoxy(newX2, newY2);
        cout << caracter;
    }

    // Dibujar la parte media del hexágono
    for (int i = 0; i < altura; i++) {
        int newX1 = x - lado;
        int newY1 = y + lado + i;
        ajustarCoordenadas(newX1, newY1, maxX, maxY);
        gotoxy(newX1, newY1);
        cout << caracter;

        int newX2 = x + 2 * lado - 1;
        int newY2 = y + lado + i;
        ajustarCoordenadas(newX2, newY2, maxX, maxY);
        gotoxy(newX2, newY2);
        cout << caracter;
    }

    // Dibujar la parte inferior del hexágono
    for (int i = 0; i < lado; i++) {
        int newX1 = x - i;
        int newY1 = y + altura + i;
        ajustarCoordenadas(newX1, newY1, maxX, maxY);
        gotoxy(newX1, newY1);
        cout << caracter;

        int newX2 = x + lado + i;
        int newY2 = y + altura + i;
        ajustarCoordenadas(newX2, newY2, maxX, maxY);
        gotoxy(newX2, newY2);
        cout << caracter;
    }

    SetConsoleTextAttribute(hConsole, 15); // Restaurar color predeterminado
}

void guardarPantalla(const string& nombreArchivo) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    COORD bufferSize = csbi.dwSize;
    COORD bufferCoord = { 0, 0 };
    SMALL_RECT readRegion = { 0, 0, bufferSize.X - 1, bufferSize.Y - 1 };
    CHAR_INFO* buffer = new CHAR_INFO[bufferSize.X * bufferSize.Y];

    if (ReadConsoleOutput(hConsole, buffer, bufferSize, bufferCoord, &readRegion)) {
        ofstream archivo(nombreArchivo);
        if (archivo.is_open()) {
            for (int y = 0; y < bufferSize.Y; ++y) {
                for (int x = 0; x < bufferSize.X; ++x) {
                    archivo << buffer[y * bufferSize.X + x].Char.AsciiChar;
                }
                archivo << endl;
            }
            archivo.close();
            cout << "Pantalla guardada en " << nombreArchivo << endl;
        } else {
            cout << "No se pudo abrir el archivo." << endl;
        }
    } else {
        cout << "No se pudo leer la consola." << endl;
    }

    delete[] buffer;
}

int main() {
    int base, altura, lado, longitud;
    char direccion;
    char caracter = '*';  // Carácter por defecto
    int color = 15;
    int x = 10, y = 10;

    while (true) {
        gotoxy(x, y);

        if (_kbhit()) {
            int tecla = _getch();
            gotoxy(x, y); // Restaurar el cursor a la posición anterior sin dibujar nada

            switch (tecla) {
                case 72: y--; break; // Arriba
                case 80: y++; break; // Abajo
                case 75: x--; break; // Izquierda
                case 77: x++; break; // Derecha
                case 59: // Triángulo (F1)
                    limpiarLinea(25, 80);
                    gotoxy(0, 25);
                    cout << "Ingrese la base del triangulo: ";
                    cin >> base;
                    limpiarLinea(25, 80); // Borra el texto después de ingresar la base
                    gotoxy(x, y);
                    dibujarTriangulo(base, x, y, caracter, color);
                    break;
                case 60: // Cuadrado (F2)
                    limpiarLinea(25, 80);
                    gotoxy(0, 25);
                    cout << "Ingrese la longitud del lado del cuadrado: ";
                    cin >> lado;
                    limpiarLinea(25, 80); // Borra el texto después de ingresar la longitud del lado
                    gotoxy(x, y);
                    dibujarCuadrado(lado, x, y, caracter, color);
                    break;
                case 61: // Rectángulo (F3)
                    limpiarLinea(25, 80);
                    gotoxy(0, 25);
                    cout << "Ingrese la base del rectangulo: ";
                    cin >> base;
                    limpiarLinea(25, 80);
                    cout << "Ingrese la altura del rectangulo: ";
                    cin >> altura;
                    limpiarLinea(25, 80); // Borra el texto después de ingresar la base y altura
                    gotoxy(x, y);
                    dibujarRectangulo(base, altura, x, y, caracter, color);
                    break;
                case 62: // Círculo (F4)
                    limpiarLinea(25, 80);
                    gotoxy(0, 25);
                    cout << "Ingrese el diametro del circulo: ";
                    cin >> base;
                    limpiarLinea(25, 80); // Borra el texto después de ingresar el diámetro
                    gotoxy(x, y);
                    dibujarCirculo(base, x, y, caracter, color);
                    break;
                case 63: // Línea (F5)

                    gotoxy(0, 25);
                    cout << "Orientacion de la linea:" << endl;
                    cout << "1. Arriba diagonal" << endl;
                    limpiarLinea(25, 80);
                    cout << "2. Abajo diagonal" << endl;
                    limpiarLinea(25, 80);
                    cout << "3. Derecha horizontal" << endl;
                    limpiarLinea(25, 80);
                    cout << "4. Izquierda horizontal" << endl;
                    limpiarLinea(25, 80);
                    cin >> direccion;
                    limpiarLinea(25, 80);
                    gotoxy(0, 25);
                    cout << "Ingrese la longitud de la linea: ";
                    cin >> longitud;
                    limpiarLinea(25, 80); // Borra el texto después de ingresar la dirección y longitud
                    gotoxy(x, y);
                    dibujarLinea(longitud, x, y, direccion, caracter, color);
                    break;
                case 64: // Rombo (F6)
                    limpiarLinea(25, 80);
                    gotoxy(0, 25);
                    cout << "Ingrese la longitud de los lados del rombo: ";
                    cin >> lado;
                    limpiarLinea(25, 80); // Borra el texto después de ingresar la longitud de los lados
                    gotoxy(x, y);
                    dibujarRombo(lado, x, y, caracter, color);
                    break;
                case 65: // Hexágono (F7)
                    limpiarLinea(25, 80);
                    gotoxy(0, 25);
                    cout << "Ingrese la longitud de los lados del hexagono: ";
                    cin >> lado;
                    limpiarLinea(25, 80); // Borra el texto después de ingresar la longitud de los lados
                    gotoxy(x, y);
                    dibujarHexagono(lado, x, y, caracter, color);
                    break;
                case 66: // Nuevo carácter (F8)
                    limpiarLinea(25, 80);
                    gotoxy(0, 25);
                    cout << "Ingrese el nuevo caracter: ";
                    cin >> caracter;
                    limpiarLinea(25, 80);
                    gotoxy(x, y);
                    break;
                case 67: // Limpiar pantalla (F9)
                    system("cls");
                    break;
                case 68:// Color (F10)
                    limpiarLinea(25, 80);
                    gotoxy(0, 25);
                    mostrarColores();
                    color = elegirColor();
                    limpiarLinea(25, 80);
                    gotoxy(x, y);
                    break;
                case 57: // Guardar pantalla (9)
                    limpiarLinea(25, 80);
                    gotoxy(0, 25);
                    cout << "Ingrese el nombre del archivo (con ruta): ";
                    {
                        string nombreArchivo;
                        cin >> nombreArchivo;
                        limpiarLinea(25, 80); // Borra el texto después de ingresar el nombre del archivo
                        guardarPantalla(nombreArchivo);
                    }
                    gotoxy(x, y);
                    break;
                case 1: // Abrir archivo (Ctrl + A)
                    limpiarLinea(25, 80);
                    gotoxy(0, 25);
                    cout << "Ingrese la ruta del archivo: ";
                    {
                        string rutaArchivo;
                        cin >> rutaArchivo;
                        limpiarLinea(25, 80); // Borra el texto después de ingresar la ruta del archivo
                        ifstream archivo(rutaArchivo);
                        if (archivo.is_open()) {
                            string linea;
                            int fila = 0;
                            while (getline(archivo, linea)) {
                                gotoxy(0, fila++);
                                cout << linea << endl;
                            }
                            archivo.close();
                        } else {
                            cout << "No se pudo abrir el archivo." << endl;
                        }
                    }
                    gotoxy(x, y);
                    break;
            }
        }
        Sleep(1); // Ajusta la velocidad de actualización
    }

    return 0;
}

