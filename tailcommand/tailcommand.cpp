// Author. John Xu. 6/23/2019
// Draft of this code was written on 6/21/2019 on the flight back from Plantation, FL. After onsite interview at Magic Leap
//
// After many wam up practices and exercies of implementing all sorts of algorithms on arrays, lists, stack and queues, etc. Some
// of the basics of C++ and basic I/O operations may be ignored.  Implementing the tail command usually seen on Linux os
// is a ncie way to warm up the basic I/O operations using C++. Especially for those of old programmers who have been using
// printf and file.read/file.write/file.seek for too long, read and warm up on the C++ ways of doing console I/O is a good
// excercise
//
// Problem statement: Implementing the 'tail' command seen on Linux.
//
// Remaining issues of this version: We still see Segmentation fault at end of execution
//
// compiling instruction: g++ --std=c++17 tailcommand.cpp -o tail

// updates on 6/24/2019
// the segmentation fault was happening in filesystem::exists() call. It was fixed after upgradimg g++ to 9.0 using 
// following command:
//
//  sudo apt install g++-9
//  sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-9 10


#include <fstream>
#include <iostream>
#include <filesystem>  //C++17 feature. For C++14, use <experimental/filesystem>

// Following constants has following intention: our tail command will output at most last 10 lines of the file. We at most
// printout the last 800 characters from the file. We at most print out 256 characters in any given line
// 
#define MAXLINES 30
#define MAXCHS   600
#define MAXLINELEN 256

int tail(char* filepath, int lines = MAXLINES)
{
    using namespace std;
    namespace fs = std::filesystem;  //On C++ 14 we need std::experimental::filesystem On C++ 17, just std::filesystem

    cout << " file : " << filepath << endl;   //debug output

    fs::path fp {filepath};

    cout << " 0 " << endl;                  //debug output

    if (!fs::exists(fp)){
        cout << "file " << filepath << " not exist" << endl;
        return 0;
    }

    cout << " 1 " << endl;                  //debug output


    cout << " 2 " << endl;                  //debug output

    int filesize = fs::file_size(fp);
    ifstream fstrm(filepath);

    cout << " 3 " << " fileze = " << filesize << endl;                  //debug output

    if (filesize > MAXCHS)
        fstrm.ignore((filesize - MAXCHS), EOF);

    cout << " 4 " << endl;                  //debug output

    char buffer[MAXLINELEN];
    for (int i=0; i < lines; i++) {
//    cout << " 5 " << endl;                  //debug output

//        if (fstrm.peek() == EOF) break;
        if (fstrm.eof()) break;
        fstrm.getline(buffer, MAXLINELEN);
        cout << buffer << endl;
    }
    cout << std::flush;
    fstrm.close();

    return 0;
}

int main(int argc, char* argv[])
{
    using namespace std;
    if (argc < 2) {
        cout << "usage: tail filename" << endl;
        return 0;
    }

    if (argc >= 3) {
        int maxlines = atoi(argv[2]);
        tail(argv[1], maxlines);
    }
    else
        tail(argv[1]);

    return 0;
}