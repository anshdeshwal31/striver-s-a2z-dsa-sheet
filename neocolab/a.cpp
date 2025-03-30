#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin>>n;
    vector<vector<int>> dist(n,vector<int>(n,-1));
    for (int i = 0;i<n;i++){
        for(int j = 0 ;j<n;j++){
            cin>>dist[i][j];
        }
    }
    

    for(int k = 0; k<n;k++){
        for(int i = 0; i<n;i++){
            for(int j = 0; j<n;j++){
               dist[i][j]  = dist[i][j] || (dist[i][k] && dist[k][j]); 
            }
        }
    }


    for(int i = 0;i<n;i++){
        for(int j = 0;j<n;j++){
            cout<<dist[i][j]<<" ";
        }
        cout<<endl;
    }
    int u;
    int v;
    cin >> u;
    cin >> v;
    if(dist[u][v]) cout<<"Path Exists"<<endl;
    else cout<<"Path does not Exist"<<endl;

}


int main (){
    int V ;
    int E;
    cin >> V;
    cin >> E;
    int adj[V][V];
    for(int i = 0;i<E;i++){
        int u;
        int v;
        cin >> u;
        cin >> v;
        adj[u][v] = 1;
        adj[v][u] = 1;
    }

    queue<int> q;
    vector<int> visited(V,0);
    q.push(0);
    visited[0] = 1;
    
    for(int i = 0;i<V;i++){
        while(!q.empty()){
            int node = q.front();
            q.pop();
            cout<<node<<" ";
            for(int j = 0;j<V;j++){
                if(adj[node][j] == 1 && visited[j] == 0){
                    q.push(j);
                    visited[j] = 1;
                }
            }
        }
    }

}




const int MAX = 100;

void dfs(int adj[MAX][MAX],int source,int visited[MAX] , int V){
    visited[source] = 1;
    cout<<source<<" ";
    for(int j = 0 ; j<V; j++){
        if(adj[source][j] == 1 && visited[j] == 0){
            dfs(adj,j,visited,V);
        }
    }

}
int main (){
    int V ;
    int E;
    cin >> V;
    cin >> E;
    int adj[V][V];
    for(int i = 0;i<E;i++){
        int u;
        int v;
        cin >> u;
        cin >> v;
        adj[u][v] = 1;
        adj[v][u] = 1;
    }
    int visited[V];
    for(int i = 0;i<V;i++){
        visited[i] = 0;
    }
    int source;
    cin >> source;
    cout<<"DFS Traversal starting from vertex"<< source<<endl;
    for(int i = 0;i<V;i++){
        if(visited[i] == 0){
            dfs(adj,i,visited,V);
        }
    }
}


class Node{
    public:
    int data;
    Node* next;
    Node(int data){
        this->data = data;
        this->next =  NULL;
    }
};


Node *swapAdjacent(Node* head ){
    if(!head || !head->next) return head;

    swapAdjacent(head->next->next);
    Node* temp1 = head;
    Node* temp2 = head->next;
    temp1->next = temp2->next;
    temp2->next = temp1;
    head = temp2;
    return head;
}