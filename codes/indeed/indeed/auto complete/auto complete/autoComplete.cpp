//
//  main.cpp
//  auto complete
//
//  Created by BlairWu on 01/02/2018.
//  Copyright © 2018 UW. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Trie{
public:
    Trie* children[26];
    bool isLeaf;
    
    Trie(){
        this->isLeaf = false;
        fill_n(children, 26, nullptr);
    }
    
    ~Trie(){
        for(int i = 0; i < 26; ++i)
            delete children[i];
    }
};

void insert(string word, Trie* root){
    for (int i = 0; i < word.size(); i++) {
        if(!root->children[word[i] - 'a'])
            root->children[word[i] - 'a'] = new Trie();
        root = root->children[word[i] - 'a'];
    }
    root->isLeaf = true;
}

void build(vector<string> dict, Trie* root){
    for (string str : dict)
        insert(str, root);
}

void dfs(Trie* root, string& tmp, vector<string>& res){
    for (int i = 0; i < 26; i++) {
        if (root->children[i]) {
            tmp += (char) 'a' + i;
            if (root->children[i]->isLeaf) {
                res.push_back(tmp);
            }
            dfs(root->children[i], tmp, res);
            tmp.pop_back();
        }
    }
}

vector<string> autoComplete(vector<string> dict, string prefix){
    vector<string> res;
    Trie* root = new Trie();
    build(dict, root);
    for (int i = 0; i < prefix.size(); i++) {
        if (!root->children[prefix[i] - 'a'])
            return res;
        root = root->children[prefix[i] - 'a'];
    }
    string tmp = prefix;
    dfs(root, tmp, res);
    return res;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    // std::cout << "Hello, World!\n";
    vector<string> dict = {"cat", "catch", "car", "cash", "carry"};
    string prefix = "ca";
    vector<string> ans = autoComplete(dict, prefix);
    for(auto str : ans)
        cout<<str<<" ";
    cout<<endl;
    return 0;
}
