#include "handle.h"
#include <string>
#include <vector>
namespace string_handle{

	void handleLine(std::string &str) {
		for(auto &item: str){
			item = (ispunct(item)? ' ' : item);
			item = (isupper(item)? tolower(item) : item);
		}
	}

	int calLessRound(const std::vector<unsigned> &st1 ,const std::vector<unsigned> &st2)
	{
		std::vector<int> pre(st1.size() + 1, 0);
		std::vector<int> now(st1.size() + 1, 0);
		for (size_t i = 1; i <= st1.size(); i++) {
			pre[i] = i;
		}
		for (size_t i = 1; i <= st2.size(); i++) {
			now[0] = pre[0] + 1;
			for (size_t j = 1; j <= st1.size(); j++) {
				if (st1[j - 1] == st2[i - 1]) {
					now[j] = pre[j - 1];
				} else {
					now[j] = pre[j - 1] < pre[j]?
							 pre[j - 1] : pre[j];
					now[j] = now[j - 1] < now[j]?
							 now[j - 1] : now[j];
					now[j]++;
				}
			}
			swap(now, pre);
		}
		return pre[st1.size()];
	}
}
