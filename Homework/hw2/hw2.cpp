#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "ArgumentManager.h"
using namespace std;

struct node {
    int id;
    string username;
    int score;
    char grade;
    node* next;
};

class linkedlist {
    private:
    node* head;
    int size = 0;
    public:
    linkedlist() { head = nullptr;};
    int getSize() {return size;};
    void addAtTail(int id_, string username_ , int score_ , char grade_) {
        node* temp = new node;
        temp->id = id_;
        temp->username = username_;
        temp->score = score_;
        temp->grade = grade_;
        temp->next = nullptr;

        node* cu = head;
        if (cu == nullptr) {
            head = temp;
        }
        else {
            while (cu->next != nullptr) {
                if (cu->next->id == id_) {
                    cu->next = temp;
                    size--;
                    break;
                }
                else if (cu->next->username == username_) {
                    return;
                }
                cu = cu->next;
            }
            cu->next = temp;
        }
        size++;
    }; 

    void addAtPosition(int pos, int id_, string username_ , int score_ , char grade_) {
        node *temp = new node;
        temp->id = id_;
        temp->username = username_;
        temp->score = score_;
        temp->grade = grade_;
        temp->next = nullptr;
        //cout << "59linked ben id" << temp->id << endl;
        if (pos > size || pos < 0) {
            return;
        }
        if (isIdDuplicate(id_) == true) {
            head->username = username_;
            head->grade = grade_;
            head->score = score_;   
            return;
        }
        else if (isUserDuplicate(username_) == true) {  
            return;
        }
        if (pos == size) {
            node* cu = head;
        if (cu == nullptr) {
            head = temp;
        }
        else {
            while (cu->next != nullptr) {
                if (cu->next->id == id_) {
                    cu->next = temp;
                    size--;
                    break;
                }
                else if (cu->next->username == username_) {
                    return;
                }
                cu = cu->next;
            }
            cu->next = temp;
        }
        size++;
        return;
        }

        if (pos == 0) {
            if (head == nullptr) {
                head = temp;
                return;
            }
            else {
            temp->next = head;
            head = temp;
            return;
            }
        }

        node* cu = head;
          
        for (int i = 0; i < pos; i++) {
            if (cu->next->id == id_) {
                    cu->next = temp;
                    //cout << "linked ben id" << cu->id << endl;
                    return;
                }

            cu = cu->next;
        }
        //cout << "linked ben id" << cu->id << endl;
        temp->next = cu->next;
        cu->next = temp;
        size++;
    }

    void idRemove(int id_) {
        if (head == nullptr) {
            return;
        }
        while (head->id == id_) {
            node *temp = head;
            if (head->next == nullptr) {
                head = nullptr;
                delete temp;
                return;
            }
            head = head->next;
            delete temp;
            size--;
        }
        node *prev = head;
        node *cu = head->next;
        while (cu!= nullptr) {
            if(cu->id == id_) {
                node *temp = cu;
                prev->next = cu->next;
                cu = cu->next;
                delete temp;
                size--;
            }
            else {
                prev = cu;
                cu = cu->next;
            }
        }
    }

    void userRemove(string username_) {
        if (head == nullptr) {
            return;
        }
        while (head->username == username_) {
            node *temp = head;
            if (head->next == nullptr) {
                head = nullptr;
                delete temp;
                return;
            }
            head = head->next;
            delete temp;
            size--;
        }
        node *prev = head;
        node *cu = head->next;
        while (cu!= nullptr) {
            if(cu->username == username_) {
                node *temp = cu;
                prev->next = cu->next;
                cu = cu->next;
                delete temp;
                size--;
            }
            else {
                prev = cu;
                cu = cu->next;
            }
        }
    }

    void scoreRemove(int score_) {
        if (head == nullptr) {
            return;
        }
        while (head->score == score_) {
            node *temp = head;
            if (head->next == nullptr) {
                head = nullptr;
                delete temp;
                return;
            }
            head = head->next;
            delete temp;
            size--;
        }
        node *prev = head;
        node *cu = head->next;
        while (cu!= nullptr) {
            if(cu->score == score_) {
                node *temp = cu;
                prev->next = cu->next;
                cu = cu->next;
                delete temp;
                size--;
            }
            else {
                prev = cu;
                cu = cu->next;
            }
        }
    }

    void gradeRemove(int grade_) {
        if (head == nullptr) {
            return;
        }
        while (head->grade == grade_) {
            node *temp = head;
            if (head->next == nullptr) {
                head = nullptr;
                delete temp;
                return;
            }
            head = head->next;
            delete temp;
            size--;
        }
        node *prev = head;
        node *cu = head->next;
        while (cu!= nullptr) {
            if(cu->grade == grade_) {
                node *temp = cu;
                prev->next = cu->next;
                cu = cu->next;
                delete temp;
                size--;
            }
            else {
                prev = cu;
                cu = cu->next;
            }
        }
    }
    
