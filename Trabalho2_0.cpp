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


int nthOccurrence(string& str, string findMe, int nth){
        
        size_t  pos = 0;
        int     cnt = 0;

        while( cnt != nth )
        {
            pos+=1;
            pos = str.find(findMe, pos);
            if ( pos == string::npos )
                return -1;
            cnt++;
        }
        return pos;
}

 //Pega os números entre "\n" para verificar se o grafo tem peso ou não, se possuir 3 números entre os "\n" ele tem peso.
bool is_weighted_graph(string str){
    string sub = str.substr(nthOccurrence(str, "\n", 1) + 1 ,nthOccurrence(str, "\n", 2) - 2  );

    vector<float> numbers;
    stringstream stream(sub);
    while(1) { // Pega os números entre os espaços
        float n;
        stream >> n;
        if(!stream)
            break;
        numbers.push_back(n);
    }

    if (numbers.size() == 3){
        return true;
    }
    else{
        return false;
    }
};

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
    bool weighted_graph;
    bool isThereNeg;
    bool isNegCycle;
    bool isDir;
    int min_degree;
    int max_degree = 0;
    vector<int> degrees;
    vector <float> edges;
    int M = 0;
    double sum = 0;
    string str;
    list<pair<int, float>> *L;
    list<int> *L_no_weight;
    bool* visited;
    int* parent;
    int* parentMST;
    int* level;
    float* dist;
    list<int> components;

