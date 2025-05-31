#include <bits/stdc++.h>
using namespace std;

// number of provinces
void dfs(vector<vector<int>> &isConnected, vector<bool> &visited, int i){
    visited[i] = true;
    for(auto x : isConnected[i]){
        if(!visited[x]){
            dfs(isConnected, visited, x);
        }
    }
}
int findCircleNum(vector<vector<int>>& isConnected) {
    vector<vector<int>> adjList(isConnected.size());
    for(int i = 0; i < isConnected.size(); i++){
        for(int j = 0; j < isConnected[0].size(); j++){
            if(isConnected[i][j] == 1){
                adjList[i].push_back(j);
            }
        }
    }
    vector<bool> visited(isConnected.size(), false);
    int count = 0;
    for(int i = 0; i < isConnected.size(); i++){
        if(!visited[i]){
            dfs(adjList, visited, i);
            count++;
        }
    }
    return count;
}


// flood fill

// method 1
void solve(vector<vector<int>> &image, int sr, int sc, int color, int newColor){
    vector<vector<int>> dir = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; // up, right, down, left
    image[sr][sc] = newColor;
    queue<pair<int, int>> q;
    q.push({sr, sc});
    while(!q.empty()){
        auto top = q.front();
        q.pop();
        int x = top.first;
        int y = top.second;
        for(auto d : dir){
            int nx = x + d[0];
            int ny = y + d[1];
            if(nx >= 0 && nx < image.size() && ny >= 0 && ny < image[0].size() && image[nx][ny] == color){
                image[nx][ny] = newColor;
                q.push({nx, ny});
            }
        }
    }
}
vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
    int oldColor = image[sr][sc]; // old color
    if(oldColor == color) return image;
    solve(image, sr, sc, oldColor, color);
    return image;
}

// method 2
void solve(vector<vector<int>> &image, int sr, int sc, int color, int newColor){
    vector<vector<int>> dir = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; // up, right, down, left
    image[sr][sc] = newColor;
    queue<pair<int, int>> q;
    q.push({sr, sc});

    while(!q.empty()){
        int size = q.size();
        for(int i = 0; i < size; i++){
            auto top = q.front();
            q.pop();
            int x = top.first;
            int y = top.second;
            for(auto d : dir){
                int nx = x + d[0];
                int ny = y + d[1];
                if(nx >= 0 && nx < image.size() && ny >= 0 && ny < image[0].size() && image[nx][ny] == color){
                    image[nx][ny] = newColor;
                    q.push({nx, ny});
                }
            }
        }
    }
}

vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
    int oldColor = image[sr][sc]; // old color
    if(oldColor == color) return image;
    solve(image, sr, sc, oldColor, color);
    return image;
}


// cycle detection in a undirected graph

// method 1- using bfs
bool solveBfs(vector<vector<int>> &adjList, vector<int> &visited, vector<int> &parent, int i){
    queue<int> q;
    q.push(i);
    visited[i] = 1;
    parent[i] = i;

    while(!q.empty()){
        int node = q.front();
        q.pop();
        for(auto x : adjList[node]){
            if(!visited[x]){
                visited[x] = 1;
                q.push(x);
                parent[x] = node;
            }
            else if(parent[node] != x){
                return true;
            }
        }
    }
    return false;
}
string cycleDetection(vector<vector<int> > &edges, int n, int m) {
    vector<vector<int>> adjList(n+1);
    for(auto edge : edges){
        adjList[edge[0]].push_back(edge[1]);
        adjList[edge[1]].push_back(edge[0]);
    }
    vector<int> visited(n+1, 0);
    vector<int> parent(n+1, -1);
    for(int i = 1; i <= n; i++){
        if(!visited[i]){
            if(solveBfs(adjList, visited, parent, i)){
                return "YES";
            }
        }
    }
    return "NO";
}

// method 2 - using dfs
bool solveDfs(vector<vector<int>> &adjList, vector<int> &visited, int i, int parent){
    visited[i] = 1;
    for(auto x : adjList[i]){
        if(!visited[x]){
            if(solveDfs(adjList, visited, x, i)){
                return true;
            }
        }
        else if(x != parent){
            return true;
        }
    }
    return false;
}

