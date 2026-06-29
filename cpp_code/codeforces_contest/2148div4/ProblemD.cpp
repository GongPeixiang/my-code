#include<bits/stdc++.h>
using namespace std;

int arr[200000]={};
int a[200000]={};
int b[200000]={};

int main()
{
    int t=0;
    cin>>t;
    for(int i=0;i<t;i++)
    {
        long long ans=0;
        int n=0;
        cin>>n;
        for(int j=0;j<n;j++)
        {
            cin>>arr[j];
        }
        int cnt1=0;
        int cnt2=0;
        for(int j=0;j<n;j++)
        {
            if((arr[j]%2)!=0)
            {
                a[cnt1]=arr[j];
                cnt1++;
            }
            else
            {
                b[cnt2]=arr[j];
                cnt2++;
            }
        }
        if(cnt1==0)
        {
            ans=0;
        }
        else
        {
            sort(a,a+cnt1);
            sort(b,b+cnt2);
            for(int j=0;j<cnt2;j++)
            {
                ans+=b[j];
            }
            int k=(cnt1+1)/2;
            for(int j=cnt1-1;j>=cnt1-k;j--)
            {
                ans+=a[j];
            }  
        }
        cout<<ans<<endl;
    }
    return 0;
}