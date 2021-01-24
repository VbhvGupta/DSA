#include<iostream>
#include<bits/stdc++.h>
using namespace std ;

class deq
{
	T *arr;
	int front , end;
	int len, noe;

	public :

	 deq()
	{
		arr = new T[10];
		len=10;
		front=-1;
		end=-1;
		noe=0;
	}

	deq(int n , T x)
	{
		if(n<=0){}
		else
		{
			arr = new T[n] ;
			len = n;
			for(int i=0 ; i < len ; i++)
			{
				arr[i]=x;
			}
			front = 0 ;
			end = n-1;
			noe=n;
		}
	}
	
	void push_back(T x)
	{
		if(( front == 0 && end == len-1) || front == end+1) //full
		{
    	   T *temp ;
    	   temp = new T[2*len];
    	   for(int i=0;i<len;i++)
    	   {
    	   	temp[i]=arr[(front+i)%len];
    	   }
    	   delete[] arr ;
    	   arr = temp;
    	   front = 0;
    	   end = len-1;
    	   len *= 2 ;
		}

		if(front == -1)  //empty
    	{ 
           front = 0; 
           end  = 0; 
    	}

    	else if(end == len-1)
    		end = 0;

    	else
    		end = end+1;
 	    	
 	    	arr[end] = x ;
 	    	++noe;
	}
	void push_front(T x)
	{
		if(( front == 0 && end == len-1) || front == end+1) //full
		{
			 T *temp ;
    	   temp = new T[2*len];
    	   for(int i=0;i<len;i++)
    	   {
    	   	temp[i]=arr[(front+i)%len];
    	   }
    	   delete[] arr ;
    	   arr = temp;
    	   front = 0;
    	   end = len-1;
    	   len *= 2 ;			
		}
		if(front == -1) //empty
		{
			front =0;
			end=0;
		}
		
		else if(front ==0 )
			front = len-1 ;
		
		else
			front = front -1 ;

		arr[front]=x;
		++noe;
	}

	T pop_back()
	{
		if(front == -1) exit(EXIT_FAILURE) ; 	//exit if popping from a empty deque
		T temp ;
		temp = arr[end]; 
		if(end == front )				 		// one element only
			front = -1 , end = -1; 				// now deque is empty
		else if (end > 0)
			end -= 1 ;
		    --noe;
		return temp;
	}
	T pop_front()
	{
		if(front == -1) exit(EXIT_FAILURE) ; //exit if popping from a empty deque
		T temp ;
		temp = arr[front]; 
		if(front==end)						 // one element only
		 front = -1 , end = -1 ;             // now deque is empty
		else if (front >0)
			front = (front + 1 ) % len ;					
		--noe;
		return temp ;
	}
	T get_front()
	{
		return arr[front];
	}
	T get_back()
	{
		return arr[end];
	}
	bool empty()
	{		
		return ( front == -1 );
	}
	int size()
	{
		if(len<0)
		exit(EXIT_FAILURE);
		return noe;	
	}
	void resize(int n ,T x)
	{
		T *temp;
		temp = new T[n];
		if(n<=size())
		{
			for(int i=0; i< n ; i++)
			{
				temp[i] = arr[(front+i)%len] ;
			}			
		}
		if(n>size())
			{
				for (int i = 0; i < size(); ++i)
			  {
				temp[i] = arr[(front+i)%len] ;				 
			  }
			    for(int i=size() ; i<n ; i++)
			  {
				temp[i]=x;
			  }
			}  	
			delete[] arr;
			arr = temp;
			len = n;
			noe=n;
			front=0;
			end=n-1;
	}

	void clear()
	{
		delete[] arr ;
		front=-1;
		end=-1;
		noe=0;
		len=-1;
	}

	void display()
	{
		for(int i=0 ; i< size() ; i++)
		{
			cout<<arr[(front+i)%len]<<" ";
		}
	}

	T& operator[] (int index)
	{
		if(index >= len || index < 0 ) exit(EXIT_FAILURE);
		return (arr[ (front+index)%len ]) ;
	}
};

int main()
{	
	int q ;
	cin>>q;
	deq<int> dq;
	while(q)
	{
	int t;
	cin>>t;
	switch(t)
	{
		case 1 :{ int x; cin>>x; dq.push_front(x); dq.display(); break;}
		case 2 :{ dq.pop_front(); dq.display();                  break;}
		case 3 :{ int x; cin>>x; dq.push_back(x); dq.display();  break;}
		case 4 :{ dq.pop_back(); dq.display();                   break;}
		case 5 :{ dq=deq();                                      break;}
		case 6 :{ int n,x ; cin>>n>>x; dq=deq(n,x);              break;}
		case 7 :{ cout<<dq.get_front();                          break;}
		case 8 :{ cout<<dq.get_back();                           break;}
		case 9 :{ cout<<dq.empty();                              break;}
		case 10:{ cout<<dq.size();                               break;}
		case 11:{ int n,x; cin>>n>>x;dq.resize(n,x);dq.display();break;}
		case 12:{ dq.clear();                                    break;}
		case 13:{ int n; cin>>n; cout<<dq[n];                    break;}
		case 14:{ dq.display();                                  break;}
	}
	if(t!=5 && t!=6 && t!=12)
	cout<<endl;
	--q;
	}
	return 0 ;
}