// https://neetcode.io/problems/meeting-schedule

/*
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
    bool canAttendMeetings(vector<Interval>& intervals) {
        int count = 0;
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
            if(count>1) return 0;
        }
        return 1;
    }
};

/*
    here it is [start,end) so we process till x.end and consider -1 first
    as we need to know meeting end before start
*/