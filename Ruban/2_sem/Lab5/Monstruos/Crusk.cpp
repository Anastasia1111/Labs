#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <utility>
#include <iostream>
#include <iomanip>

using namespace std;
int n = 7;//num of V
int k;// num of E
int T;
vector<int> p (n);//disjoint-set

int dsu_find (int v) {
	return (v == p[v]) ? v : (T++, p[v] = dsu_find (p[v]));
}

void dsu_union (int a, int b) {
	a = dsu_find (a);
	b = dsu_find (b);
	if (a != b) {
		T++;
		p[a] = b;
	}
}



int main(int argc, char const *argv[])
{
	int i;
	int mas = 0;
	T = 0;
	vector < pair < int, pair<int,int> > > g; // вес - вершина 1 - вершина 2
	g.push_back( make_pair( 20, make_pair( 1, 2)) );
	g.push_back( make_pair( 1, make_pair( 1, 7)) );
	g.push_back( make_pair( 4, make_pair( 2, 7)) );
	g.push_back( make_pair( 23, make_pair( 1, 6)) );
	g.push_back( make_pair( 36, make_pair( 6, 7)) );
	g.push_back( make_pair( 9, make_pair( 3, 7)) );
	g.push_back( make_pair( 5, make_pair( 2, 3)) );
	g.push_back( make_pair( 28, make_pair( 5, 6)) );
	g.push_back( make_pair( 25, make_pair( 5, 7)) );
	g.push_back( make_pair( 17, make_pair( 5, 4)) );
	g.push_back( make_pair( 16, make_pair( 7, 4)) );
	g.push_back( make_pair( 3, make_pair( 3, 4)) );
	k = g.size();
	cout << "+-----+-----+-----+" << endl;
	cout << "|  A  |  B  | Mas |" << endl;
	for(i = 0; i < k; ++i) {
		int a = g[i].second.first;
		int b = g[i].second.second; 
		int l = g[i].first;
		cout << "+-----+-----+-----+" << endl;
		cout << "|" << setw(5) << a;
		cout << "|" << setw(5) << b;
		cout << "|" << setw(5) << l << "|" << endl;
	}
	cout << "+-----+-----+-----+" << endl << endl;
	vector < pair<int,int> > res;

	sort (g.begin(), g.end());
	T += k*(int)log2(k);
	p.resize (n);
	for (i = 0; i < n; ++i)
		p[i] = i;
	for (i = 0; i < k; ++i) {
		int a = g[i].second.first;
		int b = g[i].second.second; 
		int l = g[i].first;
		if (dsu_find(a) != dsu_find(b)) {
			mas += l;
			T++;
			res.push_back(g[i].second);
			dsu_union(a, b);
		}
	}
	for(int i = 0; i < res.size(); ++i) {
		cout << "<" << res[i].first << ", " << res[i].second << ">" << endl;
	}
	int theoryT = (n-1) * n + (k-n+1) + k * (int)log2(k);
	cout << "Theoretical labour <" << n << " vertexes, "<< k << " edges>: " << theoryT << endl;
	cout << "Practical labour: " << T << endl;
	system("pause");
	return 0;
}
