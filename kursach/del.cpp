#include <iostream>
#include <string>
#include <sstream>

using namespace std;

void rgr (string* b) {
    *b = "fef";
}

int main () {

    string b = "addvd";

    rgr(&b);

    cout << b;

    return 0;
}


