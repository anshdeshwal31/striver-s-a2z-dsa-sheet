#include <bits/stdc++.h>
using namespace std;



// LC 994 - rotten oranges
int solve(vector<vector<int>>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();
    
    queue<pair<int, int>> q;
    int freshOranges = 0;

    // Initialize the queue with all the rotten oranges and count fresh oranges
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == 2) {
                q.push({i, j});
            } else if (grid[i][j] == 1) {
                freshOranges++;
            }
        }
    }

    if (freshOranges == 0) return 0; 

    int minutes = 0;
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    while (!q.empty()) {
        int qSize = q.size();
        bool hasNewRotten = false;

        for (int i = 0; i < qSize; i++) {
            int x = q.front().first;
            int y = q.front().second;
            q.pop();

            for (auto& d : directions) {
                int newX = x + d.first;
                int newY = y + d.second;

                if (newX >= 0 && newX < rows && newY >= 0 && newY < cols && grid[newX][newY] == 1) {
                    grid[newX][newY] = 2;
                    freshOranges--;
                    q.push({newX, newY});
                    hasNewRotten = true;
                }
            }
        }

        if (hasNewRotten) {
            minutes++;
        }
    }

    return freshOranges == 0 ? minutes : -1;
}
int orangesRotting(vector<vector<int>>& grid) {
    return solve(grid);
}


