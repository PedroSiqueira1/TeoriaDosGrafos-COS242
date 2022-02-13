#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <map>
#include <iterator>



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
        string s = str.substr(2);
        //cout << s;
        vector<int> nums;
        
        stringstream stream(str);
        while(1) {
            int n;
            stream >> n;
            if(!stream)
                break;
            //Num.push_back(n);
            nums.push_back(n);
        }
        this-> str = str;
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
};

int main(){

    string s = "11\n11 10 1\n3 4 2\n 5 7 3\n10 2 4\n1 3 5\n1 11 6\n10 1 7";

    AdjMatrGraphW g(s);
    AdjListGraphW f(s);
    g.printMat();
    f.printList();
    return 0;
}
