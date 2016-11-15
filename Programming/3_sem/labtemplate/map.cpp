#include <cstdlib>
#include <iostream>

using namespace std;

template <typename T1, typename T2>
	class mymap
		{
			public:
				mymap() : head(NULL) {};
				//~mymap();
				friend class myiterator;
				void myinsert(T1, T2);
				void myerase();
				//myiterator begin();
				//myiterator end();
				T2 operator [](T1 key);
			protected:
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
						if(this->first == b.first)
						{
							return (this->second > b.second) ? true : false;
						}
						return (this->first > b.first) ? true : false;
					}
				};
				
				struct tree 
				{
					pair *data;
					tree *l;
					tree *r;
					int bal;
				} *head;
				
				bool R;
				void LLTurn (tree *&p);
				void RLTurn (tree *&p);
				void LRTurn (tree *&p);
				void RRTurn (tree *&p);
				void AVLTrMaking (pair *data, tree *&p);
		};
		
/*template <typename T1, typename T2>
	class myiterator
	{
		public:
			myiterator();
			~myiterator();
		protected:
			struct spis
			{
				pair *data;
				spis *next;
				spis *prev;
			};
	};
*/
template <typename T1, typename T2>
	void mymap<T1, T2>::myinsert(T1 datakey, T2 dataval)
	{
		pair *data = new pair;
		data->first = datakey;
		data->second = dataval;
		
		AVLTrMaking(data, head);
		cout << "New elem:" << head->data->first << " - " << head->data->second << "is added" << endl;
	}
	
template <typename T1, typename T2>
	void mymap<T1, T2>::myerase()
	{
		cout << "Elem:" << "is erased" << endl;
	}

template <typename T1, typename T2>	
void mymap<T1, T2>::LLTurn (tree *&p){
     tree* q = p->l;
     p->bal = 0;
     q->bal = 0;
     p->l = q->r;
     q->r = p;
     p = q;
}

template <typename T1, typename T2>
void mymap<T1, T2>::RRTurn (tree *&p){
     tree* q = p->r;
     p->bal = 0;
     q->bal = 0;
     p->r = q->l;
     q->l = p;
     p = q;
}

template <typename T1, typename T2>
void mymap<T1, T2>::LRTurn (tree *&p){
     tree* q = p->l;
     tree* r = q->r;
     if (r->bal < 0)
        p->bal = 1;
     else
        p->bal = 0;
     if (r->bal > 0)
        q->bal = -1;
     else
        q->bal = 0;
     r->bal = 0;
     q->r = r->l;
     p->l = r->r;
     r->l = q;
     r->r = p;
     p = r;
}

template <typename T1, typename T2>
void mymap<T1, T2>::RLTurn (tree *&p){
     tree* q = p->r;
     tree* r = q->l;
     if (r->bal > 0)
        p->bal = -1;
     else
        p->bal = 0;
     if (r->bal < 0)
        q->bal = 1;
     else
        q->bal = 0;
     r->bal = 0;
     p->r = r->l;
     q->l = r->r;
     r->l = p;
     r->r = q;
     p = r;
}

template <typename T1, typename T2>
void mymap<T1, T2>::AVLTrMaking (pair *data, tree *&p){
       R = true;
       if (p == NULL){   
            p = new tree;
            p->data = data;
            p->l = p->r = NULL;
            p->bal = 0;
            R = true;
        }
        else {
            if (*(p->data) > *data) {
               AVLTrMaking (data, p->l);
               if (R) {
                  if (p->bal > 0) {
                     p->bal = 0;
                     R = false;
                  } else {
                     if (p->bal == 0) {
                        p->bal=-1;
                        R = true;
                     } else {
                        if (p->l->bal < 0) {
                           LLTurn(p);
                           R = false;
                        } else {
                           LRTurn(p);
                           R = false;
                        }
                     }
                  }
               }
            } else {
                if(*(p->data) < *data) {
                   AVLTrMaking (data, p->r);
                   if (R) {
                      if (p->bal < 0) {
                         p->bal = 0;
                         R = false;
                      } else {
                         if (p->bal == 0) {
                            p->bal = 1;
                            R = true;
                         } else {
                            if (p->r->bal > 0) {
                               RRTurn(p);
                               R = false;
                            } else {
                               RLTurn(p);
                               R = false;
                            }
                         }
                      }
                   }
                } else {
                  if (*(p->data) == *data) {
                     return;
                  }
                }
            }
        }
}

template <typename T1, typename T2>
T2 mymap<T1,T2>::operator [](T1 key)
{
	if(head->data->first == key)
	{
		return head->data->second;
	}
}
	
main()
{
	mymap<int, int> n;
	n.myinsert(1, 2);
	cout << n[1] << endl;
	system("pause");
}
