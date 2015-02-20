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

ddll d[111][(1ll<<17)];
void solve() {
    for ( int i = 0 ; i < 5 ; i++ ) {
        if ( (1<<i) == N ) {
            vector<vector<ll> > optimalPoints = makeTwoPowOptimalPoints();
            vector<ll> optimalPoint = optimalPoints[i];
            for ( int j = 0 ; j < (int)optimalPoint.size() ; j++ ) 
                printBitMask(optimalPoint[j],1<<i);
            /*
            int sum = 0;
            for ( int j = 0 ; j < optimalPoint.size() ; j++ ) 
                for ( int k = 0 ; k < optimalPoint.size() ; k++ ) 
                    if ( j!=k ) 
                        sum += getDistance(optimalPoint[j],optimalPoint[k]);
            printf("%d\n",sum);
            */
            return ;
        }
    }
    for ( int i = 0 ; i < 111 ; i++ ) 
        for ( ll j = 0 ; j < (1ll<<17) ; j++ ) 
            d[i][j].first = 987654321, d[i][j].second = -1;

    for ( int j = 0 ; j < (1ll<<N) ; j++ ) 
        d[0][j].first = 0;

    for ( int i = 1 ; i < M ; i++ ) 
        for ( ll j = 0 ; j < (1ll<<N) ; j++ ) {
            for ( ll k = 0 ; k < (1ll<<N) ; k++ ) {
                if ( j == k ) continue;
                ddll prev = d[i-1][k];
                double dist = getDistance(j,k);
                ll parent = prev.second;
                for ( int l = i-2 ; l >= 0 ; l-- ) {
                    dist += getDistance(j,parent);
                    parent = d[l][parent].second;
                }
                if ( d[i][j].first > prev.first + dist ) {
                    d[i][j].first = prev.first + dist;
                    d[i][j].second = k;
                }
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

    for ( int i = 0 ; i < (int)v.size() ; i++ ) {
        for ( int j = 0 ; j < (int)v[i].length() ; j++ ) 
            printf("%c ",v[i][j]);
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

void printBitMask(ll mask,int totalSize) {
    stack<int> st;
    while ( mask ) {
        st.push(mask&1);
        mask >>= 1;
    }
    for ( int i = 0 ; i < totalSize-(int)st.size() ; i++ ) 
        printf("0 ");
    while ( !st.empty() ) {
        int now = st.top();st.pop();
        printf("%d ",now);
    }
    puts("");
}

ll stringToLongLong(string now) {
    ll ret = 0ll;
    for ( int i = 0 ; i < (int)now.length() ; i++ ) {
        ret <<= 1;
        ret |= (now[i]-'0');
    }
    return ret;
}

vector<vector<string> > pre_makeTwoPowOptimalPoints() {
    vector<vector<string> > ret;
    for ( int i = 0 ; i < MAX_DIMENSION_POW ; i++ ) {
        vector<string> now(1<<i);
        for ( int j = 0 ; j < (1<<i) ; j++ ) {
            now[j] = "";
            for ( int k = 0 ; k < (1<<i) ; k++ ) 
                now[j] += "0";
        }

        if ( i == 0 ) {
            now[0][0] = '0';
        } else {
            int lastDimension = (1<<(i-1));
            for ( int j = 0 ; j < lastDimension ; j++ ) {
                for ( int k = 0 ; k < lastDimension ; k++ ) 
                    now[j*2][k] = ret[i-1][j][k];
                for ( int k = 0 ; k < lastDimension ; k++ ) 
                    now[j*2][k+lastDimension] = ret[i-1][j][k];
                for ( int k = 0 ; k < lastDimension ; k++ ) 
                    now[j*2+1][k] = ret[i-1][j][k];
                for ( int k = 0 ; k < lastDimension ; k++ ) 
                    now[j*2+1][k+lastDimension] = ret[i-1][j][k]^1;
            }
        }
        ret.push_back(now);
    }
    return ret;
}

vector<vector<ll> > makeTwoPowOptimalPoints() {
    vector<vector<string> > t = pre_makeTwoPowOptimalPoints();
    vector<vector<ll> > ret;
    for ( int i = 0 ; i < (int)t.size() ; i++ ) {
        vector<ll> now;
        for ( int j = 0 ; j < (int)t[i].size() ; j++ ) 
            now.push_back(stringToLongLong(t[i][j]));
        ret.push_back(now);
    }
    return ret;
}
