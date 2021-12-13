#define _CRT_SECURE_NO_WARNINGS 
#include "dijoint_set.h"
#include<stdlib.h>

Member* MAKE_SET(int key)
{
    Member* x;
    x = (Member *)malloc(sizeof(Member));
    x->parent = x;
    x->key = key;
    x->rank = 0;
    return x;
}

bool LINK(Member* x, Member* y)
{
    if(x == y)
        return false;
    if(x->rank > y->rank)
        y->parent = x;
    else
    {
        x->parent = y;
        if(x->rank == y->rank)
            y->rank ++;
    }
    return true;
}

bool UNION(Member* x, Member* y)
{
    return LINK(FIND_SET(x), FIND_SET(y));
}

Member* FIND_SET(Member* x)
{
    if(x->parent != x)
        x->parent = FIND_SET(x->parent);
    return x->parent;
}