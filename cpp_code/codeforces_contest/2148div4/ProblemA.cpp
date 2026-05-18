#include<bits/stdc++.h>
using namespace std;

int main()
{
    int t=0;
    cin>>t;
    for(int i=0;i<t;i++)
    {
        int x,n;
        cin>>x>>n;
        if(n%2!=0)
        {
            cout<<x<<endl;
        }
        else
        {
            cout<<"0"<<endl;
        }
    }
    return 0;
}