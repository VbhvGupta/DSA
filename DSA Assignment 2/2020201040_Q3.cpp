#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;
int sizevar=0;

template <typename t, typename t2>
class node
{
public:
	t key;
	t2 value;
	 node *left;
	 node *right;
	node(){}
	node(t key,t2 val):key(key),value(val){}
};

node<int,int> *root=NULL ;

template <typename t, typename t2>
class Ordered_map
{

public:

Ordered_map(){}

int height(node<t,t2> *temp)
{
	int h=0;
	if (temp)
	{
		h = max(height(temp->left),height(temp->right)) + 1;
	}
	return h;
}

int diff(node<t,t2> *temp)
{
	if(!temp) return 0;
	return height(temp->left) - height(temp->right); 
}

node<t,t2> *rr_rotation(node<t,t2> *parent)
{
	node<t,t2> *temp=parent->right;
	parent->right = temp->left;
	temp->left = parent;
	return temp;
}

node<t,t2> *ll_rotation(node<t,t2> *parent)
{
	node<t,t2> *temp= parent->left;
	parent->left = temp->right;
	temp->right = parent;
	return temp;
}

node<t,t2> *lr_rotation(node<t,t2> *parent)
{
	node<t,t2> *temp = parent->left;
	parent->left = rr_rotation(temp);
	return ll_rotation(parent);
}

node<t,t2> * rl_rotation(node<t,t2> *parent)
{
	node<t,t2> *temp = parent->right;
	parent->right = ll_rotation(temp);
	return rr_rotation(parent);
}

node<t,t2> *balance(node<t,t2> *temp)
{
	int bal_factor = diff(temp);
	if (bal_factor > 1)
	{
		if (diff(temp->left) > 0)
			temp = ll_rotation(temp);
		else
			temp = lr_rotation(temp);
	}
	else if (bal_factor < -1)
	{
		if (diff(temp->right) > 0)
			temp = rl_rotation(temp);
		else
			temp = rr_rotation(temp);
	}
	return temp;
}

node<t,t2> *insert(node<t,t2> *root, t key , t2 val)						// Insertion
{
	if (!root)
	{
		++sizevar;
		return new node<t,t2>(key,val);
	}
	if(root->key == key)				// Duplicates aren't allowed			
	{
		EXIT_FAILURE;				
	}
	else
	{
	 	if (key <= root->key)
		{
			root->left = insert(root->left, key , val);
		}
		else if(key > root->key)
		{
			root->right = insert(root->right, key , val);
		}
		root = balance(root);
	}
	return root;
}

void display(node<t,t2> *ptr, int level)
{
	int i;
	if (ptr != NULL)
	{
		display(ptr->right, level + 1);
		printf("\n");
		if (ptr == root)
			cout << "Root -> ";
		for (i = 0; i < level && ptr != root; i++)
			cout << "        ";
		cout << ptr->key<<"|"<<ptr->value;
		display(ptr->left, level + 1);
	}
}

node<t,t2>* findMin(node<t,t2>* temp) 
{
	if (!temp) return NULL;
	else if (temp->left == NULL) return temp;
	else return findMin(temp->left);
}
node<t,t2>* findMax(node<t,t2>* temp) 
{
	if (!temp) return NULL;
	else if (temp->right == NULL) return temp;
	else return findMax(temp->right);
}
node<t,t2>* find(node<t,t2> *temp , t key)
{
	if(!temp) return NULL;
	if (key < temp->key)
		return find(temp->left  , key);
	else if(key > temp->key)
		return find(temp->right , key);
	else return temp;
}

node<t,t2> *remove(node<t,t2> *T, t x) 								// Deletion
{
	node<t,t2> *temp;
	if (!T) return NULL;
	
	else if (x < T->key) T->left  = remove(T->left, x);
	else if (x > T->key) T->right = remove(T->right, x);
	else
	{
		if (T->left && T->right)    							// if element has 2 child
		{
			temp = findMin(T->right);
			T->key  = temp->key;
			T->right = remove(T->right, T->key);
		}
		else  													// if element has 1 or no child 
		{
			temp = T;
			if (!T->left) T = T->right;
			else if (!T->right ) T = T->left; 
			--sizevar;
			delete temp;
		}
	}
	if (!T) return T;
	T = balance(T);
}

void inorder(node<t,t2> *root)
{
	if (!root) return;
	inorder(root->left);
	cout << root->key <<"|"<<root->value<<" ";
	inorder(root->right);
}

t2& operator[](t key)
{
	t2 val;	
	node<t,t2>* temp=find(root,key);

	if(!temp){
		
		root=insert(root,key,val);
		temp=find(root,key);
	}
		return temp->value;	
}

int size()
{
	return sizevar;
}

void clear(node<t,t2>* ptr)
{
		if(!ptr) {root=NULL; return;}

		clear(ptr->left);
		clear(ptr->right);
		--sizevar;
		cout<<ptr->key<<"|"<<ptr->value<<endl;
		delete ptr;		
}

};

int main()
{
	int choice;
	int key , value;
	Ordered_map<int,int> a;
	while (1)
	{
		cout << "**********************************"<< endl;
		cout << "1.Insert(key,value)"              	<< endl;
		cout << "2.Erase(key)"					 	<< endl;
		cout << "3.find(key)"                 		<< endl;
		cout << "4.map_obj[key]"               		<< endl;
		cout << "5.Size()"                   		<< endl;
		cout << "6.Clear()"                   		<< endl;
		cout << "Enter your Choice: " 				<< endl;
		cout << endl;
		cin  >> choice;
		switch (choice)
		{

		case 1:
			cin >> key >> value;
			root = a.insert(root, key , value);
			break;
		case 2:
			cin >> key;
			root = a.remove(root, key);
			break;
		case 3:
			cin  >> key;
			if(a.find(root,key)) cout<<"find("<<key<<") = "<<a.find(root,key)->value;
			else cout<<"Item not there";
			cout << endl;
			break;
		case 4:
			cin>> key;
			cout<<"map_obj["<<key<<"] = "<<a[key];
			cout<<endl;
			break;
		case 5:
			cout<<"Size = " << a.size();
			cout<<endl;
			break;
		case 6:
			a.clear(root);
			cout<<"deleted"<<endl;	
		default:
			cout << endl;
			EXIT_FAILURE;
		}
		cout<<endl;
			if (!root)
			{
				cout << "Tree is Empty" << endl;
				continue;
			}
			a.display(root, 1);
			cout<<endl;
	}
	return 0;
}


