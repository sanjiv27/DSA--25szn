// https://neetcode.io/problems/meeting-schedule-ii

/**
 * Definition of Interval:
 * class Interval {
 * public:
 *     int start, end;
 *     Interval(int start, int end) {
 *         this->start = start;
 *         this->end = end;
 *     }
 * }
 */

class Solution {
public:
    int minMeetingRooms(vector<Interval>& intervals) {
        int count = 0, ans = 0;
        vector<pair<int,int>> points;
        for(Interval x: intervals){
            points.push_back({x.start, 1});
            points.push_back({x.end, -1});
        }

        sort(points.begin(), points.end(), [&](auto p1, auto p2){
            if(p1.first==p2.first) return p1.second<p2.second;
            return p1.first<p2.first;
        });

        for(auto p: points){
            count+=p.second;
            ans = max(ans, count);
        }
        return ans;
    }
};

/*
minimum number of meeting rooms => max number of lines are can stacked in parllel 
as each one of them would require a seperate room

*/