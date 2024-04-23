#include <string>
#include <vector>
#include <utility>
#include <cstdlib>
#include <sstream>
#include <iostream>

#include "BMP.hpp"
#include "functions.hpp"
#include "secondary_functions.hpp"
#include "check_functions.hpp"


using namespace std;


void 
checkMirrorValues (vector <pair<string, string>> dict, Rgb** arr, int H, int W) {
    unsigned short int countValues = 0;
    int left, up, right, down, isCorrect;
    char axis;

    for (size_t i = 1; i < dict.size(); i++) {
        if (dict[i].second == "NULL") return;
        
        if (dict[i].first == "A") {
            if (dict[i].second.length() != 1 || (dict[i].second != "x" && dict[i].second != "y")) {
                cerr << "Введено некорректное значение для флага --axis" << endl;
                return;
            }
            axis = dict[i].second[0];

        } else if (dict[i].first == "L") {
            isCorrect = stringDecomposeFunc(&left, &up, dict[i].second);
            if (isCorrect != 0) {
                cerr << "Введено некорректное значение для флага --left_up" << endl;
                return;
            }

        } else if (dict[i].first == "R") {
            isCorrect = stringDecomposeFunc(&right, &down, dict[i].second);
            if (isCorrect != 0) {
                cerr << "Введено некорректное значение для флага --right_down" << endl;
                return;
            }
        
        } else if (dict[i].first == "i" || dict[i].first == "o") {
            continue;
        
        } else {
            cerr << "Введён некорректный флаг опции: " << dict[i].first << endl;
            return;
        }
        countValues++;
    }

    if (countValues == 3) {
        isCorrect = checkCoords(left, up, right, down, H, W);
        if (isCorrect != 0) {
            cerr << "Введены некорректные координаты" << endl;
            return;
        }
        mirrorFunc(arr, axis, left, up, right, down, H, W);
    } else {
        cerr << "Введены не все флаги, необходимые для опции" << endl;
    }
}


void 
checkCopyValues (vector <pair<string, string>> dict, Rgb** arr, int H, int W) {
    unsigned short int countValues = 0;
    int left, up, right, down, newLeft, newUp, isCorrect;

    for (size_t i = 1; i < dict.size(); i++) {
        if (dict[i].second == "NULL") return;
        
        if (dict[i].first == "L") {
            isCorrect = stringDecomposeFunc(&left, &up, dict[i].second);
            if (isCorrect != 0) {
                cerr << "Введено некорректное значение для флага --left_up" << endl;
                return;
            }
        } else if (dict[i].first == "R") {
            isCorrect = stringDecomposeFunc(&right, &down, dict[i].second);
            if (isCorrect != 0) {
                cerr << "Введено некорректное значение для флага --right_down" << endl;
                return;
            }
        } else if (dict[i].first == "D") {
            stringDecomposeFunc(&newLeft, &newUp, dict[i].second);
            if (isCorrect != 0) {
                cerr << "Введено некорректное значение для флага --dest_left_up" << endl;
                return;
            }
        } else if (dict[i].first == "i" || dict[i].first == "o") {
            continue;

        } else {
            cerr << "Введён некорректный флаг опции: " << dict[i].first << endl;
            return;
        }
        countValues++;
    }

    if (countValues == 3) {
        isCorrect == checkCoords(left, up, right, down, H, W);
        int copiedH, copiedW;
        copiedH = down - up;
        copiedW = right - left;
        copyFunc(arr, left, H - up - 1, right, H - down - 1, newLeft, H - newUp - 1, H, W);
    } else {
        cerr << "Введены не все флаги, необходимые для опции" << endl;
    }
}


void
checkReplaceValues (vector <pair<string, string>> dict, Rgb** arr, int H, int W) {
    unsigned short int countValues = 0;
    int r, g, b, newR, newG, newB, isCorrect;

    for (size_t i = 1; i < dict.size(); i++) {
        if (dict[i].second == "NULL") return;
        
        if (dict[i].first == "O") {
            isCorrect = colorDecomposeFunc(&r, &g, &b, dict[i].second);
            if (isCorrect == 1) {
                cerr << "Введено некорректное значение для флага --old_color" << endl;
                return;
            }
            if (isCorrect == 2) {
                cerr << "Введено некорректное знаение компоненты цвета" << endl;
                return;
            }
        } else if (dict[i].first == "N") {
            isCorrect = colorDecomposeFunc(&newR, &newG, &newB, dict[i].second);
            if (isCorrect == 1) {
                cerr << "Введено некорректное значение для флага --old_color" << endl;
                return;
            }
            if (isCorrect == 2) {
                cerr << "Введено некорректное знаение компоненты цвета" << endl;
                return;
            }
        } else if (dict[i].first == "i" || dict[i].first == "o") {
            continue;

        } else {
            cerr << "Введён некорректный флаг опции: " << dict[i].first << endl;
            return;
        }
        countValues++;
    }

    if (countValues == 2) {
        replaceFunc(arr, r, g, b, newR, newG, newB, H, W);
    } else {
        cerr << "Введены не все флаги, необходимые для опции" << endl;
        return;
    }
}


void
checkFilterValues(vector <pair<string, string>> dict, Rgb** arr, int H, int W) {
    unsigned short int countValues = 0;
    string component;
    size_t compVal;

    for (size_t i = 1; i < dict.size(); i++) {
        if (dict[i].second == "NULL") return;

        if (dict[i].first == "C") {
            component = dict[i].second;
            if (component != "red" && component != "blue" && component != "green") {
                cerr << "Введено некорректное значение для флага --component_name" << endl;
                return;
            }
        } else if (dict[i].first == "V") {
            stringstream s;
            s << dict[i].second;
            s >> compVal;
            if (s.str() != to_string(compVal) || compVal < 0 || compVal > 255) {
                cerr << "Введено некорректное значение для флага --component_value" << endl;
                return;
            }
        }else if (dict[i].first == "i" || dict[i].first == "o") {
            continue;

        } else {
            cerr << "Введён некорректный флаг опции: " << dict[i].first << endl;
            return;
        }
        countValues++;
    }

    if (countValues == 2) {
        filterFunc(arr, component, compVal, H, W);
    } else {
        cerr << "Введены не все флаги, необходимые для опции" << endl;
        return;
    }
}