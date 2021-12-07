#define _CRT_SECURE_NO_WARNINGS 
#include "fib_heap.h"
#include<iostream>
#include<stdlib.h>
#include<fstream>

#define INPUT_FILE "./2_1_input.txt"
#define OUTPUT_FILE "./2_1_result/txt"
#define OUT cout

using namespace std;

ifstream in;
ofstream out;

int main(void)
{
    in.open(INPUT_FILE);
    out.open(OUTPUT_FILE);
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
    OUT << "H1" << "\n";
    OUT << INSERT(H[0], 249) << "\t";
    OUT << INSERT(H[0], 830) << "\t";
    OUT << MINIMUM(H[0]) << "\t";
    OUT << DELETE(H[0], 127) << "\t";
    OUT << DELETE(H[0], 141) << "\t";
    OUT << MINIMUM(H[0]) << "\t";
    OUT << DECREASE_KEY(H[0], 75, 61)->key << "\t";
    OUT << DECREASE_KEY(H[0], 198, 169)->key << "\t";
    OUT << EXTRACT_MIN(H[0])->key << "\t";
    OUT << EXTRACT_MIN(H[0])->key << "\t";
    OUT << "\n";
    //step2 end
    //step3 start
    OUT << "H2" << "\n";
    OUT << INSERT(H[1], 816) << "\t";
    OUT << MINIMUM(H[1]) << "\t";
    OUT << INSERT(H[1], 345) << "\t";
    OUT << EXTRACT_MIN(H[1])->key << "\t";
    OUT << DELETE(H[1], 504) << "\t";
    OUT << DELETE(H[1], 203) << "\t";
    OUT << DECREASE_KEY(H[1], 296, 87)->key << "\t";
    OUT << DECREASE_KEY(H[1], 278, 258)->key << "\t";
    OUT << MINIMUM(H[1]) << "\t";
    OUT << EXTRACT_MIN(H[1])->key << "\t";
    OUT << "\n";
    //step3 end
    //step4 start
    OUT << "H3" << "\n";
    OUT << EXTRACT_MIN(H[2])->key << "\t";
    OUT << MINIMUM(H[2]) << "\t";
    OUT << INSERT(H[2], 262) << "\t";
    OUT << EXTRACT_MIN(H[2])->key << "\t";
    OUT << INSERT(H[2], 832) << "\t";
    OUT << MINIMUM(H[2]) << "\t";
    OUT << DELETE(H[2], 134) << "\t";
    OUT << DELETE(H[2], 177) << "\t";
    OUT << DECREASE_KEY(H[2], 617, 360)->key << "\t";
    OUT << DECREASE_KEY(H[2], 889, 353)->key << "\t";
    OUT << "\n";
    //step4 end
    //step5 start
    OUT << "H4" << "\n";
    OUT << MINIMUM(H[3]) << "\t";
    OUT << DELETE(H[3], 708) << "\t";
    OUT << INSERT(H[3], 281) << "\t";
    OUT << INSERT(H[3], 347) << "\t";
    OUT << MINIMUM(H[3]) << "\t";
    OUT << DELETE(H[3], 415) << "\t";
    OUT << EXTRACT_MIN(H[3])->key << "\t";
    OUT << DECREASE_KEY(H[3], 620, 354)->key << "\t";
    OUT << DECREASE_KEY(H[3], 410, 80)->key << "\t";
    OUT << EXTRACT_MIN(H[3])->key << "\t";
    OUT << "\n";
    //step5 end
    //step6 start
    H[4] = UNION(H[4], H[0]);
    H[4] = UNION(H[4], H[1]);
    H[4] = UNION(H[4], H[2]);
    H[4] = UNION(H[4], H[3]);
    //step6 end
    //step7 start
    OUT << "H5" << "\n";
    OUT << EXTRACT_MIN(H[4])->key << "\t";
    OUT << MINIMUM(H[4]) << "\t";
    OUT << DELETE(H[4], 800) << "\t";
    OUT << INSERT(H[4], 267) << "\t";
    OUT << INSERT(H[4], 351) << "\t";
    OUT << EXTRACT_MIN(H[4])->key << "\t";
    OUT << DECREASE_KEY(H[4], 478, 444)->key << "\t";
    OUT << DECREASE_KEY(H[4], 559, 456)->key << "\t";
    OUT << MINIMUM(H[4]) << "\t";
    OUT << DELETE(H[4], 929) << "\t";
    OUT << "\n";
    //step7 end
    in.close();
    out.close();
    return 0;
}

