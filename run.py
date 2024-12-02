# py 万能头文件
from collections import *
from functools import *
from itertools import *
from typing import *
from heapq import *
from bisect import *

from itertools import accumulate
from typing import List  # 导入List类型提示

class Solution:
    def numberOfPoints(self, nums: List[List[int]]) -> int:
        max_end = max(end for _, end in nums)
        diff = [0] * (max_end + 2)
        for start, end in nums:
            diff[start] += 1
            diff[end + 1] -= 1
        return sum(s > 0 for s in accumulate(diff))

# 创建Solution对象
solution = Solution()

# 准备测试数据
nums = [[3,6],[1,5],[4,7]]

# 调用函数并打印结果
result = solution.numberOfPoints(nums)
print("结果为:", result)