// LC 542 - 01 matrix
    // // brute force  
    // int solve(int row, int col, vector<vector<int>>& mat) {
    //     // using bfs traversal
    //     vector<vector<int>> dir = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; // up, right, down, left
    //     queue<pair<int, int>> q;
    //     q.push({row, col});

    //     // Change: Added a visited matrix to avoid revisiting
    //     vector<vector<bool>> visited(mat.size(), vector<bool>(mat[0].size(), false));
    //     visited[row][col] = true;

    //     int k = 0;
    //     while (!q.empty()) {
    //         int size = q.size();

    //         for (int i = 0; i < size; i++) {
    //             auto top = q.front();
    //             q.pop();
    //             int x = top.first;
    //             int y = top.second;

    //             // Check if current cell is 0
    //             if (mat[x][y] == 0) {
    //                 return k;  // return distance if zero is found
    //             }

    //             // Traverse in four directions
    //             for (auto d : dir) {
    //                 int newX = x + d[0];
    //                 int newY = y + d[1];
                    
    //                 // Change: Added condition to avoid revisiting cells
    //                 if (newX >= 0 && newX < mat.size() && newY >= 0 && newY < mat[0].size() && !visited[newX][newY]) {
    //                     q.push({newX, newY});
    //                     visited[newX][newY] = true;
    //                 }
    //             }
    //         }
    //         k++;  // Increase distance after checking one level of BFS
    //     }

    //     return -1;
    // }

    // vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
    //     int n = mat.size();
    //     int m = mat[0].size();
    //     vector<vector<int>> res(n, vector<int>(m, 0));

    //     for (int i = 0; i < n; i++) {
    //         for (int j = 0; j < m; j++) {
    //             if (mat[i][j] != 0) {
    //                 // Change: Initialize distance as large value instead of 0
    //                 res[i][j] = solve(i, j, mat);
    //             }
    //         }
    //     }

    //     return res;
    // }


    // optimised solution 

    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int m = mat.size(), n = mat[0].size();
        vector<vector<int>> result(m, vector<int>(n, INT_MAX)); // Initialize result matrix
        queue<pair<int, int>> q;  // Queue to store coordinates for BFS
        
        // Initialize queue with all 0's and set their distance to 0
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (mat[i][j] == 0) {
                    result[i][j] = 0;
                    q.push({i, j});  // Add all '0' positions to the queue
                }
            }
        }
    
        // Direction vectors for moving up, down, left, and right
        vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        // Perform BFS
        while (!q.empty()) {
            int x = q.front().first;
            int y = q.front().second;
            q.pop();
    
            for (auto dir : directions) {
                int newX = x + dir.first;
                int newY = y + dir.second;
                
                // If the new position is within bounds and we found a shorter distance
                if (newX >= 0 && newX < m && newY >= 0 && newY < n) {
                    if (result[newX][newY] > result[x][y] + 1) {
                        result[newX][newY] = result[x][y] + 1;  // Update distance
                        q.push({newX, newY});  // Add the new position to the queue
                    }
                }
            }
        }
    
        return result;
    }


    
    
    // number of distinct islands - https://www.geeksforgeeks.org/problems/number-of-distinct-islands/1
    void dfs(int i, int j, vector<vector<int>>& grid, vector<vector<bool>>& visited, string& path, string dir) {
        int n = grid.size(), m = grid[0].size();
        if (i < 0 || j < 0 || i >= n || j >= m || visited[i][j] || grid[i][j] == 0) return;

        visited[i][j] = true;
        path += dir;

        dfs(i+1, j, grid, visited, path, "D"); // down
        dfs(i-1, j, grid, visited, path, "U"); // up
        dfs(i, j+1, grid, visited, path, "R"); // right
        dfs(i, j-1, grid, visited, path, "L"); // left

        path += "B"; // backtrack
    }

    int countDistinctIslands(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        set<string> uniqueIslands;
        vector<vector<bool>> visited(n, vector<bool>(m, false));

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (!visited[i][j] && grid[i][j] == 1) {
                    string path = "";
                    dfs(i, j, grid, visited, path, ""); 
                    uniqueIslands.insert(path);
                }
            }
        }

        return uniqueIslands.size();
    }


    
    // LC 802. Find Eventual Safe States

    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<vector<int>> revGraph(n);
        vector<int> indegree(n, 0);

        // Step 1: Build reverse graph and count indegrees
        for (int u = 0; u < n; ++u) {
            for (int v : graph[u]) {
                revGraph[v].push_back(u); 
                indegree[u]++;            // original outdegree becomes indegree
            }
        }

        // Step 2: Queue all nodes with 0 indegree (terminal nodes)
        queue<int> q;
        for (int i = 0; i < n; ++i) {
            if (indegree[i] == 0) q.push(i);
        }

        vector<int> safe;
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            safe.push_back(node);
            for (int neighbor : revGraph[node]) {
                indegree[neighbor]--;
                if (indegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }

        sort(safe.begin(), safe.end());
        return safe;
    }



    // LC 785. Is Graph Bipartite?
    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> color(n, -1);  // -1 means uncolored

        for (int i = 0; i < n; ++i) {
            if (color[i] == -1) {  // Start BFS for each unvisited component
                queue<int> q;
                q.push(i);
                color[i] = 0;  // Start coloring with 0

                while (!q.empty()) {
                    int node = q.front();
                    q.pop();

                    for (int neighbor : graph[node]) {
                        if (color[neighbor] == -1) {
                            color[neighbor] = 1 - color[node]; // Alternate color
                            q.push(neighbor);
                        } else if (color[neighbor] == color[node]) {
                            return false; // Same color on both ends of edge
                        }
                    }
                }
            }
        }
        return true;
    }



    // LC 802. Find Eventual Safe States
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<vector<int>> revGraph(n);
        vector<int> indegree(n, 0);

        // Step 1: Build reverse graph and count indegrees
        for (int u = 0; u < n; ++u) {
            for (int v : graph[u]) {
                revGraph[v].push_back(u); 
                indegree[u]++;            // original outdegree becomes indegree
            }
        }

        // Step 2: Queue all nodes with 0 indegree (terminal nodes)
        queue<int> q;
        for (int i = 0; i < n; ++i) {
            if (indegree[i] == 0) q.push(i);
        }

        vector<int> safe;
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            safe.push_back(node);
            for (int neighbor : revGraph[node]) {
                indegree[neighbor]--;
                if (indegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }

        sort(safe.begin(), safe.end());
        return safe;
    }



    // LC 1631. Path With Minimum Effort
    int minimumEffortPath(vector<vector<int>>& heights) {
        int m = heights.size(), n = heights[0].size();
        vector<vector<int>> dist(m, vector<int>(n, INT_MAX));
        dist[0][0] = 0;

        set<tuple<int, int, int>> st;
        st.insert({0, 0, 0}); // {effort, row, col}

        vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

        while (!st.empty()) {
            auto [effort, x, y] = *st.begin();
            st.erase(st.begin());

            if (x == m - 1 && y == n - 1) return effort;

            for (auto [dx, dy] : directions) {
                int nx = x + dx, ny = y + dy;
                if (nx >= 0 && ny >= 0 && nx < m && ny < n) {
                    int diff = abs(heights[x][y] - heights[nx][ny]);
                    int maxEffort = max(effort, diff);

                    if (maxEffort < dist[nx][ny]) {
                        // Remove old entry if present
                        if (dist[nx][ny] != INT_MAX) {
                            st.erase({dist[nx][ny], nx, ny});
                        }
                        dist[nx][ny] = maxEffort;
                        st.insert({maxEffort, nx, ny});
                    }
                }
            }
        }

        return 0;
    }



    // LC 787. Cheapest Flights Within K Stops
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        vector<pair<int, int>> adj[n]; // {to, cost}
        for (auto& f : flights) {
            adj[f[0]].push_back({f[1], f[2]});
        }
    
        // {cost, stops, node}
        set<tuple<int, int, int>> st;
        st.insert({0, 0, src});
    
        // min cost to reach [node][stops]
        vector<vector<int>> dist(n, vector<int>(k + 2, INT_MAX));
        dist[src][0] = 0;
    
        while (!st.empty()) {
            auto [cost, stops, node] = *st.begin();
            st.erase(st.begin());
    
            if (node == dst) return cost;
            if (stops > k) continue;
    
            for (auto [nei, price] : adj[node]) {
                int newCost = cost + price;
                if (newCost < dist[nei][stops + 1]) {
                    dist[nei][stops + 1] = newCost;
                    st.insert({newCost, stops + 1, nei});
                }
            }
        }
    
        return -1;
    }


    // LC 127 - word ladder 1
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        if (wordSet.find(endWord) == wordSet.end()) return 0;

        queue<pair<string, int>> q;
        q.push({beginWord, 1});

        while (!q.empty()) {
            string word = q.front().first;
            int length = q.front().second;
            q.pop();

            if (word == endWord) return length;

            for (int i = 0; i < word.size(); i++) {
                string temp = word;
                for (char c = 'a'; c <= 'z'; c++) {
                    temp[i] = c;
                    if (wordSet.find(temp) != wordSet.end()) {
                        q.push({temp, length + 1});
                        wordSet.erase(temp);  // mark visited
                    }
                }
            }
        }

        return 0;
    }



    
    // LC 126 - word ladder 2
    vector<vector<string>> findSequences(string beginWord, string endWord, vector<string> &wordList){

        unordered_set<string> st(wordList.begin(), wordList.end()); 
        queue<vector<string>> q;
        q.push({beginWord});

        // A vector defined to store the words being currently used
        // on a level during BFS.
        vector<string> usedOnLevel;
        usedOnLevel.push_back(beginWord);
        int level = 0;
        vector<vector<string>> ans;

        while (!q.empty()){
            vector<string> vec = q.front();
            q.pop();

            // Now, erase all words that have been
            // used in the previous levels to transform
            if (vec.size() > level){
                level++;
                for (auto it : usedOnLevel) st.erase(it);
            }

            string word = vec.back();

            // store the answers if the end word matches with targetWord.
            if (word == endWord){
                // the first sequence where we reached end
                if (ans.size() == 0) ans.push_back(vec);
                else if (ans[0].size() == vec.size()) ans.push_back(vec);
            }
            for (int i = 0; i < word.size(); i++){   
                char original = word[i];
                for (char c = 'a'; c <= 'z'; c++){
                    word[i] = c;
                    if (st.count(word) > 0){ 
                        vec.push_back(word);
                        q.push(vec);
                        // mark as visited on the level
                        usedOnLevel.push_back(word);
                        vec.pop_back();
                    }
                }
                word[i] = original;
            }
        }
        return ans;
    }




    // LC 1976 - Number of Ways to Arrive at Destination
    
    int MOD = 1e9 + 7;

    int countPaths(int n, vector<vector<int>>& roads) {
        // Adjacency list representation of the graphLC 1976 - Number of Ways to Arrive at Destination
        vector<vector<pair<int, int>>> graph(n);
        for (const auto& road : roads) {
            int u = road[0], v = road[1], time = road[2];
            graph[u].push_back({v, time});
            graph[v].push_back({u, time});
        }

        // Distances to each node, initialized to a large value
        vector<long long> dist(n, LLONG_MAX);
        // Ways to reach each node with the shortest path
        vector<int> ways(n, 0);
        
        // Min-heap for Dijkstra's algorithm
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
        dist[0] = 0;
        ways[0] = 1;
        pq.push({0, 0});  // (distance, node)

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();

            if (d > dist[u]) continue;

            for (const auto& [v, time] : graph[u]) {
                long long newDist = d + time;
                
                if (newDist < dist[v]) {
                    dist[v] = newDist;
                    ways[v] = ways[u];
                    pq.push({newDist, v});
                } else if (newDist == dist[v]) {
                    ways[v] = (ways[v] + ways[u]) % MOD;
                }
            }
        }

        return dist[n - 1] == LLONG_MAX ? -1 : ways[n - 1];
    }



    // Minimum Multiplications to reach End - https://www.geeksforgeeks.org/problems/minimum-multiplications-to-reach-end/1
    int minimumMultiplications(vector<int>& arr, int start, int end) {
        queue<pair<int,int>> q ;// number , level
        unordered_set<int> visited;
        q.push({start , 0});

        while(!q.empty()){
            auto p = q.front();
            q.pop();

            if(p.first == end ) return p.second;

            for(int i = 0 ; i<arr.size(); i++){
                int temp = (p.first*arr[i])%100000;
                if(visited.find(temp)!= visited.end()) continue;
                q.push({(p.first*arr[i])%100000,p.second+1});
                visited.insert(temp);
            }
        }
        return -1;
    }



    // bellman ford algo 
        vector<int> bellmanFord(int V, vector<vector<int>>& edges, int src) {
        // Code here
        vector<int> dist(V,1e8);
        dist[src] = 0;
        
        for(int i = 1e8 ; i < V; i++){
            for(auto e: edges){
                int u  = e[0];
                int v = e[1];
                int wt = e[2];
                if(dist[u]!=INT_MAX && dist[u]+wt<dist[v]){
                    dist[v] = dist[u]+wt;
                }
            }
        }
        
        bool negativeCycle = false;
        for(auto e: edges){
            int u  = e[0];
            int v = e[1];
            int wt = e[2];
            if(dist[u]!=INT_MAX && dist[u]+wt<dist[v]){
                // dist[v] = dist[u]+wt;
                negativeCycle= true;
            }
        }
        if(negativeCycle) return {-1};
        return dist;
    }

    


    // floyd warshall algo 
    void floydWarshall(vector<vector<int>> &dist) {
        // Code here
        int n = dist.size();
        
        for(int  i= 0 ; i < n ; i++){
            for(int j = 0 ; j < n ; j++){
                if(i==j)dist[i][j] = 0;
            }
        }
        
        for(int via = 0 ; via < n ; via++){
            for(int i = 0 ; i<n;i++){
                for(int j =0 ; j < n ; j++){
                    if(dist[i][via]!=1e8 && dist[via][j]!=1e8)
                        dist[i][j] = min(dist[i][j], dist[i][via]+dist[via][j]);
                }
            }
        }
        
    }