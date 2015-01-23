#include "a.h"

int main(int argc,char *argv[]) {
    assert(argc >= 3);

    sscanf(argv[1],"%d",&N);
    sscanf(argv[2],"%d",&M);
    
    solve();
    return 0;
}

double getDistance(ll p1,ll p2) {
    ll XOR = p1^p2;
    int diff = __builtin_popcount(XOR);
    double dist = sqrt(double(diff));
    double ret = dabs(sqrt((double)N/2.0f)-dist);
    return ret;
}
void solve() {
    ddll d[111][(1ll<<11)];
    for ( int i = 0 ; i < 111 ; i++ ) 
        for ( ll j = 0 ; j < (1ll<<11) ; j++ ) 
            d[i][j].first = 987654321, d[i][j].second = -1;
    
    for ( int j = 0 ; j < (1ll<<N) ; j++ ) 
        d[0][j].first = 0;

    for ( int i = 1 ; i < M ; i++ ) 
        for ( ll j = 0 ; j < (1ll<<N) ; j++ ) {
            vector<ll> nowPermutation = getPermutation(__builtin_popcount(j));
            for ( int k = 0 ; k < (int)nowPermutation.size() ; k++ ) {
                if ( j == nowPermutation[k] ) continue;
                ddll prev = d[i-1][nowPermutation[k]];
                double dist = getDistance(j, nowPermutation[k]);
                ll parent = prev.second;
                for ( int l = i-2 ; l >= 0 ; l-- ) {
                    dist += getDistance(j,parent);
                    parent = d[l][parent].second;
                }
                if ( d[i][j].first > prev.first + dist ) {
                    d[i][j].first = prev.first + dist;
                    d[i][j].second = nowPermutation[k];
                }
next:;
            }
        }
    ll lastPoint = 0;
    double mn = 987654321;
    for ( ll j = 0 ; j < (1ll<<N) ; j++ ) {
        if ( d[M-1][j].first < mn ) {
            lastPoint = j;
            mn = d[M-1][j].first;
        }
    }

    vector<string> v;
    for ( int i = M-1 ; i >= 0 ; i-- ) {
        v.push_back(bitMaskToString(lastPoint));
        lastPoint = d[i][lastPoint].second;
    }

    vector<string> ans;
    for ( int i = 0 ; i < M ; i++ ) {
        string now = "";
        for ( int j = 0 ; j < N/10 ; j++ ) 
            now += v[i];
        for ( int j = 0 ; j < N%10 ; j++ ) 
            now += v[i][j];
        ans.push_back(now);
    }

    for ( int i = 0 ; i < (int)ans.size() ; i++ ) {
        for ( int j = 0 ; j < (int)ans[i].length() ; j++ ) 
            printf("%c ",ans[i][j]);
            puts("");
    }
}
string bitMaskToString(ll mask) {
    string ret = "";
    while ( mask ) {
        ret.insert(ret.begin(),(mask&1)+'0');
        mask >>= 1;
    }
    while ( (int)ret.length() != N ) 
        ret.insert(ret.begin(),'0');
    return ret;
}

void go(ll mask,set<ll>& s) {
    s.insert(mask);
    for ( int i = 2 ; i <= mask ; i <<= 1 )
        if ( mask&i ) {
            if ( !(mask&(i>>1)) ) {
                // 1's right bit is zero
                if ( s.count((mask&(~i))|(i>>1)) != 0 ) continue;
                mask &= ~(i);
                mask |= (i>>1);
                go(mask,s);
                mask &= ~(i>>1);
                mask |= (i);
            }
        }
}
vector<ll> getPermutation(int size) {
    vector<ll> ret;
    ll mask = 0;
    int pos = N-1;

    for ( int i = 0 ; i < size ; i++ ) {
        mask |= (1ll<<pos);
        pos--;
    }
    set<ll> s;
    go(mask,s);

    for ( set<ll>::iterator it=s.begin();it!=s.end();it++ ) 
        ret.push_back(*it);

    return ret;
}
void go_pbm(ll mask) {
    if ( !mask ) return;
    go_pbm(mask>>1);
    printf("%lld",mask&1);
}
void printBitMask(ll mask) {
    stack<int> st;
    while ( mask ) {
        st.push(mask&1);
        mask >>= 1;
    }
    for ( int i = 0 ; i < N-(int)st.size() ; i++ ) 
        printf("0 ");
    while ( !st.empty() ) {
        int now = st.top();st.pop();
        printf("%d ",now);
    }
    puts("");
}
