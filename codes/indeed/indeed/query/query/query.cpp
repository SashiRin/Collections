//
//  main.cpp
//  query
//
//  Created by BlairWu on 04/02/2018.
//  Copyright © 2018 UW. All rights reserved.
//

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <set>

using namespace std;

class Query{
public:
    class Maximal{
    public:
        int count;
        vector<string> list;
        Maximal(){
            this->count = 0;
            this->list = vector<string>();
        }
    };
    map<string, vector<string>> users; //words the users has queried
    //map<string, vector<string>> words; //users who have queried the word
    map<string, map<string, int>> related; //words related with counts
    map<string, Maximal> answer;
    
    void standio(){
        cout<<"Let's start here: ";
        int lines;
        cin>>lines;
        //cout<<lines<<" #"<<endl;
        while(lines){
            string info;
            getline(cin, info);
            if (!info.empty()) {
                //cout<<info<<" #"<<endl;
                size_t pos = 0, found = info.find_first_of(" ");
                string user = info.substr(pos, found - pos);
                pos = found + 1;
                string word = info.substr(pos);
                string res = search(user, word);
                cout<<res<<endl;
                lines--;
            }
        }
    }
    
    /*string search(string& user, string& word){
        string res = "";

        if(users.find(user) == users.end())
            users[user] = vector<string>(); //the user appears for the first time
        if(words.find(word) == words.end())
            words[word] = vector<string>(); //the word appears for the first time
        if(related.find(word) == related.end())
            related[word] = map<string, int>();
        if(answer.find(word) == answer.end())
            answer[word] = Maximal();
        
        int count = answer[word].count;
        vector<string> list = answer[word].list;
        users[user].push_back(word);

        if(!words[word].empty()){
            set<string> tmp;
            for(string u : words[word]){
                for(string w : users[u]){
                    if(w != word && tmp.find(w) == tmp.end()){
                        if(w == "java") cout<<"#"<<endl;
                        if(related[w].find(word) == related[w].end()){
                            related[w][word] = 1;
                        }else{
                            related[w][word]++;
                        }
                        if(answer[w].count < related[w][word]){
                            answer[w].count = related[w][word];
                            answer[w].list = {word};
                        }else if(answer[w].count == related[w][word]){
                            answer[w].list.push_back(word);
                        }
                        tmp.insert(w);
                    }
                }
            }
        }
        
        for(string w : users[user]){
            if(word != w){
                if(related[word].find(w) == related[word].end()){
                    related[word][w] = 1;
                }else{
                    related[word][w]++;
                }
                if(answer[word].count < related[word][w]){
                    answer[word].count = related[word][w];
                    answer[word].list = {w};
                }else if(answer[word].count == related[word][w]){
                    answer[word].list.push_back(w);
                }
            }
        }
                words[word].push_back(user);

        cout<<"# ";
        for(string s : answer["java"].list)
        cout<<s<<" ";
        cout<<endl;
        res += to_string(count);
        for(string w : list)
            res = res + " " + w;
        return res;
    }*/
    string search(string user, string word){
        string res = "";
        if(users.find(user) == users.end())
            users[user] = vector<string>();
        if(related.find(word) == related.end())
            related[word] = map<string, int>();
        if(answer.find(word) == answer.end())
            answer[word] = Maximal();
        
        vector<string> list = answer[word].list;
        int count = answer[word].count;
        
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
        
        // sort(list.begin(), list.end());
        res += to_string(count);
        for(string s : list)
            res = res + " " + s;
        return res;
    }
};



int main(int argc, const char * argv[]) {
    // insert code here...
    // std::cout << "Hello, World!\n";
    Query q;
    q.standio();
    return 0;
}
