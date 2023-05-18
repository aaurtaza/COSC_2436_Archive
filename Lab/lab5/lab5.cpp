#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <iterator>
#include "ArgumentManager.h"
#include <fstream>
using namespace std;

int main(int argc, char *argv[]){
	ArgumentManager am(argc, argv);
    ifstream input(am.get("input"));
    ofstream out(am.get("output"));    
    string line = "";
    map<string, int> dict;
    map<string, int>::iterator itr;
    string temp = "";
    
    while(getline(input, line)){
    	line.erase(remove(line.begin(), line.end(), '\n'), line.end());
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        line.erase(remove(line.begin(), line.end(), ','), line.end());
        line.erase(remove(line.begin(), line.end(), '.'), line.end());
        line.erase(remove(line.begin(), line.end(), '"'), line.end());
        line.erase(remove(line.begin(), line.end(), '!'), line.end());
        line.erase(remove(line.begin(), line.end(), '?'), line.end());
        for (int i = 0; i < line.length(); i++) {
            if (isupper(line[i]))
                line[i] = tolower(line[i]);
            if (line[i] == ' ') {
                ++dict[temp];
                temp = "";
            }
            else if (i == line.length()-1) {
                temp+= line[i];
                ++dict[temp];
                temp = "";
            }
            else
                temp += line[i];
        }
    }
    for (itr = dict.begin(); itr != dict.end(); ++itr) {
        out << itr->first << ": " << itr->second << endl;
    }
	return 0;
}