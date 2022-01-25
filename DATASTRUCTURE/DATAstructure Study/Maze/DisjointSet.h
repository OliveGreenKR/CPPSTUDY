#pragma once

class Pos;

class DisjointSet
{
public:
	DisjointSet(int n);

	int Find(int u);
	void Merge(int u, int v);
private:
	vector<int> _parent;
	vector<int> _rank;
};
