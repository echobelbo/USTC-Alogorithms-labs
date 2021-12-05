#pragma once
#define _CRT_SECURE_NO_WARNINGS 

struct FIB_NODE
{
	FIB_NODE* left_sibling;
	FIB_NODE* right_sibling;
	FIB_NODE* parent;
	FIB_NODE* child;
	bool mark;
	int key;
	int degree;
};
struct FIB_HEAP
{
	FIB_NODE* min;
	int n;
};
FIB_HEAP* MAKE_HEAP(void);
int INSERT(FIB_HEAP* H, int key);
int MINIMUM(FIB_HEAP* H);
FIB_NODE* EXTRACT_MIN(FIB_HEAP* H);
FIB_HEAP* UNION(FIB_HEAP* H1, FIB_HEAP* H2);
void CONSOLIDATE(FIB_HEAP* H);
void FIB_NODE_LINK(FIB_NODE* x, FIB_NODE* y);
void LINK(FIB_HEAP* H, int y_key, int x_key);
FIB_NODE* DECREASE_KEY(FIB_HEAP* H, int x_key, int k_key);
void CUT(FIB_HEAP* H, int x_key, int y_key);
void CASCADING_CUT(FIB_HEAP* H, int y_key);
FIB_NODE* DELETE(FIB_HEAP* H, int x_key);