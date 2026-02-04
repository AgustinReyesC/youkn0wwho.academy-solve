#include <bits/stdc++.h>
using namespace std;

#define fastio ios::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define pb push_back
#define fi first
#define se second
#define int long long int

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pii> vpii;
typedef vector<pll> vpll;
typedef vector<vi> vvi;
typedef vector<vll> vvll;

const int INF = 1e9 + 7;
const ll LINF = 1e18;
const double EPS = 1e-9;
const double PI = acos(-1);

vector<pair<int, int>> seg;

pii update(int idx, int l, int r, int pos, int val) {
    if(l == r) {
        seg[idx] = {val, 1};
        return seg[idx];
    }
    
    pii lr = seg[idx*2];
    pii rr = seg[idx*2 + 1];

    int mid = (l + r) / 2;
    if(pos <= mid) lr = update(idx*2, l, mid, pos, val);
    else rr = update(idx*2 + 1, mid+1, r, pos, val);
    

    if(lr.first < rr.first) return seg[idx] = lr;
    else if(lr.first > rr.first) return seg[idx] = rr;
    else return seg[idx] = {lr.first, lr.second + rr.second};
}

pii query(int idx, int l, int r, int ql, int qr) {
    if(qr < l || ql > r) return {LLONG_MAX, -1};
    if(ql <= l && r <= qr) return seg[idx];

    int mid = (l + r) / 2;
    pii lr = query(idx*2, l, mid, ql, qr);
    pii rr = query(idx*2 + 1, mid+1, r, ql, qr);

    if(lr.first < rr.first) return lr;
    else if(lr.first > rr.first) return rr;
    else return {lr.first, (rr.second + lr.second)};
}


int32_t main() {
    fastio;
    
    int n, m;
    cin >> n >> m;

    seg.assign(4*n, {});

    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        update(1, 0, n-1, i, x);
    }

    while(m--) {
        int q;
        cin >> q;
        if(q == 1) {
            int i, v;
            cin >> i >> v;
            update(1, 0, n-1, i, v);
        } else {
            int l, r;
            cin >> l >> r;
            pii qry = query(1, 0, n-1, l, r-1);
            cout << qry.first << " " << qry.second << endl;
        }
    }
    
    return 0;
}