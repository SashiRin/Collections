//
//  main.cpp
//  unrolled linked list
//
//  Created by BlairWu on 01/02/2018.
//  Copyright © 2018 UW. All rights reserved.
//

#include <iostream>
#include <string>

#define maxElemnts 5

using namespace std;

struct Node{
    int numElements;
    char unit[maxElemnts];
    Node* next;
};

class UnrolledLinkedList{
//private:

public:
    Node* list;
    
    char get(int index){
        Node* node = list;
        char res = ' ';
        while (node && node->numElements <= index) {
            index -= node->numElements;
            node = node->next;
        }
        if (node) {
            res = node->unit[index];
        }
        return res;
    }
    
    void insert(char c, int index){
        Node* head = list;
        while (head && head->numElements <= index) {
            index -= head->numElements;
            head = head->next;
        }
        if(!head || head->numElements <= index)
            return;
        if (head->numElements < maxElemnts) {
            for (int i = head->numElements; i > index; i--) {
                head->unit[i] = head->unit[i - 1];
            }
            head->unit[index] = c;
            head->numElements++;
        }else{
            Node* newNode = new Node();
            newNode->numElements = maxElemnts - index;
            for (int i = index; i < head->numElements; i++) {
                newNode->unit[i - index] = head->unit[i];
                head->unit[i] = ' ';
            }
            head->unit[index] = c;
            head->numElements = index + 1;
            newNode->next = head->next;
            head->next = newNode;
        }
    }
    
};

void printUnrolledList(Node *n)
{
    while (n != NULL)
    {
        // Print elements in current node
        for (int i=0; i<n->numElements; i++)
            cout<<n->unit[i]<<" ";
        
        // Move to next node
        n = n->next;
    }
    cout<<endl;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    // std::cout << "Hello, World!\n";
    Node* head = new Node();
    head->numElements = 4;
    head->unit[0] = '0';
    head->unit[1] = '1';
    head->unit[2] = '2';
    head->unit[3] = '3';
    head->next = nullptr;
    printUnrolledList(head);
    UnrolledLinkedList list;
    list.list = head;
    list.insert('4', 4);
    printUnrolledList(list.list);
    char c = list.get(4);
    cout<<c<<endl;
    return 0;
}
