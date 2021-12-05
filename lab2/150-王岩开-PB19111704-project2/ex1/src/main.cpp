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
    OUT << INSERT(H[0], 249) << "\n";
    OUT << INSERT(H[0], 830) << "\n";
    OUT << MINIMUM(H[0]) << "\n";
    OUT << DELETE(H[0], 127)->key << "\n";
    OUT << DELETE(H[0], 141)->key << "\n";
    OUT << MINIMUM(H[0]) << "\n";
    OUT << DECREASE_KEY(H[0], 75, 61)->key << "\n";
    OUT << DECREASE_KEY(H[0], 198, 169)->key << "\n";
    OUT << EXTRACT_MIN(H[0])->key << "\n";
    OUT << EXTRACT_MIN(H[0])->key << "\n";
    //step2 end
    // for(int i = 0; i <= 0; i++)
    // {
    //     cout << MINIMUM(H[i]) << "\n";
    //     for(FIB_NODE* x = H[i]->min->right_sibling; x != H[i]->min; x = x->right_sibling)
    //     {
    //         cout << x->key << "\n";
    //     }
    // }
    in.close();
    out.close();
    return 0;
}