string cycleDetection(vector<vector<int> > &edges, int n, int m) {
    vector<vector<int>> adjList(n+1);
    for(auto edge : edges){
        adjList[edge[0]].push_back(edge[1]);
        adjList[edge[1]].push_back(edge[0]);
    }
    vector<int> visited(n+1, 0);
    vector<int> parent(n+1, -1);
    for(int i = 1; i <= n; i++){
        if(!visited[i]){
            if(solveDfs(adjList, visited,i, -1)){
                return "YES";
            }
        }
    }
    return "NO";
}



// int solve(int row , int col , vector<vector<int>> &mat){
//     if(row < 0 || row >= mat.size() || col < 0 || col >= mat[0].size() || mat[row][col] == 0){
//         return 0;
//     }
//     mat[row][col] = 0;
//     return 1 + solve(row+1, col, mat) + solve(row-1, col, mat) + solve(row, col+1, mat) + solve(row, col-1, mat);
// }










int solve(int row , int col , vector<vector<int>> &mat){
    // using bfs traversal
    vector<vector<int>> dir = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; // up, right, down, left
    vector<vector<int>> visited(mat.size(), vector<int>(mat[0].size(), 0));
    queue<pair<int, int>> q;
    q.push({row, col});

    while(!q.empty()){
        int size = q.size();

        for(int k = 0; k < size; k++){
            auto top = q.front();
            q.pop();
            int x = top.first;
            int y = top.second;
            for(auto d : dir){
                int newX = x + d[0];
                int newY = y + d[1];
                if(newX >= 0 && newX < mat.size() && newY >= 0 && newY < mat[0].size() && mat[newX][newY] == 0){
                    return k+1;
                }
                else if(newX >= 0 && newX < mat.size() && newY >= 0 && newY < mat[0].size()&& !visited[newX][newY]){
                    visited[newX][newY] = 1;
                    q.push({newX, newY});
                }
            }
        }
    }
    return -1;
}
vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
    int n = mat.size();
    int m = mat[0].size();
    vector<vector<int>> res(n, vector<int>(m, 0));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(mat[i][j] == 1){
                res[i][j] = solve(i, j, mat);
            }
        }
    }
    return res;
}

// surrounded regions

// method 1 - using bfs
void bfs(vector<vector<char>>& board, queue<pair<int,int>> &q, vector<vector<int>> &visited){
    vector<vector<int>> dir = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; // up, right, down, left

    while(!q.empty()){
        auto top = q.front();
        q.pop();
        int x = top.first;
        int y = top.second;
        for(auto d : dir){
            int nx = x + d[0];
            int ny = y + d[1];
            if(nx >= 0 && nx < board.size() && ny >= 0 && ny < board[0].size() && board[nx][ny] == 'O' && !visited[nx][ny]){
                visited[nx][ny] = 1;
                q.push({nx, ny});
            }
        }
    }

    for(int i = 0; i < board.size(); i++){
        for(int j = 0; j < board[0].size(); j++){
            if(board[i][j] == 'O' && !visited[i][j]){
                board[i][j] = 'X';
            }
        }
    }
}
void solve(vector<vector<char>>& board) {
    vector<vector<int>> visited(board.size(), vector<int>(board[0].size(), 0));
    queue<pair<int, int>> q;
    int n = board.size();
    int m = board[0].size();
    
    for(int i = 0; i < n; i++){
        if(board[i][0] == 'O'){
            q.push({i, 0});
            visited[i][0] = 1;
        }
        if(board[i][m-1] == 'O'){
            q.push({i, m-1});
            visited[i][m-1] = 1;
        }
    }
    for(int j = 0; j < m; j++){
        if(board[0][j] == 'O'){
            q.push({0, j});
            visited[0][j] = 1;
        }
        if(board[n-1][j] == 'O'){
            q.push({n-1, j});
            visited[n-1][j] = 1;
        }
    }
    
    bfs(board, q, visited);
}

