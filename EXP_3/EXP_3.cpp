#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    vector<vector<int>> countFreq(vector<int>& arr) {
        unordered_map<int,int> freq;
        vector<vector<int>> res;
        for (int num : arr) freq[num]++;
        for (int num : arr) {
            if (freq[num] != -1) {
                res.push_back({num, freq[num]});
                freq[num] = -1;
            }
        }
        return res;
    }
};

int main() {
    Solution sol;
    vector<int> arr = {1, 2, 2, 3, 1, 4, 3, 3};
    vector<vector<int>> ans = sol.countFreq(arr);

    cout << "Element : Frequency\n";
    for (auto &p : ans) {
        cout << p[0] << " : " << p[1] << "\n";
    }

    return 0;
}
