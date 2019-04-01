#include<bits/stdc++.h>
using namespace std;
string gra[10];
int n ;
int check(string stack, int ind)
{
   int lg=gra[ind].length();
   int ls=stack.length();
   int ans=-1;
   int c=0;
   if(lg<=ls)
   for(int i=lg-1,j=0;i>=0;i--,j++)
   {
       if(gra[ind][i]==stack[ls-j-1])
       c++;
   }
   if(c==lg)
     return ind;
   return -1;    
}
int func(string stack,string input,string var)
{
  int li=input.length();
  int ls=stack.length();
  int r1=0,r2=0;
  if(li==0 && ls==1 && stack[0]==var[0])
  {
      return 1;
  }
  for(int i=0;i<n;i++)
   {
        int ans=check(stack,i);
        if(ans!=-1)
        {
            string newstack,newinput;
            newstack="";
            newinput="";
            for(int j=0;j<ls-gra[ans].length();j++)
            {
                newstack+=stack[j];
            }
            newstack+=var[ans];
            newinput=input;
            r1=func(newstack,newinput,var);
            if(r1==1)
            {
                cout<<var[ans]<<" "<<gra[i]<<" "<<newstack<<"\n";
                return 1;
            }        
        }
   }
   if(li!=0)
   {
       string newstack,newinput;
       newstack="";
       newinput="";
       newstack=stack;
       newstack+=input[0];
       newinput=input.substr(1);
       r2=func(newstack,newinput,var);
   }
   return r2;
}
int main()
{
   string stack,input,var;
   cout<<"enter no of grammar\n";
   cin>>n;
   var="";
   stack="";
   char temp;
   for(int i=0;i<n;i++)
   {
       cin>>temp>>gra[i];
       var+=temp;
   }
   cout<<"entert input\n";
   cin>>input;
   cout<<func(stack,input,var);
  return 1;
}

