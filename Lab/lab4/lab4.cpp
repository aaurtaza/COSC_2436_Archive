#include <iostream>
#include "ArgumentManager.h"
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>

using namespace std;
struct node {
    string task;
    double priority;
    node* next;
};

class priority_queue {
    private:
    node* front;
    node* end;
    public:
    priority_queue() {front = end = nullptr;};
    void enqueue(string s, double p) {
        node* temp = new node();
        temp->task = s;
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
        return front->task;
    };
    bool empty() {
        return (front == nullptr);
    };
};

int main(int argc, char *argv[]) {
    ArgumentManager am(argc, argv);
    ifstream input(am.get("input"));
    ofstream out(am.get("output"));

    priority_queue pq;
    string in = "";

    while (getline(input, in))  {
    in.erase(remove(in.begin(), in.end(), '\n'), in.end());
    in.erase(remove(in.begin(), in.end(), '\r'), in.end());
    int split = in.find_last_of(' ');
    string task = in.substr(0, split);
    double p = stod(in.substr(split));
    pq.enqueue(task, p);
    }

    while (!pq.empty()) {
        out << pq.getFront() << endl;
        pq.dequeue();
    }

    return 0;
}