#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//rewrite the other version and reduce lines of code
int main()
{
    ifstream infile("retail.txt");

    if(!infile.is_open())
    {
        cout << "Failed to open file" << endl;
        return 0;
    }

    const string delimiter = " ";
    string line;
    size_t pos;
    long number;
    long buckets = 0;// ie number of lines in the file

    //get each number in the line
    while (getline(infile, line))
    {
        pos = 0;

        while ((pos = line.find(" ")) != string::npos)
        {
            number = stol(line.substr(0, pos));//get the token, convert to long
            cout << number << endl;
            line.erase(0, pos + delimiter.length());//get the next number in the line
        }

        buckets ++;
    }

    return 0;
}
