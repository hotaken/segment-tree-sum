#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct segtree {

	vector<long long> tree;
	int size;

	void init(int n) {
		size = 1;
		while (size < n) size *= 2;
		tree.assign(2 * size - 1, 0);
	}

	void build(vector<long long>& v, int x, int lx, int rx) {
		if (rx - lx == 1) {
			if (lx < v.size()) {
				tree[x] = v[lx];
			}
			return;
		}
		int m = (lx + rx) / 2;
		build(v, 2 * x + 1, lx, m);
		build(v, 2 * x + 2, m, rx);

		tree[x] = tree[2 * x + 1] + tree[2 * x + 2];

	}

	// build from vector of elements
	void build(vector<long long>& v) { 
		init(v.size());
		build(v, 0, 0, size);
	}

	void set(int i, int v, int x, int lx, int rx) {
		if (rx - lx == 1) {
			tree[x] = v;
			return;
		}

		int m = (lx + rx) / 2;

		if (i < m) {
			set(i, v, 2 * x + 1, lx, m);
		}
		else {
			set(i, v, 2 * x + 2, m, rx);
		}

		tree[x] = tree[2 * x + 1] + tree[2 * x + 2];

	}

	// number of element and new value
	void set(int i, long long v) { 
		set(i, v, 0, 0, size);
	}

	long long sum(int l, int r, int x, int lx, int rx) {

		if (lx >= r || rx <= l) {
			return 0;
		}

		if (lx >= l && rx <= r) {
			return tree[x];
		}
		int m = (lx + rx) / 2;
		return sum(l, r, 2 * x + 1, lx, m) + sum(l, r, 2 * x + 2, m, rx);

	}

	// sum from l to r-1
	long long sum(int l, int r) {
		return sum(l, r, 0, 0, size);
	}

};

int main() {
	ifstream fin = ifstream("input_generated.txt");
	int n, k;
	fin >> n >> k;
	vector <long long> v;
	for (int i = 0; i < n; i++) {
		long long t;
		fin >> t;
		v.push_back(t);
	}

	segtree tree = segtree();
	tree.build(v);

	for (int i = 0; i < k; i++){
		int type, l_index;
		long long r_value;
		long long answer;
		fin >> type >> l_index >> r_value;
		if (type == 1) // set
		{
			tree.set(l_index, r_value);
		}
		else // sum
		{
			fin >> answer;
			long long sm = tree.sum(l_index, r_value);
			string TF = (answer == sm) ? "True" : "False";
			cout << sm << " " << TF << endl;
		}
	}
}