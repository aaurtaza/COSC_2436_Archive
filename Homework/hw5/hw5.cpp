#include <iostream>
#include "ArgumentManager.h"
#include <vector>
#include <fstream>
#include <algorithm>

struct node{
  int *keys;
  node **childptr;
  int size;
  int degree;

  node(int _degree) {
    degree = _degree;
    keys = new int[_degree];
    childptr = new node*[_degree + 1];
    size = 0;

    for(int i = 0; i < _degree; i++) {
      keys[i] = -1;
    }

    for(int i = 0; i < _degree + 1; i++) {
      childptr[i] = nullptr;  
    }
  }
};

class bTree {
  private:
    node *root;
    int nDegree;

  public:
    bTree(int _degree) {
      root = nullptr;
      nDegree = _degree;
    }

    void insert(node*& cu, int data) {
      if(root == nullptr) {
        root = new node(nDegree);
        root->keys[root->size++] = data;
    }

    else {
        bool isLeaf = true;
        for(int i = 0; i<=nDegree; i++)
            if(cu->childptr[i] != nullptr)
                isLeaf = false;
        if(isLeaf){
            for(int i=0; i<cu->size; i++)
                if(cu->keys[i] == data)
                    return;
            cu->keys[cu->size++] = data;
            sort(cu->keys, cu->keys+cu->size);
        }

        else{
            int location=0;
            for(int i = 0; i<cu->size; i++){
                if(data > cu->keys[i])
                    location++;
                if(data == cu->keys[i])
                    return;
            }
            insert(cu->childptr[location], data);
            if(cu->childptr[location]->size == nDegree) {
                cu->keys[cu->size++] = cu->childptr[location]->keys[(nDegree-1)/2];
                sort(cu->keys, cu->keys+cu->size);
                int index = 0;
                for(; index<=cu->size; index++)
                    if(cu->keys[index] == cu->childptr[location]->keys[(nDegree-1)/2])
                        break;
                for(int i = nDegree; i > index; i--){
                    cu->childptr[i] = nullptr;
                    cu->childptr[i] = cu->childptr[i-1];
                }

                node* temp = new node(nDegree);
                node* temp2 = new node(nDegree);
                for(int i = 0; i <= (nDegree-1)/2; i++){
                    if(i < (nDegree-1)/2){
                        temp->keys[i] = cu->childptr[location]->keys[i];
                        temp->size++;
                    }
                    temp->childptr[i] = cu->childptr[location]->childptr[i];
                }

                for(int i = ((nDegree-1)/2)+1; i <= nDegree; i++) {
                     if(i < nDegree){
                        temp2->keys[i-((nDegree-1)/2+1)] = cu->childptr[location]->keys[i];
                        temp2->size++;
                    }
                    temp2->childptr[i-((nDegree-1)/2+1)] = cu->childptr[location]->childptr[i];
                }

                delete cu->childptr[index];
                cu->childptr[index] = cu->childptr[index+1] = nullptr;
                cu->childptr[index] = temp;
                cu->childptr[index+1] = temp2;
            }   
        }
    }
    if(cu == root && cu->size == nDegree) {
        node* temp = new node(nDegree);
        temp->childptr[0] = new node(nDegree);
        temp->childptr[1] = new node(nDegree);
        temp->keys[temp->size++] = cu->keys[((nDegree-1)/2)];

        for(int i=0; i <= (nDegree-1)/2; i++) {
            if(i < (nDegree-1)/2) {
                temp->childptr[0]->keys[i] = cu->keys[i];
                temp->childptr[0]->size++;
            }
            temp->childptr[0]->childptr[i] = cu->childptr[i];
        }

        for(int i = ((nDegree-1)/2)+1; i <= nDegree; i++) {
            if(i < nDegree) {
                temp->childptr[1]->keys[i-((nDegree-1)/2+1)] = cu->keys[i];
                temp->childptr[1]->size++;
            }
            temp->childptr[1]->childptr[i-((nDegree-1)/2+1)] = cu->childptr[i];
        }

        delete cu;
        cu = nullptr;
        root = cu = temp;
      }
    }

    node*& getRoot() {
      return root;
    }

    int getHeight(node* cu) {
      if (cu == nullptr)
        return 0;
      int max = 1 + getHeight(cu->childptr[0]);
      for (int i=1; i<=cu->size; i++)
        if(1 + getHeight(cu->childptr[i]) > max)
          max = 1 + getHeight(cu->childptr[i]);
      return max;
    }

};

void printLevel(node*,int,ofstream&, int cuHeight = 1);
void printLevel(node* cu, int l, ofstream &ben, int cuHeight) {
  if (cu == nullptr)
    return;
  if (cuHeight == l) {
    for (int i = 0; i < cu->size; i++)
      ben << cu->keys[i] << " ";
    return;
  }
  else if (cuHeight < l) {
    for (int i = 0; i <= cu->size; i++)
      printLevel(cu->childptr[i], l, ben, cuHeight + 1);
  }
}

int main(int argc, char* argv[]) {
  ArgumentManager am(argc, argv);
  ifstream input(am.get("input"));
  ofstream out(am.get("output"));
  ifstream command(am.get("command"));

  string line;
  command >> line;
  int degree;
  line.erase(remove(line.begin(), line.end(), '\n'), line.end());
  line.erase(remove(line.begin(), line.end(), '\r'), line.end());
  degree = stoi(line.substr(line.find('=') + 1));
  bTree tree(degree);
  cout << degree << endl;

  while (input >> line) {
    line.erase(remove(line.begin(), line.end(), '\n'), line.end());
    line.erase(remove(line.begin(), line.end(), '\r'), line.end());
    tree.insert(tree.getRoot(), stoi(line));
    cout << line << endl;
  }

  int height = tree.getHeight(tree.getRoot());
  out << "Height=" << height << endl;
  while (getline(command, line)) {
    line.erase(remove(line.begin(), line.end(), '\n'), line.end());
    line.erase(remove(line.begin(), line.end(), '\r'), line.end());
    string level = line.substr(line.find(" ") + 1);
    if (level != "" && level != " ") {
      if (stoi(level) > height) 
        out << "Empty" << endl;
      else
        printLevel(tree.getRoot(), stoi(level), out);
      out << endl;
      cout << level << endl; 
    }
  }

  return 0;
}       