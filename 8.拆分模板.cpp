/*一维差分模版*/
// 你有一个长为 n 的数组 a，一开始所有元素均为 0。
// 给定一些区间操作，其中 queries[i] = [left, right, x]，
// 你需要把子数组 a[left], a[left+1], ... a[right] 都加上 x。
// 返回所有操作执行完后的数组 a。
vector<int> solve(int n, vector<vector<int>> queries) {
    vector<int> diff(n); // 差分数组
    for (auto &q: queries) {
        int left = q[0], right = q[1], x = q[2];
        diff[left] += x;
        if (right + 1 < n) {
            diff[right + 1] -= x;
        }
    }
    for (int i = 1; i < n; i++) {
        diff[i] += diff[i - 1]; // 直接在差分数组上复原数组 a
    }
    return diff;
}

// 链接：https://leetcode.cn/circle/discuss/FfMCgb/

/*一维差分例子*/
int minMoves(vector<int>& nums, int limit) {
    // 因为差分数组的计算需要更新 r + 1，所以数组的总大小在 limit * 2 + 1 的基础上再 + 1
    vector<int> diff(limit * 2 + 2, 0);
    int n = nums.size();
    for (int i = 0; i < n / 2; i++)
    {
        int A = nums[i];
        int B = nums[n - 1 - i];
        // [2, 2 * limit] 范围 + 2
        diff[2] += 2;
        diff[2 * limit + 1] -= 2;
        // [1 + min(A, B), limit + max(A, B)] 范围 -1
        int left = 1 + min(A, B);
        int right = limit + max(A, B);
        diff[left]--;
        diff[right + 1]++;
        // [A + B] 再 -1    
        left = A + B, right = A + B;
        diff[left]--;
        diff[right + 1]++;
    }
    // 取最小值
    int res = INT_MAX;
    int sum = 0;
    for (int i = 2; i <= 2 * limit; i++)
    {
        sum += diff[i];
        res = min(res, sum);
    }
    return res;
}

// 链接：https://leetcode.cn/problems/minimum-moves-to-make-array-complementary/submissions/

/*二维差分模板*/
vector<vector<int>> rangeAddQueries(int n, vector<vector<int>>& queries) {
    // 二维差分模板
    vector<vector<int>> diff(n + 2, vector<int>(n + 2));
    for (auto& q : queries) {
        int r1 = q[0], c1 = q[1], r2 = q[2], c2 = q[3];
        ++diff[r1 + 1][c1 + 1];
        --diff[r1 + 1][c2 + 2];
        --diff[r2 + 2][c1 + 1];
        ++diff[r2 + 2][c2 + 2];
    }

    // 用二维前缀和复原（原地修改）
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            diff[i][j] += diff[i][j - 1] + diff[i - 1][j] - diff[i - 1][j - 1];
    // 保留中间 n*n 的部分，即为答案
    diff.pop_back(), diff.erase(diff.begin());
    for (auto& row : diff)
        row.pop_back(), row.erase(row.begin());
    return diff;
}
