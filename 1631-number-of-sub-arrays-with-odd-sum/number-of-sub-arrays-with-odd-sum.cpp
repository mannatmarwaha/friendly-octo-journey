class Solution {
public:
    int numOfSubarrays(vector<int>& arr) {
        const int MOD = 1e9 + 7;
        int even_count = 1; // Empty prefix sum (0) is even
        int odd_count = 0;
        int prefix_parity = 0;
        long long ans = 0;

        for (int x : arr) {
            prefix_parity ^= (x & 1);
            if (prefix_parity == 1) {
                ans = (ans + even_count) % MOD;
                odd_count++;
            } else {
                ans = (ans + odd_count) % MOD;
                even_count++;
            }
        }

        return static_cast<int>(ans);
    }
};