// method 2 - using dfs
void dfs(vector<vector<char>>& board, int i, int j, vector<vector<int>> &visited ,vector<vector<int>> &dir){
    visited[i][j] = 1;
    for(auto d : dir){
        int nx = i + d[0];
        int ny = j + d[1];
        if(nx >= 0 && nx < board.size() && ny >= 0 && ny < board[0].size() && board[nx][ny] == 'O' && !visited[nx][ny]){
            dfs(board, nx, ny, visited, dir);
        }
    }
}
void solve(vector<vector<char>>& board) {
    vector<vector<int>> visited(board.size(), vector<int>(board[0].size(), 0));
    vector<vector<int>> dir = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; // up, right, down, left
    int n = board.size();
    int m = board[0].size();

    for(int i = 0; i < n; i++){
        if(board[i][0] == 'O'){
            dfs(board, i, 0, visited, dir);
        }
        if(board[i][m-1] == 'O'){
            dfs(board, i, m-1, visited, dir);
        }
    }
    for(int j = 0; j < m; j++){
        if(board[0][j] == 'O'){
            dfs(board, 0, j, visited, dir);
        }
        if(board[n-1][j] == 'O'){
            dfs(board, n-1, j, visited, dir);
        }
    }
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(board[i][j] == 'O' && !visited[i][j]){
                board[i][j] = 'X';
            }
        }
    }
}


// number of enclaves - using dfs
void dfs(vector<vector<int>> &grid, int i, int j, vector<vector<int>> &visited, vector<vector<int>> &dir){
    visited[i][j] = 1;

    for(auto d : dir){
        int nx = i + d[0];
        int ny = j + d[1];
        if(nx >= 0 && nx < grid.size() && ny >= 0 && ny < grid[0].size() && grid[nx][ny] == 1 && !visited[nx][ny]){
            dfs(grid, nx, ny, visited, dir);
        }
}

}
int numEnclaves(vector<vector<int>>& grid) {
    int rowLength = grid.size();
    int colLength = grid[0].size();

    vector<vector<int>> dir = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; // up, right, down, left
    vector<vector<int>> visited(rowLength, vector<int>(colLength, 0));

    for(int j = 0; j < colLength; j++){
        if(grid[0][j] == 1 && !visited[0][j]){
            dfs(grid, 0, j, visited, dir);
        }
        if(grid[rowLength-1][j] == 1 && !visited[rowLength-1][j]){
            dfs(grid, rowLength-1, j, visited, dir);
        }
    }

    for(int i = 0; i < rowLength; i++){
        if(grid[i][0] == 1 && !visited[i][0]){
            dfs(grid, i, 0, visited, dir);
        }
        if(grid[i][colLength-1] == 1 && !visited[i][colLength-1]){
            dfs(grid, i, colLength-1, visited, dir);
        }
    }

    int count = 0;
    for(int i = 0; i < rowLength; i++){
        for(int j = 0; j < colLength; j++){
            if(grid[i][j] == 1 && !visited[i][j]){
                count++;
            }
        }
    }
    return count;
}


// topological sort 

// method 1 - using dfs
void dfs(int node, vector<int> &visited, vector<int> adjList[],stack<int>& st){
    visited[node] = 1;
    for(auto x : adjList[node]){
        if(!visited[x]){
            dfs(x, visited, adjList, st);
        }
    }
    st.push(node);
}
vector<int> topoSort(int V, vector<int> adj[]){
    vector<int> visited(V, 0);
    stack<int> st;
    for(int i = 0; i < V; i++){
        if(!visited[i]){
            dfs(i, visited, adj, st);
        }
    }
    vector<int> res;
    while(!st.empty()){
        res.push_back(st.top());
        st.pop();
    }
    return res;
}


// method 2 - using bfs/ kahn's algorithm
vector<int> topoSort(int V, vector<int> adj[]){
    vector<int> indegree(V, 0);
    vector<int> ans;
    queue<int> q;

    for(int i = 0; i < V; i++){
        for(auto x : adj[i]){
            indegree[x]++;
        }
    }

    for(int i = 0; i < V; i++){
        if(indegree[i] == 0) q.push(i);
    }

    while(!q.empty()){
        int frontVal = q.front();
        q.pop();
        ans.push_back(frontVal);

        for(auto neigh: adj[frontVal]){
            indegree[neigh]--;
            if(indegree[neigh] == 0) q.push(neigh);
        }
    }

    return ans;
}


// cycle detection in directed graph 

// method 1 - using dfs

