
#include<bits/stdc++.h>
#include<algorithm>

using namespace std;

#define ll long long 

class trieNode
{
	public:
	trieNode *left;
	trieNode *right;
	bool checkLeaf;

	trieNode()
	{
		left = NULL;
		right = NULL;
		checkLeaf = false ;
	}

	void insert(ll n)
	{
		trieNode *curr = this;
		for(ll i=63;i>=0;i--)
		{
			ll bit = (n>>i)&1;

			if(bit==0)
			{
				if(!curr->left)
				{
					curr->left = new trieNode();
				}
				 curr = curr->left;
			}
			else
			{
				if(!curr->right)
				{
					curr->right = new trieNode();
				}
				curr = curr->right;
			}
		}
	}

};

void fast()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
}

ll findMaxXor(trieNode* head , ll value )
{
		trieNode* crr = head;
		ll max_xor = 0 ;
		ll crr_xor = 0;
		for(ll j=63 ; j>=0 ; j--)
		{
			ll bit = (value >> j)&1;

			if(bit==0)
			{
				if(crr -> right)
				{
					crr_xor += pow(2,j);
					crr = crr->right;
				}
				else
				{
					crr = crr->left;
				}
			}
			else
			{
				if(crr->left)
				{
					crr_xor += pow(2,j);
					crr = crr->left;
				}
				else
				{
					crr = crr->right;
				}
			}
		}
		if(crr_xor > max_xor)
		{
			max_xor = crr_xor;
		}
	
	return max_xor;
}


int main()
{
	fast();

	ll n , q;
	cin>>n>>q;
	
	ll arr[n];
	
	trieNode* head = new trieNode();
	for(ll i=1 ; i<=n ; i++)
	{
		cin >> arr[i-1];
		head->insert(arr[i-1]);
	}
	while(q)
	{
		ll num ;
		cin >> num;
		cout << findMaxXor(head,num)<<endl;
		--q;
	}
		
	return 0;
}