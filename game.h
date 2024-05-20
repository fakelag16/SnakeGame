#ifndef GAME_H
#define GAME_H

#include <windows.h>

// ��������� ��� �������� �������� ���� � ������������ ����� ������
const int WIDTH = 20; // ������ �������� ����
const int HEIGHT = 10; // ������ �������� ����
const int MAX_LEN_SNAKE = (WIDTH - 3) * (HEIGHT - 2); // ������������ ����� ������

// ��������� ��� ����������� �������� ������
const int UP = 0;    // ����������� �����
const int DOWN = 1;  // ����������� ����
const int LEFT = 2;  // ����������� �����
const int RIGHT = 3; // ����������� ������

// ���������� ����������
extern int snake_dir; // ������� ����������� �������� ������
extern int snake_x[MAX_LEN_SNAKE]; // ���������� ������ ������ �� x
extern int snake_y[MAX_LEN_SNAKE]; // ���������� ������ ������ �� y
extern int snake_len; // ������� ����� ������
extern int food_x; // ���������� ��� �� x
extern int food_y; // ���������� ��� �� y

// ������� ����
void generateFood(); // ������� ��� ��������� ���
void drawMap(); // ������� ��� ��������� �����
void clearInputBuffer(); // ������� ��� ������� ������ �����
void startGame(); // �������� ������� ��� ������� ����

#endif // GAME_H
