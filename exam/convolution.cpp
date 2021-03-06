#include <iostream>
#include <thread>
#include <string> 
#include <vector>
#include <cmath>
using namespace std;

#define EUCMOD(a, b)  (a < 0 ? ((a + b) % b) : (a % b))


vector< pair<int, int> > splitWorkload(int n, int t) {
	vector< pair<int, int> > intervals;

	int index = 0;
	int step = n / t;
	int mod = n % t;

	while (index < n) {
		intervals.push_back(pair<int, int>(index, index + step + (mod > 0)));
		index += step + (mod > 0);
		mod--;
	}

	return intervals;
}

void convolution(vector<int> a, vector<int> b, vector<int>& r, int T) {

	if (T == 1)
	{
		for (int i = 0; i < a.size(); i++)
			for (int j = 0; j < a.size(); j++)
				r[i] += a[j] * b[EUCMOD((i - j), a.size())];
	}
	else {
		vector<thread> threads(T);
		vector<pair<int, int>> intervals = splitWorkload(a.size(), T);
		for (int k = 0; k < T; k++)
			threads[k] = thread([&, k]() {
			for (int i = intervals[k].first; i < intervals[k].second; i++)
				for (int j = 0; j < a.size(); j++)
					r[i] += a[j] * b[EUCMOD((i - j), a.size())];
			});

		for (int i = 0; i < T; i++)
			threads[i].join();
	}
	
}

int main() {

	vector<int> a;
	vector<int> b;
	vector<int> r(3, 0);

	convolution({ 1,2,3 }, { 1, 2, 3 }, r, 3);

	for (auto it : r)
		cout << it << " ";
	cout << "\n";

	return 0;
}