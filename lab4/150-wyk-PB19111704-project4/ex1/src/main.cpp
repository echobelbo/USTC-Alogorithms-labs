#define _CRT_SECURE_NO_WARNINGS 
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<string>
#include<Windows.h>
using namespace std;

#define IN_FILE "./4_1_input.txt"
#define OUT_FILE "./result.txt"
#define TIME_FILE "./time.txt"
#define ROUT out
#define TOUT time_out

string T;
string P;
int* pi;
int m;
int n;
ifstream in;
ofstream out;
ofstream time_out;
void COMPUTE_PREFIX_FUNCTION()
{
    pi = (int *)malloc(sizeof(int) * m);
    pi[0] = 0;
    int k = 0;
    for(int i = 1;i <= m-1;i++)
    {
        while(k > 0 && P[k] != P[i])
            k = pi[k - 1];
        if(P[k] == P[i])
            k++;
        pi[i] = k;
    }
}
int main(void)
{
    in.open(IN_FILE);
    out.open(OUT_FILE);
    time_out.open(TIME_FILE);
    for(int i = 0; i < 5; i++)
    {
        in >> P;
        m = P.size();
        in >> T;
        n = T.size();

        int result[10];
        int suc_times = 0;
        LARGE_INTEGER t1,t2,tc;
        double time;
        QueryPerformanceFrequency(&tc);
        QueryPerformanceCounter(&t1);

        COMPUTE_PREFIX_FUNCTION();

        int q = 0;
        for(int j = 0;j < n;j++)
        {
            while(q > 0 && P[q] != T[j])
                q = pi[q - 1];
            if(P[q] == T[j])
                q++;
            if(q == m)
            {
                result[suc_times++] = j - m + 2;
                // ROUT << j - m + 2<< " ";
                q = pi[q - 1];
            }
        }  
        ROUT << suc_times << endl;
        
        for(int j = 0; j < m;j++)
        {
            ROUT << pi[j] << " ";
        }
        ROUT << "\n";
        for(int j = 0;j < suc_times;j++)
        {
            ROUT << result[j] << " ";
        }
        ROUT << endl << endl;
        QueryPerformanceCounter(&t2);
        time = (double)(1000 * t2.QuadPart - 1000 * t1.QuadPart)/(double)tc.QuadPart; 
        TOUT << time << "ms" << endl;                                                                                              
        P.erase(0);
        T.erase(0);
        free(pi);
    }


    in.close();
    out.close();
    time_out.close();
    return 0;
}