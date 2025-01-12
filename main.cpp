#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Segment Tree class
class SegmentTree {
private:
	int n;
	vector<int> tree;

	// Function to build the segment tree
	void buildTree(const vector<int>& arr, int node, int start, int end) {
		if (start == end) {
			tree[node] = arr[start];
		} else {
			int mid = (start + end) / 2;
			buildTree(arr, 2 * node + 1, start, mid);
			buildTree(arr, 2 * node + 2, mid + 1, end);
			tree[node] = merge(tree[2 * node + 1], tree[2 * node + 2]);
		}
	}

	// Function to merge two values
	int merge(int a, int b) {
		return a + b; // For range sum queries
		// return min(a, b); // For range min queries
		// return max(a, b); // For range max queries
	}

	// Function to query the segment tree
	int query(int node, int start, int end, int left, int right) {
		if (left > end || right < start) {
			return 0; // For range sum queries
			// return INT_MAX; // For range min queries
			// return INT_MIN; // For range max queries
		}
		if (left <= start && end <= right) {
			return tree[node];
		}
		int mid = (start + end) / 2;
		return merge(
		           query(2 * node + 1, start, mid, left, right),
		           query(2 * node + 2, mid + 1, end, left, right)
		       );
	}

	// Function to update the segment tree
	void update(int node, int start, int end, int idx, int val) {
		if (start == end) {
			tree[node] = val;
		} else {
			int mid = (start + end) / 2;
			if (idx <= mid) {
				update(2 * node + 1, start, mid, idx, val);
			} else {
				update(2 * node + 2, mid + 1, end, idx, val);
			}
			tree[node] = merge(tree[2 * node + 1], tree[2 * node + 2]);
		}
	}

public:
	// Constructor to initialize the segment tree
	SegmentTree(const vector<int>& arr) {
		n = arr.size();
		tree.resize(4 * n);
		buildTree(arr, 0, 0, n - 1);
	}

	// Function to perform range sum query
	int rangeSumQuery(int left, int right) {
		return query(0, 0, n - 1, left, right);
	}

	// Function to perform range min query
	int rangeMinQuery(int left, int right) {
		return query(0, 0, n - 1, left, right);
	}

	// Function to perform range max query
	int rangeMaxQuery(int left, int right) {
		return query(0, 0, n - 1, left, right);
	}

	// Function to update an element in the segment tree
	void update(int idx, int val) {
		update(0, 0, n - 1, idx, val);
	}

	// Function to perform range GCD query
	int rangeGCDQuery(int left, int right) {
		return queryGCD(0, 0, n - 1, left, right);
	}

	// Function to perform range LCM query
	int rangeLCMQuery(int left, int right) {
		return queryLCM(0, 0, n - 1, left, right);
	}

	// Function to perform range AND query
	int rangeANDQuery(int left, int right) {
		return queryAND(0, 0, n - 1, left, right);
	}

	// Function to perform range OR query
	int rangeORQuery(int left, int right) {
		return queryOR(0, 0, n - 1, left, right);
	}

	// Function to perform range XOR query
	int rangeXORQuery(int left, int right) {
		return queryXOR(0, 0, n - 1, left, right);
	}

	// Function to query the segment tree for GCD
	int queryGCD(int node, int start, int end, int left, int right) {
		if (left > end || right < start) {
			return 0;
		}
		if (left <= start && end <= right) {
			return tree[node];
		}
		int mid = (start + end) / 2;
		return gcd(
		           queryGCD(2 * node + 1, start, mid, left, right),
		           queryGCD(2 * node + 2, mid + 1, end, left, right)
		       );
	}

	// Function to query the segment tree for LCM
	int queryLCM(int node, int start, int end, int left, int right) {
		if (left > end || right < start) {
			return 1;
		}
		if (left <= start && end <= right) {
			return tree[node];
		}
		int mid = (start + end) / 2;
		return lcm(
		           queryLCM(2 * node + 1, start, mid, left, right),
		           queryLCM(2 * node + 2, mid + 1, end, left, right)
		       );
	}

	// Function to query the segment tree for AND
	int queryAND(int node, int start, int end, int left, int right) {
		if (left > end || right < start) {
			return -1;
		}
		if (left <= start && end <= right) {
			return tree[node];
		}
		int mid = (start + end) / 2;
		return queryAND(2 * node + 1, start, mid, left, right) &
		       queryAND(2 * node + 2, mid + 1, end, left, right);
	}

	// Function to query the segment tree for OR
	int queryOR(int node, int start, int end, int left, int right) {
		if (left > end || right < start) {
			return 0;
		}
		if (left <= start && end <= right) {
			return tree[node];
		}
		int mid = (start + end) / 2;
		return queryOR(2 * node + 1, start, mid, left, right) |
		       queryOR(2 * node + 2, mid + 1, end, left, right);
	}

	// Function to query the segment tree for XOR
	int queryXOR(int node, int start, int end, int left, int right) {
		if (left > end || right < start) {
			return 0;
		}
		if (left <= start && end <= right) {
			return tree[node];
		}
		int mid = (start + end) / 2;
		return queryXOR(2 * node + 1, start, mid, left, right) ^
		       queryXOR(2 * node + 2, mid + 1, end, left, right);
	}

	// Function to calculate GCD
	int gcd(int a, int b) {
		if (b == 0) {
			return a;
		}
		return gcd(b, a % b);
	}

	// Function to calculate LCM
	int lcm(int a, int b) {
		return (a * b) / gcd(a, b);
	}
};

int main() {
	vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	SegmentTree segmentTree(arr);

	cout << "Range Sum Query: " << segmentTree.rangeSumQuery(1, 5) << endl;
	cout << "Range Min Query: " << segmentTree.rangeMinQuery(1, 4) << endl;
	cout << "Range Max Query: " << segmentTree.rangeMaxQuery(1, 4) << endl;
	cout << "Range GCD Query: " << segmentTree.rangeGCDQuery(1, 4) << endl;
	cout << "Range LCM Query: " << segmentTree.rangeLCMQuery(1, 4) << endl;
	cout << "Range AND Query: " << segmentTree.rangeANDQuery(1, 4) << endl;
	cout << "Range OR Query: " << segmentTree.rangeORQuery(1, 4) << endl;
	cout << "Range XOR Query: " << segmentTree.rangeXORQuery(1, 4) << endl;

	segmentTree.update(2, 10);
	cout << "Updated Range Sum Query: " << segmentTree.rangeSumQuery(1, 4) << endl;

	return 0;
}
