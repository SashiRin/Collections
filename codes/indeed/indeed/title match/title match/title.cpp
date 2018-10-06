//
//  main.cpp
//  title match
//
//  Created by BlairWu on 04/02/2018.
//  Copyright © 2018 UW. All rights reserved.
//

#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

void split(string& str, vector<string>& s){
    size_t pos = 0, found = 0;
    while((found = str.find_first_of(" ", pos)) != string::npos){
        s.push_back(str.substr(pos, found - pos));
        pos = found + 1;
    }
    s.push_back(str.substr(pos));
}

int getScore(string& rawTitle, string& cleanTitle){
    int s = 0;
    set<string> c;
    size_t pos = 0, found;
    while ((found = cleanTitle.find_first_of(" ", pos)) != string::npos) {
        c.insert(cleanTitle.substr(pos, found - pos));
        pos = found + 1;
    }
    c.insert(cleanTitle.substr(pos));
    vector<string> r;
    split(rawTitle, r);
    for (int i = 0; i < r.size(); i++) {
        if(c.find(r[i]) != c.end())
            s++;
        if(s == c.size())
            break;
    }
    return s;
}

string getMatch(string& rawTitle, vector<string>& cleanTitles){
    string res;
    int highest = -1;
    for(string clean : cleanTitles){
        int tmp = getScore(rawTitle, clean);
        if(tmp > highest){
            highest = tmp;
            res = clean;
        }
    }
    return res;
}

int getScoreDup(string rawTitle, string cleanTitle){
    int s = 0;
    vector<string> r;
    vector<string> c;
    split(rawTitle, r);
    split(cleanTitle, c);
    int row = c.size();
    int col = r.size();
    vector<vector<int>> dp(row, vector<int>(col, 0));
    for (int i = 0; i < row; i++) {
        string cCur = c[i];
        for (int j = 0; j < col; j ++) {
            string rCur = r[j];
            if(cCur == rCur){
                if(i == 0 || j == 0)
                    dp[i][j] = 1;
                else
                    dp[i][j] = max(1, dp[i - 1][j - 1] + 1);
            }
            s = max(s, dp[i][j]);
            if(s == min(row, col))
                break;
        }
    }
    return s;
}

string getMatchDup(string rawTitle, vector<string> cleanTitles){
    string res;
    int high = -1;
    for(string s : cleanTitles){
        int tmp = getScoreDup(rawTitle, s);
        if(tmp > high){
            high = tmp;
            res = s;
        }
    }
    return res;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    // std::cout << "Hello, World!\n";
    vector<string> cleanTitles = {"senior software engineer", "mechanical engineer", "engineer"};
    string rawTitle = "software engineer";
    vector<string> c = {"a a a b", "a b"};
    string r = "a a b";
    cout<<getMatch(rawTitle, cleanTitles)<<endl;
    cout<<getScoreDup(r, c[0])<<endl;
    return 0;
}
