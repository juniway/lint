#include <iostream>
#include <vector>
using namespace std;

int findMagicIndex0(vector<int>& nums) {
    int n = nums.size();
    int flag = 0;
    while (flag < n) {
        if (nums[flag] == flag) {
            return flag;
        } else if (nums[flag] > flag) {
            flag = nums[flag];
        }else{
            flag++;
        }
    }

    return -1;
}

int findMagicIndex1(vector<int>& nums) {
    int low = 0, high = nums.size();
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (nums[mid] != mid) {
            if (nums[mid] >= 0) {
                high = mid;
            } else {
                low = mid + 1;
            }
        } else { // has duplicate?
            low = mid + 1;
        }
    }

    return low - 1;
}
int findMagicIndex(vector<int>& a,int low,int high) {
    int mid=(low+high)/2;
    if(a[mid]==mid) {
       return mid;
    }
    else if(a[mid]<mid) {
       return findMagicIndex(a,low,a[mid]);
    }
    else { //a[mid]>mid
       return findMagicIndex(a,a[mid],high);
    }
}

void testMagicIndex() {
    vector<int> nums = {0, 1, 3, 3, 4};
    // cout << findMagicIndex0(nums) << endl;
    // cout << findMagicIndex1(nums) << endl;
    cout << findMagicIndex(nums, 0, nums.size() - 1) << endl;
}

int main(int argc, char *argv[]) {
    testMagicIndex();
    return 0;
}
