#define _CRT_SECURE_NO_WARNINGS 
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<Windows.h>

using namespace std;


#define MAX 9223372036854775807

long long int* mul_times;
int* position;
ifstream in;
ofstream out;
ofstream time_file;

void matrix_chain_order(int n, long long int * matrix_size)
{
	for (int i = 0; i < n; i++)
	{
		mul_times[n * i + i] = 0;
	}
	for (int length = 2; length <= n; length++)
	{
		for (int start = 0; start <= n - length; start++)
		{
			int end = start + length - 1;
			mul_times[n * start + end] = MAX;
			for (int k = start;k < end; k++)
			{
				long long int q = mul_times[start * n + k] + mul_times[(k + 1) * n + end]
					+ matrix_size[start] * matrix_size[k + 1] * matrix_size[end + 1];
				if (q < mul_times[n * start + end])
				{
					mul_times[n * start + end] = q;
					position[start * n + end] = k;
				}
			}
		}
	}
}

void print_optimal_parens(int i, int j, int n)
{
	if (i == j) out << "A[" << i << "]";
	else
	{
		out << '(';
		print_optimal_parens(i, position[i * n + j], n);
		print_optimal_parens(position[i * n + j] + 1, j, n);
		out << ')';
	}
}


int main(void)
{
	int n;//number of matrix
	long long int* matrix_size;


	//teststart
	// char buffer[256];

	in.open("../input/1_1_input.txt");
	out.open("../output/1_1_output.txt");
	time_file.open("../output/time.txt");
	// if(!in.is_open())
	// {
	// 	cout << "Error";
	// 	exit(1);
	// }
	// in >> buffer;
	// cout << buffer << endl;


	//testend
	while(!in.eof())
	{
		in >> n;
		matrix_size = (long long int*)malloc(sizeof(long long int) * (n + 1));
		for (int i = 0; i <= n; i++)
			in >> matrix_size[i];

		mul_times = (long long int *)malloc(sizeof(long long int) * n * n);
		position = (int*)malloc(sizeof(int) * n * n);

		LARGE_INTEGER t1,t2,tc;
   		QueryPerformanceFrequency(&tc);
    	QueryPerformanceCounter(&t1);

		matrix_chain_order(n, matrix_size);

		QueryPerformanceCounter(&t2);
    	double time=(double)(1000 * t2.QuadPart - 1000 * t1.QuadPart)/(double)tc.QuadPart; 
    	time_file<< time << "ms" << endl;

		out << mul_times[n - 1] << endl;
		print_optimal_parens(0, n - 1, n);

		out << endl;
		for (int i = 0; i < n; i++)
		{
			for (int j = n - 1;j >= i; j--)
			{
				printf("%lld\t", mul_times[i * n + j]);
			}
			printf("\n");
		}
		for (int i = 0; i < n - 1; i++)
		{
			for (int j = n - 1;j >= i + 1; j--)
			{
				printf("%d\t", position[i * n + j]);
			}
			printf("\n");
		}
		free(matrix_size);
		free(mul_times);
	}
	in.close();
	out.close();
	time_file.close();
	return 0;
}