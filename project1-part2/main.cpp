#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <unordered_set>
#include <vector>

using namespace std;

int main()
{
    ifstream infile("retail.txt");

    if(!infile.is_open())
    {
        cout << "Failed to open file" << endl;
        return 0;
    }

    //FIRST PASSTHROUGH
    const string delimiter = " ";
    string line;
    size_t pos;

    long hashValue;
    long number;
    long buckets = 0;// ie number of lines in the file

    //read the file line by line
    vector<long> numbers;
    map<long,long> pairFrequency;
    map<long, long> hashmap;

    cout << "PCY Algorithm: " << endl;
    cout << "Part 1: Pair Frequency" << endl;

    //read the file line by line
    while (getline(infile, line))
    {
        //get all numbers in the line
        pos = 0;

        while ((pos = line.find(" ")) != string::npos)
        {
            number = stol(line.substr(0, pos));//get the token, convert to long
            numbers.push_back(number);
            hashmap[number] ++;
            //cout << number << endl;
            line.erase(0, pos + delimiter.length());//get the next number in the line
        }

        buckets ++;

        //generate tuples
        for (auto it1 = numbers.begin(); it1 != numbers.end();)
        {
            for (auto it2 = it1 +1; it2 != numbers.end();)
            {
                //cout << "Line: " << buckets << " Tuples: " << *it1 << ", " << *it2 << endl;
                hashValue = (*it1 * *it2) % 10000;
                pairFrequency[hashValue]++;
                ++ it2;
            }

            ++ it1;
        }

        numbers.clear();
    }

    cout << "Number of Buckets " << buckets << endl;

    //filter for frequent singles
    double threshold = buckets * 0.01;

    vector<long> frequentSingles;

    for(auto it = hashmap.begin(); it != hashmap.end();)
    {
        if(it->second >= threshold)
        {
            frequentSingles.push_back(it->first);
            //cout << "Frequent Singles: " << it->first << " Count: " << it->second << endl;
        }

        it ++;
    }

    vector<vector<long>> tuples;

    //generate pairs from frequent singles
    for (auto it1 = frequentSingles.begin(); it1 != frequentSingles.end();)
    {
        for (auto it2 = it1 +1; it2 != frequentSingles.end();)
        {
            //cout << "Line: " << buckets << " Tuples: " << *it1 << ", " << *it2 << endl;
            tuples.push_back(vector<long>{*it1, *it2});
            cout << "Tuples: " << *it1 << " , " << *it2 << endl;
            ++ it2;
        }

        ++ it1;
    }

    cout << "Number of potential Tuples: " << tuples.size() << endl;

    //filter any potential tuples with the bitmap
    vector<vector<long>> filterTuples;
    vector<long> tupleFrequency;

    for(auto v: tuples)
    {
        hashValue = (v[0] * v[1]) % 10000;
        if(pairFrequency[hashValue] >= threshold)
        {
            cout << "Tuple: " << v[0] << ", " << v[1] << endl;
            filterTuples.push_back(v);
            tupleFrequency.push_back(0);
        }
    }

    cout << "Number of tuple after bitmap filter: " << filterTuples.size() << endl;

    //second passthrough
    numbers.clear();
    infile.clear();
    infile.seekg(0, ios::beg);

    unordered_set<long> numbers2;

    while (getline(infile, line))
    {
        //get all numbers in the line
        pos = 0;

        while ((pos = line.find(" ")) != string::npos)
        {
            number = stol(line.substr(0, pos));//get the token, convert to long
            numbers2.insert(number);
            //cout << number << endl;
            line.erase(0, pos + delimiter.length());//get the next number in the line
        }

        for(unsigned long i = 0; i < filterTuples.size(); i ++)
        {
            if(numbers2.find(filterTuples[i][0]) != numbers2.end())
            {
                if(numbers2.find(filterTuples[i][1]) != numbers2.end())
                {
                    tupleFrequency[i] ++;
                }
            }
        }

        numbers2.clear();
    }

    int count = 0;
    for(unsigned long i = 0; i < filterTuples.size(); i ++)
    {
        if(tupleFrequency[i] >= threshold)
        {
            cout << "Frequent Tuples: " << filterTuples[i][0] << " " << filterTuples[i][1] << endl;
            count ++;
        }
    }

    cout << "Number of Frequent Tuples: " << count << endl;

    return 0;
}
