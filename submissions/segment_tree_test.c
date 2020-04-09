#include<stdio.h>
#include<stdlib.h>
#define min(__x__,__y__)((__x__)<(__y__)?(__x__):(__y__))
size_t lbound[270000],rbound[270000];
size_t idx[270000];
struct segtree
{   unsigned int*stuff; size_t size;
    unsigned int(*func)(unsigned int,unsigned int);   };
struct segtree mksegtree(size_t size,unsigned int(*func)(unsigned int,unsigned int))
{   struct segtree tree; tree.func=func;
    tree.stuff=(unsigned int*)malloc(size*4*sizeof(unsigned int));
    tree.size=size*4; return tree;   }
void build_segment_tree(struct segtree tree,unsigned int*arr,size_t size,size_t id)
{   size_t d=0;
    lbound[d]=0,rbound[d]=size;
    idx[d]=0; d=1;
    size_t lb=0,rb=0;
    size_t ind=0;
    while(d>0)
    {   lb=lbound[d-1],rb=rbound[d-1];
        d--;
        if(lb+1<rb)
        {   lbound[d]=rb; rbound[d]=lbound[d+1]=lb+rb+1>>1;
            rbound[d+1]=rb;
            idx[d+1]=idx[d]+1<<1;
            idx[d]<<=1,idx[d]++;
            d+=2;   }}
    for(unsigned int i=0;i<size*4;i++)
    {   tree.stuff[i]=id;   }
    for(unsigned int i=0;i<size;i++)
    {   tree.stuff[idx[i]]=arr[i];   }
    while(size>1)
    {   d=0;
        for(unsigned int i=0;i<size;i++)
        {   if((i&1)==0)
                d++;
            tree.stuff[idx[i]-1>>1]=tree.func(tree.stuff[idx[i]-1>>1],tree.stuff[idx[i]]);
            idx[d-1]=idx[i]-1>>1;   }
        size=d;}}
void update(struct segtree tree,unsigned int*arr,size_t size,size_t ind,size_t val)
{   size_t node=0;
    size_t l=0,r=size;
    while(l+1<r)
    {if(ind<l+r+1>>1)
        {   node=(node<<1)+1; r=l+r+1>>1;   }
        else
        {   node=node+1<<1; l=l+r+1>>1;   }
    }
    tree.stuff[node]=val;
    node=node-1>>1;
    while(node>0)
    {   tree.stuff[node]=tree.func(tree.stuff[(node<<1)+1],tree.stuff[node+1<<1]); node=node-1>>1;   }}
unsigned int query(struct segtree tree,unsigned int*arr,size_t size,size_t l,size_t r,unsigned int id)
{if(r-l<30)
    {   unsigned int ans=id;
        for(unsigned int i=l;i<r;i++)
            ans=tree.func(ans,arr[i]);
        return ans;   }
    else
    {}
}
unsigned int gcd(unsigned int x,unsigned int y)
{   if(y==0)
        return x;
    return gcd(y,x%y);   }
unsigned int minui(unsigned int x,unsigned int y)
{   return min(x,y);   }

int main(int argl,char**argv)
{
    return 0;
}