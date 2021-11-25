#define _CRT_SECURE_NO_WARNINGS 
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<string.h>
#include<Windows.h>
using namespace std;



char X[51];
char Y[51];

char  output_str[51];
char result[6000][51];
int length[50][50];
int dir[50][50];
int num_LCS;
int MAX_LCS;
ifstream in;
ofstream out;
ofstream time_file;

// char * str_LCS;
/*	in dir
	1 means up
	0 means upper_left
	-1 means left
*/

void LCS_output(int i, int j)
{
	if(length[i][j] == 0)
	{
		// printf("%s\n", output_str + 1);
		strcpy(result[num_LCS] + 1, output_str + 1);
		num_LCS++;
		return;
	}

	int temp = length[i][j];
	// int temp_loop = 0;
	while (length[i][j] == temp)
	{
		int end = j;
		while(length[i][j] == temp)
		{
			if(dir[i][j] == 0)
			{
				// if(temp_loop == 0)
				// {
				// 	output_str[temp] = X[i];
				// 	temp_loop++;
				// 	LCS_output(i - 1, j - 1);
				// }
				// else
				// {
				// 	next_str = (char *)malloc(sizeof(char)*50);
				// 	output_str[temp] = X[i];
				// 	for(int m = MAX_LCS; m >= temp; m--)
				// 	{
				// 		next_str[m] = output_str[m];
				// 	}
					
				// }
				output_str[temp] = X[i];
				LCS_output(i - 1, j - 1);
			}
			j--;
		}
		j = end;
		i--;
	}
	
}


void LCS_length(int len)
{
	for (int i = 1; i <= len; i++)
	{
		for (int j = 1; j <= len; j++)
		{
			if (X[i] == Y[j])
			{
				length[i][j] = length[i - 1][j - 1] + 1;
				dir[i][j] = 0;
			}
			else if (length[i - 1][j] > length[i][j - 1])
			{
				length[i][j] = length[i - 1][j];
				dir[i][j] = 1;
			}
			else
			{
				length[i][j] = length[i][j - 1];
				dir[i][j] = -1;
			}
		}
	}
	return;
}

void LCS_initial(int len)
{
	for(int i = 0; i <= len; i++)
	{
		for(int j = 0; j <= len; j++)
		{
			length[i][j] = 0;
			dir[i][j] = 0;
		}
	}
	for (int i = 0; i <= 50; i++)
	{
		X[i] = 0;
		Y[i] = 0;
	}
	num_LCS = 0;
	return;
}
// void LCS_print(int i, int j)
// {
// 	if (i == 0 || j == 0)
// 		return;
// 	if (dir[i][j] == 0)
// 	{
// 		LCS_print(i - 1, j - 1);
// 		printf("%c\t", X[i]);
// 	}
// 	else if(dir[i][j] == 1)
// 		LCS_print(i - 1, j);
// 	else
// 		LCS_print(i, j - 1);
// }

// void LCS_DFS(int i, int j, int LCS_len, int len, char *str_LCS)
// {
// 	if(i == 0 || j == 0)
// 	{
// 		printf("%s\n", str_LCS);
// 		free(str_LCS);
// 		return;
// 	}
// 	else if(dir[i][j] == 0)
// 	{
// 		if (LCS_len == len)
// 		{
// 			str_LCS = (char *)malloc(sizeof(char) * 50);
// 			str_LCS[len] = '\0';
// 		}
			
// 		str_LCS[LCS_len] = X[i];
// 		LCS_DFS(i - 1, j - 1, LCS_len - 1, len, str_LCS);
// 	}
// 	else if(dir[i][j] == 1)
// 		LCS_DFS(i - 1, j, LCS_len, len, str_LCS);
// 	else if(dir[i][j] == -1)
// 		LCS_DFS(i, j - 1, LCS_len, len, str_LCS);
// 	else
// 	{
// 		char *next_str = (char *)malloc(sizeof(char) * 50);
// 		for(int m = LCS_len; m <= len; m++)
// 		{
// 			next_str[m] = str_LCS[m];
// 		}
// 		LCS_DFS(i - 1, j, LCS_len, len, str_LCS);
// 		str_LCS = next_str;
// 		LCS_DFS(i, j - 1, LCS_len, len, str_LCS);
// 	}
// }





int main(void)
{
	int len;
	in.open("../input/1_2_input.txt");
	time_file.open("../output/time.txt");
	// out.open("./1_2_output.txt");
	int count = 1;
	while(!in.eof())
	{
		// scanf("%d", &len);
		// scanf("%s", X + 1);
		// scanf("%s", Y + 1);

		
		char out_file[20];
		sprintf(out_file, "../output/result_%d.txt", count);
		out.open(out_file);
		in >> len;
		LCS_initial(len);
		in >> X + 1;
		in >> Y + 1;

		LARGE_INTEGER t1,t2,tc;
   		QueryPerformanceFrequency(&tc);
    	QueryPerformanceCounter(&t1);

		LCS_length(len);
		MAX_LCS = length[len][len];

		QueryPerformanceCounter(&t2);
    	double time=(double)(1000 * t2.QuadPart - 1000 * t1.QuadPart)/(double)tc.QuadPart; 
    	time_file<< time << "ms" << endl;
		// for (int i = 0; i <= len; i++)
		// {
		// 	for (int j = 0; j <= len; j++)
		// 	{
		// 		printf("%d\t", dir[i][j]);
		// 	}
		// 	printf("\n");
		// }
		// printf("\n");
		// for (int i = 0; i <= len; i++)
		// {
		// 	for (int j = 0; j <= len; j++)
		// 	{
		// 		printf("%d\t", length[i][j]);
		// 	}
		// 	printf("\n");
		// }  
		LCS_output(len, len);

		out << num_LCS << endl;
		for(int i = 0; i < num_LCS; i++)
		{
			out << result[i] + 1 << endl;
		}
		printf("%d\n", num_LCS);

		out.close();
		count++;


	}
	in.close();
	time_file.close();
	// str_LCS = (char*)malloc(sizeof(char) * 50);
	// LCS_DFS(len, len, length[len][len], length[len][len], str_LCS);
	// LCS_print(len, len);
	return 0;

}