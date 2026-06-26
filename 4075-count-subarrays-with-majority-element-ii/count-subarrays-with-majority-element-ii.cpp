class BinaryIndexedTree {
private:
    int n;
    vector<int> bit;

public:
    BinaryIndexedTree(int sz) {
        n = sz;
        bit.assign(n + 1, 0);
    }

    void update(int idx, int val) {
        while (idx <= n) {
            bit[idx] += val;
            idx += idx & -idx;
        }
    }

    int query(int idx) {
        int res = 0;
        while (idx > 0) {
            res += bit[idx];
            idx -= idx & -idx;
        }
        return res;
    }
};

class Solution {
public:
    long long countMajoritySubarrays(vector<int>& nums, int target) {
        int n = nums.size();

        BinaryIndexedTree bit(2 * n + 1);

        int prefix = n + 1;
        bit.update(prefix, 1);

        long long ans = 0;

        for (int x : nums) {
            if (x == target)
                prefix++;
            else
                prefix--;

            ans += bit.query(prefix - 1);
            bit.update(prefix, 1);
        }

        return ans;
    }
};