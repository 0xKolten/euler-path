#include <vector> 
class matrix {
    private: 
        int v; 
        int **adj; 
        int start_vert = 0; 
        bool* visited; 
        vector<int> path; 
    public: 
        matrix(int v) {
            this->v = v;
            visited = new bool[v];
            adj = new int* [v];
            for (int i = 0; i < v; i++) {
                adj[i] = new int [v]; 
                for (int j = 0; j < v; j++) {
                    adj[i][j] = 0; 
                }
            } 
        }

        int get_start() {
            return start_vert;  
        }

        // Adds edge to graph. 
        void add_edge(int v1, int v2) {
            adj[v1 - 1][v2 - 1] = 1;
            adj[v2 - 1][v1 - 1] = 1;
        }

        // Removes edge from graph. 
        void remove_edge(int v1, int v2) {
            adj[v1][v2] = -1;
            adj[v2][v1] = -1;
        }

        // Prints adjacency list of a given graph. 
        void print_adj() {
            int i, j = 0; 
            vector<int> vals; 
            while (i < v) { 
                for (j= 0; j < v; j++) {
                    if (adj[i][j] == 1) {
                       vals.push_back(j+1); 
                    }
                }
                cout << i+1 << "->"; 
                for (int k = 0; k < vals.size(); k++) {
                    cout << vals.at(k); 
                    if (k+1 < vals.size()) {
                        cout << "->"; 
                    }
                }
                cout << endl; 
                vals.clear(); 
                i++; 
            }
        }

        // Counts vertices adjacent to a given vertex. 
        int count_adj(int i) {
            int adj_count = 0; 
            for (int j = 0; j < v; j++) {
                if (adj[i][j] == 1)
                    adj_count++;
            }
            return adj_count; 
        }

        // Returns true if a graph can be drawn in one stroke. 
        bool one_stroke() {
            int i , j = 0;  
            int odd_v = 0; 
            int adj_count = 0; 
            while (i < v) {
                adj_count = count_adj(i); 
                if (adj_count % 2 > 0) {
                    odd_v++; 
                    start_vert = i; 
                }
                i++; 
                adj_count = 0; 
            }
            if (odd_v > 2) { 
                return false; 
            }
            else {
                return true; 
            }
        }

        int dfs(int x, int c) {
            visited[x] = true; 
            int i; 
            for(i = 0; i < v; i++) {
                if(adj[x][i] == 1 && !visited[i]) {
                    c++; 
                    dfs(i,c); 
                }
            }
            return c; 
        }

        bool next_edge(int i, int j) {
            int count = count_adj(i); 
            if (count == 1) {
                return true; 
            }

            memset(visited, false, v);
            int c = 0; 
            int count1 = dfs(i,c); 
            remove_edge(i,j);
            memset(visited, false, v);
            int c2 = 0; 
            int count2 = dfs(i, c2); 
            add_edge(i+1, j+1); 

            if(count1 > count2) {
                return false; 
            }
            else {
                return true; 
            }


        }

        void find_path(int i) { 
           for (int j = 0; j < v; j++) {
               if (adj[i][j] == 1 && next_edge(i,j)) {
                    remove_edge(i,j); 
                    path.push_back(j+1); 
                    find_path(j); 
               }
           }
        }
        

        void print_path() {
            cout << start_vert+1 << "->"; 
            for (int k = 0; k < path.size(); k++) {
                cout << path.at(k);
                if (k + 1 < path.size()) {
                    cout << "->";
                }
            }
            cout << endl; 
        }
}; 