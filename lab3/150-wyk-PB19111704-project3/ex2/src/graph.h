#pragma once
class EDGE
{
private:
    /*data*/
public:
    int key;
    int out;
    EDGE* next_edge;
    
};
class VERTEX
{
private:
    /* data */
public:
    int distance;
    int fore;
    EDGE* fir_edge;
    // void insert(GRAPH* G, int num);
};
class GRAPH
{
private:
    /* data */
public:
    int ver_num;
    VERTEX** ver;  
    void INITIALIZE(GRAPH* G, int src_ver); 
    void insert(GRAPH* G,  int in_ver, int out_ver, int key);
};




GRAPH* MAKE_GRAPH(int ver_num);