#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

#include "BMP.hpp"
#include "functions.hpp"
#include "check_functions.hpp"
#include "secondary_functions.hpp"
#include "inputFunctions.hpp"


using namespace std;


int main (int argc, char* argv[]) {
    int isCorrectFile, valuesCount;
    string InputFileName, OutputFileName;
    vector <pair<string, string>> optDict;
    BitmapFileHeader bmfh;
    BitmapInfoHeader bmif;

    // Считывание данных, первичная проверка ввода
    valuesCount = inputFunction(&optDict, argc, argv);
    if (valuesCount == 0) {
        cerr << "Введите данные для работы программы" << endl;
        return 40;
    }
    if (optDict[0].first == "h") {
        printHelp();
        return 0;
    }
    // ----------------------

    // Обработка входного файла
    if (argc - 1 > valuesCount) {
        InputFileName = argv[argc - 1];
    } else {
        if (findInputFile(optDict, &InputFileName) == 0) {
            cerr << "Введите название входного файла" << endl;
            return 40;
        }
    }
    isCorrectFile = checkFileName(InputFileName);
    if (isCorrectFile == 0) {
        cerr << "Введено некорректное имя входного файла" << endl;
        return 40;
    }
    // -----------------------

    // Обработка выходного файла
    OutputFileName = "out.bmp";
    findOutputFile(optDict, &OutputFileName);
    isCorrectFile = checkFileName(OutputFileName);
    if (isCorrectFile == 0) {
        cerr << "Введено некорректное имя выходного файла" << endl;
        return 40;
    }
    // -----------------------

    // Проверка входного и выходного файлов на равенство
    if (OutputFileName == InputFileName) {
        cerr << "Входной и выходной файлы должны иметь разные названия" << endl;
        return 41;
    }
    // -----------------------

    Rgb** arr = read_bmp(InputFileName.c_str(), &bmfh, &bmif);
    if (bmif.headerSize != 40 || bmif.compression != 0 || bmif.bitsPerPixel != 24) {
        cerr << "Входной файл имеет неподдерживаемую версию bmp" << endl;
        return 49;
    }

    if (optDict[0].first == "I") {
        print_info_header(bmif);
        cout << "\n";
        print_file_header(bmfh);
        return 0;
    }

    if (optDict[0].first == "m") {
        checkMirrorValues(optDict, arr, bmif.height, bmif.width);

    } else if (optDict[0].first == "c") {
        checkCopyValues(optDict, arr, bmif.height, bmif.width);

    } else if (optDict[0].first == "r") {
        checkReplaceValues(optDict, arr, bmif.height, bmif.width);

    } else if (optDict[0].first == "f") {
        checkFilterValues(optDict, arr, bmif.height, bmif.width);

    } else {
        cerr << "Введены неверные данные" << endl;
        return 49;
    }

    write_bmp(OutputFileName.c_str(), arr, bmif.height, bmif.width, bmfh, bmif);

    return 0;
}
