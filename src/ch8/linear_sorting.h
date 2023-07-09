#pragma once

#include <vector>

/// Count sort. It only applies to integers.
/// @p A: [0, ..., n - 1]
std::vector<int> CountSort(const std::vector<int>& A);

/// Count sorting's implementation to help radix sort.
struct NumberInfo {
  int index{};
  int digit{};
};
std::vector<NumberInfo> CountSort(const std::vector<NumberInfo>& number_infos);

/// Radix sort. It assumes that the input numbers of positive integers of the
/// same number of digits.
std::vector<int> RadixSort(const std::vector<int>& A);
