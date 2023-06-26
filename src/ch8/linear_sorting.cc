#include "linear_sorting.h"

#include <algorithm>

std::vector<int> CountSort(const std::vector<int> &A) {
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
