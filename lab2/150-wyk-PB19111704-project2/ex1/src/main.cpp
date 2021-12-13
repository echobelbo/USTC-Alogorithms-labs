#define _CRT_SECURE_NO_WARNINGS 
#include "fib_heap.h"
#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<windows.h>

#define INPUT_FILE "../input/2_1_input.txt"
#define OUTPUT_FILE "../output/result.txt"
#define TIME_FILE "../output/time.txt"
#define OUT out
#define TOUT time_out

using namespace std;

ifstream in;
ofstream out;
ofstream time_out;

int main(void)
{
    in.open(INPUT_FILE);
    out.open(OUTPUT_FILE);
    time_out.open(TIME_FILE);
    LARGE_INTEGER t1,t2,tc;
    double time;

    FIB_HEAP* H[5];
    for(int i = 0; i <= 4; i++)
    {
        H[i] = MAKE_HEAP();
    }
    //step1 start   
    for(int i = 1; i <= 500; i++)
    {
        int in_key;
        in >> in_key;
        // cout << in_key << "\n";
        if(i <= 50)
            INSERT(H[0], in_key);
        else if(i <= 150)
            INSERT(H[1], in_key);
        else if(i <= 300)
            INSERT(H[2], in_key);
        else
            INSERT(H[3], in_key);
    }
    //step1 end
    //step2 start
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);

    OUT << "H1" << "\n";
    OUT << INSERT(H[0], 249) << ",";
    OUT << INSERT(H[0], 830) << ",";
    OUT << MINIMUM(H[0]) << ",";
    OUT << DELETE_FIB(H[0], 127) << ",";
    OUT << DELETE_FIB(H[0], 141) << ",";
    OUT << MINIMUM(H[0]) << ",";
    OUT << DECREASE_KEY(H[0], 75, 61)->key << ",";
    OUT << DECREASE_KEY(H[0], 198, 169)->key << ",";
    OUT << EXTRACT_MIN(H[0])->key << ",";
    OUT << EXTRACT_MIN(H[0])->key;
    OUT << "\n";

    QueryPerformanceCounter(&t2);
    time = (double)(1000 * t2.QuadPart - 1000 * t1.QuadPart)/(double)tc.QuadPart; 
    TOUT << time << "ms" << endl;

    //step2 end
    //step3 start
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);

    OUT << "H2" << "\n";
    OUT << INSERT(H[1], 816) << ",";
    OUT << MINIMUM(H[1]) << ",";
    OUT << INSERT(H[1], 345) << ",";
    OUT << EXTRACT_MIN(H[1])->key << ",";
    OUT << DELETE_FIB(H[1], 504) << ",";
    OUT << DELETE_FIB(H[1], 203) << ",";
    OUT << DECREASE_KEY(H[1], 296, 87)->key << ",";
    OUT << DECREASE_KEY(H[1], 278, 258)->key << ",";
    OUT << MINIMUM(H[1]) << ",";
    OUT << EXTRACT_MIN(H[1])->key;
    OUT << "\n";
    
    QueryPerformanceCounter(&t2);
    time = (double)(1000 * t2.QuadPart - 1000 * t1.QuadPart)/(double)tc.QuadPart; 
    TOUT << time << "ms" << endl;
    //step3 end
    //step4 start
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);

    OUT << "H3" << "\n";
    OUT << EXTRACT_MIN(H[2])->key << ",";
    OUT << MINIMUM(H[2]) << ",";
    OUT << INSERT(H[2], 262) << ",";
    OUT << EXTRACT_MIN(H[2])->key << ",";
    OUT << INSERT(H[2], 832) << ",";
    OUT << MINIMUM(H[2]) << ",";
    OUT << DELETE_FIB(H[2], 134) << ",";
    OUT << DELETE_FIB(H[2], 177) << ",";
    OUT << DECREASE_KEY(H[2], 617, 360)->key << ",";
    OUT << DECREASE_KEY(H[2], 889, 353)->key;
    OUT << "\n";

    QueryPerformanceCounter(&t2);
    time = (double)(1000 * t2.QuadPart - 1000 * t1.QuadPart)/(double)tc.QuadPart; 
    TOUT << time << "ms" << endl;
    //step4 end
    //step5 start
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);

    OUT << "H4" << "\n";
    OUT << MINIMUM(H[3]) << ",";
    OUT << DELETE_FIB(H[3], 708) << ",";
    OUT << INSERT(H[3], 281) << ",";
    OUT << INSERT(H[3], 347) << ",";
    OUT << MINIMUM(H[3]) << ",";
    OUT << DELETE_FIB(H[3], 415) << ",";
    OUT << EXTRACT_MIN(H[3])->key << ",";
    OUT << DECREASE_KEY(H[3], 620, 354)->key << ",";
    OUT << DECREASE_KEY(H[3], 410, 80)->key << ",";
    OUT << EXTRACT_MIN(H[3])->key;
    OUT << "\n";

    QueryPerformanceCounter(&t2);
    time = (double)(1000 * t2.QuadPart - 1000 * t1.QuadPart)/(double)tc.QuadPart; 
    TOUT << time << "ms" << endl;
    //step5 end
    //step6 start
    H[4] = UNION(H[4], H[0]);
    H[4] = UNION(H[4], H[1]);
    H[4] = UNION(H[4], H[2]);
    H[4] = UNION(H[4], H[3]);
    //step6 end
    //step7 start
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);

    OUT << "H5" << "\n";
    OUT << EXTRACT_MIN(H[4])->key << ",";
    OUT << MINIMUM(H[4]) << ",";
    OUT << DELETE_FIB(H[4], 800) << ",";
    OUT << INSERT(H[4], 267) << ",";
    OUT << INSERT(H[4], 351) << ",";
    OUT << EXTRACT_MIN(H[4])->key << ",";
    OUT << DECREASE_KEY(H[4], 478, 444)->key << ",";
    OUT << DECREASE_KEY(H[4], 559, 456)->key << ",";
    OUT << MINIMUM(H[4]) << ",";
    OUT << DELETE_FIB(H[4], 929);
    OUT << "\n";

    QueryPerformanceCounter(&t2);
    time = (double)(1000 * t2.QuadPart - 1000 * t1.QuadPart)/(double)tc.QuadPart; 
    TOUT << time << "ms" << endl;
    //step7 end
    in.close();
    out.close();
    time_out.close();
    return 0;
}

