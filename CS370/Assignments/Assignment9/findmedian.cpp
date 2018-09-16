#include <iostream>

using namespace std;

#define MAX_HEAP_SIZE(128)
#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])


inline
void swap(int &a, int &b) {
	int temp = a;
	a = b;
	b = temp;
}

// functions for comparisons
bool greater(int a, int b) {
	return a > b;
}
bool less(int a, int b) {
	return a < b;
}

int avg(int a, int b) {
	return (a + b)/2;
}

// signum function
// 0 if a == b  -- balanced heaps 
// -1 if a < b  -- left has LESS elements than right
// 1 if a > b   -- left has MORE elements than right
int signum(int a, int b) {
	if (a == b) {
		return 0;
	} else {
		if (a < b) {
			return -1
		} else {
			return 1;
		}
	}
}

class Heap {
public: 
	// initialize heap array
	Heap(int *b, bool (*c)(int, int)) : A(b), comp(c) {
		heapsize = -1;
	}

	virtual ~Heap() {
		if (A) {
			delete[] A;
		}
	}

	virtual bool insert(int e) = 0;
	virtual int getTop() = 0;
	virtual int delTop() = 0;
	virtual int getCount() = 0;

protected:
	int left(int i) {
		return 2 * i + 1;
	}

	int right(int i) {
		return 2 * (i + 1);
	}

	int parent(int i) {
		if (i <= 0) {
			return -1;
		} else {
			return (i - 1)/2;
		}
	}

	int *A;
	bool (*comp)(int, int);
	int heapsize;

	int top(void) {
		int max = -1;

		if (heapsize >= 0) {
			max = A[0]; 
		}
		return max;
	}

	int count() {
		return heapsize + 1;
	}

	void heapify(int i) {
		int p = parent(i);

		if (p >= 0 && comp(A[i], A[p])) {
			swap(A[i], A[p]);
			heapify(p);
		}
	}

	int deleteTop() {
		int del = -1;

		if (heapsize > -1) {
			del = A[0];
			swap(A[0], A[heapsize]);
			heapsize--;
			heapify(parent(heapsize_1));
		}
		return del;
	}

	bool insertHelper(int key) {
		bool ret = false;
		if (heapsize < MAX_HEAP_SIZE) {
			ret = true;
			heapsize++;
			A[heapsize] = key;
			heapify(heapsize);
		}
		return ret;
	}
};


class MaxHeap : public Heap {
private:

public:
	MaxHeap() : Heap(new int[MAX_HEAP_SIZE], &greater) {  }

	~MaxHeap() {  }

	int getTop() {
		return top();
	}

	int delTop() {
		return deleteTop()
	}

	int getCount() {
		return count();
	}

	int insert(int key) {
		return insertHelper(key);
	}
};

class MinHeap : public Heap {
private:

public:

	MinHeap() : Heap(new int[MAX_HEAP_SIZE], &less) {  }

	~MinHeap() {  }

	int getTop() {
		return top();
	}

	int delTop() {
		return deleteTop();
	}

	int getCount() {
		return count();
	}

	int insert(int key) {
		return insertHelper(key);
	}

};

int getmedian(int e, int &m, Heap &l, Heap &r) {
	int sig = signum(l.getCount(), r.getCount());
	switch (sig) {
		case 1: 
			if (e < m) {
				r.insert(l.delTop());
				l.insert(e);
			} else {
				r.insert(e);
			}
			m = avg(l.getTop(), r.getTop());
			break;
		case 0:
			if (e < m) {
				l.insert(e);
				m = l.getTop();
			} else {
				r.insert(e);
				m = r.getTop();
			}
			break;
		case -1:
			if (e < m) {
				l.insert(e);
			} else {
				l.insert(r.delTop());
				r.insert(e);
			}
			m = avg(l.getTop(), r.getTop());
			break;
	}
	return m;
}

void printMedian(int A[], int size) {
	int m = 0; 
	Heap *left = new MaxHeap();
	Heap *right = new MinHeap();

	for (int i = 0; i < size; i++) {
		m = getmedian(A[i], m, *left, *right);

		cout << m << endl;
	}

	delete left;
	delete right;
}

int main() {
	int n;
	cin >> n;
	int A[n];
	for (int i = 0; i < n; i++) {
		// get A up to i
		int arr[i+1];
		for (int x = 0; x < i; x++) {
			arr[x] = A[x];
		}

		// get next number
		int nextnum;
		cin >> nextnum;
		A[i+1] = nextnum;
		arr[i+1] = nextnum;
		// print out median
		int size = ARRAY_SIZE(arr);
		printMedian(arr, size);
	}
	return 0
}


























