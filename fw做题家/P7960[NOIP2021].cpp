#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e7 + 1e4;

bool flag[MAXN + 1] = {0};

vector<int> ok;

bool has7(int i) { // 十进制存在7
    for (; i; i /= 10) {
        if (i % 10 == 7) return true;
    }

    return false;
}

void pre() { // 筛法预处理
    for(int i = 1; i <= MAXN; ++i) {
        flag[i] |= has7(i);
        if(flag[i]) {
            if(i * 2 <= MAXN) flag[i * 2] = true;
            for(int ti = 1; i * (ti * 2 + 1) <= MAXN; ++ti)
                flag[i * (ti * 2 + 1)] = true;
        } else {
            ok.push_back(i);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    pre();
    int T, q; cin >> T;
    while (T--) {
        cin >> q;
        vector<int>::iterator it = lower_bound(ok.begin(), ok.end(), q); // 二分查询
        if(it == ok.end() || (*it) != q) {
            cout << -1 << endl;
        }
        else {
            ++it;
            cout << *it << endl;
        }
    }
    return 0;
}