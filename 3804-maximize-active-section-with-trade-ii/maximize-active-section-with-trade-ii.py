from bisect import bisect_left, bisect_right
from typing import List


class SegmentTree:
    def __init__(self, values: List[int]):
        self.n = len(values)
        self.tree = [0] * (4 * self.n)

        if self.n > 0:
            self._build(1, 0, self.n - 1, values)

    def _build(self, node: int, left: int, right: int, values: List[int]) -> None:
        if left == right:
            self.tree[node] = values[left]
            return

        mid = (left + right) // 2
        self._build(node * 2, left, mid, values)
        self._build(node * 2 + 1, mid + 1, right, values)
        self.tree[node] = max(self.tree[node * 2], self.tree[node * 2 + 1])

    def query(self, query_left: int, query_right: int) -> int:
        if query_left > query_right:
            return 0

        return self._query(1, 0, self.n - 1, query_left, query_right)

    def _query(self, node: int, left: int, right: int, query_left: int, query_right: int) -> int:
        if query_left <= left and right <= query_right:
            return self.tree[node]

        mid = (left + right) // 2
        answer = 0

        if query_left <= mid:
            answer = max(answer, self._query(node * 2, left, mid, query_left, query_right))

        if query_right > mid:
            answer = max(answer, self._query(node * 2 + 1, mid + 1, right, query_left, query_right))

        return answer


class Solution:
    def maxActiveSectionsAfterTrade(self, s: str, queries: List[List[int]]) -> List[int]:
        n = len(s)
        original_ones = s.count("1")

        zero_lengths = []
        zero_starts = []
        zero_ends = []

        index = 0
        while index < n:
            start = index
            while index < n and s[index] == s[start]:
                index += 1

            if s[start] == "0":
                zero_lengths.append(index - start)
                zero_starts.append(start)
                zero_ends.append(index - 1)

        zero_count = len(zero_lengths)

        if zero_count < 2:
            return [original_ones for _ in queries]

        gains = [zero_lengths[i] + zero_lengths[i + 1] for i in range(zero_count - 1)]
        segment_tree = SegmentTree(gains)

        answers = []

        for left, right in queries:
            first_block = bisect_left(zero_ends, left)
            last_block = bisect_right(zero_starts, right) - 1

            if first_block >= zero_count or last_block < 0 or first_block >= last_block:
                answers.append(original_ones)
                continue

            first_length = zero_ends[first_block] - max(zero_starts[first_block], left) + 1
            last_length = min(zero_ends[last_block], right) - zero_starts[last_block] + 1

            if first_block + 1 == last_block:
                best_gain = first_length + last_length
                answers.append(original_ones + best_gain)
                continue

            left_boundary_gain = first_length + zero_lengths[first_block + 1]
            right_boundary_gain = zero_lengths[last_block - 1] + last_length
            internal_gain = segment_tree.query(first_block + 1, last_block - 2)

            best_gain = max(left_boundary_gain, right_boundary_gain, internal_gain)
            answers.append(original_ones + best_gain)

        return answers