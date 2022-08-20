from typing import List


def twoSum(nums: List[int], target: int) -> List[int]:
    prevMap = {} # Val : Index
    for i, n in enumerate(nums):
        diff = target - n
        if diff in prevMap:
            return [prevMap[diff], i]
        prevMap[n] = i
    return None

print("The indices of the two sums are: ", twoSum([2,7,11,15], 9))