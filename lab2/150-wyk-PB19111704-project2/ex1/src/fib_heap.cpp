#define _CRT_SECURE_NO_WARNINGS 
#include "fib_heap.h"
#include<stdlib.h>
#include<iostream>
using namespace std;
#define OUT cout
FIB_NODE* KEY_TO_NODE[1001];//用于存储每个key对应的FIB_NODE地址

FIB_NODE* SEARCH_KEY(int key)
{
    return KEY_TO_NODE[key];
}

FIB_HEAP* MAKE_HEAP(void)
{
    FIB_HEAP* H;
    H = (struct FIB_HEAP*)malloc(sizeof(FIB_HEAP));
    H->min = NULL;
    H->n = 0;
    return H;
}
void FIB_NODE_LINK(FIB_NODE* x, FIB_NODE* y)
{
    if(x == NULL)
        return;
    else if(y == NULL)
    {
        y = x;
    }
    else
    {
        FIB_NODE* last = x->left_sibling;
        FIB_NODE* first = x;   
        last->right_sibling = y->right_sibling;
        first->left_sibling = y;
        y->right_sibling->left_sibling = last;
        y->right_sibling = first;
    }
    
}
int INSERT(FIB_HEAP* H, int key)
{
    FIB_NODE* x = (struct FIB_NODE* )malloc(sizeof(FIB_NODE));

    KEY_TO_NODE[key] = x;
    x->degree = 0;
    x->parent = NULL;
    x->child = NULL;
    x->mark = false;
    x->key = key;
    if(H->min == NULL)
    {
        H->min = x;
        x->left_sibling = x;
        x->right_sibling = x;
    }
    else
    {
        x->right_sibling = H->min->right_sibling;
        H->min->right_sibling = x;
        x->left_sibling = H->min;
        x->right_sibling->left_sibling = x;
        if(x->key < H->min->key)
            H->min = x;
    }
    H->n = H->n + 1;
    return H->n;
}

int MINIMUM(FIB_HEAP* H)
{
    return H->min->key;
}

FIB_NODE* EXTRACT_MIN(FIB_HEAP* H)
{
    FIB_NODE* z = H->min;
    if(z != NULL)
    {
        if(z->child != NULL)
        {
            FIB_NODE* child_last = z->child->left_sibling;
            FIB_NODE* child_first = z->child;   
            child_first->left_sibling = z;
            child_last->right_sibling = z->right_sibling;
            z->right_sibling->left_sibling = child_last;
            z->right_sibling = child_first;
            // FIB_NODE_LINK(z->child, z);
            z->child = NULL;
            for(FIB_NODE* i = child_first; i != child_last; i = i->right_sibling)
            {
                i->parent = NULL;
            }
        }
        z->left_sibling->right_sibling = z->right_sibling;
        z->right_sibling->left_sibling = z->left_sibling;
        if(z == z->right_sibling)
            H->min = NULL;
        else  
        {
            H->min = z->right_sibling;
            CONSOLIDATE(H);
        }
        H->n = H->n - 1;
    }
    return z;
}

FIB_HEAP* UNION(FIB_HEAP* H1, FIB_HEAP* H2)
{
    
    
    FIB_HEAP* H = MAKE_HEAP();
    // OUT << "H1n\t" << H1->n << "\n";
    // OUT << "H2n\t" << H2->n << "\n";
    H->min = H1->min;
    // FIB_NODE_LINK(H2->min, H->min);
    if(!H->min)
        H->min = H2->min;
    else if(!H2->min);
    else
    {
        FIB_NODE* last = H2->min->left_sibling;
        FIB_NODE* first = H2->min;   
        last->right_sibling = H->min->right_sibling;
        first->left_sibling = H->min;
        H->min->right_sibling->left_sibling = last;
        H->min->right_sibling = first;
    }
    if((H1->min == NULL) || (H2->min != NULL && H2->min->key < H1->min->key))
        H->min = H2->min;
    H->n = H1->n + H2->n;
    // OUT << "Hn\t"<< H->n << "\n";
    return H;
}

