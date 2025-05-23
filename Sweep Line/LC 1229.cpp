// https://leetcode.ca/all/1229.html

/*

1229. Meeting Scheduler

Given the availability time slots arrays slots1 and slots2 of two people and a meeting duration duration, 
return the earliest time slot that works for both of them and is of duration duration.
If there is no common time slot that satisfies the requirements, return an empty array.
The format of a time slot is an array of two elements [start, end] representing an inclusive time range from start to end.  
It is guaranteed that no two availability slots of the same person intersect with each other. 
That is, for any two time slots [start1, end1] and [start2, end2] of the same person, either start1 > end2 or start2 > end1.

 
Example 1:
Input: slots1 = [[10,50],[60,120],[140,210]], slots2 = [[0,15],[60,70]], duration = 8
Output: [60,68]

Example 2:
Input: slots1 = [[10,50],[60,120],[140,210]], slots2 = [[0,15],[60,70]], duration = 12
Output: []

*/

class Solution {
    vector<int> minTimeWhenSlotsMatch(vector<vector<int>> slots1, vector<vector<int>> slots2, int duration){
        vector<tuple<int,int,int>> points;
        for(vector v: slots1) {
            points.push_back({v[0], 1, 1});
            points.push_back({v[1], -1, 1});
        }

        for(vector v: slots2) {
            points.push_back({v[0], 1, 2});
            points.push_back({v[1], -1, 2});
        }

        sort(points.begin(), points.end(), [](auto &a, auto &b){
            if(get<0>(a)!=get<0>(b)) return get<0>(a)<get<0>(b);
            else if(get<1>(a)!=get<1>(b)) return get<1>(a)>get<1>(b); // +1 before -1 to capture both work at same time
            return false;
        });

        int last_start=-1, active=0;
        for(auto [time, type, person]: points){
            if(type==1) last_start = time;
            else {
                if(active>=2 && time-last_start>=duration) return {last_start, last_start+duration};
            }
            active+=type;
        }
        return {};
    }
}

/*
this only works because there is no overlap between meetings for each person.
safest is 2 pointers here
*/