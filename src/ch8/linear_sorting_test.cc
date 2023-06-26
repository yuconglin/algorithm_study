#include "linear_sorting.h"

#include <gflags/gflags.h>
#include <glog/logging.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <chrono>
#include <numeric>
#include <random>

namespace {
TEST(LinearSortingTest, CountSort) {
  constexpr int kSize = 1e6;
  std::vector<int> nums(kSize);
  std::iota(nums.begin(), nums.end(), 0);
  //
  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(nums.begin(), nums.end(), g);

  auto begin = std::chrono::steady_clock::now();
  const std::vector<int> sorted_nums = CountSort(nums);
  auto end = std::chrono::steady_clock::now();
  LOG(INFO) << "time used in count sorting is: "
            << std::chrono::duration_cast<std::chrono::milliseconds>(end -
                                                                     begin)
                   .count()
            << " [ms].";

  begin = std::chrono::steady_clock::now();
  std::sort(nums.begin(), nums.end());
  end = std::chrono::steady_clock::now();
  LOG(INFO) << "time used in comparison based sorting is: "
            << std::chrono::duration_cast<std::chrono::milliseconds>(end -
                                                                     begin)
                   .count()
            << " [ms].";

  for (int i = 0; i < kSize; ++i) {
    EXPECT_EQ(nums[i], sorted_nums[i]);
  }
}
}  // namespace

int main(int argc, char** argv) {
  google::InitGoogleLogging(argv[0]);
  FLAGS_stderrthreshold = google::INFO;
  FLAGS_colorlogtostderr = true;

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