    void idSort() {
        if (head == nullptr || head->next == nullptr) {
            return;
        }
        else {
            bool isSorted = false;
            node *cu;
            node *nxt;
            while(!isSorted) {
                isSorted = true;
                cu = head;
                nxt = cu->next;
                while (cu->next != nullptr) {
                    if (cu->id > cu->next->id) {
                        int tempId = cu->id;
                        cu->id = nxt->id;
                        nxt->id = tempId;
                        string tempUser = cu->username;
                        cu->username = nxt->username;
                        nxt->username = tempUser;
                        int tempScore = cu->score;
                        cu->score = nxt->score;
                        nxt->score = tempScore;
                        char tempGrade = cu->grade;
                        cu->grade = nxt->grade;
                        nxt->grade = tempGrade;
                        isSorted = false;
                    }
                    cu = cu->next;
                    nxt = cu->next;
                }
            }
        }
    }

    void userSort() {
        if (head == nullptr || head->next == nullptr) {
            return;
        }
        else {
            bool isSorted = false;
            node *cu;
            node *nxt;
            while(!isSorted) {
                isSorted = true;
                cu = head;
                nxt = cu->next;
                while (cu->next != nullptr) {
                    if (cu->username > cu->next->username) {
                        int tempId = cu->id;
                        cu->id = nxt->id;
                        nxt->id = tempId;
                        string tempUser = cu->username;
                        cu->username = nxt->username;
                        nxt->username = tempUser;
                        int tempScore = cu->score;
                        cu->score = nxt->score;
                        nxt->score = tempScore;
                        char tempGrade = cu->grade;
                        cu->grade = nxt->grade;
                        nxt->grade = tempGrade;
                        isSorted = false;
                    }
                    cu = cu->next;
                    nxt = cu->next;
                }
            }
        }
    }

    void scoreSort() {
        if (head == nullptr || head->next == nullptr) {
            return;
        }
        else {
            bool isSorted = false;
            node *cu;
            node *nxt;
            while(!isSorted) {
                isSorted = true;
                cu = head;
                nxt = cu->next;
                while (cu->next != nullptr) {
                    if (cu->score > cu->next->score) {
                        int tempId = cu->id;
                        cu->id = nxt->id;
                        nxt->id = tempId;
                        string tempUser = cu->username;
                        cu->username = nxt->username;
                        nxt->username = tempUser;
                        int tempScore = cu->score;
                        cu->score = nxt->score;
                        nxt->score = tempScore;
                        char tempGrade = cu->grade;
                        cu->grade = nxt->grade;
                        nxt->grade = tempGrade;
                        isSorted = false;
                    }
                    cu = cu->next;
                    nxt = cu->next;
                }
            }
        }
    }

    void gradeSort() {
        if (head == nullptr || head->next == nullptr) {
            return;
        }
        else {
            bool isSorted = false;
            node *cu;
            node *nxt;
            while(!isSorted) {
                isSorted = true;
                cu = head;
                nxt = cu->next;
                while (cu->next != nullptr) {
                    if (cu->grade > cu->next->grade) {
                        int tempId = cu->id;
                        cu->id = nxt->id;
                        nxt->id = tempId;
                        string tempUser = cu->username;
                        cu->username = nxt->username;
                        nxt->username = tempUser;
                        int tempScore = cu->score;
                        cu->score = nxt->score;
                        nxt->score = tempScore;
                        char tempGrade = cu->grade;
                        cu->grade = nxt->grade;
                        nxt->grade = tempGrade;
                        isSorted = false;
                    }
                    cu = cu->next;
                    nxt = cu->next;
                }
            }
        }
    }
    
    bool isIdDuplicate(int id_) {
        node* cu = head;
        while (cu != nullptr) {
            if (cu->id == id_) {
                return true;
            }
            cu = cu->next;
        }
        return false;
    }

    bool isUserDuplicate(string username_) {
        node* cu = head;
        while (cu != nullptr) {
            if (cu->username == username_) {
                return true;
            }
            cu = cu->next;
        }
        return false;
    }
    void print(ofstream& ben) {
        node* cu = head;
        while (cu != nullptr) {
            ben << "[id:" << cu->id << ";username:" << cu->username << ";score:" << cu->score << ";grade:" << cu->grade << "]" << endl;
            cu = cu->next;
        }
    }
    
};

