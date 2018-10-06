//
//  main.cpp
//  indeed onsite
//
//  Created by BlairWu on 09/02/2018.
//  Copyright © 2018 UW. All rights reserved.
//

#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

/*struct Maximal{
    int count; // score
    vector<string> list; // list of queries with that score
    Maximal() : count(0), list(vector<string>()) {}
};*/

class Maximal{
public:
    int count;
    vector<string> list;
    Maximal(){
        this->count = 0;
        this->list = vector<string>();
    }
};

class query{
public:
    map<string, vector<string>> users; // words the user has queried
    map<string, map<string, int>> related; // related words and its scores
    map<string, Maximal> answer; //the expected output for the input
    
    void stand_io(){
        int lines; //number of input queries
        cin>>lines;
        while(lines){
            string info;
            getline(cin, info);
            if(!info.empty()){
                size_t pos = 0, found = 0;
                found = info.find_first_of(" ");
                string user = info.substr(pos, found - pos);
                pos = found + 1;
                string word = info.substr(pos);
                string res = search(user, word);
                cout<<res<<endl;
                lines--;
            }
        }
    }
    
    string search(string user, string word){
        string res = "";
        if(users.find(user) == users.end()){
            users[user] = vector<string>();
        }
        if(related.find(word) == related.end()){
            related[word] = map<string, int>();
        }
        if(answer.find(word) == answer.end()){
            answer[word] = Maximal();
        }
        
        //first obtain the output for the current query through map "answer"
        int score = answer[word].count;
        vector<string> list = answer[word].list;
        
        //then update all the maps
        for(string w : users[user]){
            if(related[word].find(w) == related[word].end()){
                related[word][w] = 1;
            }else{
                related[word][w]++;
            }
            if(answer[word].count == related[word][w]){
                answer[word].list.push_back(w);
            }else if(answer[word].count < related[word][w]){
                answer[word].list = {w};
                answer[word].count = related[word][w];
            }
            
            if(related[w].find(word) == related[w].end()){
                related[w][word] = 1;
            }else{
                related[w][word]++;
            }
            if(answer[w].count == related[w][word]){
                answer[w].list.push_back(word);
            }else if(answer[w].count < related[w][word]){
                answer[w].list = {word};
                answer[w].count = related[w][word];
            }
        }
        users[user].push_back(word);
        
        sort(list.begin(), list.end());
        res += to_string(score);
        if(score){
            for(string str : list){
                res = res + " " + str;
            }
        }
        return res;
    }
};

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    query q;
    q.stand_io();
    return 0;
}
