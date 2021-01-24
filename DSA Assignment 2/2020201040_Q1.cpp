#include <iostream>
#include <algorithm>
#include <climits>
#include <bits/stdc++.h>
using namespace std;
template <typename t>
class node
{
public:
	t data;
	int count;
	struct node *left;
	struct node *right;
	node(){}
	node(t val):data(val){count = 1;}
};

node<int> *root=NULL ;

template <typename t>
class avl
{
node<t> *u_b , *l_b;  
public:
node<t> *upperbound(node<t>* root , t value)
{
	u_b=NULL;
	ub(root,value);
	return u_b;
}

void ub(node<t>* root , t val)
{
	if(!root) return;
	if(val < root->data)
	{
		u_b = root;
		ub(root->left , val);
	}
	else
		ub(root->right , val);
}

node<t>* lowerbound(node<t>* root, t value)
{
	l_b=NULL;
	lb(root,value);
	return l_b;
}

void lb(node<t>* root , t val)
{
	if(!root) return;
	if(val <= root->data)
	{
		l_b=root;
		lb(root->left,val);
	}
	else
		lb(root->right,val);	
}

avl(){}

int height(node<t> *temp)
{
	int h=0;
	if (temp)
	{
		h = max(height(temp->left),height(temp->right)) + 1;
	}
	return h;
}

int diff(node<t> *temp)
{
	if(!temp) return 0;
	return height(temp->left) - height(temp->right); 
}

node<t> *rr_rotation(node<t> *parent)
{
	node<t> *temp=parent->right;
	parent->right = temp->left;
	temp->left = parent;
	return temp;
}

node<t> *ll_rotation(node<t> *parent)
{
	node<t> *temp= parent->left;
	parent->left = temp->right;
	temp->right = parent;
	return temp;
}

node<t> *lr_rotation(node<t> *parent)
{
	node<t> *temp = parent->left;
	parent->left = rr_rotation(temp);
	return ll_rotation(parent);
}

node<t> * rl_rotation(node<t> *parent)
{
	node<t> *temp = parent->right;
	parent->right = ll_rotation(temp);
	return rr_rotation(parent);
}

node<t> *balance(node<t> *temp)
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

node<t> *insert(node<t> *root, t val)						// Insertion
{
	if (!root)
	{
		return new node<t>(val);
	}
	if(root->data == val)								// if duplicate data
	{
		root->count = root->count + 1;					// then increament the count
	}
	else
	{
	 	if (val <= root->data)
		{
			root->left = insert(root->left, val);
		}
		else if(val > root->data)
		{
			root->right = insert(root->right, val);
		}
		root = balance(root);
	}
	return root;
}

int countof(node<t> *ptr , t val)
{
	node<t> * temp = find(ptr , val);
	if(!temp) return 0;
	return temp->count;
}

void display(node<t> *ptr, int level)
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
		cout << ptr->data;
		display(ptr->left, level + 1);
	}
}

node<t>* findMin(node<t>* temp) 
{
	if (!temp) return NULL;
	else if (temp->left == NULL) return temp;
	else return findMin(temp->left);
}
node<t>* findMax(node<t>* temp) 
{
	if (!temp) return NULL;
	else if (temp->right == NULL) return temp;
	else return findMax(temp->right);
}
node<t>* find(node<t> *temp , t val)
{
	if(!temp) return NULL;
	if (val < temp->data)
		return find(temp->left  , val);
	else if(val > temp->data)
		return find(temp->right , val);
	else return temp;
}

int countnode(node<t> *root)
{
	if(!root)
		return 0;
	else
		return root->count + countnode(root->left) + countnode(root->right);
}

int kth_largest(node<t> *root, t val)
{
	int temp = countnode(root -> right) ;
	if(val <= temp)
		return kth_largest(root->right , val);
	else if(val > temp && val <= temp + root->count)
		return root->data;
	else
		return kth_largest(root->left ,(val- temp- root->count) );
}

