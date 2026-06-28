#include<bits/stdc++.h>
using namespace std;

int main()
{
    int t=0;
    cin>>t;
    for(int i=0;i<t;i++)
    {
        int ans=0;
        int n=0;
        cin>>n;
        int a[8]={};
        for(int j=0;j<n;j++) { cin>>a[j];}
        int cnt1=0,cnt2=0;
        for(int j=0;j<n;j++)
        {
            if(a[j]==(-1)) cnt1++;
            if(a[j]==0) cnt2++;
        }
        if(cnt1%2!=0) ans+=2;
        else ans+=0;
        ans+=cnt2;
        cout<<ans<<endl;
    }
    
    return 0;
}