int dfs(vector<int> adj[], vector<int> &visited, vector<int> &dfsVisited, int node){
    visited[node] = 1;
    dfsVisited[node] = 1;
    for(auto neigb : adj[node]){
        if(!visited[neigb]){
            int check = dfs(adj, visited, dfsVisited, neigb);
            if(check) return 1;
        }
        else if(dfsVisited[neigb]){
            return 1;
        }
    }
    dfsVisited[node] = 0;
    return 0;
}

bool isCyclic(int V, vector<int> adj[]) {
    vector<int> visited(V, 0);
    vector<int> dfsVisited(V, 0);
    for(int i = 0; i < V; i++){
        if(!visited[i]){
            int check = dfs(adj, visited, dfsVisited, i);
            if(check) return true;
        }
    }
    return false;
}


// method 2 - using bfs/kahn's algorithm
bool isCyclic(int V, vector<int> adj[]) {
    vector<int> indegree(V, 0);
    queue<int> q;

    for(int i = 0; i < V; i++){
        for(auto x : adj[i]){
            indegree[x]++;
        }
    }

    for(int i = 0; i < V; i++){
        if(indegree[i] == 0) q.push(i);
    }

    int count = 0;
    while(!q.empty()){
        int frontVal = q.front();
        q.pop();
        count++;

        for(auto neigh: adj[frontVal]){
            indegree[neigh]--;
            if(indegree[neigh] == 0) q.push(neigh);
        }
    }

    if(count == V) return false;
    return true;
}



// course schedule 2
vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    vector<int> indegree(numCourses, 0);
    vector<vector<int>> adjList(numCourses);
    vector<int> ans;

    for(auto x : prerequisites){
        adjList[x[1]].push_back(x[0]);
        indegree[x[0]]++;
    }

    queue<int> q;

    for(int i = 0; i < numCourses; i++) if(indegree[i] == 0) q.push(i);

    while(!q.empty()){
        int frontVal = q.front();
        q.pop();
        ans.push_back(frontVal);
        for(auto neigh : adjList[frontVal]){
            indegree[neigh]--;
            if(indegree[neigh] == 0) q.push(neigh);
        }
    }

    return ans.size() == numCourses ? ans : {};
}



// shortest path in directed acyclic graph
void dfs(int node , vector<vector<pair<int , int>>>& adjList, vector<int>& visited, stack<int>& st){
    visited[node] = 1;
    for(auto neigh : adjList[node]){
        if(!visited[neigh.first]){
            dfs(neigh.first, adjList, visited, st);
        }
    }
    st.push(node);  
}

stack<int> topoStack(vector<vector<pair<int ,int>>> &adjList , stack<int>& topoSort){
    vector<int> visited(adjList.size(), 0);
    for(int i = 0; i < adjList.size(); i++){
        if(!visited[i]){
            dfs(i, adjList, visited, topoSort);
        }
    }
    return topoSort;
}

vector<int> solve(int n , vector<vector<pair<int , int>>>& adjList){
    stack<int> topoSort;
    topoSort = topoStack(adjList, topoSort);
    vector<int> dist(n, INT_MAX);
    dist[0] = 0;

    while(!topoSort.empty()){
        int top = topoSort.top();
        topoSort.pop();
        for(auto neigh : adjList[top]){
            if(dist[neigh.first] > dist[top] + neigh.second){
                dist[neigh.first] = dist[top] + neigh.second;
            }
        }
    }
    return dist;
    
}
vector<int> shortestPath(int N,int M, vector<vector<int>>& edges){
    vector<vector<pair<int,int>>> adjList(N);
    for(auto edge : edges){
        adjList[edge[0]].push_back({edge[1], edge[2]});
    }
    return solve(N, adjList);
}


// djikstra's algorithm
vector <int> dijkstra(int V, vector<vector<int>> adj[], int S){
    vector<int> dist(V, INT_MAX);
    pair<int, int> p = {0, S};
    set<pair<int, int>> s;
    s.insert(p);
    dist[S] = 0;
    while(!s.empty()){
        int currentNode = (*s.begin()).second;
        // int currentNode = s.begin()->second;
        s.erase(s.begin());
        for(auto neigb: adj[currentNode]){
            int neigbNode = neigb[0];
            int neigbWeight = neigb[1];

            if(dist[currentNode] + neigbWeight < dist[neigbNode]){
                int newDist = dist[currentNode] + neigbWeight;
                if(dist[neigbNode] != INT_MAX){
                    s.erase(s.find({dist[neigbNode], neigbNode}));
                }
                dist[neigbNode] = newDist;
                s.insert({newDist, neigbNode});
            }
        }
    }
    return dist;
}



