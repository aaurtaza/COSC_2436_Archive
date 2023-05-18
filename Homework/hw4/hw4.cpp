#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <queue>
#include "ArgumentManager.h"

using namespace std;

struct node {
    string command;
    int priority;
    node *left, *right, *next;
};

class BST {
    private:
        node* root;
        void add(string val, node*& cu) {
            if (cu == nullptr) {
                cu = new node();
                cu->command = val;
            }
            else if (cu->command.size() == val.size()) {
                cu->command = val;
            }
            else if(val.size() > cu->command.size())
                return add(val, cu->right);
            else if(val.size() < cu->command.size())
                return add(val, cu->left);
        };
        void printPreOrder(node* cu, ofstream& o) {
            if (cu == nullptr)
                return;
            o << cu->command << endl;
            printPreOrder(cu->left, o);
            printPreOrder(cu->right, o);
        };
        void printInOrder(node* cu, ofstream& o) {
            if (cu == nullptr)
                return;
            printInOrder(cu->left, o);
            o << cu->command << endl;
            printInOrder(cu->right, o);
        };
        void printPostOrder(node* cu, ofstream& o) {
            if (cu == nullptr)
                return;
            printPostOrder(cu->left, o);
            printPostOrder(cu->right, o);
            o << cu->command << endl;
        };

    public:
        BST() {root = nullptr;};
        void add(string val) {add(val, root);};
        void printPreOrder(ofstream &o) { printPreOrder(root, o);};
        void printInOrder(ofstream &o) { printInOrder(root, o);};
        void printPostOrder(ofstream &o){ printPostOrder(root, o);};

};

class priorityqueue {
    private:
        node* front;
        node* end;
    public:
        priorityqueue() {front = end = nullptr;};
        void enqueue(string s, int p) {
            node* temp = new node();
            temp->command = s;
            temp->priority = p;

            if (front == nullptr)
                front = temp;
            else {
                node* cu = front;
                node* pre = nullptr; 
                if (temp->priority < front->priority) {
                    temp->next = front;
                    front = temp;
                }
                else {
                    while(cu != nullptr && temp->priority >= cu->priority) {
                        pre = cu;
                        cu = cu->next;
                    }
                    temp->next = cu;
                    pre->next = temp;
                }
            }
        };
        void dequeue() {
            if (front == nullptr)
                return;
            else {
                node* temp = front;
                front = front->next;
                delete temp;
            }
        };
        string getFront() {
            return front->command;
        };
        bool empty() {
            return (front == nullptr);
        };
};

int main(int argc, char *argv[]) {
    ArgumentManager am(argc, argv);
    ifstream input(am.get("input"));
    ofstream out(am.get("output"));
    string line = "";
    string type;
    priorityqueue commands;
    BST tree;
    queue<string> text;

    while(getline(input, line)) {
        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());
        if (line == "Preorder" || line == "Postorder" || line == "Inorder")
            type = line;
        if (line.size() == 0)
            continue;
        string cmd = line.substr(0, line.find(':'));
        if (line.find(':') == -1)
            continue;
        else if (cmd != "REMOVE" && cmd != "ADD" && cmd != "REPLACE" && cmd != "DECODE" && cmd != "SWAP" && cmd != "BST")
            continue;
        else if (cmd == "REPLACE" || cmd == "ADD" || cmd == "SWAP") {
            if(line.find('[') == -1 || line.find(']') == -1 || line.find('(') == -1 || line.find(')') == -1 || line.find(',') == -1)
    			continue;
        }
        else if (cmd == "REMOVE" || cmd =="DECODE") {
            if(line.find('[') == -1 || line.find(']') == -1 || line.find('(') == -1 || line.find(')') == -1)
                continue;
        }
        else if (line.find('(') == -1 || line.find(')') == -1)
            continue; 
        string pStr = line.substr(line.find('(') + 1, line.find(')') - line.find('(') - 1);
        int priority = stoi(pStr);
        commands.enqueue(line, priority);
    }
    while (!commands.empty()) {
        string l = commands.getFront();
        commands.dequeue();
        string task = l.substr(0, l.find(':'));
        if (task == "DECODE")
            text.push(l);
        else if (task == "REPLACE") {
            if(text.empty())
                continue;
            char original = l[l.find(',') - 1];
            char replacement = l[l.find(',') + 1];
            string newMessage = text.front();
            text.pop();
            newMessage = newMessage.substr(8, newMessage.find(']') - 8);
            while(newMessage.find(original) != -1)
		        newMessage.at(newMessage.find(original)) = replacement;
            string newDecode = "DECODE:[" + newMessage + "]";
            
            text.push(newDecode);
        }
        else if (task == "ADD") {
            if(text.empty())
                continue;
            char original = l[l.find(',') - 1];
            char replacement = l[l.find(',') + 1];
            string newMessage = text.front();
            text.pop();
            newMessage = newMessage.substr(8, newMessage.find(']') - 8);
            for (int i = 0; i < newMessage.size(); i++) {
                if (newMessage.at(i) == original) {
                    if (i == newMessage.size() - 1)
                        newMessage += replacement;
                else {
                    string left = newMessage.substr(0, i+1);
                    char in = replacement;
                    string right = newMessage.substr(i+1, newMessage.size() - i - 1);
                    newMessage = left + in + right;
                }
                i++;
                }
            }
            text.push("DECODE:[" + newMessage + "]");
        }
        else if (task == "REMOVE") {
            if(text.empty())
                continue;
            char remove = l[l.find('[') + 1];
            string newMessage = text.front();
            text.pop();
            newMessage = newMessage.substr(8, newMessage.find(']') - 8);
            while (newMessage.find(remove) != -1) {
                newMessage.erase(newMessage.find(remove), 1);
            }
            text.push("DECODE:[" + newMessage + "]");
        }
        else if (task == "SWAP") {
            if(text.empty())
                continue;
            char first = l[l.find(',') - 1];
            char second = l[l.find(',') + 1];
            string newMessage = text.front();
            text.pop();
            newMessage = newMessage.substr(8, newMessage.find(']') - 8);
            for (int i = 0; i < newMessage.size(); i++) {
                if (newMessage.at(i) == first)
                    newMessage.at(i) = second;
                else if (newMessage.at(i) == second)
                    newMessage.at(i) = first;
            }
            text.push("DECODE:[" + newMessage + "]");
        }
        else if (task == "BST") {
            if(text.empty())
                continue;
            string newMessage = text.front();
            text.pop();
            newMessage = newMessage.substr(8, newMessage.find(']') - 8);
			tree.add(newMessage);
        }
    }



    if(type == "Inorder"){
		tree.printInOrder(out);
	}
	else if(type == "Preorder"){
		tree.printPreOrder(out);
	}
	else if(type == "Postorder"){
		tree.printPostOrder(out);
	}
    return 0;
}