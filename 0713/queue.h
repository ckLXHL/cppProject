#ifndef __QUEUE_H__
#define __QUEUE_H__
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <algorithm>
using namespace std;
class QueueItem {
	friend class Queue;
	QueueItem(const int &t): item(t), next(0) { }
	int item;
	QueueItem *next;
};
class Queue {
	public:
		Queue(): head(0), tail(0) { }
		Queue(const Queue &Q): head(0), tail(0){ copy_elems(Q); }
		Queue& operator = (const Queue&);
		~Queue(){ destroy(); }
		int& front() { return head->item; }
		const int& front() const { return head->item; }
		void push(const int &);
		void pop();
		ostream &print(ostream &) const;
		bool empty() const{ return head == 0; }
	private:
		QueueItem *head;
		QueueItem *tail;
		void destroy();
		void copy_elems(const Queue&);
};
#endif
