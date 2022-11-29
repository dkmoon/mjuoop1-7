#include <fstream>
#include <iostream>
#include <string>


using namespace std;


int main(int argc, char** argv)
{
    bool alsoWord = true;
    string src;

    // -l 옵션이 주어졌는지 확인한다.
    if (argc == 3) {
        if (argv[1] == string("-l")) {
            alsoWord = false;
        }
        src = argv[2];
    }
    else {
        src = argv[1];
    }

    int numLines = 0;
    {
        ifstream ifs(src);
        string line;
        while (getline(ifs, line)) {
            ++numLines;
        }
    }

    int numWords = 0;
    if (alsoWord) {
        ifstream ifs(src);
        string word;
        while (ifs >> word) {
            ++numWords;
        }
    }

    if (alsoWord) {
        cout << numWords << " " << numLines;
    }
    else {
        cout << numLines;
    }
}