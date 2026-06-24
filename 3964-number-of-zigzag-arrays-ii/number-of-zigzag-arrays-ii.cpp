class Solution {
public:
    static constexpr long long MOD = 1000000007LL;

    using Matrix = vector<vector<long long>>;

    Matrix mul(const Matrix& A, const Matrix& B) {
        int n = A.size();
        Matrix C(n, vector<long long>(n, 0));

        for (int i = 0; i < n; i++) {
            for (int k = 0; k < n; k++) {
                if (!A[i][k]) continue;
                long long aik = A[i][k];
                for (int j = 0; j < n; j++) {
                    if (!B[k][j]) continue;
                    C[i][j] = (C[i][j] + aik * B[k][j]) % MOD;
                }
            }
        }
        return C;
    }

    vector<long long> mulMatVec(const Matrix& A,
                                const vector<long long>& v) {
        int n = A.size();
        vector<long long> res(n, 0);

        for (int i = 0; i < n; i++) {
            long long cur = 0;
            for (int j = 0; j < n; j++) {
                cur = (cur + A[i][j] * v[j]) % MOD;
            }
            res[i] = cur;
        }
        return res;
    }

    vector<long long> applyPower(Matrix base,
                                 long long exp,
                                 vector<long long> vec) {
        while (exp > 0) {
            if (exp & 1) vec = mulMatVec(base, vec);
            base = mul(base, base);
            exp >>= 1;
        }
        return vec;
    }

    long long zigZagArrays(int n, int l, int r) {
        int m = r - l + 1;

        Matrix L(m, vector<long long>(m, 0));
        Matrix R(m, vector<long long>(m, 0));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < i; j++) L[i][j] = 1;
            for (int j = i + 1; j < m; j++) R[i][j] = 1;
        }

        Matrix M = mul(L, R);
        Matrix N = mul(R, L);

        vector<long long> U2(m), D2(m);
        for (int v = 0; v < m; v++) {
            U2[v] = v;
            D2[v] = m - 1 - v;
        }

        vector<long long> U, D;
        long long k;

        if (n % 2 == 0) {
            k = (n - 2) / 2;
            U = applyPower(M, k, U2);
            D = applyPower(N, k, D2);
        } else {
            vector<long long> U3 = mulMatVec(L, D2);
            vector<long long> D3 = mulMatVec(R, U2);

            k = (n - 3) / 2;
            U = applyPower(M, k, U3);
            D = applyPower(N, k, D3);
        }

        long long ans = 0;
        for (long long x : U) ans = (ans + x) % MOD;
        for (long long x : D) ans = (ans + x) % MOD;

        return ans;
    }
};