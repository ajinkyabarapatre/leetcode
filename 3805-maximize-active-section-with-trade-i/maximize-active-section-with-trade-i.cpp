class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {
        int ones = 0;
        for (char c : s)
            if (c == '1') ones++;

        vector<pair<char, int>> blocks;
        for (char c : s) {
            if (blocks.empty() || blocks.back().first != c)
                blocks.push_back({c, 1});
            else
                blocks.back().second++;
        }

        int gain = 0;

        for (int i = 1; i + 1 < (int)blocks.size(); i++) {
            if (blocks[i - 1].first == '0' &&
                blocks[i].first == '1' &&
                blocks[i + 1].first == '0') {

                gain = max(gain,
                           blocks[i - 1].second + blocks[i + 1].second);
            }
        }

        return ones + gain;
    }
};