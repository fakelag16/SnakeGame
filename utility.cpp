#include <Windows.h> // ���������� ���������� ��� ������ � ��������� Windows
#include "utility.h" // ���������� ������������ ���� � ���������

// ������� ��� ����������� ������� � ������� � �������� ������� (x, y)
void gotoxy(int x, int y) {
    COORD pos = { (SHORT)x, (SHORT)y }; // ������� ��������� COORD ��� �������� ���������
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE); // �������� ���������� ��� ������������ ������
    SetConsoleCursorPosition(output, pos); // ������������� ������� ������� � �������
}
