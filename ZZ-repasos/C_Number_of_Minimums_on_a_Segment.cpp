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
typedef vector<pii> vpii;

const int INF = 1e9 + 7;
const ll LINF = 1e18;
const double EPS = 1e-9;
const double PI = acos(-1);

vpii seg;

pii update(int idx, int l, int r, int pos, int val) {
    if(l == r) {
        return seg[idx] = {val, 1};
    }
    
    int mid = (l + r) / 2;
    pii lq = seg[idx*2];
    pii rq = seg[idx*2 + 1];

    if(pos <= mid) lq = update(idx*2, l, mid, pos, val);
    else rq = update(idx*2 + 1, mid+1, r, pos, val);

    if(lq.first < rq.first) return seg[idx] = lq;
    if(lq.first > rq.first) return seg[idx] = rq;
    return seg[idx] = {lq.first, lq.second + rq.second};
}

pii query(int idx, int l, int r, int ql, int qr) {
    if(qr < l || ql > r) return {LLONG_MAX, 0}; //no overlap
    if(ql <= l && r <= qr) return seg[idx]; //total overlap

    int mid = (l + r) / 2;
    pii lq = query(idx*2, l, mid, ql, qr);
    pii rq = query(idx*2+1, mid+1, r, ql, qr);

    if(lq.first < rq.first) return lq;
    if(lq.first > rq.first) return rq;
    return {lq.first, lq.second + rq.second};
}

int32_t main() {
    fastio;
    
    int n, m;
    cin >> n >> m;

    seg.assign(4*n, {LLONG_MAX, 0});

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
            pii res = query(1, 0, n-1, l, r-1);
            cout << res.first << " " << res.second << endl;
        }
    }
    
    return 0;
}