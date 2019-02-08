#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <unordered_set>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    long buckets = 0;// ie number of lines in the file

    ifstream infile("retail.txt");
    string line;
    const string delimiter = " ";

    //FIRST PASSTHROUGH
    map<long, long> hashmap;
    size_t pos;
    long number;

    //read the file line by line
    while (getline(infile, line))
    {
        //cout << line << endl;

        //get each number in the line
        pos = 0;

        while ((pos = line.find(" ")) != string::npos)
        {
            number = stol(line.substr(0, pos));//get the token, convert to long
            hashmap[number] ++;//add the number to the hash and increase its frequency
            //cout << token << endl;
            line.erase(0, pos + delimiter.length());//get the next number in the line
        }

        buckets ++;
    }

    double threshold = buckets * 0.01;

    cout << "Number of buckets: " << buckets << endl;
    cout << "Threshold: " << threshold << endl;
    cout << endl;
    cout << "Raw values from file: " << hashmap.size() << endl;
    cout << endl;

    for (auto it = hashmap.begin(); it != hashmap.end();)
    {
        if(it->second < threshold)
        {
            it = hashmap.erase(it);
        }
        else
        {
            ++ it;
        }
    }

    //output
    /*
    for (auto pair : hashmap)
    {
        //cout << "Frequent Value: " << pair.first << " Frequency: " << pair.second << endl;
    }
    */
    cout << "Number of frequent values: " << hashmap.size() << endl;
    cout << endl;

    //SECOND PASSTHROUGH
    vector<pair<long,long>> tuples;
    vector<long> tuplesFrequency;
    pair<long,long> temp;

    //generate tuples
    for (auto it1 = hashmap.begin(); it1 != hashmap.end();)
    {
        ++ it1;

        for (auto it2 = it1; it2 != hashmap.end();)
        {
            ++ it2;
            temp.first = it1->first;
            temp.second = it2->first;
            tuples.push_back(temp);
            tuplesFrequency.push_back(0);
        }
    }

    //output
    /*
    for (auto pair : tuples)
    {
        cout << "Tuple: " << pair.first << "," << pair.second << endl;
    }
    */

    cout << "Number of tuples: " << tuples.size() << endl;

    infile.clear();
    infile.seekg(0, ios::beg);

    unordered_set<long> numbers;

    //read the file line by line
    while (getline(infile, line))
    {
        //get all numbers in the line
        pos = 0;

        while ((pos = line.find(" ")) != string::npos)
        {
            number = stol(line.substr(0, pos));//get the token, convert to long

            numbers.insert(number);

            line.erase(0, pos + delimiter.length());//get the next number in the line
        }

        //check all tuples to see if they appear in the line
        for(unsigned long i = 0; i < tuples.size(); i ++)
        {
            if(numbers.find(tuples[i].first) != numbers.end())
            {
                if(numbers.find(tuples[i].second) != numbers.end())
                {
                    tuplesFrequency[i] ++;
                }
            }
        }

        numbers.clear();

        //cout << token << endl;
    }

    long count = 0;

    for(unsigned long i = 0; i < tuples.size(); i ++)
    {
        if(tuplesFrequency[i] >= threshold)
        {
            count ++;
            cout << "Tuple: " << tuples[i].first << "," << tuples[i].second << " Tuple Frequency: " << tuplesFrequency[i] << endl;
        }
    }

    cout << "Number of frequent tuples:" << count << endl;

    return 0;
}
