class Solution {
public:
    int climbStairs(int n, vector<int>& costs) {
        // Initialize DP array with a large value representing infinity
        vector<int> dp(n + 1, 1e9); 
        dp[0] = 0; // Starting point cost is 0
        
        // Compute min cost for each step up to n
        for (int j = 1; j <= n; ++j) {
            for (int k = 1; k <= 3; ++k) {
                if (j - k >= 0) {
                    // costs[j-1] aligns the 1-indexed problem statement with 0-indexed C++ vector
                    dp[j] = min(dp[j], dp[j - k] + costs[j - 1] + k * k);
                }
            }
        }
        
        return dp[n];
    }
};
