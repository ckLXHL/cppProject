#include "queue.h"
void Queue::destroy()
{
	while (!empty())
		pop();
}
void Queue::pop()
{
	QueueItem* p = head;
	head = head->next;
	delete p;
}
void Queue::push(const int& val)
{
	QueueItem *pt = new QueueItem(val);
	if(empty())
		head = tail = pt;
	else{
		tail->next = pt;
		tail = pt;
	}
}
void Queue::copy_elems(const Queue& orig)
{
	for(QueueItem *pt = orig.head;
			pt != orig.tail;
			pt = pt -> next){
		push(pt->item);
	}
}
ostream& Queue::print(ostream &os) const {
	os.clear();
	for(QueueItem *pt = head;
			pt != tail;
			pt = pt -> next){
		os << pt -> item << endl;
	}
	os << tail -> item << endl;
	return os;
}
