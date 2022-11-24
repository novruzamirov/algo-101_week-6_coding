// Novruz Amirov
// Question Link: https://www.hackerrank.com/challenges/kruskalmstrsub/problem
#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'kruskals' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts WEIGHTED_INTEGER_GRAPH g as parameter.
 */

/*
 * For the weighted graph, <name>:
 *
 * 1. The number of nodes is <name>_nodes.
 * 2. The number of edges is <name>_edges.
 * 3. An edge exists between <name>_from[i] and <name>_to[i]. The weight of the edge is <name>_weight[i].
 *
 */

// Union Find Structure:
vector<int> size_set(3000); // for the size of each set
vector<int> link(3000); // for the parent of each set

// to find the parent of the set
int find(int x){
    while(x != link[x]) 
        x = link[x];
    return x;
}

// to find if 2 nodes are in same set or not
bool same(int x, int y){
    // if the parent is same, then yes
    if(find(x) == find(y))
        return true;
    
    // otherwise, in seperated sets
    return false;
}

void unite(int a, int b){
    a = find(a); // the parent of node a
    b = find(b); // the parent of node b
    
    if(size_set[a] < size_set[b]) swap(a, b);
    
    size_set[a] += size_set[b]; // size of bigger set increased by the size of smaller set.
    
    link[b] = link[a]; // the parent of smaller set is the parent of bigger set now.
}

int kruskals(int g_nodes, vector<int> g_from, vector<int> g_to, vector<int> g_weight) {
    int cost = 0; // to find the cost of MST
    
    for(int i = 1; i < link.size(); i++) link[i] = i; // initially, each node is seperate
    for(int i = 1; i< size_set.size(); i++) size_set[i] = 1; // initially, the size of all sets are 1.
    
    vector<vector<int>> edges;
    for(int i = 0; i < g_from.size(); i++){
        edges.push_back({g_weight[i], g_from[i], g_to[i]});
    }
    
    // sort in ascending order, ACCORDING TO THE WEIGHT OF EDGES!
    sort(edges.begin(), edges.end());
    
    for(auto u : edges){
        int w = u[0];
        int a = u[1];
        int b = u[2];
        
        int x = find(a);
        int y = find(b);
        
        if(x == y)
            continue;
        
        unite(x, y);
        cost += w;
    }
    
    return cost;
    /*
        Time Complexity is: O(ElogV).
    */
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string g_nodes_edges_temp;
    getline(cin, g_nodes_edges_temp);

    vector<string> g_nodes_edges = split(rtrim(g_nodes_edges_temp));

    int g_nodes = stoi(g_nodes_edges[0]);
    int g_edges = stoi(g_nodes_edges[1]);

    vector<int> g_from(g_edges);
    vector<int> g_to(g_edges);
    vector<int> g_weight(g_edges);

    for (int i = 0; i < g_edges; i++) {
        string g_from_to_weight_temp;
        getline(cin, g_from_to_weight_temp);

        vector<string> g_from_to_weight = split(rtrim(g_from_to_weight_temp));

        int g_from_temp = stoi(g_from_to_weight[0]);
        int g_to_temp = stoi(g_from_to_weight[1]);
        int g_weight_temp = stoi(g_from_to_weight[2]);

        g_from[i] = g_from_temp;
        g_to[i] = g_to_temp;
        g_weight[i] = g_weight_temp;
    }

    int res = kruskals(g_nodes, g_from, g_to, g_weight);

    // Write your code here.
    fout << res;

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
