//
//  main.cpp
//  reverse html
//
//  Created by BlairWu on 03/02/2018.
//  Copyright © 2018 UW. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

string reverseString(string& str){
    int l = 0, r = str.size() - 1;
    while (l < r) {
        swap(str[l], str[r]);
        l++;
        r--;
    }
    return str;
}

string reverseHTML(string& str){
    string res = "";
    vector<string> list;
    string tmp;
    int start = 0;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == '&') {
            tmp = str.substr(start, i - start);
            tmp = reverseString(tmp);
            list.push_back(tmp);
            start = i;
        }
        if (str[i] == ';') {
            tmp = str.substr(start, i - start + 1);
            list.push_back(tmp);
            start = i + 1;
        }
    }
    if(str[str.size() - 1] != ';'){
        tmp = str.substr(start);
        tmp = reverseString(tmp);
        list.push_back(tmp);
    }
    for (int i = list.size() - 1; i >= 0; i--) {
        res += list[i];
    }
    return res;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    // std::cout << "Hello, World!\n";
    string s1 = "html&lt;123&yen;html";
    //s1 = reverseString(s1);
    s1 = reverseHTML(s1);
    cout<<s1<<endl;
    return 0;
}
