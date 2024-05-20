#include <Windows.h> // Подключаем библиотеку для работы с функциями Windows
#include "utility.h" // Подключаем заголовочный файл с утилитами

// Функция для перемещения курсора в консоли в заданную позицию (x, y)
void gotoxy(int x, int y) {
    COORD pos = { (SHORT)x, (SHORT)y }; // Создаем структуру COORD для хранения координат
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE); // Получаем дескриптор для стандартного вывода
    SetConsoleCursorPosition(output, pos); // Устанавливаем позицию курсора в консоли
}
