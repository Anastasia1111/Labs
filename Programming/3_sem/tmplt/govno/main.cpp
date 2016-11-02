#include <cstdlib>
#include <iostream>
#include "ok.h"
using namespace std;


int main(int argc, char *argv[])
{
	
	Queue<pair<int, double> > q;
	for(int i=10; i<100; ++i){
		q.push(make_pair(i,i/10.1));
	}	
	while(!q.empty()){
		cout<<q.front().first<<" "<<q.front().second<<endl;
		q.pop();
	}
	system("pause");
	return 0;
}
