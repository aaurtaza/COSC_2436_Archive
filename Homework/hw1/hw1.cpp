#include <iostream>
#include "ArgumentManager.h"
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Characters {
  char letter;
  string value;
  Characters(char letter_, string value_): letter(letter_), value(value_) {}
};

int main(int argc, char *argv[]) {
    ArgumentManager am(argc, argv);
    //ifstream input(am.get("input"));
    //ifstream command(am.get("command"));
    //ofstream out(am.get("output"));

  // *** Use this if you need to test each input individually, but you need to change back to using argumentmanager when you submit the assignment ***
    ifstream input("input9.txt");
    ifstream command("command9.txt");
    ofstream out("output9.txt");

  string in = "";
  string id = ""; 
  string charvalue = "";
  char letter;
  int charnum = 0;
  vector <string> ids;
  vector <Characters> characters;
  vector <string> first;
  vector <string> last;

  while(getline(input, in)) {
    // Clean up blank spaces, \n and \r, and skip blank lines
    in.erase(remove(in.begin(), in.end(), '\n'), in.end());
    in.erase(remove(in.begin(), in.end(), '\r'), in.end());
    in.erase(remove(in.begin(), in.end(), ' '), in.end());
    if(in.size() == 0)
      continue;

    if (in.find("id:") == string::npos) { // ben
      continue;
    }
    // continue to process the input below
    characters.clear();
    for(int i = 0; i < in.find("id:"); i++) {
        if (isalpha(in[i])) {
            charvalue = "";
            letter = in[i];
            i+=2;
            while(in[i] != ';') {
              charvalue.push_back(in[i]);
              i++;
            }
            characters.push_back(Characters(letter, charvalue));
        }
        else { // ben
              continue;
            }
    } 
    if (characters.size() == string::npos) {
        break;
    }

    id = "";
    for(int i = in.find("id:") + 3; i < in.length(); i++ ) {
        id.push_back(in[i]);
    }
    

    for (int i = 0; i < id.size(); i++) {
      for(int j = 0; j < characters.size(); j++) {
        if(id[i] == characters[j].letter) {
          id.replace(i, 1, characters[j].value);
          //cout << i << " ";
          //cout << characters.size() << endl;
        } 
      }
      
    } // 78911456123312245617123
    //   
    for (int i = id.size() - 1; i >= 0; i--) {
      if (id[i] == '#') {
        id.replace(i, 1, to_string(i));
      }
    }
    ids.push_back(id);

    
  }

  string cmd = "";
  string temp = "";

  while(getline(command, cmd)) {
    // Clean up blank spaces, \n and \r, and skip blank lines
    cmd.erase(remove(cmd.begin(), cmd.end(), '\n'), cmd.end());
    cmd.erase(remove(cmd.begin(), cmd.end(), '\r'), cmd.end());
    cmd.erase(remove(cmd.begin(), cmd.end(), ' '), cmd.end());
    if(cmd.size() == 0)
      continue;
    if (cmd.find("first4:") != string::npos) {
      for(int i = 0 + 7; i < cmd.size(); i++) {
        temp.push_back(cmd[i]);
      }
      first.push_back(temp);
      temp = "";
    }
    else if (cmd.find("last4:") != string::npos) {
      for(int i = 0 + 6; i < cmd.size(); i++) {
        temp.push_back(cmd[i]);
      }
      last.push_back(temp);
      temp = "";
    }
  } 
  
  if (first.size() == 0 && last.size() == 0) {
    for (int i = 0; i < ids.size(); i++) {
    cout << ids[i] << endl;
    }
  }
  else if (last.size() == 0) {
    for (int i = 0; i < ids.size(); i++) {
      for (int j = 0; j < first.size(); j++) {
        if (ids[i].find(first[j]) == 0) {
          cout << ids[i] << endl;
        } 
      }
    }

  }
  else if (first.size() == 0) {
    for (int i = 0; i < ids.size(); i++) {
      for (int j = 0; j < last.size(); j++) {
        if (ids[i].substr(ids[i].size()-4).find(last[j]) != string::npos) {
          cout << ids[i] << endl;
        } 
      }
    }
  }
  else {
    for (int i = 0; i < ids.size(); i++) {
      for (int j = 0; j < first.size(); j++) {
        if (ids[i].find(first[j]) == 0) {
          for (int k = 0; k < last.size(); k++) {
          if (ids[i].substr(ids[i].size()-4).find(last[k]) != string::npos) {
          cout << ids[i] << endl;
        } 
      }
        } 
      }
    }
  }
    return 0;
}