// shortest path in  binary matrix
int solve(vector<vector<int>> & grid ){
    vector<vector<int>> dir = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}}; // down , right, up, left, down-right, up-right , down-left, up-left
    int level = 0;
    queue<pair<int, int>> q;
    q.push({0, 0});

    while(!q.empty()){
        int size = q.size();
        for(int i = 0; i < size; i++){
            auto top = q.front();
            q.pop();
            int x = top.first;
            int y = top.second;
            if(x == grid.size()-1 && y == grid[0].size()-1){
                level++;
                return level;
            }
            for(auto d : dir){
                int nx = x + d[0];
                int ny = y + d[1];
                if(nx >= 0 && nx < grid.size() && ny >= 0 && ny < grid[0].size() && grid[nx][ny] == 0){
                    grid[nx][ny] = 1;
                    q.push({nx, ny});
                }
            }
        }
        level++;
    }
    return -1;
}
int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
    if(grid[0][0] == 1) return -1;
    return solve(grid);
}






int minimumEffortPath(vector<vector<int>>& heights) {
    int rows = heights.size();
    int cols = heights[0].size();
    
    priority_queue<pair<int, pair<int, int>>,vector<pair<int, pair<int, int>>>,greater<pair<int, pair<int, int>>>> pq;
    
    vector<vector<int>> dist(rows, vector<int>(cols, INT_MAX));
    vector<pair<int, int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    
    // Start from (0,0) with effort 0
    dist[0][0] = 0;
    pq.push({0, {0, 0}});
    
    while(!pq.empty()) {
        int effort = pq.top().first;
        int x = pq.top().second.first;
        int y = pq.top().second.second;
        pq.pop();

        if(x == rows-1 && y == cols-1) return effort;
        if(effort > dist[x][y]) continue;
        
        for(auto& dir : dirs) {
            int newX = x + dir.first;
            int newY = y + dir.second;
            
            if(newX >= 0 && newX < rows && newY >= 0 && newY < cols) {
                int newEffort = max(effort,abs(heights[x][y] - heights[newX][newY]));
                
                if(newEffort < dist[newX][newY]) {
                    dist[newX][newY] = newEffort;
                    pq.push({newEffort, {newX, newY}});
                }
            }
        }
    }
    return 0;
}



int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
    // Step 1: Build the adjacency list for the graph
    unordered_map<int, vector<pair<int, int>>> graph;
    for (auto& flight : flights) {
        int from = flight[0], to = flight[1], price = flight[2];
        graph[from].push_back({to, price});
    }

    // Step 2: Initialize priority queue for BFS {cost, {current_city, stops}}
    priority_queue<pair<int, pair<int, int>>, 
                    vector<pair<int, pair<int, int>>>, 
                    greater<pair<int, pair<int, int>>>> pq;
    
    pq.push({0, {src, 0}});  // {cost, {city, stops}}
    
    // Step 3: Vector to track minimum cost with exact stops
    vector<int> minStops(n, INT_MAX);
    
    while (!pq.empty()) {
        auto [cost, node_info] = pq.top();
        int city = node_info.first, stops = node_info.second;
        pq.pop();
        
        // If reached destination within allowed stops, return cost
        if (city == dst) {
            return cost;
        }
        
        // If we used more stops than k, continue to next in queue
        if (stops > k) {
            continue;
        }
        
        // If we have more stops than the previously known minimum stops for this city, skip
        if (stops >= minStops[city]) {
            continue;
        }
        minStops[city] = stops;
        
        // Step 4: Process neighbors
        for (auto& [nextCity, price] : graph[city]) {
            int newCost = cost + price;
            pq.push({newCost, {nextCity, stops + 1}});
        }
    }

    return -1;
}


