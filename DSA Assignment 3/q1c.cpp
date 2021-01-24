#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
void fast()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}
  
string longestPalindrome(string s) 
{

    int len=s.length();
    
    int tmplen=2*len+3;

    char tmp[tmplen];
    int  Len[tmplen];
    
    tmp[0]='@';

    for(int i=1;i<2*len;i+=2)
    {
        tmp[i]='~';
        tmp[i+1]=s[i/2];
    }

    tmp[2*len+1]='~';                   
    tmp[2*len+2]='$';                       //init the string as @~a~b~a~c~a~$ 

    //cout<<tmp;
    int mx=0,ans=0,po=0,pos=0;
    
    for(int i=1;i<tmplen;i++)
    {
        if(mx>i)
        {
          Len[i]=min(mx-i,Len[2*po-i]);
        }
        else
            Len[i]=1;
        while(tmp[i-Len[i]]==tmp[i+Len[i]])
        {
             Len[i]++;
        }
        if(i+Len[i]>mx)
        {
            po=i;
            mx=i+Len[i];
        }
        if(Len[i]>ans)
        {
            ans=Len[i];
            pos=i;
        }
    }
    string result(ans-1,'~');int j=0;
    for(int i=pos-ans+1;i<=pos+ans-1;i++)
    {
        if(tmp[i]!='~')
        {
            result[j]=tmp[i];
            j++;
        }
    }
    return result;
}


int main() 
{
    fast();
    string word;
    cin >> word;
    
    string mpl = longestPalindrome(word);
    cout << mpl;
    return 0;
}