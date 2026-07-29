class Solution {
public:
    static const int LIM = 1000001;

    vector<vector<int>> C;

    void buildComb(int n) {
        C.assign(n + 1, vector<int>());
        for (int i = 0; i <= n; i++) {
            C[i].resize(i + 1);
            C[i][0] = C[i][i] = 1;
            for (int j = 1; j < i; j++) {
                long long x = (long long)C[i - 1][j - 1] + C[i - 1][j];
                if (x > LIM) x = LIM;
                C[i][j] = (int)x;
            }
        }
    }

    int countWays(vector<int>& freq) {
        int total = 0;
        for (int x : freq) total += x;

        long long ans = 1;
        int rem = total;

        for (int f : freq) {
            if (f == 0) continue;
            ans = ans * C[rem][f];
            if (ans > LIM) ans = LIM;
            rem -= f;
        }

        return (int)ans;
    }

    string smallestPalindrome(string s, int k) {
        vector<int> cnt(26, 0);

        for (char c : s)
            cnt[c - 'a']++;

        vector<int> half(26, 0);

        char mid = 0;

        for (int i = 0; i < 26; i++) {
            half[i] = cnt[i] / 2;
            if (cnt[i] % 2)
                mid = char('a' + i);
        }

        int m = s.size() / 2;

        buildComb(m);

        if (countWays(half) < k)
            return "";

        string left;

        for (int pos = 0; pos < m; pos++) {

            for (int c = 0; c < 26; c++) {

                if (half[c] == 0)
                    continue;

                half[c]--;

                int ways = countWays(half);

                if (ways >= k) {
                    left.push_back(char('a' + c));
                    break;
                }

                k -= ways;
                half[c]++;
            }
        }

        string right = left;
        reverse(right.begin(), right.end());

        if (mid)
            return left + string(1, mid) + right;

        return left + right;
    }
};