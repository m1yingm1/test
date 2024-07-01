
//力扣模板
按照周赛分数刷题：https://huxulm.github.io/lc-rating/
git pull
git add .  
git commit  -m  "default"  
git push -u origin main   

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

2.   3193. 统计逆序对的数目
class Solution {
	const int MOD = 1e9 + 7;
public:
	int numberOfPermutations(int n, vector<vector<int>>& requirements) {
		ranges::sort(requirements);
		vector<int> ans(n, -1);
		ans[0] = 0;
		for (auto requirement : requirements)
			ans[requirement[0]] = requirement[1];
		if (ans[0] != 0)
			return 0;
		int m = ranges::max(ans);
		vector<vector<int>> memo(n, vector<int>(m + 1, -1));
		auto dfs = [&](auto&& dfs, int i, int j)->int {
			if (i == 0)
				return 1;
			int& res = memo[i][j];
			if (res != -1)
				return res;
			res = 0;
			int r = ans[i - 1];
			if (r != -1)
			{
				if (r >= j - i && r <= j)
					res = dfs(dfs, i - 1, r);
			}
			else
			{
				for (int k = 0; k <= min(i, j); k++)
					res = (res + dfs(dfs, i - 1, j - k)) % MOD;
			}
			return res;

			};
		return dfs(dfs, n - 1, ans[n - 1]);
	}
};

作者：灵茶山艾府
链接：https://leetcode.cn/problems/count-the-number-of-inversions/solutions/2819143/jiao-ni-yi-bu-bu-si-kao-dpcong-ji-yi-hua-974t/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

3.class Solution {
public:
	int maximalPathQuality(vector<int>& values, vector<vector<int>>& edges, int max_time) {
		int n = values.size();
		vector<vector<pair<int, int>>> dp(n);
		for (auto& edge : edges) {
			int x = edge[0], y = edge[1], t = edge[2];
			dp[x].emplace_back(y, t);
			dp[y].emplace_back(x, t);
		}
		int ans = 0;
		vector<bool> vis(n);
		vis[0] = true;
		auto dfs = [&](auto&& dfs, int x, int sum_time, int sum_value) -> void {
			if (x == 0) 
				ans = max(ans, sum_value);
			for (auto& [y, t] : dp[x]) {
				if (sum_time + t > max_time) 
					continue;
				if (vis[y])
					dfs(dfs, y, sum_time + t, sum_value);
				else {
					vis[y] = true;
					// 每个节点的价值至多算入价值总和中一次
					dfs(dfs, y, sum_time + t, sum_value + values[y]);
					vis[y] = false; // 恢复现场
				}
			}
			};
		dfs(dfs, 0, 0, values[0]);
		return ans;
	}
};