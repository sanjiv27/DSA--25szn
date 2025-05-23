// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2387

/*
BFS:
checking each multiple is ineffiecent. here we can construct smallest number divisible by K. 

Number Theory:
1) new = old * 10 + x; new rem = old rem * 10 + x. remainder will behave same
2) no need to explore same remainder further as they will behave same with mod K.
*/

#include <iostream>
#include <queue>
#include <vector>
#include <array>
#include <climits>

using namespace std;

struct State {
    int rem;
    bool has_zero;
    int length;
    int count_3;
};

void solve(int K) {
    if (K == 0) return;

    // visited[rem][has_zero] = {min_length, max_3_count}
    vector<array<pair<int, int>, 2>> visited(K);
    for (int i = 0; i < K; ++i) {
        visited[i][0] = {INT_MAX, 0};
        visited[i][1] = {INT_MAX, 0};
    }

    // Start with '3'
    int initial_rem = 3 % K;
    if (initial_rem == 0) {
        cout << "1 1 0" << endl;
        return;
    }
    visited[initial_rem][0] = {1, 1};
    queue<State> q;
    q.push({initial_rem, false, 1, 1});

    while (!q.empty()) {
        State current = q.front();
        q.pop();

        if (current.rem == 0) {
            int zeros = current.length - current.count_3;
            cout << current.length << " " << current.count_3 << " " << zeros << endl;
            return;
        }

        if (!current.has_zero) {
            // Add '3'
            int new_rem = (current.rem * 10 + 3) % K;
            int new_length = current.length + 1;
            int new_count_3 = current.count_3 + 1;
            auto& vis = visited[new_rem][0];
            if (new_length < vis.first || (new_length == vis.first && new_count_3 > vis.second)) {
                if (new_length < vis.first) vis = {new_length, new_count_3};
                else if (new_count_3 > vis.second) vis.second = new_count_3;
                q.push({new_rem, false, new_length, new_count_3});
            }

            // Add '0'
            new_rem = (current.rem * 10) % K;
            new_length = current.length + 1;
            new_count_3 = current.count_3;
            auto& vis_zero = visited[new_rem][1];
            if (new_length < vis_zero.first || (new_length == vis_zero.first && new_count_3 > vis_zero.second)) {
                if (new_length < vis_zero.first) vis_zero = {new_length, new_count_3};
                else if (new_count_3 > vis_zero.second) vis_zero.second = new_count_3;
                q.push({new_rem, true, new_length, new_count_3});
            }
        } else {
            // Can only add '0'
            int new_rem = (current.rem * 10) % K;
            int new_length = current.length + 1;
            int new_count_3 = current.count_3;
            auto& vis = visited[new_rem][1];
            if (new_length < vis.first || (new_length == vis.first && new_count_3 > vis.second)) {
                if (new_length < vis.first) vis = {new_length, new_count_3};
                else if (new_count_3 > vis.second) vis.second = new_count_3;
                q.push({new_rem, true, new_length, new_count_3});
            }
        }
    }

    cout << "0 0 0" << endl;
}

int main() {
    int K;
    while (cin >> K) solve(K);
    return 0;
}