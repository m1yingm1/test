
//力扣模板
按照周赛分数刷题：https://huxulm.github.io/lc-rating/


1.//【模板】恰好装满型 0 - 1 背包
class Solution {
public:
	int lengthOfLongestSubsequence(vector<int>& nums, int target) {
		vector<int> dp(target + 1, INT_MIN);
		dp[0] = 0;
		int sum = 0;
		for (int num : nums) {
			sum = min(sum + num, target);
			for (int j = sum; j >= num; j--) 
				dp[j] = max(dp[j], dp[j - num] + 1);
		}
		return dp[target] > 0 ? dp[target] : -1;
	}
};