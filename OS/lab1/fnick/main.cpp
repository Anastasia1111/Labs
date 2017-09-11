#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

template<class T>
class MyList
{
private:
	vector<T> storage;
public:
	MyList()
	{
	};
	
	void push_front(T item) { storage.insert(storage.begin(), item); };
	
	void push_back(T item) { storage.push_back(item); };
	
	T front() { return storage.front(); };
	
	T back() { return storage.back(); };
	
	T el_on_pos(int pos) { return storage.at(pos); };
	
	void pop_front() { storage.erase(storage.begin()); };
	
	void pop_back() { storage.pop_back(); };
	
	void pop(int pos)
	{
		if (pos < storage.size() && pos >= 0)
			storage.erase(storage.begin()+pos);
	}
	
	void clear() { storage.clear(); };
	
	bool empty() { return storage.empty(); };
	
	void print()
	{
		typename vector<T>::iterator it;
		for (it = storage.begin(); it != storage.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
};

int main(int argc, char *argv[])
{
	MyList<int> *list = new MyList<int>;
	for(int i=1; i<=10; i++)
	{
		list->push_front(i);
	}
	cout << list->front() << " " << list->el_on_pos(5) << " " << list->back() << endl; 
	list->print();
	for(int i=1; i<=10; i++)
	{
		list->push_back(i);
	}
	cout << list->front() << " " << list->el_on_pos(5) << " " << list->back() << endl; 
	list->print();
	list->pop_front();
	cout << list->front() << " " << list->el_on_pos(5) << " " << list->back() << endl; 
	list->print();
	list->pop_back();
	cout << list->front() << " " << list->el_on_pos(5) << " " << list->back() << endl; 
	list->print();
	list->pop(5);
	cout << list->front() << " " << list->el_on_pos(5) << " " << list->back() << endl; 
	list->print();
	list->pop(30);
	cout << list->front() << " " << list->el_on_pos(5) << " " << list->back() << endl; 
	list->print();
	cout << "is empty: " << list->empty() << endl;
	list->clear();
	cout << "is empty: " << list->empty() << endl;
	system("PAUSE");
	return EXIT_SUCCESS;
}
