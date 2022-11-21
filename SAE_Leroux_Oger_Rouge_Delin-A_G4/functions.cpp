#include "functions.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

vector<string> functions::separateWords(const string & line, const char & delimiter) {
    size_t indexBegin (0);
    size_t indexEnd;
    vector<string> words;
    while (indexBegin < line.size()) {
        indexEnd = line.find_first_of(delimiter, indexBegin);
        words.push_back(line.substr(indexBegin, indexEnd-indexBegin));
        indexBegin += words.back().size() + 1; // 1 = delimiter size
    }
    return words;
}

vector<string> functions::getListOptions(ifstream & file) {
    vector<string> options;
    string firstLine;
    getline(file, firstLine, '\n');
    options = separateWords(firstLine, '-');
    return options;
}

vector<vector<unsigned>> functions::getListVotes(ifstream & file) {
    string line;
    vector<string> ListvaluesStr;
    vector<unsigned> listValuesUnsigned;
    vector<vector<unsigned>> votes;  
    while(true) {
        getline(file, line);
        if (file.eof()) break;
        ListvaluesStr = separateWords(line, '-');
        listValuesUnsigned = {};
        for (const string &value : ListvaluesStr) {
            listValuesUnsigned.push_back(stoul(value));
        }
        votes.push_back(listValuesUnsigned);
    }
    return votes;
}

void functions::printVectorOfVector(const vector<vector<unsigned>> & vectorOfVector) {
    for (const vector<unsigned> &vector : vectorOfVector) {
        for (unsigned value : vector) {
            cout << value << "  ";
        }
        cout << endl;
    }
}

bool functions::isEntryValid_ranked(const vector<unsigned> & vote, const vector<string> & options) {
    // use in the case where options need to be ranked between 1 and options.size()
    if (vote.size() != options.size()) return false;
    unsigned expectedValue (1); //goes from 1 to options.size()
    for (size_t i = 0; i < options.size(); ++i) {
        if(find(vote.begin(), vote.end(), expectedValue) == vote.end()) return false; // expected value was not find
        //cout << i <<" - ok" << endl;
        ++expectedValue;
    }
    return true;
}