int main(int argc, char *argv[]) {
    ArgumentManager am(argc, argv);
    ifstream input(am.get("input"));
    ifstream command(am.get("command"));
    ofstream out(am.get("output"));
    //ifstream input("input3.txt");
    //ifstream command("command3.txt");
    //ofstream out("output.txt");

    string in;
    int idIndex, userIndex, scoreIndex, gradeIndex = 0;
    linkedlist list;

    while(getline(input, in)) {
        in.erase(remove(in.begin(), in.end(), '\n'), in.end());
        in.erase(remove(in.begin(), in.end(), '\r'), in.end());

        idIndex = in.find("id:");
        userIndex = in.find("username:");
        scoreIndex = in.find("score:");
        gradeIndex = in.find("grade:");

        if (idIndex == -1 || userIndex == -1 || scoreIndex == -1 || gradeIndex == -1) {
            continue;
        }

        if (idIndex > userIndex || userIndex > scoreIndex || scoreIndex > gradeIndex) {
            continue;
        }
        
        string temp = "";
        for (int i = idIndex + 3; i < in.find("id:") + 7; i++) {
            temp.push_back(in[i]);
        }
        int id = stoi(temp);
        //cout << id << endl;

        string user = "";
        for (int i = userIndex + 9; in[i] != ';'; i++) {
            user.push_back(in[i]);
        }
        //cout << user << endl;

        temp = "";
        for (int i = scoreIndex + 6; in[i] != ';'; i++) {
            temp.push_back(in[i]);
        }
        int score = stoi(temp);
        //cout << score << endl;

        char grade = in[gradeIndex + 6];
        //cout << grade << endl;

        list.addAtTail(id, user, score, grade);
        
    }
    string cmd;
    while (getline(command, cmd)) {
        cmd.erase(remove(cmd.begin(), cmd.end(), '\n'), cmd.end());
        cmd.erase(remove(cmd.begin(), cmd.end(), '\r'), cmd.end());
        int addIndex = cmd.find("Add");
        int removeIndex = cmd.find("Remove");
        int sortIndex = cmd.find("Sort");

        if (addIndex != string::npos) {
        
        idIndex = cmd.find("id:");
        userIndex = cmd.find("username:");
        scoreIndex = cmd.find("score:");
        gradeIndex = cmd.find("grade:");

        if (idIndex == -1 || userIndex == -1 || scoreIndex == -1 || gradeIndex == -1) {
            continue;
        }

        if (idIndex > userIndex || userIndex > scoreIndex || scoreIndex > gradeIndex) {
            continue;
        }

        string temp = "";
        for (int i = idIndex + 3; i < idIndex + 7; i++) {
            temp.push_back(cmd[i]);
        }
        int id = stoi(temp);
        //cout << id << endl;

        string user = "";
        for (int i = userIndex + 9; cmd[i] != ';'; i++) {
            user.push_back(cmd[i]);
        }
        //cout << user << endl;

        temp = "";
        for (int i = scoreIndex + 6; cmd[i] != ';'; i++) {
            temp.push_back(cmd[i]);
        }
        int score = stoi(temp);
        //cout << score << endl;

        char grade = cmd[gradeIndex + 6];
        //cout << grade << endl;
        //cout << addIndex << endl;
        int position = int(cmd[addIndex + 5]) - 48;

        list.addAtPosition(position, id, user, score, grade);
        }
        else if (removeIndex != string::npos) {
            idIndex = cmd.find("id:");
            userIndex = cmd.find("username:");
            scoreIndex = cmd.find("score:");
            gradeIndex = cmd.find("grade:");

            if (idIndex != string::npos) {
                string temp;
                for (int i = idIndex + 3; i < idIndex + 7; i++) {
                    temp.push_back(cmd[i]);
                }
                int id = stoi(temp);
                list.idRemove(id);
                
            }
            if (userIndex != string::npos) {
                string user;
                for (int i = userIndex + 9; cmd[i] != ')'; i++) {
                    user.push_back(cmd[i]);
                }
                list.userRemove(user);
            }
            if (scoreIndex != string::npos) {
                string temp;
                for (int i = scoreIndex + 6; cmd[i] != ')'; i++) {
                    temp.push_back(cmd[i]);
                }
                int score = stoi(temp);
                list.scoreRemove(score);
            }
            if (gradeIndex != string::npos) {
                char grade = cmd[gradeIndex + 6];
                list.gradeRemove(grade);
            }
        }
        else if (sortIndex != string::npos) {
            idIndex = cmd.find("id");
            userIndex = cmd.find("username");
            scoreIndex = cmd.find("score");
            gradeIndex = cmd.find("grade");
            if (idIndex != string::npos) {
                list.idSort();
            }
            if (userIndex != string::npos) {
                list.userSort();
            }
            if (scoreIndex != string::npos) {
                list.scoreSort();
            }
            if (gradeIndex != string::npos) {
                list.gradeSort();
            }
        }
    }
    list.print(out);
    //cout << list.getSize() << endl;
    return 0;
}