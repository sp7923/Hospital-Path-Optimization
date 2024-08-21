#include<bits/stdc++.h>
using namespace std;

class Cities{
    public:
        int no_of_cities;
        vector<pair<double,double>> coordinates;
        vector<int> weights;
        vector<vector<int>> distanceMatrix;
        int depot;
        multimap<double,int> angle;
        int maxcapacity;


    void setCoordinates(){
        coordinates = {{0,0},{-2,4},{4,4},{-4,3},{-3,3},{1,2},{3,2},{-1,1},{2,1},{1,-1},{4,-1},{-3,-2}};
    }
    
    void setWeight(){
        weights = {0, 270, 351, 283, 314, 412, 356, 259,315, 178, 292, 311};
    }

    void setDistanceMatrix(){
        distanceMatrix = {
            {0, 11, 17, 14, 9, 20, 26, 18, 13, 4, 4, 12},      
            {11, 0, 24, 30, 19, 50, 7, 35, 29, 14, 18, 29},
            {17, 24, 0, 9, 27, 5, 27, 11, 46, 24, 40, 12},
            {14, 30, 9, 0, 11, 25, 17, 50, 14, 19, 12, 51},
            {9, 19, 27, 11, 0, 53, 26, 38, 13, 7, 11, 40},
            {20, 50, 5, 25, 53, 0, 22, 30, 19, 24, 58, 7},
            {26, 7, 27, 17, 26, 22, 0, 53, 19, 46, 35, 10},
            {18, 35, 11, 50, 38, 30, 53, 0, 34, 38, 23, 46},
            {13, 29, 46, 14, 13, 19, 19, 34, 0, 27, 38, 8},
            {4, 14, 24, 19, 7, 24, 46, 38, 27, 0, 34, 33},
            {4, 18, 40, 12, 11, 58, 35, 23, 38, 34, 0, 27},
            {12, 29, 12, 51, 40, 7, 10, 46, 8, 33, 27, 0},
        }; 
    }

    void setAngle(){
        double pi = 2 * asin(1.0);

        for(int i=1;i<coordinates.size();i++){
            if(coordinates[i].first>=0 && coordinates[i].second>=0){
                double slope = coordinates[i].second/coordinates[i].first;
                double degree = atan(slope)*180/pi;
                angle.insert({degree,i});
            }
            else if(coordinates[i].first>=0 && coordinates[i].second<=0){
                double slope = coordinates[i].second/coordinates[i].first;
                double degree = atan(slope)*180/pi+360;
                angle.insert({degree,i});
            }
            else if(coordinates[i].first<=0 && coordinates[i].second<=0){
                double slope = coordinates[i].second/coordinates[i].first;
                double degree = atan(slope)*180/pi+180;
                angle.insert({degree,i});
            }
            else {
                double slope = coordinates[i].second/coordinates[i].first;
                double degree = atan(slope)*180/pi+180;
                angle.insert({degree,i});
            }
            
        }
    }

    int get_total_weight(){
        int sum =0;
        for(int i:weights) sum+=i;
        return sum;
    }

    void setMaxCapacity(){
        
    }
    int getMaxcapacity(){
        return 80;
    }

    vector<set<int>> makeGroups(){
        vector<set<int>> groups;
        int total_weight = get_total_weight();
        maxcapacity = 1400;
        int waste = 0;
        set<int> group;
        for(auto i:angle){
            if(waste+weights[i.second]<=maxcapacity){
                group.insert(i.second);
                waste+=weights[i.second];
            }
            else{
                groups.push_back(group);
                waste=weights[i.second];
                group.clear();
                group.insert(i.second);
            }
        }
        groups.push_back(group);
        group.clear();
        return groups;
    }
};

class PathOptimizer{
    public :
        Cities cities;
};

const int INF = INT_MAX;
int dumpyard=0;

void printPath(int source, int mask, int n, vector<vector<int>>& distances, vector<vector<int>>& dp, vector<vector<int>>& parent,map<int,string>& ref) {
    if (mask == (1 << n) - 1) {
        return;
    }

    int bestNext = -1;
    int bestDist = INF;
    
    for (int next = 0; next < n; ++next) {
        if (mask & (1 << next)) continue; // Already visited node
        int newMask = mask | (1 << next);
        int candidate = distances[source][next] + dp[next][newMask];
        if (candidate < bestDist) {
            bestDist = candidate;
            bestNext = next;
        }
    }
    
    cout << " -> " <<ref[bestNext];
    printPath(bestNext, mask | (1 << bestNext), n, distances, dp, parent,ref);
}

int tsp(int source, int mask, int n, vector<vector<int>>& distances, vector<vector<int>>& dp, vector<vector<int>>& parent) {
    if (mask == (1 << n) - 1) {
        return distances[source][dumpyard]; // Return to the source node
    }

    if (dp[source][mask] != -1) {
        return dp[source][mask];
    }

    int ans = INF;
    int bestNext = -1;

    for (int next = 0; next < n; ++next) {
        if (mask & (1 << next)) continue; // Already visited node
        int newMask = mask | (1 << next);
        int candidate = distances[source][next] + tsp(next, newMask, n, distances, dp, parent);
        if (candidate < ans) {
            ans = candidate;
            bestNext = next;
        }
    }

    parent[source][mask] = bestNext;
    return dp[source][mask] = ans;
}

map<int,string> numberToCity;

int main(){

    Cities city;
    city.setCoordinates();
    city.setDistanceMatrix();
    city.setWeight();
    city.setAngle();
    
    numberToCity[1] = "Thousand Lights";
    numberToCity[2] = "Anna Nagar West Extension";
    numberToCity[3] = "Ambattur";
    numberToCity[4] = "Ambattur Industrial Estate";
    numberToCity[5] = "Koyambedu";
    numberToCity[6] = "Chromepet";
    numberToCity[7] = "Tambaram";
    numberToCity[8] = "Karapakkam";
    numberToCity[9] = "Perungudi";
    numberToCity[10] = "Nandanam";
    numberToCity[11] = "Cenotaph Rd";
    vector<set<int>> groups = city.makeGroups();

    int i = 1;
    for (set<int> s:groups){

        cout<<"Group :"<<i++<<endl;

        for(auto a:s){
            cout<<numberToCity[a]<<"("<<city.weights[a]<<")"<<" ";
        }

        cout<<endl;
        vector<vector<int>> set_distance(s.size()+1, vector<int>(s.size()+1));
        int m=0,l=0;
        map<int,string> ref;
        int cnt = 0;
        for(int i:s){
            ref[++cnt] = numberToCity[i];
        }

        for(int i:s){
            for (int j:s){
                set_distance[m][l] = city.distanceMatrix[i][j];
                l++;
            }
            m++;
            l=0;
        }
        for (int i:s){
            set_distance[m][l] =  city.distanceMatrix[dumpyard][i];
            l++;
        }
        m = 0;
        for (int i:s){
            set_distance[m][l] =  city.distanceMatrix[i][dumpyard];
            m++;
        }

        int  n = s.size()+1;
        vector<vector<int>> dp(n, vector<int>(1 << n, -1));
        vector<vector<int>> parent(n, vector<int>(1 << n, -1));

        int shortestPath = tsp(dumpyard, 1, n, set_distance, dp,parent); // Start from node 0 and initialize the mask with the source node

        cout << "Shortest path length: " << shortestPath << endl;
        cout << "Path: Dumpyard";
        printPath(dumpyard, 1, n, set_distance, dp, parent,ref);

        cout<<endl<<endl;
    }

}