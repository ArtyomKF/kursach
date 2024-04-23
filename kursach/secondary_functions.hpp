Rgb**
read_bmp (const char file_name[], BitmapFileHeader* bmfh, BitmapInfoHeader* bmif);

void
write_bmp (const char file_name[], Rgb** arr, int H, int W, BitmapFileHeader bmfh, BitmapInfoHeader bmif);

int
stringDecomposeFunc(int* first, int* second, std::string value);

int
colorDecomposeFunc(int* r, int* g, int* b, std::string value);

void 
print_file_header (BitmapFileHeader header);

void 
print_info_header (BitmapInfoHeader header);

int
checkCoords (int left, int up, int right, int down, int H, int W);

int
findInputFile (std::vector <std::pair<std::string, std::string>> dict, std::string* InputFileName);

void
findOutputFile (std::vector <std::pair<std::string, std::string>> dict, std::string* OutputFileName);

int 
checkFileName (std::string filename);