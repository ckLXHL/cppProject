#ifndef HANDLE_H
#define HANDLE_H 
#include <vector>
#include <string>
namespace string_handle{
	std::vector<uint32_t> translate(const std::string&);
	int calLessRound(const std::vector<uint32_t>&, const std::vector<uint32_t>&);
	struct matchWord
	{
		explicit matchWord(const std::string &st, int cnt, int matchNum):
			word_(st), cnt_(cnt_), matchNum_(matchNum) {};
		std::string word_;
		int cnt_;
		int matchNum_;
		bool operator < (const matchWord &A) const 
		{ return matchNum_ != A.matchNum_? 
			(matchNum_ > A.matchNum_) : 
				(cnt_ < A.cnt_); }
	};
}
#endif  /*HANDLE_H*/
