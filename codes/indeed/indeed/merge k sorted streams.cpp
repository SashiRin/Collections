//
//  merge k sorted streams.cpp
//  
//
//  Created by BlairWu on 01/02/2018.
//

/*
 iterator
 int peek() : return the value of the first element in the stream
 int next() : return the value of the first element in the stream and delete that element
 bool hasNext() : return if there's element next
 */

#include <stdio.h>
#include <iostream>
#include <list>
#include <priority_queue>
#include <vector>

class Node{
    int val;
    iterator nxt;
    public Node(iterator itr){
        this.val = itr.next();
        this.nxt = itr;
    }
};

struct cmp{
    bool operator()(Node n1, Node n2){
        return n1.val > n2.val;
    }
};

vector<int> findK(vector<iterator> streams, int k){
    vector<int> res;
    priority_queue<Node> minHeap;
    for (int i = 0; i < streams.size(); i++) {
        if (streams[i]) {
            minHeap.push(Node(streams[i]));
        }
    }
    Node cur = minHeap.top();
    int curVal = cur.val, count = 1;
    minHeap.pop();
    while (cur.nxt) {
        int val = cur.nxt.next();
        if(val == curVal)
            continue;
        cur.val = val;
        minHeap.push(cur);
        break;
    }
    while (!minHeap.empty()) {
        Node cur = minHeap.top();
        minHeap.pop();
        if (cur.val == curVal) {
            count++;
        } else {
            if(minHeap.size() < k)
                break;
            if(count >= k)
                res.push_back(curVal);
            curVal = cur.val;
            count = 1;
        }
        while (cur.nxt) {
            int val = cur.nxt.next();
            if(val == curVal)
                continue;
            cur.val = val;
            minHeap.push(cur);
            break;
        }
    }
    if(count >= k)
        res.push_back(curVal);
    return res;
}
