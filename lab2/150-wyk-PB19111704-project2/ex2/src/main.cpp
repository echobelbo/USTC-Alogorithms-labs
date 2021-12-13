#define _CRT_SECURE_NO_WARNINGS 
#include "dijoint_set.h"
#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<windows.h>

using namespace std;


#define IN_FILE "../input/2_2_input.txt"
#define OUT_FILE "../output/result.txt"
#define TIME_FILE "../output/time.txt"
#define OUT out
#define TOUT time_out

int N[5] = {10, 15, 20, 25, 30};
ifstream in;
ofstream out;
ofstream time_out;

int main(void)
{
    in.open(IN_FILE);
    out.open(OUT_FILE);
    time_out.open(TIME_FILE);

    for(int i = 0; i <= 4; i++)
    {
        LARGE_INTEGER t1,t2,tc;
        double time;
        QueryPerformanceFrequency(&tc);
        QueryPerformanceCounter(&t1);

        int set_count = N[i];
        Member** set_root;
        set_root = (Member **)malloc(sizeof(Member*) * N[i]);
        for(int j = 0; j < N[i]; j++)
            set_root[j] = MAKE_SET(j);
        for(int m = 0; m < N[i]; m++)
        {
            for(int n = 0; n < N[i]; n++)
            {
                int op;
                in >> op;
                if(op)
                {
                    if(UNION(set_root[m], set_root[n]))
                        set_count--;
                }
            }
        }
        QueryPerformanceCounter(&t2);
        time = (double)(1000 * t2.QuadPart - 1000 * t1.QuadPart)/(double)tc.QuadPart; 
        TOUT << time << "ms" << endl;
        OUT <<"n = " << N[i] << " " << set_count << endl;
    }

    in.close();
    out.close();
    time_out.close();
    return 0;
}