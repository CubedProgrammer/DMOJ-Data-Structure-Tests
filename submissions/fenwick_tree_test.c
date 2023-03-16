#include<stdio.h>
unsigned arr[100000];
unsigned sumtree[100000], ordtree[100000];
void update(unsigned *tree, unsigned sz, unsigned ind, unsigned val)
{
    for(; ind <= sz; ind += ind & -ind)
        tree[ind - 1] += val;
}
long query(unsigned *tree, unsigned ind)
{
    long sum = 0;
    for(; ind > 0; ind -= ind & -ind)
        sum += tree[ind - 1];
    return sum;
}
int main(int argl, char *argv[])
{
    unsigned m, n;
    unsigned l, r;
    unsigned v;
    long ans;
    char op[3];
    scanf("%u %u", &n, &m);
    for(unsigned i = 0; i < n; ++i)
    {
        scanf("%u", arr + i);
        update(sumtree, n, i + 1, arr[i]);
        update(ordtree, 100000, arr[i], 1);
    }
    for(unsigned i = 0; i < m; ++i)
    {
        scanf("%s", op);
        switch(op[0])
        {
            case'C':
                scanf("%u %u", &l, &r);
                update(sumtree, n, l, r - arr[l - 1]);
                update(ordtree, 100000, r, 1);
                update(ordtree, 100000, arr[l - 1], -1);
                arr[l - 1] = r;
                ans = -1;
                break;
            case'S':
                scanf("%u %u", &l, &r);
                ans = query(sumtree, r);
                if(--l)
                    ans -= query(sumtree, l);
                break;
            case'Q':
                scanf("%u", &v);
                ans = query(ordtree, v);
        }
        if(ans >= 0)
            printf("%li\n", ans);
    }
    return 0;
}
