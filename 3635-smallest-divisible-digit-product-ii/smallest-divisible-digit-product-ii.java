class Solution {

    public String smallestNumber(String num, long t) {

        // Store the original value of t.
        // We'll divide it repeatedly to check if it only contains
        // prime factors that can be formed using digits (2,3,5,7).
        long remainingFactor = t;

        // Remove every possible factor from 2 to 9.
        for (int factor = 2; factor <= 9; factor++) {
            while (remainingFactor % factor == 0) {
                remainingFactor /= factor;
            }
        }

        // If something is still left,
        // it means t contains a prime factor like 11,13...
        // Such factors can never be produced using decimal digits.
        if (remainingFactor > 1) {
            return "-1";
        }

        int len = num.length();

        // requiredFactor[i]
        // stores how much factor is still needed
        // after processing first i digits.
        long[] requiredFactor = new long[len + 1];
        requiredFactor[0] = t;

        // Assume initially we'll try changing the last digit.
        int firstZeroIndex = len - 1;

        // Convert string into character array
        // because characters are easy to modify.
        char[] digits = num.toCharArray();

        // Process every digit from left to right.
        for (int i = 0; i < len; i++) {

            // Zero is not allowed in the final answer.
            // Once we see a zero,
            // we'll start modifying from this position.
            if (digits[i] == '0') {
                firstZeroIndex = i;
                break;
            }

            // Remove the common factors contributed
            // by the current digit.
            requiredFactor[i + 1] =requiredFactor[i] / gcd(requiredFactor[i], digits[i] - '0');
        }

        // If all required factors are already satisfied,
        // then the given number itself is our answer.
        if (requiredFactor[len] == 1) {
            return num;
        }

        // Try modifying digits from right to left.
        // This helps us obtain the smallest possible answer.
        for (int i = firstZeroIndex; i >= 0; i--) {

            // Try every bigger digit at current position.
            while (++digits[i] <= '9') {

                // Calculate remaining factors
                // after choosing this digit.
                long currentNeed =requiredFactor[i] /gcd(requiredFactor[i], digits[i] - '0');

                // Start filling remaining positions
                // using the largest digit first.
                int candidateDigit = 9;

                // Fill suffix greedily.
                for (int j = len - 1; j > i; j--) {

                    // Find the largest digit
                    // that divides currentNeed.
                    while (currentNeed % candidateDigit != 0) {
                        candidateDigit--;
                    }

                    // Remove those factors.
                    currentNeed /= candidateDigit;

                    // Place that digit.
                    digits[j] = (char) ('0' + candidateDigit);
                }

                // If every required factor is covered,
                // we've found the smallest valid answer.
                if (currentNeed == 1) {
                    return new String(digits);
                }
            }
        }

        // If same length answer doesn't exist,
        // we need a longer number.
        StringBuilder answer = new StringBuilder();

        long remaining = t;

        // Build the number using largest digits first.
        // (We'll reverse it later.)
        for (int digit = 9; digit >= 2; digit--) {

            while (remaining % digit == 0) {

                answer.append((char) ('0' + digit));
                remaining /= digit;
            }
        }

        // Add extra '1's if required
        // so that new number becomes longer than original.
        int extraOnes = Math.max(len + 1 - answer.length(), 0);

        while (extraOnes-- > 0) {
            answer.append('1');
        }

        // Reverse because we built digits
        // from largest to smallest.
        return answer.reverse().toString();
    }

    // Standard Euclidean Algorithm
    // Returns Greatest Common Divisor of two numbers.
    private long gcd(long first, long second) {

        while (second != 0) {
            long temp = second;
            second = first % second;
            first = temp;
        }

        return first;
    }
}