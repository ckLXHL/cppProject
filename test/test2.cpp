#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <memory.h>
using namespace std;
class DP {
        public:
                DP(int n, int m): N_(n), M_(m) { };
				static map<int, bool> num;
                void init();
                void cal();
        private:
                int N_, M_, max_;
                vector<int> A_;
                vector<int> C_;
};
void DP::init() {
        int tmp;
        for (int i = 0; i < N_; i++) {
                scanf("%d", &tmp);
                A_.push_back(tmp);
        }
        for (int i = 0; i < N_; i++) {
                scanf("%d", &tmp);
                C_.push_back(tmp);
        }
		num
		max_ = 0;
}
void DP::cal() {
        int pre;
        cat[0] = 1;
        int sum = 0;
        for(int i = 0; i < N_; i++) {
                for(int j = A_[i]; j <= M_; j++) {
					//检测所有的状态转移
                        if(cat[pre = j - A_[i]] &&
								!cat[j] &&
                                !(dp[pre][0] == A_[i] &&
                                dp[pre][1] == C_[i])) {
							//条件为本状态之前不存在，转移前的
							//状态存在，当前用来状态转移的数是否用完
							//dp[i][0]用来记录用来状态转移的数字
							//dp[i][1]用来记录该数字使用的次数
                                sum += (cat[j] = true);
                                dp[j][0] = A_[i];
                                dp[j][1] = (dp[pre][0] == A_[i] ?
                                                (dp[pre][1] + 1) : 1);
								max_ = max_ > j? max_ : j;
                        }
						if(pre > max_) break;
                }
        }
        printf("%d\n", sum);
}
int main() {
        int n ,m;
        while (scanf("%d %d", &n, &m) != EOF) {
                if((n + m) == 0) break;
                DP ddp(n, m);
                ddp.init();
                ddp.cal();
        }
}
