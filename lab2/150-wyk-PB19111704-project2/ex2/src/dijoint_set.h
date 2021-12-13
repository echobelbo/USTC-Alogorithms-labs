#pragma once
#define _CRT_SECURE_NO_WARNINGS 

struct Member {
	int key;
	Member* parent;
	int rank;
};

Member* MAKE_SET(int key);
bool LINK(Member* x, Member* y);
bool UNION(Member* x, Member* y);
Member* FIND_SET(Member* x);