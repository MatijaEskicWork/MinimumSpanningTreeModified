#include <iostream>
#include <vector>
using namespace std;
#define N 10	
#define INF 1000000000

int arr[8];

const int price[10][10] = { {0, 374, 35, 223, 108, 178, 252, 285, 240, 356},
							{374, 0, 27, 166, 433, 199, 135, 95, 136, 17},
							{35, 27, 0, 41, 52, 821, 180, 201, 131, 247},
							{223, 166, 41, 0, 430, 47, 52, 84, 40, 155},
							{108, 433, 52, 430, 0, 453, 478, 344, 389, 423},
							{178, 199, 821, 47, 453, 0, 91, 37, 64, 181},
							{252, 135, 180, 52, 478, 91, 0, 25, 83, 117},
							{285, 95, 201, 84, 344, 37, 25, 0, 51, 42},
							{240, 136, 131, 40, 389, 64, 83, 51, 0, 118},
							{356, 17, 247, 155, 423, 181, 117, 42, 118, 0}};


vector<int> decode(const vector<int>& v, int& cost) {
	int i, j, q = 0;
	int n = v.size() + 2;
	int len = v.size();
	vector<int> V(n);
	vector<int> T(2 * (len + 1));
	vector<int> badRet;
	int eliminateCost = 0;
	int tmpCost = 0;
	int pos;
	for (i = 0; i < len; i++) {
		pos = v[i] - 1;
		V[pos] += 1;
		if (V[pos] > 3) eliminateCost += 150;
	}
	if (eliminateCost >= cost) return badRet;
	for (i = 0; i < len; i++) {
		for (j = 0; j < n; j++) {
			if (V[j] == 0) {
				pos = v[i];
				V[j] = -1;
				T[q++] = j + 1;
				T[q++] = pos;
				V[pos - 1]--;
				break;
			}
		}
	}
	j = 0;
	for (i = 0; i < n; i++) {
		if (V[i] == 0 && j == 0) {
			T[q++] = i + 1;
			j++;
		}
		else if (V[i] == 0 && j == 1) {
			T[q++] = i + 1;
			break;
		}
	}

	vector<int> times(n);
	int ind;
	for (i = 0; i < 2 * (len + 1); i++) {
		ind = T[i] - 1;
		times[ind]++;
		if (times[ind] > 3) tmpCost += 150;
		if (i % 2 == 1) {
			tmpCost += price[ind][T[i - 1] - 1];
		}
		if (tmpCost >= cost) return badRet;
	}
	if (tmpCost < cost) {
		cost = tmpCost;
		return T;
	}


	return badRet;
}


vector<int> variations_with_repetitions(int n, int k, int& minSol) {
	int q;
	int* P = new int[k];
	vector<int> arr(k);
	vector<int> tmp;
	vector<int> solve;
	int cnt = 0;
	for (int i = 0; i < k; i++)
		P[i] = 0;
	do {
		if (cnt % 13000000 == 0) cout << "Working...Please wait..." << endl;
		for (int i = 0; i < k; i++) {
			arr[i] = P[i] + 1;
		}
		tmp = move(decode(arr, minSol));
		cnt++;
		if (tmp.size() > 0) {
			solve = move(tmp);
		}
		q = k - 1;
		while (q >= 0) {
			P[q]++;
			if (P[q] == n) {
				P[q] = 0;
				q--;
			}
			else break;
		}

	} 	while (q >= 0);
	delete[] P;
	return solve;
}




int main() {
	
	vector<int> solve, tmp, T(2*(N-1));
	int minCost = INF, currCost = 0;
	solve = variations_with_repetitions(N, N - 2, minCost);
	cout << endl;
	for (int i = 0; i < solve.size(); i++) {
		if (i % 2 == 1) {
			cout << (char)('A' + (solve[i - 1] - 1)) << " " << (char)('A' + (solve[i] - 1)) << " ";
		}
		if (i < solve.size() - 1) {
			cout << "|";
		}
	}
	cout << endl;
	for (int i = 0; i < solve.size(); i++) {
		if (i % 2 == 1) {
			cout <<solve[i - 1] << " " << solve[i] << " ";
		}
		if (i < solve.size() - 1) {
			cout << "|";
		}
	}
	cout << endl << endl;

	cout << "Minimum cost is: " << minCost << endl;
	return 0;
}