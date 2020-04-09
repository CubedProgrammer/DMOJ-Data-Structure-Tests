#ifndef DMOJ_DATA_STRUCTURE_TESTS_DISJOINT_SET_UNION_H
#define DMOJ_DATA_STRUCTURE_TESTS_DISJOINT_SET_UNION_H
#include<stdbool.h>
#include<stdlib.h>
size_t dsu_fnd_set(struct __dsu*dsu,size_t n);
void dsu_mrg_sets(struct __dsu*dsu,size_t u,size_t v);
bool from_same_set(struct __dsu*dsu,size_t u,size_t v);
struct __dsu
{   size_t size;
#ifdef __cplusplus
    size_t dsu_fnd_set(size_t n);
    void dsu_mrg_sets(size_t u,size_t v);
    bool from_same_set(size_t u,size_t v);
#else
    size_t(*dsu_fnd_set)(struct __dsu*dsu,size_t n);
    void(*dsu_mrg_sets)(struct __dsu*dsu,size_t u,size_t v);
    bool(*from_same_set)(struct __dsu*dsu,size_t u,size_t v);
#endif
    size_t*id,*sz;   };
struct __dsu*mkdsu(size_t size)
{   struct __dsu dsu; dsu.size=size;
    dsu.id=(size_t*)malloc(size*sizeof(size_t));
    dsu.sz=(size_t*)malloc(size*sizeof(size_t));
    for(size_t i=0;i<size;i++)
    {   dsu.id[i]=i,dsu.sz[i]=1;   }
    dsu.dsu_fnd_set=&dsu_find_set;
    dsu.dsu_mrg_sets=&dsu_mrg_sets;
    dsu.from_same_set=&from_same_set;
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
#ifdef __cplusplus
typedef __dsu disjoint_set_union;
#else
typedef struct __dsu*disjoint_set_union;
#endif
#endif//DMOJ_DATA_STRUCTURE_TESTS_DISJOINT_SET_UNION_H
