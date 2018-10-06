//
//  main.cpp
//  validate python indentation
//
//  Created by BlairWu on 31/01/2018.
//  Copyright © 2018 UW. All rights reserved.
//

#include <iostream>
#include <string>
#include <stack>
#include <vector>

using namespace std;

int countTab(string str){
    int count = 0;
    // int i = 0;
    while (count < str.size() && str[count] == ' ') {
        count++;
    }
    if (str[count] == '#' || count == str.size()) {
        return -1;
    } else {
        return count;
    }
    // return count;
}

int getLast(string str){
    int n = str.size();
    while(n >= 0 && str[n] == ' ')
        n--;
    return n;
}

bool validatePython(vector<string>& code){
    stack<int> indentation;
    indentation.push(0);
    bool newTab = false;
    for (int i = 0; i < code.size(); i++) {
        int cur = indentation.top();
        int tmp = countTab(code[i]);
        if (tmp == -1) {
            continue;
        }
        if(cur == tmp && !newTab)
            ;
        else if(cur < tmp && newTab){
            indentation.push(tmp);
            newTab = false;
        }else if (cur > tmp){
            while (cur != tmp && cur) {
                indentation.pop();
                cur = indentation.top();
            }
            if(cur != tmp)
                return false;
        }else
            return false;
        if (code[i][code[i].size() - 1] == ':') {
            newTab = true;
        }
    }
    return true;
}
int main(int argc, const char * argv[]) {
    // insert code here...
    //cout << "Hello, World!\n";
    //string str1 = "hi\rI am \r yours.\r";
    //cout<<str1;
    string str1 = "for i in range(1, 20):";
    string str2 = "";
    string str3 ="  # this is a comment";
    string str4 = "  sum = 0";
    string str5 = "  for j in range(i, 20):";
    string str6 = "    sum += j";
    string str7 = "  print(sum)";
    string str8 = "print(\"finished\")";
    //vector<string> code = {str1, str2, str3, str4, str5, str6, str7, str8};
    vector<string> code;
    for(string str : code)
        cout<<str<<endl;
    if (validatePython(code)) {
        cout<<"true"<<endl;
    } else {
        cout<<"false"<<endl;
    }
    return 0;
}
