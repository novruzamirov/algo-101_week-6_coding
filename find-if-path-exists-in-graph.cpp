// Novruz Amirov
// Question Link: https://leetcode.com/problems/find-if-path-exists-in-graph/description/
class Solution {
    /*
        This Problem can be solved by using DFS (time complexity O(E + V))
        The time complexity of Dijkstra using adjacency list (O(E*logV)). 
        Therefore, in most cases, even using DFS can be better. 
        The aim is only to show that Dijkstra can be used to find
        if there is path between 2 nodes or not.
    */

public:
    bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
        bool result = false;

        // using adjacency list in dijkstra's algorithm is more better than matrix
        vector<vector<pair<int, int>>> adjacencyList(n, vector<pair<int, int>>(0));

        for(int i = 0; i < edges.size(); i++){
            adjacencyList[edges[i][0]].push_back(make_pair(edges[i][1], 1));
            adjacencyList[edges[i][1]].push_back(make_pair(edges[i][0], 1));
        }

        // because the nodes are from 0 to n - 1,
        // we do not need to use n+1 memory for vectors
        vector<int> distance(n, INT_MAX);
        vector<bool> visited(n, false);
        priority_queue<pair<int, int>>pq;

        distance[source] = 0;
        pq.push({0, source});

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

        // If there is no path between source and
        // destionation, the "shortest path" between
        // the nodes will be INT_MAX (have not changed) 
        if(distance[destination] != INT_MAX)
            result = true;

        return result;
        /*
            Time Complexity: O(E*logV)
            E -> number of edges
            N -> number of nodes
        */
    }
};