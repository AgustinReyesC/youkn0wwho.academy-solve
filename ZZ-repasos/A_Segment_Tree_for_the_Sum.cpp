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

vi seg;

void build(vi &vec, int idx, int l, int r) {
    if(l == r) {
        seg[idx] = vec[l];
        return;
    }

    int mid = (l + r) / 2;

    build(vec, idx*2, l, mid);
    build(vec, idx*2 + 1, mid+1, r);
    seg[idx] = seg[idx*2] + seg[idx*2 + 1];
}

void update(int idx, int l, int r, int pos, int val) {
    if(l == r) {
        seg[idx] = val;
        return;
    }

    int mid = (l + r) / 2;
    if(pos <= mid) update(idx*2, l, mid, pos, val);
    else update(idx*2 + 1, mid+1, r, pos, val);

    seg[idx] = seg[idx*2] + seg[idx*2 + 1];
}

int query(int idx, int l, int r, int ql, int qr) {
    if(qr < l || ql > r) return 0; //no overlap
    if(ql <= l && r <= qr) return seg[idx]; //total overlap

    int mid = (l + r) / 2;
    int lq = query(idx*2, l, mid, ql, qr);
    int rq = query(idx*2 + 1, mid+1, r, ql, qr);
    return lq + rq;
}

int32_t main() {
    fastio;
    
    int n, m;
    cin >> n >> m;

    seg.assign(4*n, 0);
    vi vec(n);

    for(int i = 0; i < n; i++) cin >> vec[i];
    build(vec, 1, 0, n-1);

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
            cout << query(1, 0, n-1, l, r-1) << endl;
        }
    }
    
    return 0;
}