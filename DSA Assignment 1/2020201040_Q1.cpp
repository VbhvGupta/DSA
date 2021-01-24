#include <iostream>
#include<cstring>
#include<cmath>
#include<iomanip>
using namespace std;
 int SIZE = 10000 ;

template <class T>
class stack {
  T *stck;
  int tos;
  int SIZE  ;


public:

  stack(int size)
  {
    if(size<=0)
    {}
    else
    {
    stck = new T[size];
    this->SIZE = size ;
    tos=0;
    }
  }

  bool isempty()
  {
    if(tos==0)
    return true;
    else
    return false ;
  }

  T peek()
  {
    if(tos==0)
    {
      cout<<"Error\n";
      exit(EXIT_FAILURE);
    }
      return(stck[tos-1]);
   }

   void push(T ob)
   {
    if(tos==SIZE)
      {
        cout << "Error\n";
          exit(EXIT_FAILURE);
      }
      stck[tos] = ob;
      tos++;
    }

    T pop()
    {
      if(tos==0) {
        cout << "Error\n";
          exit(EXIT_FAILURE); // return null on empty stack
      }
      tos--;
      return stck[tos];
    }
};

double compute(string expr)
{
  stack<double> ds(expr.length()) ;
  stack<char> cs(expr.length()) ;

  size_t numc=0 , pos = 0;
  bool numflag=false , dflag = false ;


 for(int i=0 ;i < expr.length(); i++)
 {
    if(expr[i]=='.')
    {
      if(numflag==false)
      exit(EXIT_FAILURE) ;
      dflag=true;
      numc++;
      continue ;
    }

    else if(expr[i] >= '0' && expr[i] <= '9')
    {

      if(numflag==false)
      {
        pos = i ;
      }

      numflag=true;
      numc++;
      continue ;
    }

    else
    {

     if(numflag==true)
     {
      if(dflag==false)
      {
        double n = stod ( expr.substr(pos , numc) ) ;
        ds.push(n) ;
        numflag = false ;
        numc = 0;
      }
      if(dflag == true)
      {
        double d = stod ( expr.substr(pos , numc) ) ;
        ds.push(d) ;
        numflag = false ;
        dflag = false;
        numc = 0 ;
      }
    }

     switch ( expr[i] )
     {

                  case '(' : {
                          cs.push(expr[i]);
                        break;
                  }

                  case ')' : {
                    while( cs.peek() != '(' )
                    {
                          double b = ds.pop();
                          double a = ds.pop();

                            char c = cs.pop();
                            switch(c)
                            {
                              case '*' : {
                                            double tx = a*b ;
                                            ds.push(tx);
                                            break;
                                         }
                              case '/' : {
                                            double tx = a/b ;
                                            ds.push(tx);
                                            break ;
                                         }
                              case '%' : {
                                            double tx = fmod(a,b) ;
                                            if(tx<0)
                                            tx = b + tx ;
                                            ds.push(tx);
                                            break;
                                          }
                              case '+' :  {
                                            double tx = a+b;
                                            ds.push(tx);
                                            break;
                                          }
                              case '-' : {
                                            double tx = a-b;
                                            ds.push(tx);
                                            break;
                                         }
                            }
                    }
                    cs.pop();
                    break;
                 }

                  case '*' : {
                    while( cs.peek() != '+' && cs.peek() != '-'  && cs.peek() != '(' )
                    {
                        double b = ds.pop();
                        double a = ds.pop();

                        char c = cs.pop();
                        switch(c)
                        {
                          case '*' : {
                                        double tx = a*b ;
                                        ds.push(tx);
                                        break;
                                     }
                          case '/' : {
                                        double tx = a/b ;
                                        ds.push(tx);
                                        break ;
                                     }
                          case '%' : {
                                        double tx = fmod(a,b) ;
                                        if(tx<0)
                                        tx = b + tx ;
                                        ds.push(tx);
                                        break;
                                      }
                         }
                    }
                    cs.push(expr[i]);
                    break;
                  }

                  case '/' : {
                                while( cs.peek() != '+' && cs.peek() != '-'  && cs.peek() != '(' )
                                {
                                    double b = ds.pop();
                                    double a = ds.pop();

                                    char c = cs.pop();
                                    switch(c)
                                    {
                                      case '*' : {
                                                    double tx = a*b ;
                                                    ds.push(tx);
                                                    break;
                                                 }
                                      case '/' : {
                                                    double tx = a/b ;
                                                    ds.push(tx);
                                                    break ;
                                                 }
                                      case '%' : {
                                                    double tx = fmod(a,b);
                                                    if(tx<0)
                                                    tx = b + tx;
                                                    ds.push(tx);
                                                    break;
                                                  }
                                     }
                                }
                                cs.push(expr[i]);
                                break;
                              }

                  case '%' : {
                                      while( cs.peek() != '+' && cs.peek() != '-'  && cs.peek() != '(' )
                                        {
                                              double b = ds.pop();
                                              double a = ds.pop();

                                              char c = cs.pop();
                                              switch(c)
                                              {
                                                case '*' : {
                                                            double tx = a*b ;
                                                              ds.push(tx);
                                                              break;
                                                             }
                                                case '/' : {
                                                              double tx = a / b ;
                                                              ds.push(tx);
                                                              break ;
                                                             }
                                                case '%' : {
                                                              double tx =fmod(a,b);
                                                              if(tx<0)
                                                              tx=b+tx;
                                                              ds.push(tx);
                                                              break;
                                                            }
                                               }
                                          }
                                            cs.push(expr[i]);
                                            break;
                                          }

                  case '+' : {
                          while ( cs.peek() != '(' )
                          {
                                double b = ds.pop();
                              double a = ds.pop();

                              char c = cs.pop();
                              switch(c)
                              {
                                case '*' : {
                                              double tx = a*b ;
                                              ds.push(tx);
                                              break;
                                           }
                                case '/' : {
                                              double tx = a/b ;
                                              ds.push(tx);
                                              break ;
                                           }
                                case '%' : {
                                              double tx = fmod(a,b);
                                              if(tx<0)
                                              tx=b+tx;
                                              ds.push(tx);
                                              break;
                                            }
                                case '+' :  {
                                              double tx = a+b;
                                              ds.push(tx);
                                              break;
                                            }
                                case '-' : {
                                              double tx = a-b;
                                              ds.push(tx);
                                              break;
                                           }
                              }
                           }
                           cs.push(expr[i]);
                           break;
                         }

                  case '-' :  {
                                       while ( cs.peek() != '(' )
                                       {
                                             double b = ds.pop();
                                           double a = ds.pop();

                                           char c = cs.pop();
                                           switch(c)
                                           {
                                             case '*' : {
                                                           double tx = a*b ;
                                                           ds.push(tx);
                                                           break;
                                                        }
                                             case '/' : {
                                                           double tx = a/b ;
                                                           ds.push(tx);
                                                           break ;
                                                        }
                                             case '%' : {
                                                           double tx = fmod(a,b);
                                                           if(tx<0)
                                                           tx=b+tx;
                                                           ds.push(tx);
                                                           break;
                                                         }
                                             case '+' :  {
                                                           double tx = a+b;
                                                           ds.push(tx);
                                                           break;
                                                         }
                                             case '-' : {
                                                           double tx = a-b;
                                                           ds.push(tx);
                                                           break;
                                                        }
                                           }
                                        }
                                        cs.push(expr[i]);
                                        break;
                                      }

                  default :
                        {
                            cout<< " Invalid input " << endl ;
                            return -1 ;
                        }

          }

    }
  }
double x = ds.pop();
return  x;
}

int main()
{
     cout<< "Enter your Equation   : "  ;

     string s = "(" , ap ;
     getline(cin,ap);
     s.append(ap);
     s.append(")");
     ap.erase();

     double ans = compute(s);

     cout << "Equation evaluates to : " << fixed <<setprecision(5)<< ans<<endl ;

  return 0;
}
