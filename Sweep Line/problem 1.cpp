/*
https://dilipkumar.medium.com/sweep-line-algorithm-e1db4796d638

Total duration where number of people in the hall is greater than k

For given [arrival, departure] time for a person in a hall, 
we need to find out the total duration when more than k people were in the hall.

*/

#include<bits/stdc++.h>
#include<iostream>

using namespace std;

struct Point {
    int x, y;
};

int totalDuration(vector<vector<int>> intervals, int k){
    vector<Point> points;
    for(auto v: intervals){
        points.push_back({v[0], 1});
        points.push_back({v[1], -1});
    }

    sort(points.begin(), points.end(), [&](Point a, Point b){
        if(a.x==b.x) return a.y>b.y;
        return a.x<b.x; 
    });

    int ans = 0, currentPeople = 0;
    for(int i=0;i<points.size();i++){
        currentPeople+=points[i].y;
        if(currentPeople>k && i+1<points.size()){
            ans+= points[i+1].x-points[i].x;
        }
    }

    return ans;
}

int main() {
    cout << totalDuration({{50, 80}, {80, 90}}, 0) << '\n';  // 40
    cout << totalDuration({{1, 4}, {2, 5}, {7, 8}}, 1) << '\n'; // 2
    cout << totalDuration({}, 0) << '\n';                     // 0
}
