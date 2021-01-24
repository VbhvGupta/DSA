#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define BKT 10

template <class T, class U>
class Unordered_map
{
  public:
    ll bucket = BKT;

    class node
    {
      public:
        T key;
        U value;
        node *next;
        node(){}
        node(T key , U value):key(key),value(value){next=NULL;}
    }*my_map[BKT]={NULL};

    ll CalcHash(T key)
    {
        ostringstream os;
        os<<key;
        string s = os.str();
        ll hash_val = 1315423911;
        ll i =0;
        while(i < s.length() )
        {
          // hash Function
          hash_val= ((hash_val ^ ((hash_val<<5)+ s[i]+ (hash_val>>2)))% BKT)%BKT;
          ++i;
        }
        return hash_val;
    }

    void insert(T key , U value)
    {
        ll index = CalcHash(key);
        node *head = my_map[index];
        if(!head)
        {
            node *temp = new node(key,value);
            my_map[index] = temp;
            return ;
        }
        else if(! head->next)
        {
            if(key == head->key) return;
            else
            {
                node *temp = new node(key,value);
                head->next = temp;
                return;
            }
        }
        else
        {
            node *temp = head;
            while(temp->next)
            {
                if(key == temp->key)
                    return;
                else
                    temp = temp->next;
            }
            if(key == temp->key) return;
            node *t = new node(key,value);
            temp->next = t ;
            return;
        }
        return;
    }

    void display()
    {
        for(ll i =0; i< BKT ; ++i)
        {
            cout<<"\n"<<i<<":";
            node *st = my_map[i];
            while(st)
            {
                cout << "=>[" << st->key << "=" << st->value << "]";
                st = st->next;
            }
            cout<<"\n";
        }
    }

    U& operator[] (T key)
    {
    	ll index = CalcHash(key);
    	node *head = my_map[index];
    	if(!head)
        {
            U var;
            insert(key,var);
            head = my_map[index];
        }
    	else if(head)
    	{
    		node *temp = head;
    		while(temp)
    		{
    			if(key == temp->key)
    				return temp->value;
    			else
    				temp = temp->next;
    		}
    		EXIT_FAILURE;
    	}
    }  

    bool find(T key)
    {
        ll index = CalcHash(key);
        node *head = my_map[index];
        if(!head) return false ;
        else
        {
            node *temp = head;
            while(temp)
            {
                if(key == temp->key)
                    return true ;
                else
                    temp = temp->next;
            }
            return false;
        }
    }

    void erase(T key)
    {
        ll index = CalcHash(key);
        node *head = my_map[index];
        node *temp = head, *prev = NULL;
        if (!head)
        {
            cout << "No Data Found" << endl;
            return;
        }
        else
        {
            if (key == head->key)
            {
                temp = head;
                head = head->next;
                my_map[index] = head;
                free(temp);
                return;
            }
            while (temp->next && !(key == temp->key) )
            {
                prev = temp;
                temp = temp->next;
            }
            if ( !temp->next && !(key == temp->key) )
            {
                cout << "No Data Found" << endl;
                return;
            }
            else
            {
                prev->next = temp->next;
                free(temp);
            }
        }
        return;
    }

};

int main()
{
    string s,val;
    Unordered_map<string,string> um;
    while(1)
    {

        cout << "**********************************"<< endl;
        cout << "1.Insert "                         << endl;
        cout << "2.Erase  "                         << endl;
        cout << "3.Find  "                          << endl;
        cout << "4.map[key]"                        << endl;
        cout << "Enter your Choice: "               << endl;

        int c;
        cin >> c;
        switch(c)
        {
             case 1: 
                cin >> s;
                cin >> val;
                um.insert(s,val);
                cout<<endl;
                break;

             case 2:
                cin >> s;
                um.erase(s);
                cout<<endl;
                break;

             case 3:
                cin  >> s;
                um.find(s) ? cout<<"true" : cout<<"false"; 
                cout<<endl;
                break;                

             case 4:
             	cin  >> s;
                //cin  >> val;
                cout << endl;
             	//um[s] = val;   
                cout <<"map["<<s<<"] = "<< um[s];
                cout << endl;
                break;
        }
        um.display();
        cout<<"\n\n";
    }
    return 0;
}