#include<stdio.h>
#include<stdlib.h>
#define height_of_ostn(ostn)(ostn==NULL?0:ostn->height)
#define size_of_ostn(ostn)(ostn==NULL?0:ostn->size)
#define min(__x__,__y__)((__x__)<(__y__)?(__x__):(__y__))
#define max(__x__,__y__)((__x__)>(__y__)?(__x__):(__y__))
#define OST_INF 999999999
struct __ostn
{   struct __ostn*up;
    struct __ostn*left,*right;
    int val,id;
    size_t height,size;   };
struct __ost
{   struct __ostn*rt;size_t size;
    int id;   };
struct __ostn*mkostn(int val,int id,struct __ostn*up,struct __ostn*left,struct __ostn*right,size_t height,size_t size)
{   struct __ostn*node=(struct __ostn*)malloc(sizeof(struct __ostn));
    node->val=val; node->id=id;
    node->left=left; node->right=right;
    node->height=height; node->size=size;
    node->up=up; return node;   }
struct __ost*mkost()
{   struct __ost*ost=(struct __ost*)malloc(sizeof(struct __ost));
    ost->rt=NULL; ost->size=0;
    ost->id=((int)ost)*46369669; return ost;   }
void stat_update_ost(struct __ostn*node)
{   if(node==NULL)
        return;
    node->height=max(height_of_ostn(node->left),height_of_ostn(node->right))+1;
    node->size=size_of_ostn(node->left)+size_of_ostn(node->right)+1;
    stat_update_ost(node->up);   }
void ccw(struct __ost*ost,struct __ostn*node)
{   struct __ostn*tmp=node->right;
    node->right=node->right->left;
    tmp->up=node->up;
    tmp->left=node;
    if(node->right!=NULL)
        node->right->up=node;
    node->up=tmp;
    node->height=max(height_of_ostn(node->left),height_of_ostn(node->right))+1;
    node->size=size_of_ostn(node->left)+size_of_ostn(node->right)+1;
    tmp->height=max(height_of_ostn(tmp->left),height_of_ostn(tmp->right))+1;
    tmp->size=size_of_ostn(tmp->left)+size_of_ostn(tmp->right)+1;
    if(tmp->up==NULL)
        ost->rt=tmp;
    else
    {   if(tmp->up->left==node)
            tmp->up->left=tmp;
        else
            tmp->up->right=tmp;   }
    stat_update_ost(tmp);   }
void cw(struct __ost*ost,struct __ostn*node)
{   struct __ostn*tmp=node->left;
    node->left=node->left->right;
    tmp->up=node->up;
    tmp->right=node;
    if(node->left!=NULL)
        node->left->up=node;
    node->up=tmp;
    node->height=max(height_of_ostn(node->left),height_of_ostn(node->right))+1;
    node->size=size_of_ostn(node->left)+size_of_ostn(node->right)+1;
    tmp->height=max(height_of_ostn(tmp->left),height_of_ostn(tmp->right))+1;
    tmp->size=size_of_ostn(tmp->left)+size_of_ostn(tmp->right)+1;
    if(tmp->up==NULL)
        ost->rt=tmp;
    else
    {   if(tmp->up->left==node)
            tmp->up->left=tmp;
        else
            tmp->up->right=tmp;   }
    stat_update_ost(tmp);   }
void fix_ost_node(struct __ost*ost,struct __ostn*ostn)
{   if(ostn==NULL)
        return;
    size_t lh=height_of_ostn(ostn->left),rh=height_of_ostn(ostn->right);
    struct __ostn*p=ostn->up;
    if(rh+2<=lh)
    {   lh=height_of_ostn(ostn->left->left),rh=height_of_ostn(ostn->left->right);
        if(lh<rh)
            ccw(ost,ostn->left);
        cw(ost,ostn);   }
    else if(lh+2<=rh)
    {   lh=height_of_ostn(ostn->right->left),rh=height_of_ostn(ostn->right->right);
        if(rh<lh)
            cw(ost,ostn->right);
        ccw(ost,ostn);   }
    fix_ost_node(ost,p);   }
void ost_ins_val(struct __ost*ost,int val)
{   struct __ostn*node=ost->rt;
    if(node==NULL)
    {   ost->rt=mkostn(val,ost->id,NULL,NULL,NULL,1,1); ++ost->size;
        return;   }
    __begin:
    if(val<node->val)
    {   if(node->left!=NULL)
        {   node=node->left;goto __begin;   }
        node->left=mkostn(val,ost->id,node,NULL,NULL,1,1);   }
    else if(val>node->val)
    {   if(node->right!=NULL)
        {   node=node->right;goto __begin;   }
        node->right=mkostn(val,ost->id,node,NULL,NULL,1,1);   }
    else
    {   int id=ost->id+1;
        __dupbegin:
        if(val<node->val||val==node->val&&id<node->id)
        {   if(node->left!=NULL)
            {node=node->left;goto __dupbegin;}
            node->left=mkostn(val,id,node,NULL,NULL,1,1);   }
        else if(val>node->val||val==node->val&&id>node->id)
        {   if(node->right!=NULL)
            {node=node->right;goto __dupbegin;}
            node->right=mkostn(val,id,node,NULL,NULL,1,1);   }
        else
        {   id++;goto __dupbegin;   }}
    stat_update_ost(node);
    fix_ost_node(ost,node);
    ++ost->size;
    ++ost->id;   }
