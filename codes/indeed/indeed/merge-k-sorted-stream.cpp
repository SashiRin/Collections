//
//  merge_k_sorted_stream.cpp
//  Indeed_Onsite
//
//  Created by Xinglian Liu on 1/30/18.
//  Copyright © 2018 Xinglian Liu. All rights reserved.
//
/* =============================================================================
 Question Description
 =============================================================================
 Given n sorted stream, and a constant number k. The stream type is like iterator
 and it has two functions, move() and getValue(), find a list of numbers that each
 of them appears at least k times in these streams. Duplicate numbers in a stream
 should be counted as once.

 Note: In the interview, we should use min heap method
 =============================================================================
 code
 =============================================================================*/

#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;

class Stream{
private:
    vector<int> nums;
    
public:
    vector<int>::iterator it;
    Stream(vector<int> v): nums(v) {
        it = nums.begin();
    }
    bool move(){
        return it != nums.end();
    }
    int getValue(){
        ++it;
        return *it;
    }
};
class Comp{
public:
    bool operator()(Stream& s1, Stream& s2){
        return *(s1.it) > *(s2.it);
    }
};

class Merge_stream{
private:
    priority_queue<Stream, vector<Stream>, Comp> pq;
public:

    vector<int> find_nums(vector<Stream> streams, int k){
        vector<int> res;
        if (streams.size() == 0) return res;
        for (int i = 0; i < streams.size(); ++i){
            if (streams[i].move())
                pq.push(streams[i]);
        }
        while (!pq.empty()){
            Stream cur_s  = pq.top();
            pq.pop();
            int cur_val = *(cur_s.it);
            int count = 1;
            while (cur_s.move() && cur_s.getValue() == cur_val);
            if (cur_s.move())
                pq.push(cur_s);
            
            // deal with other streams with the same vals
            while (!pq.empty() && cur_val == *(pq.top().it)){
                ++count;
                Stream cur_top = pq.top();
                pq.pop();
                while (cur_top.move() && cur_top.getValue() == cur_val);
                if (cur_top.move())
                    pq.push(cur_top);
            }
            if (count >= k)
                res.push_back(cur_val);
        }
        return res;
    }
};


int main(){
    vector<int> v1 = {1, 2, 2, 3};
    vector<int> v2 = {0, 1, 3};
    vector<int> v3 = {0, 2, 3};
    Stream s1(v1);
    Stream s2(v2);
    int a = -1;
    for (int i = 0; i < 4; ++i){
        if (s2.move())
            a = s2.getValue();
    }
    Stream s3(v3);
    vector<Stream> s = {s1, s2, s3};
    Merge_stream m;
    vector<int> res;
    res = m.find_nums(s, 3);
    
    return 0;
}
