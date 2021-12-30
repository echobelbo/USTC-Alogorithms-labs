#define _CRT_SECURE_NO_WARNINGS 
#include "graph.h"
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<string.h>
#include<windows.h>
using namespace std;


#define MAX 0x0fffffff
#define TIME_FILE "./time.txt"
#define ROUT out
int N[4] = {27, 81, 243, 729};
ifstream in;
ofstream out;
ofstream time_file;


void RELAX(GRAPH* G, int x, int y, int key)
{
    if (G->ver[y]->distance == MAX && G->ver[x]->distance == MAX)
        return;
    if(G->ver[y]->distance > G->ver[x]->distance + key)
    {
        G->ver[y]->distance = G->ver[x]->distance + key;
        G->ver[y]->fore = x;
    }
}

void BELLMAN_FORD(GRAPH *G, int src_ver)
{
    G->INITIALIZE(G, src_ver);
    for(int i = 1; i < G->ver_num; i++)
    {
        for(int j = 0; j < G->ver_num; j++)
        {
            EDGE* op_edge = G->ver[j]->fir_edge;
            while(op_edge)
            {
                RELAX(G, j, op_edge->out, op_edge->key);
                op_edge = op_edge->next_edge;
            }
        }
    }
}

int main(void)
{
    LARGE_INTEGER t1, t2, tc;
    double time;
    time_file.open(TIME_FILE);
    for(int file0 = 1; file0 <= 4; file0++)
    {
        for(int file1 = 1; file1 <= 2; file1++)
        {


            char INPUT_FILE[20];
            char OUTPUT_FILE[20];
            sprintf(INPUT_FILE, "./input%d%d.txt", file0, file1);
            sprintf(OUTPUT_FILE, "./result%d%d.txt", file0, file1);

            in.open(INPUT_FILE);
            out.open(OUTPUT_FILE);
            GRAPH* G;
            int ver_num;
            G = MAKE_GRAPH(N[file0 - 1]);
            for(int i = 0; i < N[file0 - 1]; i++)
            {
                for(int j = 0;j < N[file0 - 1];j++)
                {
                    int temp;
                    char comma;
                    in >> temp;
                    if(temp != 0)
                    {
                        G->insert(G, i, j, temp);
                    }
                    in >> comma;
                }
            }
            QueryPerformanceFrequency(&tc);
            QueryPerformanceCounter(&t1);

            BELLMAN_FORD(G, 0);

            QueryPerformanceCounter(&t2);
            time = (double)(1000 * t2.QuadPart - 1000 * t1.QuadPart) / (double)tc.QuadPart;
            time_file << time << "ms" << endl;

            for(int i = 1;i < N[file0 - 1]; i++)
            {
                if(G->ver[i]->fore != -1)
                {
                    ROUT << "0," << i << "," << G->ver[i]->distance << ";";
                    int path[800];
                    // path = (int*)malloc(sizeof(int) * N[file0 - 1]);
                    int length = 0;
                    int flag = i;
                    while(G->ver[flag]->fore != 0)
                    {
                        path[length] = flag;
                        flag = G->ver[flag]->fore;
                        length++;
                    }
                    path[length] = flag;
                    ROUT << "0";
                    for(int j = length; j >= 0; j--)
                    {
                        ROUT << "," << path[j];
                    }
                    ROUT << "\n";
                }

            }

            in.close();
            out.close();
        }
    }
    time_file.close();
    return 0;
}