node<t> *remove(node<t> *T, t x) 								// Deletion
{
	node<t> *temp;
	if (!T) return NULL;
	
	else if (x < T->data) T->left  = remove(T->left, x);
	else if (x > T->data) T->right = remove(T->right, x);
	else if (T->count >1) T->count -= 1;
	else
	{
		if (T->left && T->right)    							// if element has 2 child
		{
			temp = findMin(T->right);
			T->data  = temp->data;
			T->right = remove(T->right, T->data);
		}
		else  													// if element has 1 or no child 
		{
			temp = T;
			if (!T->left) T = T->right;
			else if (!T->right ) T = T->left; 
			delete temp;
		}
	}
	if (!T) return T;
	T = balance(T);
}

void inorder(node<t> *root)
{
	if (!root) return;
	inorder(root->left);
	cout << root->data << "  ";
	inorder(root->right);
}

void getclose(node<t> *ptr, t val, t &min_diff, t &min_diff_key) 
{ 
    if (!ptr)    return ; 

    if (val == ptr->data ) 
    { 
        min_diff_key = val; 
        return; 
    } 
  
    if (abs(ptr->data - val) < min_diff) 
    { 
        min_diff = abs(ptr->data - val); 
        min_diff_key = ptr->data; 
    }   

    if (val < ptr->data) 
        getclose(ptr->left, val, min_diff, min_diff_key); 
    else
        getclose(ptr->right, val, min_diff, min_diff_key); 
} 
  
t getclosestof(node<t> *root, t val) 
{ 
    t min_diff = INT_MAX, min_diff_key ; 
  
    getclose(root, val, min_diff, min_diff_key); 
  
    return min_diff_key; 
} 

int elements_in_range(node<t> *root, t first, t last)
{
    if(!root) return 0;
    if(root->data == last && root->data == first)
      return root->count;
    if(last >= root->data && first <= root->data)
     return root->count + elements_in_range(root->left,first,last)+ elements_in_range(root->right,first,last);
    else if(first>root->data)
      return elements_in_range(root->right,first,last);
    else
      return elements_in_range(root->left,first,last);     
}
};

int main()
{
	int choice, item;
	avl<int> a;
	while (1)
	{
		cout << "**********************************"<< endl;
		cout << "1.Insert Element into the tree" 	<< endl;
		cout << "2.Delete Element into the tree" 	<< endl;
		cout << "3.Search"                   		<< endl;
		cout << "4.Find Occurences of :" 			<< endl;
		cout << "5.Lower Bound"						<< endl;
		cout << "6.Upper Bound"                     << endl;  
		cout << "7.Closest element to :"            << endl;
		cout << "8.Kth Largest element :"           << endl;
		cout << "9.Number of elements between "     << endl;
		cout << "Enter your Choice: " 				<< endl;
		cin >> choice;

		switch (choice)
		{
		case 1:
			cin >> item;
			root = a.insert(root, item);
			break;
		case 2:
			cin >> item;
			root = a.remove(root, item);
			break;
		case 3:
			cin  >> item;
			if(a.find(root,item)) cout<<a.find(root,item)->data;
			else cout<<"Item not there";
			cout << endl;
			break;
		case 4:
			cin>> item;
			cout<<	a.countof(root,item) <<	endl;
			break;
		case 5:
			cin>>item;
			cout<<a.lowerbound(root,item) -> data;
			cout<<endl;
			break;
		case 6:
			cin  >> item;
			cout << a.upperbound(root,item) -> data;
			cout << endl;
			break;
		case 7:
			cin  >> item;
			cout << a.getclosestof(root , item);
			cout << endl;
			break;
		case 8:
			cin  >> item;
			cout << a.kth_largest(root,item);
			cout << endl;
			break;	
		case 9:
			cin  >> item; int item2; cin>>item2;
			cout << a.elements_in_range(root,item,item2);
			cout << endl;
			break;	
		default:
			cout << "Wrong Choice" << endl;
			EXIT_FAILURE;
		}
		if (root == NULL)
		{
			cout << "Tree is Empty" << endl;
			continue;
		}
		a.display(root, 1);
		cout<<endl;
	}
	return 0;
}


