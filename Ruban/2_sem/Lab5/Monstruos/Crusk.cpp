#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <iostream>
#include <iomanip>

using namespace std;
int n = 7;
vector<int> p (n);

int dsu_get (int v) {
	return (v == p[v]) ? v : (p[v] = dsu_get (p[v]));
}

void dsu_unite (int a, int b) {
	a = dsu_get (a);
	b = dsu_get (b);
	if (a != b)
		p[a] = b;
}

int main(int argc, char const *argv[])
{
	int i;
	vector < pair < int, pair<int,int> > > g; // вес - вершина 1 - вершина 2
	g.push_back(make_pair( 20, make_pair( 1, 2)));
	g.push_back(make_pair( 1, make_pair( 1, 7)));
	g.push_back(make_pair( 4, make_pair( 2, 7)));
	g.push_back(make_pair( 23, make_pair( 1, 6)));
	g.push_back(make_pair( 36, make_pair( 6, 7)));
	g.push_back(make_pair( 9, make_pair( 3, 7)));
	g.push_back(make_pair( 5, make_pair( 2, 3)));
	g.push_back(make_pair( 28, make_pair( 5, 6)));
	g.push_back(make_pair( 25, make_pair( 5, 7)));
	g.push_back(make_pair( 17, make_pair( 5, 4)));
	g.push_back(make_pair( 16, make_pair( 7, 4)));
	g.push_back(make_pair( 3, make_pair( 3, 4)));

	cout << "+-----+-----+-----+" << endl;
	cout << "|  A  |  B  | Mas |" << endl;
	for(i = 0; i < g.size(); ++i) {
		int a = g[i].second.first;
		int b = g[i].second.second; 
		int l = g[i].first;
		cout << "+-----+-----+-----+" << endl;
		cout << "|" << setw(5) << a;
		cout << "|" << setw(5) << b;
		cout << "|" << setw(5) << l << "|" << endl;
	}
	cout << "+-----+-----+-----+" << endl << endl;

	int cost = 0;
	vector < pair<int,int> > res;

	sort (g.begin(), g.end());
	p.resize (n);
	for (i = 0; i < n; ++i)
		p[i] = i;
	for (i = 0; i < g.size(); ++i) {
		int a = g[i].second.first;
		int b = g[i].second.second; 
		int l = g[i].first;
		if (dsu_get(a) != dsu_get(b)) {
			cost++;
			res.push_back(g[i].second);
			dsu_unite(a, b);
		}
	}
	for(int i = 0; i < res.size(); ++i) {
		cout << "<" << res[i].first << ", " << res[i].second << ">" << endl;
	}
	system("pause");
	return 0;
}
