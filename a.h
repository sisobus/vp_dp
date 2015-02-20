#include <cstdio>
#include <string>
#include <set>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>
#include <stack>
#include <cassert>
using namespace std;

#define K 10 // dp dim limit

typedef long long ll;
typedef pair<double,ll> ddll;
int N,M; // N = dim, M = points size

string bitMaskToString(ll mask);
double dabs(double a){return a>=0?a:-a;}
double getDistance(ll p1,ll p2);
void solve();
void go(ll mask,set<ll>& s);
vector<ll> getPermutation(int size);
void go_pbm(ll mask);
void printBitMask(ll mask,int totalSize);

#define MAX_DIMENSION_POW 6
ll stringToLongLong(string now);
vector<vector<string> > pre_makeTwoPowOptimalPoints();
vector<vector<ll> > makeTwoPowOptimalPoints();
