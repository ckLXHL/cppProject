#include "handle.h"
#include <string>
#include <vector>
namespace string_handle{
	std::vector<uint32_t> translate(const std::string &st) {
		vector<uint32_t> ret;
		for(int i = 0; i < st.size(); i++) {
			uint32_t word = (unsigned char)st[i];
			if (st[i] & 0x80) {
				word = (word << 8) + (unsigned char)st[i + 1];
				word = (word << 8) + (unsigned char)st[i + 2];
				i += 2;
			}
			ret.push_back(word);
		}
		return ret;
	}
	uint32_t Zi(const std::string &st)
	{
		uint32_t ret = (unsigned char)st[0];
		if (st[0] & 0x80)
		{
			for (int i = 1; i <= 2; i++) {
				ret += (unsigned char)st[i];
			}
		}
		return ret;
	}
	int calLessRound(const std::vector<uint32_t> &st1 ,const std::vector<uint32_t> &st2)
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
