/*
https://dilipkumar.medium.com/sweep-line-algorithm-e1db4796d638

Offline query to get the sum of top k for a given interval y

Here we have given [left, right, x] as [[1,9,1],[3,10,3],[5,7,2],[11,19,5],[13,15,6]] 
and the list of intervals to perform queries as [[2,2],[4,2],[6,2],[14,2]] 
where each query is represented as [y,k]. We need to find the top k sum for a given interval y . 
Answer should be [1, 4, 5,11]

*/

#include<bits/stdc++.h>
using namespace std;

struct Event{
    int time, value, type; // 0: add, 1: query  2: remove
};

void sumTopK(vector<tuple<int,int,int>> intervals, vector<vector<int>> queries){
    vector<Event> events;
    for(auto [l, r, x]: intervals){
        events.push_back({l, x, 0});
        events.push_back({r+1, x, 2});
    }
    for(auto q: queries){
        events.push_back({q[0], q[1], 1});
    }

    sort(events.begin(), events.end(), [&](Event a, Event b){
        if(a.time!=b.time) return a.time<b.time;
        return a.type < b.type;
    });

    vector<int> ans;
    multiset<int> activePoints; 

    for(auto [time, value, type]: events){
        if(type==0) activePoints.insert(value);
        else if(type==2) activePoints.erase(activePoints.find(value));
        else {
            int S = 0, K = value;
            for(auto it=activePoints.rbegin(); it!=activePoints.rend() && K>0; it++,K--) S+=*it;
            ans.push_back(S);
        }
    }

    for(int x: ans) cout<<x<<" ";
    cout<<endl;
}
int main(){
    vector<tuple<int, int, int>> intervals = {{1, 9, 1}, {3, 10, 3}, {5, 7, 2}, {11, 19, 5}, {13, 15, 6}};
    vector<vector<int>> queries = {{2, 2}, {4, 2}, {6, 2}, {14, 2}};
    
    sumTopK(intervals, queries); // 1, 4, 5, 11
    return 0;
}


/*
- first convert the offline problem to online by generating list of actions we need to perform.
- multiset because its insert and delete is o(logn).
- sorting order is important here as here [l,r] we need to include both hence r+1, and we can remove after querying.
if it was [l,r) we should consider removing first then adding and querying will be given same priority 
*/