int minimumMultiplications(vector<int> &arr,int start, int end){
    // Create a queue for storing the numbers as a result of multiplication
    // of the numbers in the array and the start number.
    queue<pair<int, int>> q;
    q.push({start, 0});

    // Create a dist array to store the no. of multiplications to reach
    // a particular number from the start number.
    vector<int> dist(100000, 1e9);
    dist[start] = 0;
    int mod = 100000;

    // Multiply the start no. with each of numbers in the arr
    // until we get the end no.
    while (!q.empty()){
        int node = q.front().first;
        int steps = q.front().second;
        q.pop();

        for (auto it : arr){
            int num = (it * node) % mod;

            // If the no. of multiplications are less than before
            // in order to reach a number, we update the dist array.
            if (steps + 1 < dist[num])
            {
                dist[num] = steps + 1;

                // Whenever we reach the end number
                // return the calculated steps
                if (num == end)
                    return steps + 1;
                q.push({num, steps + 1});
            }
        }
    }
    return -1;
}



int minimumMultiplications(vector<int>& arr, int start, int end) {
    queue<int> q;
    q.push(start);
    int level = 0;

    while(!q.empty()){
        int size = q.size();
        for(int i = 0; i < size; i++){
            int top = q.front();
            q.pop();
            if(top == end) return level;
            for(auto x : arr){
                int num = (top * x) % 100000;
                q.push(num);
            }
        }
        level++;
    }
    return -1;
}       




// kruskal's algo - https://www.geeksforgeeks.org/problems/minimum-spanning-tree-kruskals-algorithm/1
int findParent(vector<int>& parent , int v){
    if(parent[v] == v) return v;
    return parent[v] = findParent(parent , parent[v]);
}
void unionSet(vector<int>&parent , vector<int>& rank ,int a , int b ){
    int parentA = findParent(parent , a); 
    int parentB = findParent(parent , b); 

    if(rank[parentA]>rank[parentB]) parent[parentB] = parentA;
    else if(rank[parentB] > rank[parentA]) parent[parentA] = parentB;
    else{
        parent[parentB] = parentA;
        rank[parentA]++;
    } 
}

bool compare(vector<int>& a, vector<int>& b){
    return a[2]<b[2];
}

int kruskalsMST(int V, vector<vector<int>> &edges) {
    vector<int> rank(V,0);
    vector<int> parent(V);
    for(int i = 0 ; i < V ; i++){
        parent[i] = i;
    }

    sort(edges.begin(), edges.end(), compare);

    int ans = 0;
    for(auto e:edges){
        int u = e[0];
        int v = e[1];
        int wt = e[2];
        int parentU = findParent(parent , u );
        int parentV = findParent(parent , v );
        if(parentU != parentV){
            unionSet(parent , rank , u , v);
            ans+=wt;
        }
    }
    return ans;
}


void dfs(vector<vector<int>> adjList , int node , int parent , int & backEdge, vector<int>& visited){
    visited[node] = 1;
    for(auto neigb:adjList[node]){
        if(!visited[neigb]){
            dfs(adjList,neigb , node , backEdge , visited);
        }
        else{
            if(neigb == parent)continue;
            else backEdge++;
        }
    }
}


int makeConnected(int n, vector<vector<int>>& connections) {
    vector<vector<int>> adjList(n);
    for(auto e: connections){
        int u = e[0];
        int v = e[1];
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }
    vector<int> visited(n,0);
    int connectedComponents = 0;
    int backEdge = 0;
    for(int i = 0 ; i<n ; i++){
        if(!visited[i]){
            dfs(adjList , i , i , backEdge , visited);
            connectedComponents++;
        }
    }

    if(connectedComponents>backEdge) return -1;
    else return connectedComponents;
}



// LC - 1319. Number of Operations to Make Network Connected
void dfs(vector<vector<int>>& adjList, int node, vector<int>& visited) {
    visited[node] = 1;
    for (auto neigh : adjList[node]) {
        if (!visited[neigh])
            dfs(adjList, neigh, visited);
    }
}

int makeConnected(int n, vector<vector<int>>& connections) {
    if (connections.size() < n - 1) return -1;  // Not enough cables

    vector<vector<int>> adjList(n);
    for (auto& e : connections) {
        adjList[e[0]].push_back(e[1]);
        adjList[e[1]].push_back(e[0]);
    }

    vector<int> visited(n, 0);
    int connectedComponents = 0;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(adjList, i, visited);
            connectedComponents++;
        }
    }

    return connectedComponents - 1;
}



