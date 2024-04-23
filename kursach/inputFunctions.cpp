#include <vector>
#include <string>
#include <getopt.h>

#include "inputFunctions.hpp"

using namespace std;


int
inputFunction (vector<pair<string, string>>* dict, int argc, char* argv[]) {
    int opt, optionIndex, valuesCount;
    char* charValue = nullptr;
    valuesCount = 0;

    static struct option longOptions[] = 
        {
            {"mirror", no_argument, 0, 'm'}, {"axis", required_argument, 0, 'A'},
            {"left_up", required_argument, 0, 'L'}, {"right_down", required_argument, 0, 'R'},

            {"copy", no_argument, 0, 'c'}, {"dest_left_up", required_argument, 0, 'D'},

            {"color_replace", no_argument, 0, 'r'}, {"old_color", required_argument, 0, 'O'},
            {"new_color", required_argument, 0, 'N'},

            {"rgbfilter", no_argument, 0, 'f'}, {"component_name", required_argument, 0, 'C'},
            {"component_value", required_argument, 0, 'V'},

            {"input", required_argument, 0, 'i'}, {"output", required_argument, 0, 'o'}, 
            {"info", no_argument, 0, 'I'}, {"help", no_argument, 0, 'h'},

            {0, 0, 0, 0}
        };

    opt = getopt_long(argc, argv, "mA:L:R:cD:rO:N:fC:V:i:o:h", longOptions, &optionIndex);
    
    while (opt != -1) {
        charValue = optarg;
        valuesCount++;
        string value;
        char a[1];
        a[0] = opt;
        string name(a);
        
        if (charValue != NULL) {
            valuesCount++;
            value += charValue;
        } else {
            value += "NULL";
        }
        (*dict).emplace_back(name, value);

        opt = getopt_long(argc, argv, "mA:L:R:cD:rO:N:fC:V:i:o:h", longOptions, &optionIndex);
    }
    return valuesCount;
}
