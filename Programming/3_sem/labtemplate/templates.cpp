#include <cstdlib>
#include <iostream>

using namespace std;

template <typename T1, typename T2>
	class psevdomap
	{
		private:
			struct pair
			{
				T1 first;
				T2 second;
				bool operator< (pair b)
				{
					if(this->first == b.first)
					{
						return (this->second < b.second) ? true : false;
					}
					return (this->first < b.first) ? true : false;
				}
				
				bool operator== (pair b)
				{
					return ( (this->first == b.first) && (this->second == b.second) );
				}
				
				bool operator> (pair b)
				{
					return (b < *this);
				}
			};
			struct tree
			{
				pair *data;
				tree *left;
				tree *right;	
			};
			tree* head;
			
		public:
			psevdomap();
			
			~psevdomap();
			
			void add(T1, T2);	
	};

template <typename T1, typename T2>
	psevdomap<T1, T2>::psevdomap() : head(NULL)
	{
	}
/*
template <typename T1, typename T2>
	bool pair::operator < (pair <T1, T2> b)
	{
		if(this->first == b.first)
		{
			return (this->second < b.second) ? true : false;
		}
		return (this->first < b.first) ? true : false;
	}
	
template <typename T1, typename T2>
	bool pair::operator == (pair <T1, T2> b)
	{
		return ( (this->first == b.first) && (this->second == b.second) );
	}
	
template <typename T1, typename T2>
	bool pair :: operator > (pair <T1, T2> b)
	{
		return (b < *this);
	}
*/
template <typename T1, typename T2>
	void psevdomap<T1, T2>::add(T1 fm, T2 sm)
	{
		tree* buff = head;
		pair* npair = new pair;
		npair->first = fm;
		npair->second = sm;
		while (buff)
		{
			if(*npair < *(buff->data))
			{
				buff = buff->left;
			} else {
				if(*npair > *(buff->data))
				{
					buff = buff->right;
				} else {
					cout << "Element was created earlier!" << endl;
					delete npair;
					return;
				}
			}
		}
		buff = new tree;
		buff->data = npair;
		buff->left = buff->right = NULL;
	}

int main(void)
{
	return 0;
}
