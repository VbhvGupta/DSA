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

ll findPrefixSize(string a, string b)
{
    ll size=min(a.size(), b.size());
    ll count=0;
    for(ll i=0;i<size;i++){
        if(a[i]==b[i]){
            count++;
        }
        else return count;
    }
    return count;
}  

ll longest_substr_k_times(vector<vector <ll>> v1, ll n, ll k, string s)
{
	ll h, i, j, is[n], lcp[n], l, t;
	for(i=0; i<n; i++)
		is[v1[i][0]]=i;
	h=0;
	for(i=0; i<n; i++)
	{
		if(is[i]+1<n)
		{
			j=v1[is[i]+1][0];
			while(i+h<n && j+h<n && s[i+h]==s[j+h])
				h++;
			lcp[is[i]]=h;
			if(h>0)
				h=h-1;
		}
		else
			lcp[is[i]]=0;
	}
	l=-1;
	for(i=0; i<=n-k+1; i++)
	{
		t=n;
		for(j=i; j<i+k-1; j++)
			t=min(t, lcp[j]);
		l=max(l, t);
	}
	return(l);
} 

int main()
{
	fast();
	string s;
	cin>>s;
	ll n=s.len;
	//ll arr[n];
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
	ll k1=2;
	
	while(k1<=n)
	{
		for(ll i=0;i<n;i++)
		{
			ll d=p[i].ss+k1;
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
		k1=k1*2;
	}

	vector<vector<ll>> ans ;
	for(ll i=0;i<n;i++)
	{
		//arr[i] = p[i].ss;
		//cout<<p[i].ff.ff<<"  " <<p[i].ff.ss << "  " <<  p[i].ss <<endl;
		vector<ll>anspart;
		anspart.push_back(p[i].ss);
		anspart.push_back(p[i].ff.ff);
		anspart.push_back(p[i].ff.ss);
		ans.push_back(anspart);
	}
	//cout<<minLexRot(s ,arr ,s1.length());
	ll K;
	cin >> K ;
	ll val = longest_substr_k_times(ans ,n ,K ,s);
	cout<<"ANS: "<<val<<endl;
	return 0;
}