// Novruz Amirov
// Question Link: https://www.hackerrank.com/challenges/primsmstsub/problem
#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'prims' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. 2D_INTEGER_ARRAY edges
 *  3. INTEGER start
 */

int prims(int n, vector<vector<int>> edges, int start) {
    int cost = 0; // for calculatng the cost of MST
    
    // representing the graph using adjacency list
    vector<vector<pair<int, int>>> adjacencyList(n + 1, vector<pair<int, int>>(0));
    
    for(int i = 0; i < edges.size(); i++){
        adjacencyList[edges[i][0]].push_back(make_pair(edges[i][1], edges[i][2]));
        adjacencyList[edges[i][1]].push_back(make_pair(edges[i][0], edges[i][2]));
    }
    
    int startingNode = edges[0][0]; // can be arbitrarily chosen, won't matter
    
    // Prim's Algorithm Implementation:
    vector<int> distance(n+1, INT_MAX);
    vector<bool> visited(n+1, false);
    priority_queue<pair<int, int>> pq;
    
    distance[startingNode] = 0;
    pq.push({0, startingNode});
    
    while(!pq.empty()){
        int a = pq.top().second;
        pq.pop();
        
        if(visited[a])
            continue;
            
        visited[a] = true;
        
        for(auto u : adjacencyList[a]){
            int b = u.first;
            int w = u.second;

            if(!visited[b] && distance[b] > w){
                if(distance[b] != INT_MAX)
                    cost -= distance[b];
                distance[b] = w;
                pq.push({-distance[b], b});
                cost += w;
            }
        }
    }
    
    return cost;
    /*
        Time Complexity is: O(V + ElogV).
    */
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int m = stoi(first_multiple_input[1]);

    vector<vector<int>> edges(m);

    for (int i = 0; i < m; i++) {
        edges[i].resize(3);

        string edges_row_temp_temp;
        getline(cin, edges_row_temp_temp);

        vector<string> edges_row_temp = split(rtrim(edges_row_temp_temp));

        for (int j = 0; j < 3; j++) {
            int edges_row_item = stoi(edges_row_temp[j]);

            edges[i][j] = edges_row_item;
        }
    }

    string start_temp;
    getline(cin, start_temp);

    int start = stoi(ltrim(rtrim(start_temp)));

    int result = prims(n, edges, start);

    fout << result << "\n";

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
