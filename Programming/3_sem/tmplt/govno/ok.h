template<typename T>
class Queue{
	protected:
		struct el{
			T data;
			el * next;
		} * head,* tail;
	public:
		Queue();
		bool empty();
		void push(T data);
		void pop();
		T front();
};
