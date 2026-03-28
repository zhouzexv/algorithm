#include <bits/stdc++.h>
using namespace std;
#define ll long long int 
string s;
int k,l;

int main()
{
    cin>>s>>k;
    l=s.size();
    int i;
    while(k)
    {
        for(i=0;s[i]<=s[i+1];i++);
        s.erase(i,1);
        k--;
    }
    while(s[0]=='0' && s.size()>1) s.erase(0,1);
    cout<<s;
    return 0;
}