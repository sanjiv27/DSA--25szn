/*
https://dilipkumar.medium.com/sweep-line-algorithm-e1db4796d638
Offline query to get the max score for a given interval y

Here we have given [left, right, x] as [[1,9,1],[3,10,3],[5,7,2],[11,19,5],[13,15,6]]
and the list of intervals to perform queries as [2,4,6,14] 
where each query is represented as [y]. 
We need to find the max score for a given interval y . Answer should be [1, 3, 3,6] .

*/


#include<bits/stdc++.h>
using namespace std;

struct Event{
    int time, value, type; // 0: add, 1: query  2: remove
};

void maxInQuery(vector<tuple<int,int,int>> intervals, vector<int> queries){
    vector<Event> events;
    for(auto [l, r, x]: intervals){
        events.push_back({l, x, 0});
        events.push_back({r+1, x, 2});
    }
    for(auto q: queries){
        events.push_back({q, -1, 1});
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
        else ans.push_back(*activePoints.rbegin());
    }

    for(int x: ans) cout<<x<<" ";
    cout<<endl;
}
int main(){
    vector<tuple<int, int, int>> intervals = {{1, 9, 1}, {3, 10, 3}, {5, 7, 2}, {11, 19, 5}, {13, 15, 6}};
    vector<int> queries = {2, 4, 6, 14};
    
    maxInQuery(intervals, queries); // 1, 3, 3, 6
    return 0;
}