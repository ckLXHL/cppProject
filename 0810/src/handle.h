#ifndef HANDLE_H
#define HANDLE_H 
namespace string_handle{
	void handleLine(std::string&);
	int calLessRound(const std::string&, const std::string&);

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
