//
//  main.cpp
//  dice sum
//
//  Created by BlairWu on 03/02/2018.
//  Copyright © 2018 UW. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
using namespace std;

float sumProbability(int dice, int target){
    if (target < dice || target > dice * 6) {
        return 0;
    }
    int total = pow(6, dice);
    int totalS = 0;
    vector<vector<int>> dp(dice + 1, vector<int>(target + 1, 0));
    for (int i = 1; i <= min(6, target); i++) {
        dp[1][i] = 1;
    }
    for (int i = 2; i <= dice; i++) {
        for (int j = 1; j <= target; j++) {
            for (int k = 1; k <= 6 && k < j; k++) {
                dp[i][j] += dp[i - 1][j - k];
            }
        }
    }
    totalS = dp[dice][target];
    return (float) totalS / total;
}

void dfs(int& totalS, int dice, int target){
    if(dice == 0 && target == 0){
        totalS++;
        return;
    }
    if (target > dice * 6 || target < dice) {
        return;
    }
    for (int k = 1; k <= min(6, target); k++) {
        dfs(totalS, dice - 1, target - k);
    }
}

float sumDFS(int dice, int target){
    int total = pow(6, dice);
    int totalS = 0;
    dfs(totalS, dice, target);
    return (float) totalS / total;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    // std::cout << "Hello, World!\n";
    float p1 = sumProbability(5, 22);
    float p2 = sumDFS(5, 22);
    cout<<p1<<" "<<p2<<endl;
    return 0;
}
