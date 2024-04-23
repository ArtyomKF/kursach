#include <cstdio>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>

#include "BMP.hpp"
#include "secondary_functions.hpp"
#include "secondary_functions.hpp"


using namespace std;


void print_file_header (BitmapFileHeader header) {
    printf("signature:\t%x (%hu)\n", header.signature, header.signature);
    printf("filesize:\t%x (%u)\n", header.filesize, header.filesize);
    printf("reserved1:\t%x (%hu)\n", header.reserved1, header.reserved1);
    printf("reserved2:\t%x (%hu)\n", header.reserved2, header.reserved2);
    printf("pixelArrOffset:\t%x (%u)\n", header.pixelArrOffset, header.pixelArrOffset);
} 


void print_info_header (BitmapInfoHeader header) {
    printf("headerSize:\t%x (%u)\n", header.headerSize, header.headerSize);
    printf("width: \t%x (%u)\n", header.width, header.width);
    printf("height: \t%x (%u)\n", header.height, header.height);
    printf("planes: \t%x (%hu)\n", header.planes, header.planes);
    printf("bitsPerPixel:\t%x (%hu)\n", header.bitsPerPixel, header.bitsPerPixel);
    printf("compression:\t%x (%u)\n", header.compression, header.compression);
    printf("imageSize:\t%x (%u)\n", header.imageSize, header.imageSize);
    printf("xPixelsPerMeter:\t%x (%u)\n", header.xPixelsPerMeter, header.xPixelsPerMeter);
    printf("yPixelsPerMeter:\t%x (%u)\n", header.yPixelsPerMeter, header.yPixelsPerMeter);
    printf("colorsInColorTable:\t%x (%u)\n", header.colorsInColorTable, header.colorsInColorTable);
    printf("importantColorCount:\t%x (%u)\n", header.importantColorCount, header.importantColorCount);
}


Rgb**
read_bmp (const char file_name[], BitmapFileHeader* bmfh, BitmapInfoHeader* bmif) {
    FILE* f = fopen(file_name, "rb");

    fread(bmfh, 1, sizeof(BitmapFileHeader), f);
    fread(bmif, 1, sizeof(BitmapInfoHeader), f);

    unsigned int H = bmif->height;
    unsigned int W = bmif->width;

    Rgb** arr;
    arr = (Rgb**)malloc(H * sizeof(Rgb*));

    for (size_t i = 0; i < H; i++) {
        arr[i] = (Rgb*)malloc(W * sizeof(Rgb) + (W * 3) % 4);
        fread(arr[i], 1, W * sizeof(Rgb) + (W * 3) % 4, f);
    }

    fclose(f);

    return arr;
}


void
write_bmp (const char file_name[], Rgb** arr, int H, int W, BitmapFileHeader bmfh, BitmapInfoHeader bmif) {
    FILE* ff = fopen(file_name, "wb");

    fwrite(&bmfh, 1, sizeof(BitmapFileHeader), ff);
    fwrite(&bmif, 1, sizeof(BitmapInfoHeader), ff);

    for (size_t i = 0; i < H; i++) {
        fwrite(arr[i], 1, W * sizeof(Rgb) + (W * 3) % 4, ff);
    }

    fclose(ff);
}


int
stringDecomposeFunc(int* first, int* second, string value) {
    char dot;
    istringstream sd(value);
    sd >> *first >> dot >> *second;
    sd.clear();

    if (sd.fail() || dot != '.') return 1;
    return 0;
}


int
colorDecomposeFunc(int* r, int* g, int* b, string value) {
    char dot1, dot2;
    istringstream sd(value);

    sd >> *r >> dot1 >> *g >> dot2 >> *b;
    sd.clear();

    if (sd.fail() || dot1 != '.' || dot2 != '.') return 1;

    if (*r > 255 || *r < 0 || *b > 255 || *b < 0 || *g > 255 || *g < 0) return 2;

    return 0;
}


int
checkCoords (int left, int up, int right, int down, int H, int W) {
    if (left >= right || down <= up) {
        cerr << "Координаты точек не соответствуют друг другу" << endl;
        return 1;
    }
    if (right >= W || down >= H || left < 0 || up < 0) {
        cerr << "Выход за границы изображения" << endl;
        return 1;
    }
    return 0;
}


int
findInputFile (vector <pair<string, string>> dict, string* InputFileName) {
    for (size_t i = 0; i < dict.size(); i++) {
        if (dict[i].first == "i" && dict[i].second != "NULL") {
            (*InputFileName) = dict[i].second;
            return 1;
        }
    }
    return 0;
}


void
findOutputFile (vector <pair<string, string>> dict, string* OutputFileName) {
    for (size_t i = 0; i < dict.size(); i++) {
        if (dict[i].first == "o" && dict[i].second != "NULL") {
            (*OutputFileName) = dict[i].second;
            return;
        }
    }
}


int // 0 - wrong file; 1 - normal file
checkFileName (string filename) {
    if (filename.size() < 5) return 0;

    size_t dotPos = 0;
    string extension;
    for (size_t i = 0; i < filename.size(); i++) {
        if (filename[i] == '.') {
            if (i == 0 || dotPos != 0) return 0;
            dotPos = i;
        }
        if (dotPos != 0) {
            extension += filename[i];
        }
    }
    return (extension == ".bmp");
}