void CONSOLIDATE(FIB_HEAP* H)
{
    FIB_NODE* A[11];
    for(int i = 0; i < 11; i++)
        A[i] = NULL;
    bool flag = false;
    FIB_NODE* x = H->min;
    //test
    // OUT << x->key << "before CON \n";
    // for(FIB_NODE* temp = x->right_sibling; temp != x; temp = temp->right_sibling)
    // {
    //     OUT << temp->key << " ";
    // }
    // OUT << "\n";
    //test
    while(true)
    {
        
        int d = x->degree;
        //test
        //test
        // OUT << x->key << "\n";
        // for(FIB_NODE* temp = x->right_sibling; temp != x; temp = temp->right_sibling)
        // {
        //     OUT << temp->key << " ";
        // }
        // OUT << "\n";
        //test
        //test
        while(A[d] != NULL)
        {
            FIB_NODE* y = A[d];
            if(y == x)
            {
                flag = true;
                break;
            }
            if(x->key > y->key)
            {

                FIB_NODE* z = x;
                x = y;
                y = z;
                KEY_TO_NODE[x->key] = x;
                KEY_TO_NODE[y->key] = y;
            }
            LINK(H, y->key, x->key);
            A[d] = NULL;
            d++;
        } 
        if(flag)
            break; 
        A[d] = x;     
        x = x->right_sibling;
        
    }
            //test
        //     OUT << "\nA\n";
        // for(int i = 0; i < 11; i ++)
        // {
        //     if(A[i] != NULL)
        //         OUT << A[i] ->key << "\t";

        // }
        // OUT << "\n";
        // OUT << x->key << "final\n";
        // for(FIB_NODE* temp = x->right_sibling; temp != x; temp = temp->right_sibling)
        // {
        //     OUT << temp->key << " ";
        // }
        // OUT << "\n";
        //test
    H->min = x;
    FIB_NODE* temp = x;
    do{
        if(temp->key < H->min->key)
            H->min = temp;
        temp = temp->right_sibling;
    }while(temp != x);
}

void LINK(FIB_HEAP* H, int y_key, int x_key)
{
    FIB_NODE* y = SEARCH_KEY(y_key);
    FIB_NODE* x = SEARCH_KEY(x_key);

    y->left_sibling->right_sibling = y->right_sibling;
    y->right_sibling->left_sibling = y->left_sibling;

    if(x->child == NULL)
    {
        x->child = y;
        y->parent = x;
        y->left_sibling = y;
        y->right_sibling = y;
    }
    else
    {
        y->right_sibling = x->child->right_sibling; 
        y->left_sibling = x->child;
        x->child->right_sibling->left_sibling = y;
        x->child->right_sibling = y;
        y->parent = x;
    }
    x->degree++;
    y->mark = false;
}

FIB_NODE* DECREASE_KEY(FIB_HEAP* H, int x_key, int k_key)
{
    if(x_key < k_key)
        exit(-1);
    FIB_NODE* x = SEARCH_KEY(x_key);
    x->key = k_key;
    KEY_TO_NODE[x_key] = NULL;
    KEY_TO_NODE[k_key] = x;

    FIB_NODE* y = x->parent;
    if(y != NULL && x->key < y->key)
    {
        CUT(H, x->key, y->key);
        CASCADING_CUT(H, y->key);
    }
    if(x->key < H->min->key)
    {
        H->min = x;
    }
    return H->min;
}

void CUT(FIB_HEAP* H, int x_key, int y_key)
{
    FIB_NODE* x = SEARCH_KEY(x_key);
    FIB_NODE* y = SEARCH_KEY(y_key);

    if(x->right_sibling == x)
    {
        y->child = NULL;
    }
    else
    {
        x->left_sibling->right_sibling = x->right_sibling;
        x->right_sibling->left_sibling = x->left_sibling;
        if(y->child == x)
            y->child = x->right_sibling;
    } 
    y->degree --;
    x->parent = NULL;          
    x->right_sibling = H->min->right_sibling;
    x->left_sibling = H->min;
    H->min->right_sibling->left_sibling = x;
    H->min->right_sibling = x;
    x->mark = false;
}

void CASCADING_CUT(FIB_HEAP* H, int y_key)
{
    FIB_NODE* y = SEARCH_KEY(y_key);
    FIB_NODE* z = y->parent;

    if(z != NULL)
    {
        if(y->mark == false)
            y->mark = true;
        else
        {
            CUT(H, y->key, z->key);
            CASCADING_CUT(H, z->key);
        }
    }
}

int DELETE_FIB(FIB_HEAP* H, int x_key)
{
    DECREASE_KEY(H, x_key, 0);
    // OUT << H->min->key << " ";
    // for(FIB_NODE* temp = H->min->right_sibling; temp != H->min; temp = temp->right_sibling)
    // {
    //     OUT << temp->key << " ";
    // }
    // OUT << "\n";
    EXTRACT_MIN(H);
    return H->n;
}