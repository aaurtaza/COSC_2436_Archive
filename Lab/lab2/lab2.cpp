#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include "ArgumentManager.h"

using namespace std;

template <typename T>
struct node {
    T data;
    node<T>* next;
};

template <typename T>
class linkedlist {
    private:
    node<T>* head;
    int size;
    public:
    linkedlist();
    ~linkedlist();
    bool isEmpty() {return head == nullptr;};
    int getSize() {return size;};
    void addAtHead(T value);
    void addAtTail(T value);
    void removeAtHead();
    void removeAtTail();
    void print(ofstream& );

};

template <typename T>
linkedlist<T>::linkedlist() {

    head = nullptr;
    size = 0;
}

template <typename T>
linkedlist<T>::~linkedlist() {
    node<T>* cu = head;
    while (cu != nullptr) {
        node<T>* temp = cu;
        cu = cu->next;
        delete temp;
    }
}

template <typename T>
void linkedlist<T>::addAtHead(T value) {
    if (isEmpty()) {
        head = new node<T>();
        head->data = value;
    }
    else {
    node<T>* temp = new node<T>();
    temp->data = value;
    temp->next = head;

    head = temp;
    }
    size++;
}

template <typename T>
void linkedlist<T>::addAtTail(T value) {
    node<T>* temp = new node<T>();
    temp->data = value;
    temp->next = nullptr;

    node<T>* cu = head;
    if (cu == nullptr) {
        head = temp;
    }

    else {
        while (cu->next != nullptr) {
            cu = cu->next;
        }
        cu->next = temp;
    }
    size++;
}

template<typename T>
void linkedlist<T>::removeAtHead() {
    node<T>* cu = head;
    if (head == nullptr) {
        return;
    }
    head = head->next;
    delete cu;
    size--;
}

template<typename T>
void linkedlist<T>::removeAtTail() {
    node<T>* cu = head;
    node<T>* prev = nullptr;
    if(cu == nullptr) {
        return;
    }else if(cu->next == nullptr){
        head = nullptr;
    }
    else {
        while (cu->next != nullptr) {
            prev = cu;
            cu = cu->next;
        }
        prev->next = nullptr;
        delete cu;
        size--;
    }
}

template<typename T>
void linkedlist<T>::print(ofstream& ben) {
    node<T>* cu = head;
    while (cu != nullptr) {
        if (cu->next == nullptr) {
            ben << cu->data;
            cu = cu->next;
        }
        else {
        ben << cu->data << " ";
        cu = cu->next;
        }
    }
}

int main(int argc, char *argv[]) {
    ArgumentManager am(argc, argv);

    ifstream input(am.get("input"));
    ofstream out(am.get("output"));

    //ifstream input("input1.txt");
    //ofstream out("output.txt");
        
    string in = "";
    string type = "";
    string addfrom = "";

    getline(input, type);
    type.erase(remove(type.begin(), type.end(), '\n'), type.end());
    type.erase(remove(type.begin(), type.end(), '\r'), type.end());
    if (type == "string") {
        linkedlist<string> list1;
        getline(input, addfrom);
        addfrom.erase(remove(in.begin(), in.end(), '\n'), in.end());
        addfrom.erase(remove(in.begin(), in.end(), '\r'), in.end());
        if (addfrom == "head") {
            while (getline(input, in)) {
                in.erase(remove(in.begin(), in.end(), '\n'), in.end());
                in.erase(remove(in.begin(), in.end(), '\r'), in.end());
                if (in == "remove head") {
                    list1.removeAtHead();
                }
                else if (in == "remove tail") {
                    list1.removeAtTail();
                }
                else {
                    list1.addAtHead(in);
                }
            }
        }
        else if (addfrom == "tail") {
            while (getline(input, in)) {
                in.erase(remove(in.begin(), in.end(), '\n'), in.end());
                in.erase(remove(in.begin(), in.end(), '\r'), in.end());
                if (in == "remove head") {
                    list1.removeAtHead();
                }
                else if (in == "remove tail") {
                    list1.removeAtTail();
                }
                else {
                    list1.addAtTail(in);
                }
            }
        }
        list1.print(out);
    }

    else if (type == "int") {
        linkedlist<int> list1;
        getline(input, addfrom);
        addfrom.erase(remove(in.begin(), in.end(), '\n'), in.end());
        addfrom.erase(remove(in.begin(), in.end(), '\r'), in.end());
        if (addfrom == "head") {
            
            while (getline(input, in)) {
                in.erase(remove(in.begin(), in.end(), '\n'), in.end());
                in.erase(remove(in.begin(), in.end(), '\r'), in.end());
                if (in == "remove head") {
                    list1.removeAtHead();
                }
                else if (in == "remove tail") {
                    list1.removeAtTail();
                }
                else {
                    list1.addAtHead(stoi(in));
                }
            }
        }
        else if (addfrom == "tail") {
            while (getline(input, in)) {
                in.erase(remove(in.begin(), in.end(), '\n'), in.end());
                in.erase(remove(in.begin(), in.end(), '\r'), in.end());
                if (in == "remove head") {
                    list1.removeAtHead();
                }
                else if (in == "remove tail") {
                    list1.removeAtTail();
                }
                else {
                    list1.addAtTail(stoi(in));
                }
            }
        }
        list1.print(out);
    }

    else if (type == "char") {
        linkedlist<char> list1;
        getline(input, addfrom);
        addfrom.erase(remove(in.begin(), in.end(), '\n'), in.end());
        addfrom.erase(remove(in.begin(), in.end(), '\r'), in.end());
        if (addfrom == "head") {
            while (getline(input, in)) {
                in.erase(remove(in.begin(), in.end(), '\n'), in.end());
                in.erase(remove(in.begin(), in.end(), '\r'), in.end());
                if (in == "remove head") {
                    list1.removeAtHead();
                }
                else if (in == "remove tail") {
                    list1.removeAtTail();
                }
                else {
                    list1.addAtHead(in.at(0));
                }
            }
        }
        else if (addfrom == "tail") {
            while (getline(input, in)) {
                in.erase(remove(in.begin(), in.end(), '\n'), in.end());
                in.erase(remove(in.begin(), in.end(), '\r'), in.end());
                if (in == "remove head") {
                    list1.removeAtHead();
                }
                else if (in == "remove tail") {
                    list1.removeAtTail();
                }
                else {
                    list1.addAtTail(in.at(0));
                }
            }
        }
        list1.print(out);
    }

    return 0;
}