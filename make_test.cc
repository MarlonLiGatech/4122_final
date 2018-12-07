#include <iostream>
#include <fstream>
using namespace std;

void writeFile()
{
    ofstream myfile;
    myfile.open("Tower16.txt");
    myfile << "16 16 \n";
    for (int i = 0; i < 256; ++i)
    {
        myfile << i << ' ';
        if ((i + 1) % 16 == 0) {
            myfile << endl;
        }
    }
    myfile.close();
}

int main()
{
    writeFile();
}