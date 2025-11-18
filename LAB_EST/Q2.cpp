#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> tails;

        for (int x : nums) {
            auto it = lower_bound(tails.begin(), tails.end(), x);
            if (it == tails.end()) {
                tails.push_back(x);
            } 
            else {
                *it = x;
            }
        }
        return tails.size(); 
    }
};

int main() {
    vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};
    
    Solution sol;
    int ans = sol.lengthOfLIS(nums);

    cout << "Length of LIS = " << ans << endl;

    return 0;
}
