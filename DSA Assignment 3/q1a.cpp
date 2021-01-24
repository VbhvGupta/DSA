#include <bits/stdc++.h>
#include <fstream>
using namespace std;
#define ll long long
#define ff first
#define ss second
#define len length()
void fast()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
}
  
string minLexRot(string str,ll a[],int n)
{
    string minlexstr="";
    for(int i=0;i<2*n;i++)
    {
        if(a[i]<n)
        {
            minlexstr=str.substr(a[i],n);
            break;
        }
    }
    return minlexstr;
}     
   

int main()
{
	fast();
	string s,s1;
	cin>>s1;
	s=s1+s1;
	ll n=s.len;
	ll arr[n];
	pair<pair<ll,ll>,ll> p[n];
	for(ll i=0;i<n;i++)
	{
		if(i<n-1)
			p[i]=make_pair(make_pair(s[i]-'a',s[i+1]-'a'),i);
		else
			p[i]=make_pair(make_pair(s[i]-'a',-1),i);
	}
	ll a[n];
	sort(p,p+n);
	ll rank=0;
	pair<ll,ll> prev;
	for(ll i=0;i<n;i++)
	{
		if(i==0)
		{
			a[p[i].ss]=i;
			prev=p[i].ff;
			p[i].ff.ff=i;
		}
		else
		{
			if(prev!=p[i].ff)
			{
				rank++;
				a[p[i].ss]=rank;
				prev=p[i].ff;
				p[i].ff.ff=rank;
			}
			else
			{
				a[p[i].ss]=rank;
				p[i].ff.ff=rank;
			}
		}
	}
	ll k=2;
	
	while(k<=n)
	{
		for(ll i=0;i<n;i++)
		{
			ll d=p[i].ss+k;
			if(d<n)
			{
				p[i].ff.ss=a[d];
			}
			else
			{
				p[i].ff.ss=-1;		
			}
		}
		sort(p,p+n);
		ll rank=0;
		pair<ll,ll> prev;
		for(ll i=0;i<n;i++)
		{
			if(i==0)
			{
				a[p[i].ss]=i;
				prev=p[i].ff;
				p[i].ff.ff=i;
			}
			else
			{
				if(prev!=p[i].ff)
				{
					rank++;
					a[p[i].ss]=rank;
					prev=p[i].ff;
					p[i].ff.ff=rank;
				}
				else
				{
					a[p[i].ss]=rank;
					
					p[i].ff.ff=rank;
				}
			}
		}
		k=k*2;
	}

	for(ll i=0;i<n;i++)
	{
		arr[i] = p[i].ss;
		//cout<<p[i].ff.ff<<"  " <<p[i].ff.ss << "  " <<  p[i].ss <<endl;
	}

	cout<<minLexRot(s ,arr ,s1.length());
	return 0;
}