// LC 721 - Accounts merge
class DisjointSet {
    vector<int> rank, parent, size;
    public:
    DisjointSet(int n) {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        size.resize(n + 1);
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    int findUPar(int node) {
        if (node == parent[node])
            return node;
        return parent[node] = findUPar(parent[node]);
    }

    void unionByRank(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (rank[ulp_u] < rank[ulp_v]) {
            parent[ulp_u] = ulp_v;
        }
        else if (rank[ulp_v] < rank[ulp_u]) {
            parent[ulp_v] = ulp_u;
        }
        else {
            parent[ulp_v] = ulp_u;
            rank[ulp_u]++;
        }
    }

    void unionBySize(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (size[ulp_u] < size[ulp_v]) {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        }
        else {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }
};



class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>> &details) {
        int n = details.size();
        DisjointSet ds(n);
        sort(details.begin(), details.end());
        unordered_map<string, int> mapMailNode;
        for (int i = 0; i < n; i++) {
            for (int j = 1; j < details[i].size(); j++) {
                string mail = details[i][j];
                if (mapMailNode.find(mail) == mapMailNode.end()) {
                    mapMailNode[mail] = i;
                }
                else {
                    ds.unionBySize(i, mapMailNode[mail]);
                }
            }
        }

        vector<string> mergedMail[n];
        for (auto it : mapMailNode) {
            string mail = it.first;
            int node = ds.findUPar(it.second);
            mergedMail[node].push_back(mail);
        }

        vector<vector<string>> ans;

        for (int i = 0; i < n; i++) {
            if (mergedMail[i].size() == 0) continue;
            sort(mergedMail[i].begin(), mergedMail[i].end());
            vector<string> temp;
            temp.push_back(details[i][0]);
            for (auto it : mergedMail[i]) {
                temp.push_back(it);
            }
            ans.push_back(temp);
        }
        sort(ans.begin(), ans.end());
        return ans;
    }
};



// Number Of Islands(Number of islands 2 on leetcode) - https://www.geeksforgeeks.org/problems/number-of-islands/1

class Solution {
public:
    vector<int> numOfIslands(int n, int m, vector<vector<int>> &operators) {
        vector<vector<int>> grid(n, vector<int>(m, 0));
        vector<int> parent(n * m, -1);
        vector<int> rank(n * m, 0);
        vector<int> res;
        int islands = 0;

        function<int(int)> find = [&](int x) {
            if (parent[x] != x)
                parent[x] = find(parent[x]);
            return parent[x];
        };

        // directions: right, down, left, up
        vector<pair<int, int>> dirs;
        dirs.push_back(make_pair(0, 1));
        dirs.push_back(make_pair(1, 0));
        dirs.push_back(make_pair(0, -1));
        dirs.push_back(make_pair(-1, 0));

        for (int i = 0; i < operators.size(); ++i) {
            int x = operators[i][0];
            int y = operators[i][1];
            int node = x * m + y;

            if (grid[x][y] == 1) {
                res.push_back(islands);
                continue;
            }

            grid[x][y] = 1;
            parent[node] = node;
            islands++;

            for (int d = 0; d < 4; ++d) {
                int nx = x + dirs[d].first;
                int ny = y + dirs[d].second;

                if (nx >= 0 && ny >= 0 && nx < n && ny < m && grid[nx][ny] == 1) {
                    int neighbor = nx * m + ny;
                    int parentNode = find(node);
                    int parentNeighbor = find(neighbor);

                    if (parentNode != parentNeighbor) {
                        // union by rank
                        if (rank[parentNode] > rank[parentNeighbor]) {
                            parent[parentNeighbor] = parentNode;
                        } else if (rank[parentNeighbor] > rank[parentNode]) {
                            parent[parentNode] = parentNeighbor;
                        } else {
                            parent[parentNeighbor] = parentNode;
                            rank[parentNode]++;
                        }
                        islands--; // merged two islands into one
                    }
                }
            }

            res.push_back(islands);
        }

        return res;
    }
};




// LC 827 - Making a large island
class disjointSet{
    public:

    vector<int>size;
    vector<int>rank;
    vector<int>parent;

    disjointSet(int n ){
        size.resize(n,1);
        rank.resize(n,0);
        parent.resize(n);

        for(int i = 0; i <n;i++)parent[i]=i;
    }

