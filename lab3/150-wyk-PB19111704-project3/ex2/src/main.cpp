#define _CRT_SECURE_NO_WARNINGS 
#include "graph.h"
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<string.h>
#include<windows.h>
#include<set>
#include<map>
#include<queue>
// #include"priorityqueue.h"

using namespace std;


#define MAX 0x0fffffff
#define TIME_FILE "./time.txt"
#define ROUT out
int N[4] = {27, 81, 243, 729};
// int dis[800][800];
ifstream in;
ofstream out;
ofstream time_file;


// int cmp(Datatype a, Datatype b)
// {
//     return(a.dist - b.dist);
// }

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
void DIJKSTRA(GRAPH *G, int src_ver)
{
    priority_queue<pair<int, int>,vector<pair<int,int>>,greater<pair<int ,int>>> Q;//first int is dist, second int is out
    G->INITIALIZE(G, src_ver);
    bool* S;
    S = (bool*)malloc(sizeof(bool) * G->ver_num);
    for(int i = 0; i < G->ver_num;i++)
    {
            S[i] = false;
    }
    EDGE* flag = G->ver[src_ver]->fir_edge;
    for(;flag != NULL;flag = flag->next_edge)
    {
        RELAX(G, src_ver, flag->out, flag->key);
        Q.push({G->ver[flag->out]->distance, flag->out});
    }
    S[src_ver] = true;
    while(!Q.empty())
    {
        int enqueue;
        int dist;
        tie(dist, enqueue) = Q.top();
        Q.pop();
        if(!S[enqueue])
        {
            // dis[src_ver][enqueue] = G->ver[enqueue]->distance;
            for(flag = G->ver[enqueue]->fir_edge; flag != NULL; flag = flag->next_edge)
            {
                RELAX(G, enqueue, flag->out, flag->key);
                Q.push({G->ver[flag->out]->distance, flag->out});
            }
            S[enqueue] = true;
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
            GRAPH* G, * G_temp;
            int ver_num;
            G = MAKE_GRAPH(N[file0 - 1]);
            G_temp = MAKE_GRAPH(N[file0 - 1] + 1);
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
                        G_temp->insert(G_temp, i, j, temp);
                    }
                    in >> comma;
                }
            }
            for(int j = 0;j < N[file0 - 1];j++)
            {
                G_temp->insert(G_temp, N[file0 - 1], j, 0);
            }
            QueryPerformanceFrequency(&tc);
            QueryPerformanceCounter(&t1);

            BELLMAN_FORD(G_temp, N[file0 - 1]);

            for(int i = 0; i < N[file0 - 1]; i++)
            {
                EDGE* flag = G->ver[i]->fir_edge;
                while(flag)
                {
                    flag->key = flag->key + G_temp->ver[i]->distance - G_temp->ver[flag->out]->distance;
                    flag = flag->next_edge;
                }
            }
            // int dis[800];
            // for(int i = 0; i < N[file0 - 1]; i++)
            // {
            //     dis[800] = MAX;
            //     // dis[i][i] = 0;
            // }
            
            for(int i = 0; i < N[file0 - 1]; i++)
            {
                DIJKSTRA(G, i);
                for(int j = 0; j < N[file0 - 1]; j++)
                {
                    if(G->ver[j]->distance != MAX)
                    {
                        ROUT << G->ver[j]->distance + G_temp->ver[j]->distance - G_temp->ver[i]->distance << " ";
                    }
                    else
                        ROUT << "X" << " ";
                    
                }
                ROUT << endl;

            }
            QueryPerformanceCounter(&t2);
            time = (double)(1000 * t2.QuadPart - 1000 * t1.QuadPart) / (double)tc.QuadPart;
            time_file << time << "ms" << endl;
            
            // for(int i = 0;i < N[file0 - 1]; i++)
            // {
            //     // if(G->ver[i]->fore != -1)
            //     // {
            //     //     ROUT << "0," << i << "," << G->ver[i]->distance << ";";
            //     //     int* path;
            //     //     path = (int*)malloc(sizeof(int) * N[file0 - 1]);
            //     //     int length = 0;
            //     //     int flag = i;
            //     //     while(G->ver[flag]->fore != 0)
            //     //     {
            //     //         path[length] = flag;
            //     //         flag = G->ver[flag]->fore;
            //     //         length++;
            //     //     }
            //     //     path[length] = flag;
            //     //     ROUT << "0";
            //     //     for(int j = length; j >= 0; j--)
            //     //     {
            //     //         ROUT << "," << path[j];
            //     //     }
            //     //     ROUT << "\n";
            //     // }
            //     for(int j = 0; j < N[file0 - 1]; j++)
            //     {
            //         ROUT << dis[i][j] << " ";
            //     }
            //     ROUT << endl;
            // }

            in.close();
            out.close();
        }
    }
    time_file.close();
    return 0;
}