void ost_del_node(struct __ost*ost,struct __ostn*node)
{   if(ost->size==1&&node->up==NULL)
    {   free(ost->rt);ost->rt=NULL;   }
    else if(node->left!=NULL&&node->right!=NULL)
    {   struct __ostn*tmp = node->right;
        while (tmp->left != NULL)
            tmp = tmp->left;
        int tmpv=node->val,tmpid=node->id;
        node->val=tmp->val,node->id=tmp->id;
        tmp->val=tmpv,tmp->id=tmpid;
        ost_del_node(ost,tmp); return;   }
    else if(node->left==NULL)
    {   struct __ostn*child=node->right,*p=node->up;
        if(p==NULL)
        {   free(ost->rt);ost->rt=child;
            child->up=NULL;   }
        else if(p->left==node)
        {   free(p->left);p->left=child;
            if(child!=NULL)child->up=p;   }
        else
        {   free(p->right);p->right=child;
            if(child!=NULL)child->up=p;   }
        stat_update_ost(p); fix_ost_node(ost,p);   }
    else if(node->right==NULL)
    {   struct __ostn*child=node->left,*p=node->up;
        if(p==NULL)
        {   free(ost->rt);ost->rt=child;
            child->up=NULL;   }
        else if(p->left==node)
        {   free(p->left);p->left=child;
            child->up=p;   }
        else
        {   free(p->right);p->right=child;
            child->up=p;   }
        stat_update_ost(p); fix_ost_node(ost,p);   }
    --ost->size;   }
void ost_del_val(struct __ost*ost,int val)
{   if(ost->size==0)
        return;
    struct __ostn*node=ost->rt;
    __begin:
    if(val<node->val)
    {   node=node->left;
        if(node!=NULL)
            goto __begin;   }
    else if(val>node->val)
    {   node=node->right;
        if(node!=NULL)
            goto __begin;   }
    else if(node!=NULL)
        ost_del_node(ost,node);   }
int ost_select_itemr(struct __ostn*node,size_t p)
{   size_t ls=size_of_ostn(node->left);
    if(p<ls)
        return ost_select_itemr(node->left,p);
    else if(p>ls)
        return ost_select_itemr(node->right,p-ls-1);
    else
        return node->val;   }
int ost_select_item(struct __ost*ost,size_t p)
{   return ost_select_itemr(ost->rt,p);   }
size_t ost_rnk_itemr(struct __ostn*node,int val)
{   if(node==NULL)
        return OST_INF;
    if(val<node->val)
        return ost_rnk_itemr(node->left,val);
    if(val>node->val)
        return size_of_ostn(node->left)+1+ost_rnk_itemr(node->right,val);
    size_t less=ost_rnk_itemr(node->left,val);
    return min(less,size_of_ostn(node->left));   }
size_t ost_rnk_item(struct __ost*ost,int val)
{   return ost_rnk_itemr(ost->rt,val);   }
void ost_inorder_travr(struct __ostn*node,struct __ostn*end,FILE*f)
{   if(node==NULL)
        return;
    ost_inorder_travr(node->left,end,f); fprintf(f,"%d",node->val);
    if(node==end)
        fprintf(f,"\n");
    else
        fprintf(f," ");
    ost_inorder_travr(node->right,end,f);   }
void ost_inorder_trav(struct __ost*ost,FILE*f)
{   if(ost->size==0)
        return;
    struct __ostn*node=ost->rt;
    while(node->right!=NULL)
        node=node->right;
    ost_inorder_travr(ost->rt,node,f);   }
typedef struct __ost*order_statistic_tree;

#define INSERT 'I'
#define REMOVE 'R'
#define SELECT 'S'
#define RANK 'L'
char cmd[2];
int main(int argl,char**argv)
{
    order_statistic_tree tree=mkost();
    unsigned int m=0,n=0;
    size_t rnk=0;
    int lastans=0,x=0;
    scanf("%u %u",&n,&m);
    for(unsigned int i=0;i<n;i++)
    {
        scanf("%d",&x);
        ost_ins_val(tree,x);
    }
    for(unsigned int i=0;i<m;i++)
    {
        scanf("%s %d",cmd,&x);
        if(cmd[0]==INSERT)
        {
            ost_ins_val(tree,x^lastans);
        }
        else if(cmd[0]==REMOVE)
        {
            ost_del_val(tree,x^lastans);
        }
        else if(cmd[0]==SELECT)
        {
            printf("%d\n",lastans=ost_select_item(tree,(x^lastans)-1));
        }
        else if(cmd[0]==RANK)
        {
            rnk=ost_rnk_item(tree,x^lastans);
            printf("%d\n",lastans=rnk>=tree->size?-1:rnk+1);
        }
    }
    ost_inorder_trav(tree,stdout);
    return 0;
}