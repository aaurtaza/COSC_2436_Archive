#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "ArgumentManager.h"
#include <fstream>
#include <queue>
using namespace std;

int max(int a, int b) {
	if (a > b)
		return a;
	else
		return b;
}

struct node {
	int data;
	node* left;
	node* right;
	int height;
	node(int d) {
		data = d;
		left = nullptr;
		right = nullptr;
		height = 0;
	}
};

class avlTree {
private:
  node* root;

public:
  avlTree() { root = nullptr; }

  void add(int data) { root = insert(root, data); }

  node* getRoot() { return root; }

	node* insert(node* t, int x) {
		if (t == nullptr)
			t = new node(x);
		else if (x < t->data) {
			t->left = insert(t->left, x);
			if (bFactor(t) == 2) {
				if (x < t->left->data)
					t = singleRight(t);
				else
					t = leftRight(t);
			}
		}
		else if (x > t->data) {
			t->right = insert(t->right, x);
			if (bFactor(t) == -2) {
				if (x > t->right->data)
					t = singleLeft(t);
				else
					t = rightLeft(t);
			}
		}
		t->height = max(height(t->left), height(t->right)) + 1;
		return t;
	}

	node* singleRight(node* t) {
		node* u = t->left;
		t->left = u->right;
		u->right = t;
		t->height = max(height(t->left), height(t->right)) + 1;
		u->height = max(height(u->left), height(u->right)) + 1;
		return u;
	}

	node* singleLeft(node* t) {
        node* u = t->right;
        t->right = u->left;
        u->left = t;
        t->height = max(height(t->left), height(t->right)) + 1;
		u->height = max(height(u->left), height(u->right)) + 1;
        return u;
	}

	node* leftRight(node* t) {
		t->left = singleLeft(t->left);
		return singleRight(t);
	}

	node* rightLeft(node* t) {
        t->right = singleRight(t->right);
        return singleLeft(t);
	}

	int height(node* cu) {
		if (cu == nullptr)
			return -1;
		else
			return cu->height;
	}

	int bFactor(node* cu) {
		return (height(cu->left) - height(cu->right));
	}

    void levelorder(vector<int>& ben) {
        if (root == nullptr)
            return;
        node* cu = root;
        queue<node*> q;
        q.push(cu);
        while (!q.empty()) {
            int levelSize = q.size();
            for (int i = 0; i < levelSize; i++) {
                node *cu = q.front();
                q.pop();           
                ben.push_back(cu->data);
                if (cu->left != nullptr)
                    q.push(cu->left);
                if (cu->right != nullptr)
                    q.push(cu->right);
            }
        }
    }
};

int main(int argc, char *argv[]){
	ArgumentManager am(argc, argv);
    ifstream input(am.get("input"));
    ofstream out(am.get("output"));
    string line = "";
    avlTree tree;
    vector<int> result;

    getline(input,line);
    line.erase(remove(line.begin(), line.end(), '\n'), line.end());
    line.erase(remove(line.begin(), line.end(), '\r'), line.end());
    int count = stoi(line);

    for(int i = 0; i < count; i++) {
        getline(input,line);
        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        int val = stoi(line);
        tree.add(val);
    }

    tree.levelorder(result);
    for (int i = 0; i < result.size(); i++) {
        if (i == result.size() - 1)
            out << result[i];
        else
            out << result[i] << " ";
    }

    return 0;
}  