class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();

        // exact[j] = latest index in word1 from which
        // word2[j...] can be matched exactly.
        vector<int> exact(m + 1, -1);

        // almost[j] = latest index in word1 from which
        // word2[j...] can be matched with at most one mismatch.
        vector<int> almost(m + 1, -1);

        // Empty suffix can always be matched.
        exact[m] = n;
        almost[m] = n;

        // Store positions of each character in word1.
        vector<vector<int>> pos(26);

        for (int i = 0; i < n; i++) {
            pos[word1[i] - 'a'].push_back(i);
        }

        // Find the largest position < limit having character c.
        auto getLast = [&](char c, int limit) -> int {
            auto &v = pos[c - 'a'];

            auto it = lower_bound(v.begin(), v.end(), limit);

            if (it == v.begin())
                return -1;

            --it;
            return *it;
        };

        // --------------------------------------------------
        // Build exact[]
        // --------------------------------------------------

        int limit = n;

        for (int j = m - 1; j >= 0; j--) {
            int p = getLast(word2[j], limit);

            exact[j] = p;

            if (p == -1) {
                // No exact subsequence for this suffix.
                limit = -1;
            } else {
                limit = p;
            }
        }

        // --------------------------------------------------
        // Build almost[]
        // --------------------------------------------------

        for (int j = m - 1; j >= 0; j--) {

            // Option 1:
            // Match word2[j] exactly and use the mismatch
            // somewhere in word2[j+1...].
            int option1 = -1;

            if (almost[j + 1] != -1) {
                option1 = getLast(word2[j], almost[j + 1]);
            }

            // Option 2:
            // Use the one mismatch at word2[j].
            // Then the remaining suffix must be exact.
            int option2 = -1;

            if (exact[j + 1] != -1) {
                auto &v = pos; // just for readability

                // Find latest index < exact[j+1]
                // whose character is NOT word2[j].
                int bound = exact[j + 1];

                for (int c = 0; c < 26; c++) {
                    if (c == word2[j] - 'a')
                        continue;

                    int p = getLast(char('a' + c), bound);
                    option2 = max(option2, p);
                }
            }

            almost[j] = max(option1, option2);
        }

        // --------------------------------------------------
        // Greedily construct answer
        // --------------------------------------------------

        vector<int> ans;

        int prev = -1;
        bool usedMismatch = false;

        for (int j = 0; j < m; j++) {

            bool found = false;

            for (int i = prev + 1; i < n; i++) {

                if (word1[i] == word2[j]) {

                    // We match this character exactly.
                    //
                    // The remaining suffix may use one mismatch.
                    if (i < almost[j + 1]) {
                        ans.push_back(i);
                        prev = i;
                        found = true;
                        break;
                    }

                } else if (!usedMismatch) {

                    // Use our one mismatch here.
                    //
                    // Everything after this must match exactly.
                    if (i < exact[j + 1]) {
                        ans.push_back(i);
                        prev = i;
                        usedMismatch = true;
                        found = true;
                        break;
                    }
                }
            }

            if (!found)
                return {};
        }

        return ans;
    }
};