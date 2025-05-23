// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2287

// SOLUTION 1: USING BFS
// O(n*t) ~10^9 TLE
#include <bits/stdc++.h>
#include <iostream>
#include <queue>
#include <unordered_set>

typedef long long ll;
using namespace std;

int min_flips_to_target(ll n, ll l, ll r, ll t) {
    if (t == 1) return 0;  // Already on target page
    
    queue<pair<ll, int>> q;  // (current_page, flips)
    unordered_set<ll> visited;
    
    q.push({1, 0});
    visited.insert(1);
    
    while (!q.empty()) {
        auto [page, flips] = q.front();
        q.pop();
        
        // Try flipping right
        ll next_page = page + r;
        if (next_page == t) return flips + 1;
        if (next_page <= n && !visited.count(next_page)) {
            visited.insert(next_page);
            q.push({next_page, flips + 1});
        }
        
        // Try flipping left
        next_page = page - l;
        if (next_page == t) return flips + 1;
        if (next_page >= 1 && !visited.count(next_page)) {
            visited.insert(next_page);
            q.push({next_page, flips + 1});
        }
    }
    
    return -1;  // Indicating "uh-oh!"
}

void f(){
    int n,l,r,t;
    cin>>n>>l>>r>>t;
    int res = min_flips_to_target(n,l,r,t);
    if(res==-1) cout<<"uh-oh!"<<endl;
    else cout<<res<<endl;
}

int main(){
    int t=1;
    cin>>t;
    while(t--) f();
    return 0;
}










// SOLUTION 2: USING EXTENDED EUCLIDEAN ALGORITHM
// O(log(min(l,r))*t) ~2300

// #include <bits/stdc++.h>
// #include <iostream>
// using namespace std;

// int gcd(int a, int b) {
//     return (b == 0) ? abs(a) : gcd(b, a % b);
// }

// pair<int, int> extended_euclidean(int a, int b){
//     if(b==0){
//         return make_pair(1,0);
//     }
//     pair<int,int> xy = extended_euclidean(b, a%b);
//     int x1 = xy.first, y1 = xy.second;
//     int x, y;
//     x = y1;
//     y = x1 - (a/b)*y1;
//     return make_pair(x,y);
// }

// void f(){
//     int n, l, r, t;
//     cin>>n>>l>>r>>t;
//     t = t-1;
//     int g = gcd(r, -l);
//     if(t%g!=0){
//         cout<<"uh-oh!"<<endl;
//         return;
//     }
    
//     pair<int, int> xy = extended_euclidean(r, l);
//     long long x0 = xy.first * (t / g);
//     long long y0 = -xy.second * (t / g); 

//     int l_div_g = l / g;
//     int r_div_g = r / g;

//     // Calculate k_min to ensure x >=0 and y >=0
//     // x = x0 + k * l_div_g >=0 => k >= ceil((-x0) / l_div_g)
//     // y = y0 + k * r_div_g >=0 => k >= ceil((-y0) / r_div_g)
//     long long k1 = ceil((-x0) / (double)l_div_g);
//     long long k2 = ceil((-y0) / (double)r_div_g);
//     long long k_min = max(k1, k2);

//     // Compute x and y with k_min
//     long long x = x0 + k_min * l_div_g;
//     long long y = y0 + k_min * r_div_g;

//     // Check if x and y are non-negative
//     if (x < 0 || y < 0) {
//         cout << "uh-oh!" << endl;
//         return;
//     }

//     cout << x + y << endl;
// }

// int main() {
//     int t=1;
//     cin>>t;
//     for(int i=0;i<t;i++) f();
//     return 0;
// }