#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

void writeFile()
{
    ofstream myfile;
    int size = 2048;    //change this to create different sized tests
    myfile.open("Tower" + to_string(size) + ".txt");
    myfile << size << ' ' << size << endl;
    for (int i = 0; i < size * size; ++i)
    {
        myfile << rand() % 255 << ' ';
        if ((i + 1) % size == 0) {
            myfile << endl;
        }
    }
    myfile.close();
}

int main()
{
    writeFile();
}