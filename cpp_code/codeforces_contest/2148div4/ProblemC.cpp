#include<bits/stdc++.h>
using namespace std;

int main()
{
    int t=0;
    cin>>t;
    for(int i=0;i<t;i++)
    {
        int score=0;
        int n=0,m=0;
        cin>>n>>m;
        int a=0,b=0;
        int c=0,d=0;
        int p=0,q=0;
        for(int j=0;j<n;j++)
        {
            cin>>a>>b;
            p=abs(a-c);
            q=abs(b-d);
            //必须加绝对值,否则并非我们想要的结果
            if((p%2)!=(q%2))
            {
                score+=p-1;
            }
            else
            {
                score+=p;
            }
            c=a;
            d=b;
        }
        score+=m-c;
        cout<<score<<endl;
    }
    return 0;
}