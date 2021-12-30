#include "graph.h"

#include<stdlib.h>
#define MAX 0x0fffffff

GRAPH* MAKE_GRAPH(int ver_num)
{
    GRAPH* G;
    G = (GRAPH*)malloc(sizeof(GRAPH));
    G->ver = (VERTEX**)malloc(sizeof(VERTEX*) * ver_num);
    for(int i = 0; i < ver_num;i++)
    {
        G->ver[i] = (VERTEX*)malloc(sizeof(VERTEX));
        G->ver[i]->fir_edge= NULL;
    }
    G->ver_num = ver_num;
    return G;
}

// void VERTEX::insert(GRAPH* G, int num)
// {
//     VERTEX* ver;
//     ver = (VERTEX*)malloc(sizeof())
// }
void GRAPH::INITIALIZE(GRAPH* G, int src_ver)
{
    for(int i = 0;i < G->ver_num; i++)
    {
        G->ver[i]->distance = MAX;
        G->ver[i]->fore = -1;
    }
    G->ver[src_ver]->distance = 0;
}

void GRAPH::insert(GRAPH* G, int in_ver, int out_ver, int key)
{
    EDGE* e;
    e = (EDGE*)malloc(sizeof(EDGE));
    e->out = out_ver;
    e->key = key;
    e->next_edge = NULL;
    EDGE* ins_pos = G->ver[in_ver]->fir_edge;
    if(ins_pos == NULL)
        G->ver[in_ver]->fir_edge = e;
    else
    {
        for(ins_pos = G->ver[in_ver]->fir_edge; ins_pos->next_edge != NULL; ins_pos = ins_pos->next_edge);
        ins_pos->next_edge = e;
    }
}
