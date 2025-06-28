/*
    2040. Kth Smallest Product of Two Sorted Arrays
    Given two sorted 0-indexed integer arrays nums1 and nums2 as well as an integer k, 
    return the kth (1-based) smallest product of nums1[i] * nums2[j] where 0 <= i < nums1.length and 0 <= j < nums2.length.

    Example:

    Input: nums1 = [-4,-2,0,3], nums2 = [2,4], k = 6
    Output: 0
    Explanation: The 6 smallest products are:
        - nums1[0] * nums2[1] = (-4) * 4 = -16
        - nums1[0] * nums2[0] = (-4) * 2 = -8
        - nums1[1] * nums2[1] = (-2) * 4 = -8
        - nums1[1] * nums2[0] = (-2) * 2 = -4
        - nums1[2] * nums2[0] = 0 * 2 = 0
        - nums1[2] * nums2[1] = 0 * 4 = 0
    The 6th smallest product is 0.

    
    Constraints:

        1 <= nums1.length, nums2.length <= 5 * 104
        -105 <= nums1[i], nums2[j] <= 105
        1 <= k <= nums1.length * nums2.length
        nums1 and nums2 are sorted.


*/

using ll = long long;
class Solution {
public:
    long long kthSmallestProduct(vector<int>& nums1, vector<int>& nums2, long long k) {
        ll lo = LLONG_MAX, hi = LLONG_MIN, ans = -1;

        // auto ceil_div = [](ll a, ll b) -> ll {
        //     return a / b + ((a ^ b) > 0 && a % b != 0);
        // };
        // auto floor_div = [](ll a, ll b) -> ll {
        //     return a / b - (((a ^ b) < 0) && (a % b));
        // };
        
        auto count = [&](ll mid){
            ll c = 0;
            for(auto x: nums1){
                if(x>0) c+=upper_bound(nums2.begin(), nums2.end(), floor(1.0*mid/x)) - nums2.begin();
                else if(x<0) c+=nums2.end()-lower_bound(nums2.begin(),nums2.end(), ceil(1.0*mid/x));
                else c+=((mid>=0)?nums2.size():0);
            }
            return c;
        };
        
        for(auto x: {nums1.front(), nums1.back()}){
            for(auto y: {nums2.front(), nums2.back()}){
                lo = min(lo, (ll)x*y);
                hi = max(hi, (ll)x*y);
            }
        }

        while(lo<=hi){
            ll mid = lo + (hi-lo)/2;
            if(count(mid)>=k) {
                ans = mid;
                hi = mid-1;
            }
            else lo = mid+1;
        }
        return ans;
    }
};


/*
- Binary search on answer space 
- [isGood()] function is monotonically non-decreasing => First true
- 3 cases for each x*y<=mid

Extra:
- use ceil_div, floor_div; double divison doesnt behave properly after 1e16
*/