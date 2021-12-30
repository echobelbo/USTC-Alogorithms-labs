#define _CRT_SECURE_NO_WARNINGS 
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
#include<Windows.h>
using namespace std;

#define IN_FILE "./4_2_input.txt"
#define OUT_FILE "./result.txt"
#define TIME_FILE "./time.txt"
#define ROUT cout
#define TOUT time_out

string T;
string P;
int m;
int n;
int s_time[10];
ifstream in;
ofstream out;
ofstream time_out;
int d[4] = {2, 2, 10, 10};
int q[4] = {13, 1009, 13, 1009};
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
        int real = 0;
        int fake_time[4];
        
        for(int j = 0; j < 4; j++)
        {
            
            // ROUT << "d is" << d[j];
            // ROUT << " q is" << q[j] << endl;
            
            int fake = 0;
            int h = 1;

            for(int i_0 = 1;i_0 <= m - 1;i_0++)
            {
                h = h * d[j];
                h = h % q[j]; 
            }
                
            int p = 0;
            int* t;
            t = (int*)malloc(sizeof(int) * (n - m + 1));
            t[0] = 0;
            for(int i_0 = 0; i_0 < m; i_0++)
            {
                p = (d[j] * p + P[i_0]) % q[j];
                t[0] = (d[j] * t[0] + T[i_0]) % q[j];
            }
            for(int s = 0;s <= n - m;s++)
            {
                if(p == t[s])
                {
                    int flag = 0;
                    for(; flag < m;flag++)
                    {
                        if(T[flag + s] != P[flag])
                        {
                            fake++;
                            break;
                        }
                    }
                    if(flag == m)
                    {
                        s_time[real] = s + 1;
                        real++;
                    }
                }
                if(s < n - m)
                {
                    t[s + 1] = (d[j] * (t[s] - T[s] * h) + T[s + m]) % q[j];
                    if(t[s + 1] < 0)
                        t[s + 1] = q[j] + t[s + 1];     
                }
            }
            fake_time[j] = fake;
        }
        real = real/4;
        ROUT << real << endl;
        for(int i_0 = 0;i_0 < 4;i_0++)
        {
            ROUT << fake_time[i_0] << " ";
        }
        ROUT << endl;
        for(int i_0 = 0;i_0 < real;i_0++)
        {
            ROUT << s_time[i_0] << " ";
        }
        ROUT << endl << endl;
    }
    in.close();
    out.close();
    time_out.close();
    return 0;
}