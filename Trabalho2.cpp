#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <map>
#include <iterator>
#include <limits.h>



using namespace std;


class AdjMatrGraphW{
    private:
    int M;
    int** AdjMat;
    int min_degree;
    int max_degree = 0;
    vector<int> degrees;
    double sum = 0;
    string str;
    bool** visited;
    list<int> components;
    bool* visitedbfs;
    int* parent;
    int* level;

    public:
    int N;
        AdjMatrGraphW(string str){
            this->str = str;
            this->M = 0;
            string s = str.substr(2);
            //cout << s;
            vector<int> nums;

            stringstream stream(str);
            while(1) {
               int n;
               stream >> n;
                if(!stream)
                    break;
                nums.push_back(n);
            }

            //int len = nums.size();
            N = nums.at(0) + 1;
            AdjMat = new int*[N];
            for(int i = 0; i < N; i++){
                AdjMat[i] = new int[N];
                for(int j = 0; j < N; j++){
                    AdjMat[i][j] = 0;
                }
            }
            int len = 0;
            for (int element: nums){
                len++;
            }
            //cout << len;
            int x,y,z = 0;
            for(int i = 1; i < len; i = i + 3){
                x = nums[i];
                int k = i + 1;
                y = nums[k];
                z = nums[k+1];
                //cout << x << " and " << y << " and " << z << endl;
                AdjMat[x][y] = z;
                AdjMat[y][x] = z;
            }
            M = (len - 1)/2;


        }

        void printMat(){
            for (int i = 0; i < N; i++){
                //cout << i << " : ";
                for(int j = 0; j < N; j++){
                    cout << AdjMat[i][j] << " ";
                }
            cout << endl;
            }
        }

        void NumOfEdges(){
            cout << "M is " << M;
        }
};

class AdjListGraphW{
private:

    int min_degree;
    int max_degree = 0;
    vector<int> degrees;
    int M = 0;
    double sum = 0;
    string str;
    list<pair<int, int>> *L;
    bool* visited;
    int* parent;
    int* level;
    int* parentdfs;
    int* leveldfs;
    list<int> components;

public:
    int N;
    AdjListGraphW(string str){
        this->str = str;
        this->M = 0;
        vector<int> nums;
        
        stringstream stream(str);
        while(1) { // Pega os números entre os espaços
            int n;
            stream >> n;
            if(!stream)
                break;
            nums.push_back(n);
        }
        
        N = nums[0] + 1;
        //cout << N;
        L = new list<pair<int,int>>[N, N];
        int len = nums.size();
        int x,y,z = 0;
        for(int i = 1; i < len; i = i + 3){
            x = nums[i];
            int k = i + 1;
            y = nums[k];
            z = nums[k + 1];
            //cout << x << " and " << y << " and " << z << endl;
            L[x].push_back(make_pair(y,z));
            L[y].push_back(make_pair(x,z));
            
        }
        M = (len - 1)/2;
    }


    void printList(){
        int s, r;
        for(int i = 0; i < N+1; i++){
                cout << "N: " << i << " -> | ";
            for(auto vals = L[i].begin(); vals != L[i].end(); vals++){
                
                s = vals -> first;
                r = vals -> second;
                cout << s << " de peso: " << r << " | ";
            }

            cout << endl;
        }

    }

    void numOfEdges(){
        cout << "M is " << M << '\n';
    }

    double findMean(){
        return sum/N;
    }



    int findMedian(){
        std::sort(std::begin(degrees), std::end(degrees));
        if (N % 2 != 0){
            return degrees.at(N / 2);
        }
        else{
            return degrees.at((((N - 1) / 2) + degrees.at(N / 2)) / 2);
        }
    }

    int minDistance(int dist[], bool Set[]){
        
        int min = INT_MAX, min_index; // Initialize min value
    
        for (int v = 0; v < N; v++)
            if (Set[v] == false && dist[v] <= min)
                min = dist[v], min_index = v;
    
        return min_index;
    }


    void dijkstra(int src){

        int vertice, weight;
        int dist[N]; //Distância do vertice inicial até o vertice escolhido
    
        bool Set[N]; // True para vertices explorados
    
        for (int i = 0; i < N; i++){
            dist[i] = INT_MAX, Set[i] = false;
    
        }

        dist[src] = 0;
        for (int count = 0; count < N - 1; count++) {

            // Menor distancia entre os vertice ainda não explorados
            // u = src na primeira iteração


            int u = minDistance(dist, Set);
            
            Set[u] = true;

    
            for(auto vals = L[u].begin(); vals != L[u].end(); vals++){ // Percorre os vizinhos de u
                    
                
                    vertice = vals -> first;
                    weight = vals -> second;
                   
                    // Update dist[v] only if is not in sptSet, there is an edge from
                    // u to v, and total weight of path from src to  v through u is
                    // smaller than current value of dist[v]
                    if (!Set[vertice] && dist[u] != INT_MAX && dist[u] + weight < dist[vertice]){
                        dist[vertice] = dist[u] + weight;
                    }
                }

            
        }

        cout <<"Vertice \t Distância da Origem" << endl;
        for (int i = 0; i < N; i++)
        cout  << i << " \t\t"<<dist[i]<< endl;
    }

    void BFS(int value){
        int vertice;
        visited = new bool[N];
        parent = new int[N];
        level = new int[N];

        for( int i = 0; i < N; i++){
            visited[i] = 0;
            parent[i] = 0;
            level[i] = 0;
        }
        //Marca a raiz como marcado
        visited[value] = true;
        parent[value] = -1;
        level[value] = 0;
        //Cria a fila e coloca o valor na fila
        list<int> Q;
        list<int>::iterator i;
        Q.push_back(value);
        
        //Enquanto Q não estiver vazia
        while(!Q.empty()){
            //retira v de Q
            int v = Q.front();
            Q.pop_front();
            //para todo vizinho w de v:
            for(auto vals = L[v].begin(); vals!=L[v].end(); vals++){

                vertice = vals -> first;
                //Se não estiver nos visitados
                if(!visited[vertice]){
                    //Marca como visitado
                     visited[vertice] = true;
                     //Coloca no Q
                     Q.push_back(vertice);
                     parent[vertice] = v;
                     level[vertice] = level[v] + 1;
                }
            }
        }
        
        
        ofstream answer;
        answer.open("Resposta.txt");
        if (answer.is_open()){
            for(int i = 0; i < N; i++){
            answer << "number: " << i << " / level:" << level[i] << " / parent: " << parent[i] << endl;
            }
        }
            
        for(int i = 0; i < N; i++){
            cout << "number: " << i << " / level:" << level[i] << " / parent: " << parent[i] << endl;
        }
    }
    
};

int main(){

    string s = "11\n11 10 1\n3 4 2\n5 7 3\n10 2 4\n1 3 5\n1 11 6\n10 1 7";
    string a = "7\n1 2 1\n1 4 4\n1 5 2\n2 4 2\n5 4 2\n2 3 4\n5 6 3\n3 4 1\n4 6 2\n3 7 2\n6 7 3\n";
    
    int min = INT_MAX, min_index;
    cout << min_index << '\n';

    //AdjMatrGraphW g(s);
    AdjListGraphW f(a);
    //g.printMat();
    // f.printList();
    f.dijkstra(1);
    f.BFS(1);
    return 0;
}
