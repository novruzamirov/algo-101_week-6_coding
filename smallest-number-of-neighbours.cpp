// Novruz Amirov
// Question Link: https://leetcode.com/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/description/

class Solution {
/*
    For each node, we need to do Dijkstra's Algorithm to find shortest distance
    to each node. After completing Dijkstra's Algorithm we will find the number
    of nodes which has a distance with less than threshold value from starting node.
    All number of nodes which is less than the threshold value for each node will
    be stored in array, and starting from right one, we will find the index of minimum.
*/

public:
    int thresholdValues(vector<vector<pair<int, int>>>& adjacencyList, int node, int threshold){
        int count = 0;

        vector<int> distance(adjacencyList.size(), INT_MAX);
        vector<bool> visited(adjacencyList.size(), false);
        priority_queue<pair<int, int>> pq;
        pq.push({0, node});
        distance[node] = 0;

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

        for(int i = 0; i < distance.size(); i++){
            if(distance[i] <= threshold && i != node)
                count++; 
        }
        return count;
    }

    
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        vector<vector<pair<int, int>>> adjacencyList(n, vector<pair<int, int>>(0));

        for(int i = 0; i < edges.size(); i++){
            adjacencyList[edges[i][0]].push_back(make_pair(edges[i][1], edges[i][2]));
            adjacencyList[edges[i][1]].push_back(make_pair(edges[i][0], edges[i][2]));
        }

        vector<int> results; // to store number of nodes less than threshold value

        for(int i = 0; i < n; i++){
            int threshold = thresholdValues(adjacencyList, i, distanceThreshold);
            results.push_back(threshold);
        }

        int res = INT_MAX; // to find the minimum
        int res_index = n; // to find the minimum index
        for(int i = n-1; i >= 0; i--){
            if(results[i] < res){
                res = results[i];
                res_index = i;
            }
        }
    
        return res_index;
        /*
            The Time Complexity is: O(V * ElogV)
        */
    }
};