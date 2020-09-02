def searchRotated(nums, t):
    low, high = 0, len(nums)
    while (low + 1 < high):
        mid = low + (high - low) // 2
        if nums[mid] >= nums[low]:
            if (t >= nums[low] and t <= nums[mid]):
                high = mid
            else:
                low = mid + 1
        else:
            if (t >= nums[mid] and t <= nums[high]):
                low = mid
            else:
                high = mid - 1

    if (nums[high] == t): return high
    if (nums[low] == t): return low


