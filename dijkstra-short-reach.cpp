// Novruz Amirov
// Question Link: https://www.hackerrank.com/challenges/dijkstrashortreach/problem
#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'shortestReach' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. 2D_INTEGER_ARRAY edges
 *  3. INTEGER s
 */

vector<int> shortestReach(int n, vector<vector<int>> edges, int s) {
vector<int> result; // for result output
    // representing graph in form of adjacency list to decrease time complexity
    vector<vector<pair<int, int>>> adjacencyList(n+1, vector<pair<int, int>>(0));

    for(int i = 0; i < edges.size(); i++){
        adjacencyList[edges[i][0]].push_back(make_pair(edges[i][1], edges[i][2]));
        adjacencyList[edges[i][1]].push_back(make_pair(edges[i][0], edges[i][2]));
    }
    
    // Dijkstra's Algorithm using adjacency list
    vector<int> distance(n+1, INT_MAX);
    vector<bool> visited(n+1, false);
    distance[s] = 0;
    
    priority_queue<pair<int, int>> pq;
    pq.push({0, s});
    
    while(!pq.empty()){
        int a = pq.top().second;
        pq.pop();
        
        if(visited[a])
            continue;
        
        visited[a] = true;

        for(auto u : adjacencyList[a]){
            int b = u.first;
            int w = u.second;

            if(distance[b] > distance[a] + w){
              distance[b] = distance[a] + w;
                pq.push({-distance[b], b});
            }
        }
    }
    

    for(int i = 1; i < distance.size(); i++){
        // do not include the node itself
        if(i == s)
            continue;
        // if the distance is infinite, then disconnected node
        if(distance[i] == INT_MAX){ 
            result.push_back(-1);
        }
        else{
            result.push_back(distance[i]);
        }
    }
    
    return result;
    /*
      Time Complexity is: O(E*logV)
    */
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string t_temp;
    getline(cin, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++) {
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

        string s_temp;
        getline(cin, s_temp);

        int s = stoi(ltrim(rtrim(s_temp)));

        vector<int> result = shortestReach(n, edges, s);

        for (size_t i = 0; i < result.size(); i++) {
            fout << result[i];

            if (i != result.size() - 1) {
                fout << " ";
            }
        }

        fout << "\n";
    }

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
