//力扣模板
/*按照周赛分数刷题：https://huxulm.github.io/lc-rating/
git pull
git add .  
git commit  -m  "default"  
git push -u origin main   
*/

// 1. 3193统计逆序对的数目,https://leetcode.cn/problems/count-the-number-of-inversions/solutions/2819143/jiao-ni-yi-bu-bu-si-kao-dpcong-ji-yi-hua-974t/
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

// 2. 2065最大化一张图中的路径价值,https://leetcode.cn/problems/maximum-path-quality-of-a-graph/?envType=daily-question&envId=2024-07-01
class Solution {
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

//3.【模板】恰好装满型 0 - 1 背包
//2915和为目标值的最长子序列的长度，https://leetcode.cn/problems/length-of-the-longest-subsequence-that-sums-to-target/
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

// 4. 416分割等和子集，https://leetcode.cn/problems/partition-equal-subset-sum/
class Solution {
public:
	bool canPartition(vector<int>& nums) {
		int sum = reduce(nums.begin(), nums.end());
		if (sum & 1)
			return false;
		int n = nums.size();
		int halfSum = sum / 2;
		vector<vector<int>> memo(n, vector<int>(halfSum + 1, -1)); 
		auto dfs = [&](auto&& dfs, int i, int target) -> bool {
			if (i < 0) 
				return target == 0;
			int& res = memo[i][target]; 
			if (res != -1)  
				return res;
			if (target >= nums[i])
			{
				res = dfs(dfs, i - 1, target - nums[i]);
				if (res) 
					return true;
			}
			res = dfs(dfs, i - 1, target);
			return res;
		};
		return dfs(dfs, n - 1, halfSum);
	}
};

5.322. 零钱兑换https://leetcode.cn/problems/coin-change/description/

6.518零钱兑换 II,https://leetcode.cn/problems/coin-change-ii/
class Solution {
public:
	int change(int amount, vector<int>& coins) {
		int n = coins.size();
		vector<vector<int>> memo(n, vector<int>(amount + 1, -1));
		auto dfs = [&](auto&& dfs, int i, int amount)->int {
			if (i < 0)
				return amount == 0 ? 1:0;
			int& res = memo[i][amount];
			if (res != -1)
				return res;
			res = 0;
			if (amount >= coins[i])
				res += dfs(dfs, i, amount - coins[i]);
			return res += dfs(dfs, i - 1, amount);
			};
		int ans = dfs(dfs, n - 1, amount);
		return ans ;
	}
};


