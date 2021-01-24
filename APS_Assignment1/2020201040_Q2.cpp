#include <iostream>
#include <string>
#include <bits/stdc++.h>
using namespace std;

class bigInt
{
  public:
  string num;

  public :

  bigInt()
  {

  }

  bigInt(const int number)
  {
    int n=number ;
    while(n)
    {
      num.push_back(n%10);
      n = n/10;
    }
  }

  void operator= (const bigInt &x)
  {
        num = x.num;
  }

  bool operator!= ( bigInt &x)
  {
    trim();
    x.trim();
    if(num == x.num)
      return false ;
    
      return true ;
  }

  bool operator< (bigInt &x)
  {
    return x > *this ;
  }

  bool operator> (bigInt &x)
  {
      trim();
      x.trim();
      int xlen = x.num.length() , len = num.length() ;
      if(len>xlen)
        return true ;
      else if ( len < xlen )
        return false ;
      else
      {
        for(int i=len-1 ; i >= 0 ; i-- )
        {
          if(num[i] == x.num[i]) continue ;
          if(num[i] > x.num[i]) return true ;
          if(num[i] < x.num[i]) return false ;
        }
      }
      return false ;
  }

  bigInt operator- ( bigInt &x)
 { 
    trim();
    x.trim();
    bigInt result ;
         for (int i = 0, borrow = 0; i < (int)num.length()  ; ++i )
        {
            if( i == (int)x.num.size())
                x.num.push_back(0);

            int n =0;
            n =  num[i] - x.num[i] - borrow ;
           if(n<0)
            {
              borrow=1;
              n=10+n;
              result.num.push_back(n);          
            }
            else
            {
              result.num.push_back(n);
              borrow=0;
              n=0;
            }
        }
        x.trim();
        return result;
  }

  void trim()
  {
     int len = num.length() , count=0;
     for(int i = len-1 ; i >= 0 ; --i)
     {
       if(num[i]!=0)
       break ;
       else
        ++count ;
     }
     if (count>0)
      num.resize(len-count) ;
  }

  bigInt operator*(const bigInt &x)
  {
    bigInt res ;
    
    int len1 = num.size(); 
    int len2 = x.num.size(); 
    if (len1 == 0 || len2 == 0) 
    {
     res.num.push_back(0);
     return res; 
    }
    int result[len1 + len2] = {0}; 
   
    int i_n1 = 0;  
    int i_n2 = 0;  

    for (int i=0; i < len1; i++) 
    { 
        int carry = 0; 
        int n1 = num[i]; 
  
        i_n2 = 0;  
                   
        for (int j=0; j<len2; j++) 
        { 
            int n2 = x.num[j] ; 
  
            int sum = n1*n2 + result[i_n1 + i_n2] + carry; 
  
            carry = sum/10; 
  
            result[i_n1 + i_n2] = sum % 10; 
  
            i_n2++; 
        } 
        if (carry > 0) 
            result[i_n1 + i_n2] += carry; 
        i_n1++; 
    }
    int i = len1 + len2 - 1; 
    while (i>=0 && result[i] == 0) 
    i--; 
  
    if (i == -1) 
    {
      res.num.push_back(0);
      return res ; 
    }
     
    while (i >= 0) 
    res.num += result[i--]; 
    reverse(res.num.begin() , res.num.end());
    return res;

  }

  bigInt operator+(bigInt &x) 
  {
     bigInt result;
         for (int i = 0, carry = 0; i < (int)max( x.num.length() , num.length() ) || carry ; ++i )
        {
          
            if( i == (int)x.num.size())
                x.num.push_back(0);
           
            int n =0;
          if( i < (int)num.size() )
          {
            n = carry + num[i] + x.num[i] ;
           if(n>=10)
            {
              n=n%10;
              result.num.push_back(n);
              carry=1;
              n=0;
            }
            else
            {
              result.num.push_back(n);
              carry=0;
              n=0;
            }
          }
          else
          {
            n = carry + x.num[i] ;
            if(n>=10)
            {
              n=n%10;
              result.num.push_back(n);
              carry=1;
              n=0;
            }
            else
            {
            result.num.push_back(n);
            carry=0;
            n=0;
            }
          }
        }
      x.trim();
      trim();
        return result;
  }

  friend ostream& operator << (ostream &os , bigInt &x)
  {
    os << ( x.num.empty() ? 0 : x.to_string()) ;
    return os ;
  }

  string to_string()
  {
    for(size_t i= 0 ; i < this->num.length() ; i++ )
    num[i]+='0';
    reverse(this->num.begin(), this->num.end());
    return num;
  }

  friend istream& operator >> (istream &is , bigInt &x)
  {
    string str ;
    is >> str ;
    x.read(str) ;
    return is ;
  }

  void read(string &str)
  {
    size_t pos = 0;
    while( pos < str.length() && (str[pos]=='-'|| str[pos] == '+'))
     {
      if(str[pos] == '-')
        ++pos ;
     }
    for( ; pos < str.length() ; ++pos )
      {
        this->num.push_back(str[pos] - '0');
      }
      reverse(this->num.begin() , this->num.end());
  }
};

bigInt factorial(int n)
{
  bigInt ans(1) ;
  for(int i=2 ; i <= n ; i++)
  {
    bigInt temp(i);
    ans = ans * temp ;
  }
  return ans;
}

bigInt pow(bigInt base ,int exp)
{
  bigInt ans(1);
  while(exp>0)
  {
    if(exp & 1)
      {
        ans = base * ans ;
      }
    exp = exp >> 1;
    base = base * base ;
  }
  return ans;
}

bigInt gcd(bigInt a , bigInt b)
{	
  bigInt result ;
  if(a.iszero() || b.iszero())
  {
  	result.num.push_back(0);
  	return result;
  }
  while(a!=b)
  {
    if(a>b) {a=a-b; }
    else if(b>a)  {b=b-a ;}
  }
  result.num=a.num;
  return result;
}

int main()
{
 int q;
 cin>>q;
 while(q--)
 {
   int t;
   cin>>t;
   switch(t)
   {
     case 1 :    {
                   bigInt b ,c; int e;
                   cin>>b; cin>>e; 
                   c= pow(b,e); 
                   cout<<c;
                   break;
                 }
     case 2 :    {
                   bigInt a,b,c;
                   cin>>a;
                   cin>>b;
                   c=gcd(a,b); 
                   cout<<c;
                   break;
                 } 
     case 3 :    {
                   int a; cin>>a;
                   bigInt c;
                   c=factorial(a);
                   cout<<c;
                   break; 
                 }                      

   }
   cout<<endl;
 }

return 0;
}