    int findParent(int c){
        if(c == parent[c]) return c;

        return parent[c] = findParent(parent[c]);
    }

    void unionByRank(int a , int b){
        int parentA = findParent(a);
        int parentB = findParent(b);

        if(parentA== parentB)return;

        if(rank[parentA]>rank[parentB]){
            parent[parentB] = parentA;
        }
        else if(rank[parentB]>rank[parentA]){
            parent[parentA] = parentB;
        }
        else{
            parent[parentB] = parentA;
            rank[parentA]++;
        }
    }

    void unionBySize(int a , int b){
        int parentA = findParent(a);
        int parentB  = findParent(b);

        if(parentA== parentB)return;

        if(size[parentA] >size[parentB]){
            parent[parentB] = parentA;
            size[parentA] += size[parentB];
        }
        else{
            parent[parentA] = parentB;
            size[parentB]+=size[parentA];
        }
    }

};

class Solution {
public:
int largestIsland(vector<vector<int>>& grid) {
    int rowSize = grid.size();
    int colSize = grid[0].size();

    disjointSet ds(rowSize*colSize);
    vector<pair<int , int>> dir = {{0,-1},{1,0},{0,1},{-1,0}};  // left , down , right , up
    set<int> s;
    int maxArea= 0;

    for(int i = 0; i < rowSize; i++) {
        for(int j = 0; j < colSize; j++) {
            if(grid[i][j] == 1) {
                for(auto d : dir) {
                    int ny = i + d.first;
                    int nx = j + d.second;
                    if(ny >= 0 && ny < rowSize && nx >= 0 && nx < colSize && grid[ny][nx] == 1) { // bounds + 1 check
                        int node1 = i * colSize + j;
                        int node2 = ny * colSize + nx;
                        ds.unionBySize(node1, node2);
                    }
                }
            }
        }
    }

    bool hasZero = false;

    for(int i = 0 ; i < rowSize; i++){
        for(int j = 0 ; j < colSize; j++){
            if(grid[i][j]==0){
                int tempArea = 1;
                int node = i*colSize+j;

                for(auto d: dir){
                    int ny = i+d.first;
                    int nx = j+d.second;

                    if(ny >= 0 && ny < rowSize && nx >= 0 && nx < colSize && grid[ny][nx] == 1){
                        int neighbour = ny*colSize+nx;
                        int par = ds.findParent(neighbour);
                        if(s.find(par) == s.end()){
                            tempArea += ds.size[par];
                            s.insert(par);
                        }
                    }
                }
                s.clear();
                maxArea = max(maxArea,tempArea);
            }
        }
    }

    if(!hasZero){
        for(int i = 0; i < rowSize * colSize; i++){
            if(ds.findParent(i) == i)
                maxArea = max(maxArea, ds.size[i]);
        }
    }

    return maxArea;
}
};



// LC 1192 - critical connections in a network/tarjan's algo to find bridges in a graph
void dfs(int node , vector<int>&dist , vector<int>& low , vector<int>& visited , vector<vector<int>>& adjList , vector<vector<int>>& result,int& parent ,int& timer){

    visited[node] = 1;
    dist[node] = low[node] = timer++;
    
    for(auto neigb:adjList[node]){
        if(neigb == parent)continue;

        if(!visited[neigb]){
            dfs(neigb,dist ,low ,visited,adjList,result,node ,timer);
            low[node] = min(low[node],low[neigb]);
            
            if(low[neigb]>dist[node]){
                result.push_back({node,neigb});
            }
        }
        // back edge
        else{
            low[node] = min(low[node],dist[neigb]);
        }
    }
}

vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
    vector<int>dist(n,-1);
    vector<int>low(n,-1);
    vector<int>visited(n,0);
    vector<vector<int>> result;
    vector<vector<int>> adjList(n);


    for(int i = 0 ; i<connections.size() ; i++){
        int u = connections[i][0];
        int v = connections[i][1];
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    int parent = -1;
    int timer = 0;

    for(int i = 0 ;  i < adjList.size(); i ++){
        if(!visited[i]){
            dfs(i,dist,low ,visited,adjList,result , parent , timer);
        }
    }
    return result;
}