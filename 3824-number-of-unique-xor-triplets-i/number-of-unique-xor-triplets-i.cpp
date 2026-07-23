class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        int n = nums.size();

        if (n < 3) return n;

        int bits = 32 - __builtin_clz(n);   // bit length of n
        return 1 << bits;
    }
};