// Подключаем необходимые библиотеки и заголовочные файлы
#include "game.h" // Заголовочный файл игры
#include <string> // Библиотека для работы со строками
#include <iostream> // Библиотека для ввода-вывода
#include <Windows.h> // Библиотека для работы с функциями Windows
#include <ctime> // Библиотека для работы со временем
#include "utility.h" // Дополнительный заголовочный файл с утилитами
#include "resource.h" // Заголовочный файл для ресурсов

// Используем пространство имен std для упрощения синтаксиса
using namespace std;

int snake_dir = RIGHT; // Изначально змейка движется вправо
int snake_x[MAX_LEN_SNAKE] = { 0 };
int snake_y[MAX_LEN_SNAKE] = { 0 };
int snake_len = 1;
int food_x;
int food_y;
char map[HEIGHT + 1][WIDTH + 1] = {
    "####################",
    "#                  #",
    "#                  #",
    "#                  #",
    "#                  #",
    "#                  #",
    "#                  #",
    "#                  #",
    "#                  #",
    "####################"
};
char snake = '0';
char food = '*';

// Функция для генерации еды
void generateFood() {
    food_x = 1 + (rand() % (WIDTH - 2));
    food_y = 1 + (rand() % (HEIGHT - 2));
}

// Функция для отрисовки карты и змейки
void drawMap() {
    gotoxy(0, 0);
    cout << "Length: " << snake_len << endl;
    map[food_y][food_x] = food;
    for (int i = 0; i < snake_len; i++) {
        map[snake_y[i]][snake_x[i]] = snake;
    }
    for (int i = 0; i < HEIGHT; i++) {
        cout << map[i] << endl;
    }
    for (int i = 0; i < snake_len; i++) {
        map[snake_y[i]][snake_x[i]] = ' ';
    }
}

// Функция для очистки буфера ввода
void clearInputBuffer() {
    cin.clear();
}

// Основная функция для запуска игры
void startGame() {
    srand(static_cast<unsigned int>(time(0)));

    bool readyToPlay = true;

    while (readyToPlay) {
        cout << "Press 1 if you are ready or press any other button to exit the game" << endl;
        int number;
        cin >> number;
        clearInputBuffer();
        if (number != 1) {
            bool validInput = false;
            while (!validInput) {
                cout << "Are you sure? (Yes/No)" << endl;
                string answerForClosing;
                cin >> answerForClosing;
                clearInputBuffer();

                if (answerForClosing == "Yes") {
                    readyToPlay = false;
                    validInput = true;
                    cout << "Closing game..." << endl;
                }
                else if (answerForClosing == "No") {
                    validInput = true;
                    cout << "Starting game..." << endl;
                }
            }
        }
        else {
            bool isRunning = true;
            snake_len = 1;
            snake_dir = RIGHT;
            snake_x[0] = WIDTH / 3;
            snake_y[0] = HEIGHT / 2;
            generateFood();

            double lastTime = static_cast<double>(clock());
            const double delay = 0.1 * CLOCKS_PER_SEC;

            while (isRunning) {
                int new_dir = snake_dir;

                if (GetAsyncKeyState('W') & 0x8000) {
                    new_dir = UP;
                }
                if (GetAsyncKeyState('A') & 0x8000) {
                    new_dir = LEFT;
                }
                if (GetAsyncKeyState('S') & 0x8000) {
                    new_dir = DOWN;
                }
                if (GetAsyncKeyState('D') & 0x8000) {
                    new_dir = RIGHT;
                }

                if ((snake_dir == UP && new_dir != DOWN) ||
                    (snake_dir == DOWN && new_dir != UP) ||
                    (snake_dir == LEFT && new_dir != RIGHT) ||
                    (snake_dir == RIGHT && new_dir != LEFT)) {
                    snake_dir = new_dir;
                }

                double currentTime = static_cast<double>(clock());

                if (currentTime - lastTime >= delay) {
                    lastTime = currentTime;

                    if (snake_x[0] == food_x && snake_y[0] == food_y) {
                        snake_len++;
                        generateFood();
                    }

                    for (int i = snake_len - 1; i > 0; i--) {
                        snake_x[i] = snake_x[i - 1];
                        snake_y[i] = snake_y[i - 1];
                    }

                    if (snake_dir == UP) {
                        --snake_y[0];
                    }
                    if (snake_dir == DOWN) {
                        ++snake_y[0];
                    }
                    if (snake_dir == LEFT) {
                        --snake_x[0];
                    }
                    if (snake_dir == RIGHT) {
                        ++snake_x[0];
                    }

                    if (snake_x[0] <= 0 || snake_y[0] <= 0 || snake_x[0] >= WIDTH - 1 || snake_y[0] >= HEIGHT - 1) {
                        cout << "Game Over! Reason: Hit the wall" << endl;
                        isRunning = false;
                    }

                    for (int i = 1; i < snake_len; i++) {
                        if (snake_x[0] == snake_x[i] && snake_y[0] == snake_y[i]) {
                            cout << "Game Over! Reason: Hit itself" << endl;
                            isRunning = false;
                            break;
                        }
                    }

                    drawMap();
                }
            }

            gotoxy(1, HEIGHT / 2);
            cout << "  YOUR SCORE IS: " << endl << "         " << snake_len;
            gotoxy(WIDTH, HEIGHT);
        }
    }
}

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wcex;
    ZeroMemory(&wcex, sizeof(WNDCLASSEX));
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = DefWindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"SampleWindowClass";
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

    if (!RegisterClassEx(&wcex)) {
        MessageBox(NULL, L"Call to RegisterClassEx failed!", L"Windows Desktop Guided Tour", NULL);
        return 1;
    }

    HWND hWnd = CreateWindow(
        L"SampleWindowClass",
        L"Sample Window",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hWnd) {
        MessageBox(NULL, L"Call to CreateWindow failed!", L"Windows Desktop Guided Tour", NULL);
        return 1;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // Ваш основной игровой цикл здесь
    startGame();

    return 0;
}
