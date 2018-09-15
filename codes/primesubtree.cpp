// Complete the primeQuery function below.
bool isPrime(int num) {
    if (num == 1) return false;
    if (num == 2) return true;
    for (int i = 2; i * i <= num; ++i) {
        if (num % i == 0) return false;
    }
    return true;
}
 
int dfs(unordered_map<int, unordered_set<int>> &graph, int cur, vector<int>& dp, vector<int> values) {
    if (dp[cur] == -1) {
        dp[cur] = 0;
        for (auto next: graph[cur]) {
            dp[cur] += dfs(graph, next, dp, values);
        }
        if (isPrime(values[cur - 1])) dp[cur] += 1;   
    }
    return dp[cur];
}
 
void dfs0(unordered_map<int, unordered_set<int>> &graph, int parent, int cur) {
    for (auto next: graph[cur]) {
        if (parent != next) {
            dfs0(graph, cur, next);
        }
    }
    graph[cur].erase(parent);
}
 
vector<int> primeQuery(int n, vector<int> first, vector<int> second, vector<int> values, vector<int> queries) {
    unordered_map<int, unordered_set<int>> graph;
    for (int i = 0; i < first.size(); ++i) {
        graph[first[i]].insert(second[i]);
        graph[second[i]].insert(first[i]);
    }
    dfs0(graph, -1, 1);
    vector<int> dp(n + 1, -1);
    vector<int> ret;
    for (auto q: queries) {
        if (dp[q] == -1)
            ret.push_back(dfs(graph, q, dp, values));
        else
            ret.push_back(dp[q]);
    }
    return ret;
}