public:
    int N;
    void addEdge(vector <pair<int, float> > adj[], int u, int v, float wt){
        adj[u].push_back(make_pair(v, wt));
        adj[v].push_back(make_pair(u, wt));
    }

    AdjListGraphW(string str, bool isDir = false){

        weighted_graph = is_weighted_graph(str); 
        this->str = str;
        this->M = 0;
        this-> isThereNeg = false;
        this-> isDir = isDir;
        vector<float> nums;
        
        stringstream stream(str);
        while(1) { // Pega os números entre os espaços
            float n;
            stream >> n;
            if(!stream)
                break;
            nums.push_back(n);
        }
        
        if (weighted_graph == true) {
            N = nums[0] + 1;
        
            L = new list<pair<int,float>>[N, N];
            int len = nums.size();
            int x,y;
            float z = 0;
            for(int i = 1; i < len; i = i + 3){
                x = nums[i];
                int k = i + 1;
                y = nums[k];
                z = nums[k + 1];
                
                if (z<0){
                    isThereNeg = true;
                }
                
                if(isDir){
                    L[x].push_back(make_pair(y,z));
                }
                else{
                    L[x].push_back(make_pair(y,z));
                    L[y].push_back(make_pair(x,z));
                }
            }
            M = (len - 1)/3;
            this -> edges;         
            for(int i = 1; i < len; i++){
                edges.push_back(nums[i]);
            }

        }

        if (weighted_graph == false) {

            N = nums[0] + 1;
            L_no_weight = new list<int>[N];
            int len = nums.size();
            int x,y = 0;
            for(int i = 1; i < len; i = i + 2){
                x = nums[i];
                int k = i + 1;
                y = nums[k];
                L_no_weight[x].push_back(y);
                L_no_weight[y].push_back(x);
            }
            M = (len - 1)/2;
        }

        
        
    }

    

    void printList(){


        if (weighted_graph == true){

        
            int s;
            float r;
            for(int i = 1; i < N; i++){
                    cout << "N: " << i << " -> | ";
                for(auto vals = L[i].begin(); vals != L[i].end(); vals++){
                    
                    s = vals -> first;
                    r = vals -> second;
                    cout << s << " de peso: " << r << " | ";
                }

                cout << endl;
            }
        }

        if (weighted_graph == false) {

            for(int i = 0; i < N; i++){
                    cout << "N: " << i << " -> | ";
                for(int x:L_no_weight[i]){
                    cout << x <<" | ";
                }
                
                cout << endl;
            }
        }
        

    }


    int minDistance(float dist[], bool Set[]){
        
        float min = INT_MAX, min_index; // Initialize min value
    
        for (int v = 0; v < N; v++)
            if (Set[v] == false && dist[v] <= min)
                min = dist[v], min_index = v;
    
        return min_index;
    }


    void dijkstra(int src){

        int vertice;
        float weight;
        dist = new float[N]; //Distância do vertice inicial até o vertice escolhido
       // float dist[N]; 
    
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
                   
                    
                    if (!Set[vertice] && dist[u] != INT_MAX && dist[u] + weight < dist[vertice]){
                        dist[vertice] = dist[u] + weight;
                    }
            }

            
        }
    }
    
    void bellman(int src){
        if(isDir){
            float dist[N]; //Distância do vertice inicial até o vertice escolhido
        
            for (int i = 0; i < N; i++){
                dist[i] = INT_MAX;
        
            }
    
            dist[src] = 0;
            for (int count = 0; count <= N - 1; count++) {
                for (int i = 0; i < edges.size(); i = i + 3){
                        
                        int u = edges[i];
                        int vertice = edges[i + 1];
                        float weight = edges[i + 2];
                       
                        if (dist[u] != INT_MAX && dist[u] + weight < dist[vertice]){
                            dist[vertice] = dist[u] + weight;
                        }
                }
    
            }
            
            if(isThereNeg = true){
                for (int i = 0; i < edges.size(); i = i + 3){
                            
                        int u = edges[i];
                        int vertice = edges[i + 1];
                        float weight = edges[i + 2];
                       
                        if (dist[u] != INT_MAX && dist[u] + weight < dist[vertice]){
                            cout << "Tem ciclo negativo!" << endl;
                            isNegCycle = true;
                        }
                }
            }
            if(isNegCycle = false){
                cout <<"Vertice \t Distância da Origem" << endl;
                for (int i = 0; i < N; i++){
                    cout  << i << " \t\t"<<dist[i]<< endl;
                }
            }
        }
        else{
            cout << "Não é um grafo direcionado!" << endl;
        }
    }


    void BFS(int value){
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
            for(i = L_no_weight[v].begin(); i!=L_no_weight[v].end(); i++){
                int w = *i;
                //Se não estiver nos visitados
                if(!visited[w]){
                    //Marca como visitado
                     visited[w] = true;
                     //Coloca no Q
                     Q.push_back(w);
                     parent[w] = v;
                     level[w] = level[v] + 1;
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
            


    }

    int minKey(float key[], bool checked[]){
        int min = INT_MAX, min_index;
    
        for (int v = 0; v < N; v++)
            if (checked[v] == false && key[v] < min)
                min = key[v], min_index = v;
    
        return min_index;
    }


    void primMST(int num){

        int vertice;
        float weight;
        float total_weight = 0.0;

        parentMST = new int[N];
        float custoMST[N];
        bool mstSet[N];
    
      
        for (int i = 0; i < N; i++){
            custoMST[i] = INT_MAX, mstSet[i] = false;
        }    

        custoMST[num] = 0;
        parentMST[num] = -1; // Primeiro nó é a raiz

        for (int count = 0; count < N - 1; count++){
            
            int u = minKey(custoMST, mstSet);
      
            mstSet[u] = true;


            for(auto vals = L[u].begin(); vals != L[u].end(); vals++){ // Percorre os vizinhos de u
                    
                
                vertice = vals -> first;
                weight = vals -> second;
                
            
                if (mstSet[vertice] == false && weight < custoMST[vertice]){
                    parentMST[vertice] = u, custoMST[vertice] = weight;
                }
            }
        }
    
        
        
        ofstream answer;
        answer.open("MST.txt");
        if (answer.is_open()){

            answer<<"Edge \tWeight\n";

            for (int i = 1; i < N; i++){

                for(auto vals = L[i].begin(); vals != L[i].end(); vals++){ // Percorre os vizinhos de u
                        
                    
                    vertice = vals -> first;
                    weight = vals -> second;


                    if(vertice == parentMST[i]){
                        
                        total_weight += weight;
                        answer<<parentMST[i]<<" - "<<i<<" \t"<< weight <<" \n";
                    }
                    
                }
            }
        answer << "Peso total = " << total_weight << endl;
        }
        
    }


    void distance_to_all(int num){

        if(weighted_graph == false){
            BFS(num);
            for(int i = 0; i < N; i++){
                cout << "number: " << i << " / level:" << level[i] << " / parent: " << parent[i] << endl;
            }
        }

        if(weighted_graph == true){
            dijkstra(num);
            cout <<"Vertice \t Distância da Origem" << endl;
            for (int i = 0; i < N; i++){
                cout  << i << " \t\t"<<dist[i]<< endl;
            }
        }

    }

    void distance_from_to(int num1, int num2){
        if(weighted_graph == false){
            int x;
            BFS(num1);
            cout <<"Distância de " << num1 << " até " << num2 << " é: " << level[num2] <<endl;

            x = num2;
            cout << x;
            while (parent[x] != -1){
                cout<< "--"<< parent[x];
                x = parent[x];
            }
        }

        if(weighted_graph == true){
            int x;
            dijkstra(num1);
            cout <<"Distância de " << num1 << " até " << num2 << " é: " << dist[num2] <<endl;

            primMST(num1);
            x = num2;
            cout<<x;
            while (parentMST[x] != -1){
                cout<< "--"<< parentMST[x];
                x = parentMST[x];
            }
            
        }

    }
};


int main(){

    string s = "11\n11 10 1\n3 4 2\n5 7 3\n10 2 4\n1 3 5\n1 11 6\n10 1 7";
    string b = "7\n1 2\n1 4\n1 5\n2 4\n5 4\n2 3\n5 6\n3 4\n4 6\n3 7\n6 7";
    string a = "7\n1 2 1.1\n1 4 4.1\n1 5 2.1\n2 4 2.1\n5 4 2.1\n2 3 4.1\n5 6 3.1\n3 4 1.1\n4 6 2.1\n3 7 2.1\n6 7 3.1";
    string k ="4\n0 1 1\n1 2 -1\n2 3 -1\n3 0 1";




    //AdjMatrGraphW g(s);
    AdjListGraphW f(a);
    

   
    f.printList();
    f.bellman(0);
    //f.primMST(1);
    //f.dijkstra(1);
    //f.distance_to_all(1);
    //f.distance_from_to(1,7);
    return 0;
}
