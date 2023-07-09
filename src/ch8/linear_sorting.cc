#include "linear_sorting.h"

#include <algorithm>

std::vector<int> CountSort(const std::vector<int>& A) {
  const int k = *std::max_element(A.begin(), A.end());
  const int n = A.size();
  // C[0..k].
  std::vector<int> C(k + 1);
  for (int i = 0; i < n; ++i) {
    C[A[i]] += 1;
  }

  for (int i = 1; i <= k; ++i) {
    C[i] += C[i - 1];
  }

  std::vector<int> B(n);
  for (int j = n - 1; j >= 0; --j) {
    // B is a 0-index array and therefore we used [C[A[j]] - 1] as the index.
    B[C[A[j]] - 1] = A[j];
    C[A[j]] -= 1;
  }

  return B;
}

std::vector<NumberInfo> CountSort(const std::vector<NumberInfo>& number_infos) {
  const int k = std::max_element(number_infos.begin(), number_infos.end(),
                                 [](const auto& a, const auto& b) {
                                   return a.digit < b.digit;
                                 })
                    ->digit;
  const int n = number_infos.size();
  // C[0..k].
  std::vector<int> C(k + 1);
  for (int i = 0; i < n; ++i) {
    C[number_infos[i].digit] += 1;
  }

  for (int i = 1; i <= k; ++i) {
    C[i] += C[i - 1];
  }

  std::vector<NumberInfo> B(n);
  for (int j = n - 1; j >= 0; --j) {
    // B is a 0-index array and therefore we used [C[A[j]] - 1] as the index.
    B[C[number_infos[j].digit] - 1] = number_infos[j];
    C[number_infos[j].digit] -= 1;
  }

  return B;
}

std::vector<int> RadixSort(const std::vector<int>& nums) {
  int digits = 0;
  int number = nums[0];
  while (number != 0) {
    number /= 10;
    ++digits;
  }

  const int n = nums.size();
  std::vector<NumberInfo> number_infos;
  for (int i = 0; i < n; ++i) {
    number_infos.push_back(NumberInfo{.index = i, .digit = nums[i] % 10});
  }

  int division = 1;
  for (int k = 0; k < digits; ++k) {
    number_infos = CountSort(number_infos);
    if (k == digits - 1) {
      break;
    }
    division *= 10;
    for (int i = 0; i < n; ++i) {
      number_infos[i].digit = (nums[number_infos[i].index] / division) % 10;
    }
  }

  std::vector<int> ans(n);
  for (int i = 0; i < n; ++i) {
    ans[i] = nums[number_infos[i].index];
  }
  return ans;
}
