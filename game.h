#ifndef GAME_H
#define GAME_H

#include <windows.h>

// Константы для размеров игрового поля и максимальной длины змейки
const int WIDTH = 20; // Ширина игрового поля
const int HEIGHT = 10; // Высота игрового поля
const int MAX_LEN_SNAKE = (WIDTH - 3) * (HEIGHT - 2); // Максимальная длина змейки

// Константы для направлений движения змейки
const int UP = 0;    // Направление вверх
const int DOWN = 1;  // Направление вниз
const int LEFT = 2;  // Направление влево
const int RIGHT = 3; // Направление вправо

// Глобальные переменные
extern int snake_dir; // Текущее направление движения змейки
extern int snake_x[MAX_LEN_SNAKE]; // Координаты частей змейки по x
extern int snake_y[MAX_LEN_SNAKE]; // Координаты частей змейки по y
extern int snake_len; // Текущая длина змейки
extern int food_x; // Координата еды по x
extern int food_y; // Координата еды по y

// Функции игры
void generateFood(); // Функция для генерации еды
void drawMap(); // Функция для отрисовки карты
void clearInputBuffer(); // Функция для очистки буфера ввода
void startGame(); // Основная функция для запуска игры

#endif // GAME_H
