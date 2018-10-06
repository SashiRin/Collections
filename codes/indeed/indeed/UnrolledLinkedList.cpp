#include <iostream>
#include <vector>

using namespace std;

struct Node{
    vector<char> chars;
    int len;
    Node *next;
};

struct UnRolledList{
    Node *head;
    int TotalLen;
};

class solution{
public:
    UnRolledList *list;
    
    char get(int index){
        Node *node = list->head;
        int total = list->TotalLen;
        
        if(!node || index > total) return ' ';
        
        while(node && node->len <= index){
            index -= node->len;
            node = node->next;
        }
        
        if(!node) return ' ';
        return node->chars[index];
    }
    
    
    void insert(char ch, int index){
        Node *node = list->head;
        int total = list->TotalLen;
        
        if(!node || index > total) return;
        
        while(node && node->len <= index){
            index -= node->len;
            node = node->next;
        }
        
        if(!node) return;
        
        if(node->len < 5){
            for(int i = node->len; i > index; --i) node->chars[i] = node->chars[i - 1];
            node->chars[index] = ch;
            node->len++;
        }
        else{
            Node *newNode = new Node();
            newNode->len = 5 - index;
            
            for(int i = index; i < node->len; ++i){
                newNode->chars[i - index] = node->chars[i];
                node->chars[i] = ' ';
            }
            node->chars[index] = ch;
            node->len = index + 1;
            newNode->next = node->next;
            node->next = newNode;
        }
    }
};


