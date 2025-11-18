#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return {};
        
        vector<int> res(n, -1);
        stack<int> st;
        for (int i = 2 * n - 1; i >= 0; --i) {
            int cur = nums[i % n];

            while (!st.empty() && st.top() <= cur) {
                st.pop();
            }

            if (i < n && !st.empty()) {
                res[i] = st.top();
            }

            st.push(cur);
        }

        return res;
    }
};

int main() {
    vector<int> nums = {1, 2, 1};

    Solution sol;
    vector<int> ans = sol.nextGreaterElements(nums);

    cout << "Output: ";
    for (int x : ans) cout << x << " ";
    cout << endl;

    return 0;
}
