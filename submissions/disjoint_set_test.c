#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
struct __dsu
{   size_t size;
    size_t*id,*sz;   };
struct __dsu*mkdsu(size_t size)
{   struct __dsu dsu; dsu.size=size;
    dsu.id=(size_t*)malloc(size*sizeof(size_t));
    dsu.sz=(size_t*)malloc(size*sizeof(size_t));
    for(size_t i=0;i<size;i++)
    {   dsu.id[i]=i,dsu.sz[i]=1;   }
    struct __dsu*ptr=(struct __dsu*)malloc(sizeof(struct __dsu));
    *ptr=dsu; return ptr;   }
size_t dsu_fnd_set(struct __dsu*dsu,size_t n)
{   size_t rt=n;
    while(rt!=dsu->id[rt])
        rt=dsu->id[rt];
    return dsu->id[n]=rt;   }
void dsu_mrg_sets(struct __dsu*dsu,size_t u,size_t v)
{   size_t x=dsu_fnd_set(dsu,u),y=dsu_fnd_set(dsu,v);
    if(dsu->sz[x]<dsu->sz[y])
        dsu->sz[y]+=dsu->sz[x],dsu->id[x]=y;
    else
        dsu->sz[x]+=dsu->sz[y],dsu->id[y]=x;   }
bool from_same_set(struct __dsu*dsu,size_t u,size_t v)
{   return dsu_fnd_set(dsu,u)==dsu_fnd_set(dsu,v);   }
typedef struct __dsu*disjoint_set_union;

bool used[1000000];
int main(int argl,char**argv)
{
    unsigned int m=0,n=0;
    scanf("%d %d",&n,&m);
    unsigned int x=0,y=0;
    disjoint_set_union myunion=mkdsu(n);
    unsigned int usedcnt=0;
    for(unsigned int i=0;i<m;i++)
    {
        scanf("%d %d",&x,&y); --x,--y;
        if(!from_same_set(myunion,x,y))
        {   dsu_mrg_sets(myunion,x,y);used[i]=true;
            usedcnt++;   }

    }
    if(usedcnt!=n-1)
        printf("Disconnected Graph\n");
    else
        for(unsigned int i=0;i<m;i++)
        {   if(used[i])printf("%d\n",i+1);   }
    return 0;
}