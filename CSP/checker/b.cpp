#include<queue>
#include<iostream>
#define pf(x) ((x)*(x))
using namespace std;
typedef long long ll;
const int N=205;
int n,m,k;ll r;bool vis[N];
struct node{
    ll x,y;int s,k;
    node(){}
    node(int x,int y,int s,int k):x(x),y(y),s(s),k(k){}
}g[N];
void bfs(int S=1,int T=2){
    queue<node>q;
    q.push(node(g[S].x,g[S].y,0,0));
    vis[1]=1;
    while(!q.empty()){
        node h=q.front();q.pop();
        ll cx=h.x,cy=h.y;int cs=h.s,ck=h.k,lim;
        if(cx==g[T].x&&cy==g[T].y){printf("%d\n",cs-1);return ;}
        if(ck==k) lim=n;else lim=n+m;
        for(int i=1;i<=lim;++i){
            if(vis[i]||pf(g[i].x-cx)+pf(g[i].y-cy)>r) continue;
            vis[i]=1;
            q.push(node(g[i].x,g[i].y,cs+1,ck+(i>n)));
        }
    }
}
int main(){
    scanf("%d%d%d%lld",&n,&m,&k,&r);r=r*r;
    for(int i=1;i<=n+m;++i) scanf("%lld%lld",&g[i].x,&g[i].y);
    bfs();
    return 0;
}
