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
    map<long, long> hashmap;
    long number;
    long buckets = 0;// ie number of lines in the file

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
    vector<vector<long>> tuples;
    vector<long> tuplesFrequency;

    //generate tuples
    for (auto it1 = hashmap.begin(); it1 != hashmap.end();)
    {
        ++ it1;

        for (auto it2 = it1; it2 != hashmap.end();)
        {
            ++ it2;
            tuples.push_back(vector<long>{it1->first, it2->first});
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
            if(numbers.find(tuples[i][0]) != numbers.end())
            {
                if(numbers.find(tuples[i][1]) != numbers.end())
                {
                    tuplesFrequency[i] ++;
                }
            }
        }

        numbers.clear();

        //cout << token << endl;
    }

    vector<vector<long>> frequent_tuples;

    for(unsigned long i = 0; i < tuples.size(); i ++)
    {
        if(tuplesFrequency[i] >= threshold)
        {
            frequent_tuples.push_back(tuples[i]);
            //cout << "Tuple: " << tuples[i][0] << "," << tuples[i][1] << " Tuple Frequency: " << tuplesFrequency[i] << endl;
        }
    }

    for(unsigned long i = 0; i < frequent_tuples.size(); i ++)
    {
        cout << "Tuple: " << frequent_tuples[i][0] << "," << frequent_tuples[i][1] << endl;
    }

    cout << "Number of frequent tuples:" << frequent_tuples.size() << endl;

    //THIRD PASSTHROUGH
    vector<vector<long>> triplets;
    vector<long> tripletsFrequency;

    //generate triples
    for (unsigned long it1 = 0; it1 < frequent_tuples.size(); it1 ++)
    {
        for (unsigned long it2 = it1 + 1; it2 < frequent_tuples.size(); it2 ++)
        {
            vector<long> val1 = frequent_tuples[it1];
            vector<long> val2 = frequent_tuples[it2];

            if(val1[0] == val2[0])
            {
                if(val1[0] != val2[1])
                {
                    tripletsFrequency.push_back(0);
                    triplets.push_back(vector<long>{val1[0],val1[1],val2[1]});
                }
            }
            else
            {
                break;
            }
        }
    }

    cout << endl << endl;

    for (unsigned long i = 0; i < triplets.size(); i ++)
    {
        //cout << "Triplet: " << triplets[i][0] << "," << triplets[i][1] << "," << triplets[i][2] << endl;
    }

    cout << "Number of triplets:" << triplets.size() << endl;

    numbers.clear();
    infile.clear();
    infile.seekg(0, ios::beg);

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
        for(unsigned long i = 0; i < triplets.size(); i ++)
        {
            if(numbers.find(triplets[i][0]) != numbers.end())
            {
                if(numbers.find(triplets[i][1]) != numbers.end())
                {
                    if(numbers.find(triplets[i][2]) != numbers.end())
                    {
                        tripletsFrequency[i] ++;
                    }
                }
            }
        }

        numbers.clear();
    }

    long count = 0;

    for (unsigned long i = 0; i < triplets.size(); i ++)
    {
        if(tripletsFrequency[i] >= threshold)
        {
            cout << "Triplet: " << triplets[i][0] << "," << triplets[i][1] << "," << triplets[i][2] << endl;
            count ++;
        }
    }

    cout << "Number of triplets:" << count << endl;

    return 0;
}
