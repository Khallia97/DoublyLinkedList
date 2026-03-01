#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class node{
private:
    string name;                    // stores student's name
    node* next;                    // pointer to next node
    node* prev;                    // pointer to previous node

public:                            // constructor initializes node with name
    node(string n){
        name = n;
        next = nullptr;
        prev = nullptr;
    }
                                // getter for name
    string getName(){            
        return name;
    }
                                // getter for next pointer
    node* getNext(){
        return next;
    }
                                // getter for prev pointer
    node* getPrev(){
        return prev;
    }
                                // setter for next pointer
    void setNext(node* n){
        next = n;
    }
                                // setter for prev pointer
    void setPrev(node* p){
        prev = p;
    }
};

class doublyLinkedList{
private:
    node* head;
    node* tail;

public:                    // constructor initializes empty list
    doublyLinkedList(){
        head = nullptr;
        tail = nullptr;
    }

    void insertNode(string data){        // inserts a node in sorted order
        node* newNode = new node(data);

        if(!head){
            head = tail = newNode;                // case 1: empty list
        }
        else if(data < head->getName()){          // case 2: insert before head
            newNode->setNext(head);
            head->setPrev(newNode);
            head = newNode;
        }
        else if(data > tail->getName()){            // case 3: insert after tail
            tail->setNext(newNode);
            newNode->setPrev(tail);
            tail = newNode;
        }
        else{                                        // case 4: insert somewhere in the middle
            node* current = head;                    
            while(current && current->getName() < data){
                current = current->getNext();
            }

            node* previous = current->getPrev();            // find position
            previous->setNext(newNode);
            newNode->setPrev(previous);
            newNode->setNext(current);
            current->setPrev(newNode);
        }
    }

    void deleteNode(string data){
        if(!head) return;        // empty list, nothing to delete

        node* current = head;

        while(current && current->getName() != data){        // search for the node
            current = current->getNext();
        }

        if(!current) return;

        if(current == head && current == tail){        // case 1: only one node in list
            delete current;
            head = tail = nullptr;
        }
        else if(current == head){                   // case 2: deleting head
            head = head->getNext();
            head->setPrev(nullptr);
            delete current;
        }
        else if(current == tail){                // case 3: deleting tail
            tail = tail->getPrev();
            tail->setNext(nullptr);
            delete current;
        }
        else{                                      // case 4: deleting from middle
            node* before = current->getPrev();
            node* after = current->getNext();
            before->setNext(after);
            after->setPrev(before);
            delete current;
        }
    }

    void traverseAscending(ofstream& outFile){            //traversal head to tail
        node* current = head;
        while(current){
            outFile << current->getName() << endl;
            current = current->getNext();
        }
    }

    void traverseDescending(ofstream& outFile){        //traversal tail to head
        node* current = tail;
        while(current){
            outFile << current->getName() << endl;
            current = current->getPrev();
        }
    }

    void cleanUp(){                    // free allocated memory
        node* current = head;
        while(current){
            node* temp = current;
            current = current->getNext();
            delete temp;
        }
    }
};

string toLowerCase(string str){                      // helper function to convert names to lowercase
    for(int i = 0; i < str.length(); i++){
        str[i] = tolower(str[i]);
    }
    return str;
}

int main(){
    ifstream inFile("input.txt");        // input file
    ofstream outFile("output.txt");       // output file

    doublyLinkedList list;
    string word;

    while(inFile >> word){                 // read file word by word
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

    list.traverseAscending(outFile);    // write ascending order
    outFile << "=============" << endl;
    list.traverseDescending(outFile);     // write descending order

    list.cleanUp();                    // clean up memory before exiting

    inFile.close();
    outFile.close();

    return 0;
}
