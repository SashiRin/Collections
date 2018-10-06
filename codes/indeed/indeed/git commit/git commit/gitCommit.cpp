//
//  main.cpp
//  git commit
//
//  Created by BlairWu on 03/02/2018.
//  Copyright © 2018 UW. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>

using namespace std;

struct GitNode{
    int val;
    vector<GitNode*> children;
    vector<GitNode*> parents;
    
    GitNode(int v) : val(v), children(NULL), parents(NULL) {}
};

GitNode* build(vector<vector<int>> gits, map<int, GitNode*>& nodes, map<GitNode*, int>& indegree){
    for(auto item : gits){
        int from = item[0];
        int to = item[1];
        GitNode* fromNode;
        GitNode* toNode;
        if(nodes.find(from) != nodes.end()){
            fromNode = nodes[from];
        }else{
            fromNode = new GitNode(from);
        }
        
        if (nodes.find(to) != nodes.end()) {
            toNode = nodes[to];
        } else {
            toNode = new GitNode(to);
        }
        
        fromNode->children.push_back(toNode);
        toNode->parents.push_back(fromNode);
        if(indegree.find(toNode) != indegree.end()){
            indegree[toNode]++;
        }else{
            indegree[toNode] = 1;
        }
        if(indegree.find(fromNode) == indegree.end())
            indegree[fromNode] = 0;
        
        nodes[from] = fromNode;
        nodes[to] = toNode;
    }
    cout<<"The root is ";
    GitNode* root = nullptr;
    for(auto it : indegree)
        if(it.second == 0){
            cout<<it.first->val<<" ";
            root = it.first;
        }
    cout<<endl;
    return root;
}

vector<int> findCommits(GitNode* root){
    vector<int> res;
    set<GitNode*> visited;
    queue<GitNode*> q;
    q.push(root);
    while (!q.empty()) {
        GitNode* node = q.front();
        q.pop();
        if(visited.find(node) == visited.end()){
            visited.insert(node);
            res.push_back(node->val);
        }
        for(auto child : node->children){
                q.push(child);
        }
    }
    return res;
}

int findLCA(GitNode* p, GitNode* q){
    int LCA = -1;
    map<GitNode*, int> path;
    queue<pair<GitNode*, int>> qq;
    qq.push(make_pair(p, 0));
    set<GitNode*> visited;
    while (!qq.empty()) {
        GitNode* node = qq.front().first;
        int d = qq.front().second;
        qq.pop();
        if (visited.find(node) == visited.end()) {
            path[node] = d;
            visited.insert(node);
        }
        for(auto parent : node->parents){
            qq.push(make_pair(parent, d + 1));
        }
    }
    
    visited.clear();
    int dmin = INT_MAX;
    qq.push(make_pair(q, 0));
    while (!qq.empty()) {
        GitNode* node = qq.front().first;
        int d = qq.front().second;
        qq.pop();
        if (path.find(node) != path.end()) {
            if (path[node] + d < dmin) {
                dmin = path[node] + d;
                LCA = node->val;
                break;
            }
        }
        if (visited.find(node) == visited.end()) {
            path[node] = d;
            visited.insert(node);
        }
        for(auto parent : node->parents){
            qq.push(make_pair(parent, d + 1));
        }
    }
    return LCA;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    // std::cout << "Hello, World!\n";
    vector<vector<int>> gits = {{0, 1}, {1, 3}, {3, 5}, {0, 2}, {2, 4}, {4, 5}};
    map<int, GitNode*> nodes;
    map<GitNode*, int> indegree;
    GitNode* root = build(gits, nodes, indegree);
    vector<int> commits = findCommits(root);
    cout<<"find commits for root: ";
    for(int i : commits)
        cout<<i<<" ";
    cout<<endl;
    
    GitNode* node1 = nodes[1];
    GitNode* node2 = nodes[2];
    int LCA = findLCA(node1, node2);
    cout<<"find LCA: "<<LCA<<endl;
    return 0;
}
