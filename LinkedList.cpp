#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class node{
private:
    string name;
    node* next;
    node* prev;

public:
    node(string n){
        name = n;
        next = nullptr;
        prev = nullptr;
    }

    string getName(){
        return name;
    }

    node* getNext(){
        return next;
    }

    node* getPrev(){
        return prev;
    }

    void setNext(node* n){
        next = n;
    }

    void setPrev(node* p){
        prev = p;
    }
};

class doublyLinkedList{
private:
    node* head;
    node* tail;

public:
    doublyLinkedList(){
        head = nullptr;
        tail = nullptr;
    }

    void insertNode(string data){
        node* newNode = new node(data);

        if(!head){
            head = tail = newNode;
        }
        else if(data < head->getName()){
            newNode->setNext(head);
            head->setPrev(newNode);
            head = newNode;
        }
        else if(data > tail->getName()){
            tail->setNext(newNode);
            newNode->setPrev(tail);
            tail = newNode;
        }
        else{
            node* current = head;
            while(current && current->getName() < data){
                current = current->getNext();
            }

            node* previous = current->getPrev();
            previous->setNext(newNode);
            newNode->setPrev(previous);
            newNode->setNext(current);
            current->setPrev(newNode);
        }
    }

    void deleteNode(string data){
        if(!head) return;

        node* current = head;

        while(current && current->getName() != data){
            current = current->getNext();
        }

        if(!current) return;

        if(current == head && current == tail){
            delete current;
            head = tail = nullptr;
        }
        else if(current == head){
            head = head->getNext();
            head->setPrev(nullptr);
            delete current;
        }
        else if(current == tail){
            tail = tail->getPrev();
            tail->setNext(nullptr);
            delete current;
        }
        else{
            node* before = current->getPrev();
            node* after = current->getNext();
            before->setNext(after);
            after->setPrev(before);
            delete current;
        }
    }

    void traverseAscending(ofstream& outFile){
        node* current = head;
        while(current){
            outFile << current->getName() << endl;
            current = current->getNext();
        }
    }

    void traverseDescending(ofstream& outFile){
        node* current = tail;
        while(current){
            outFile << current->getName() << endl;
            current = current->getPrev();
        }
    }

    void cleanUp(){
        node* current = head;
        while(current){
            node* temp = current;
            current = current->getNext();
            delete temp;
        }
    }
};

string toLowerCase(string str){
    for(int i = 0; i < str.length(); i++){
        str[i] = tolower(str[i]);
    }
    return str;
}

int main(){
    ifstream inFile("input.txt");
    ofstream outFile("output.txt");

    doublyLinkedList list;
    string word;

    while(inFile >> word){
        if(word == "delete"){
            string name;
            inFile >> name;
            name = toLowerCase(name);
            list.deleteNode(name);
        }
        else{
            word = toLowerCase(word);
            list.insertNode(word);
        }
    }

    list.traverseAscending(outFile);
    outFile << "=============" << endl;
    list.traverseDescending(outFile);

    list.cleanUp();

    inFile.close();
    outFile.close();

    return 0;
}
