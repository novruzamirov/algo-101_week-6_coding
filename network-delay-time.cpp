// Novruz Amirov
// Question Link: https://leetcode.com/problems/network-delay-time/description/
class Solution {
public:
    /*
        The DIRECTED Graph is given (This will be used in how to 
        represent the Graph using Adjacency List). We need to find 
        the farthest node after calculating shortest path to each node.
    */
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        // starting node is k. Dijkstra's Algorithm
       vector<vector<pair<int, int>>> adjacencyList(n+1, vector<pair<int, int>>(0));

        for(int i = 0; i < times.size(); i++){
            // because it is directed, we will not do reverse one.
            adjacencyList[times[i][0]].push_back(make_pair(times[i][1], times[i][2]));
        }

        // Dijkstra's Algorithm
        vector<int> distance(n+1, INT_MAX);
        vector<bool> visited(n+1, false);
        priority_queue<pair<int, int>> pq;
        pq.push({0, k});
        distance[k] = 0;

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

        int result = 0;
        for(int i = 1; i < distance.size(); i++){
            if(result < distance[i]){
                result = distance[i];
            }
        }

        // if the result is INT_MAX, then it means
        // there is a network node that can not be reached
        // briefly DISCONNECTED NODE. (-1)
        if(result == INT_MAX)
            return -1;

        return result;
        /*
            Time Complexity is: O(E*logV)
        */
    }
};