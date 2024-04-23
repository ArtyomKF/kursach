#include <cstdlib>
#include <string>
#include <iostream>

#include "BMP.hpp"
#include "functions.hpp"


void
mirrorFunc (Rgb** arr, char axis, int left, int up, int right, int down, int H, int W) {
    unsigned char r, g, b;
    Rgb a;

    if (axis == 'x') {
        for (size_t y = H - 1 - down; y < H - (up + down) / 2; y++) {
            for (size_t x = left; x < right; x++) {
                a = arr[y][x];
                arr[y][x] = arr[2 * H - up - down - 2 - y][x];
                arr[2 * H - up - down - 2 - y][x] = a;
            }
        }
    } else if (axis == 'y') {
        for (size_t y = H - 1 - down; y < H - up; y++) {
            for (size_t x = left; x < (left + right) / 2 + 1; x++) {
                a = arr[y][x];
                arr[y][x] = arr[y][left + right - x - 1];
                arr[y][left + right - x - 1] = a;
            }
        }
    }
}


void
copyFunc(Rgb** arr, int left, int up, int right, int down, int newLeft, int newUp, int H, int W) {
    Rgb** temporaryArr = new Rgb* [up - down];

    for (size_t i = 0; i < up - down; i++) {
        temporaryArr[i] = new Rgb [right - left];
        for (size_t j = 0; j < right - left; j++) {
            temporaryArr[i][j] = arr[up - i][left + j];
        }
    }

    for (size_t i = 0; i < up - down; i++) {
        for (size_t j = 0; j < right - left; j++) {
            if (newUp - i >= H || newUp - i < 0 || newLeft + j >= W || newLeft + j < 0) continue;
            arr[newUp - i][newLeft + j] = temporaryArr[i][j];
        }
        delete [] temporaryArr[i];
    }
    delete [] temporaryArr;
}


void
replaceFunc(Rgb** arr, int r, int g, int b, int newR, int newG, int newB, int H, int W) {
    for (size_t y = 0; y < H; y++) {
        for (size_t x = 0; x < W; x++) {
            if (arr[y][x].r == r && arr[y][x].b == b && arr[y][x].g == g) {
                arr[y][x].r = newR;
                arr[y][x].g = newG;
                arr[y][x].b = newB;
            }
        }
    }
}


void
filterFunc(Rgb** arr, std::string component, int compVal, int H, int W) {
    for (size_t y = 0; y < H; y++) {
        for (size_t x = 0; x < W; x++) {
            if (component == "red") {
                arr[y][x].r = compVal;
            } else if (component == "blue") {
                arr[y][x].b = compVal;
            } else if (component == "green") {
                arr[y][x].g = compVal;
            }
        }
    }
}


void
printHelp () {
    std::cout << "Course work for option 5.10, created by Artem Khannanov\n\n";
    std::cout << "Описание функций:\n\n\
    --mirror - отражение заданной области;\n\
        --axis - ось, по которой будет отражение\n\
        --left_up - верхняя левая координата области\n\
        --right_down - правая нижняя координата области\n\
    --copy - копирование заданной области и вставка её в впо другим координатам;\n\
        --left_up - верхняя левая координата области\n\
        --right_down - правая нижняя координата области\n\
        --dest_left_up - верхняя левая координата новой области\n\
    --color_replace - замена одного цвета на другой по всему изображению;\n\
        --old_color - старый цвет\n\
        --new_color - новый цвет\n\
    --rgbfilter - замена компонента цвета на заданное значение по всему изображению;\n\
        --component_name - название компоненты\n\
        --component_value - новое значение компоненты\n";
}