#include "linear_sorting.h"

#include <gflags/gflags.h>
#include <glog/logging.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <chrono>
#include <numeric>
#include <random>

#include "utils/tic_toc.h"

namespace {
TEST(LinearSortingTest, CountSort) {
  constexpr int kSize = 1e6;
  std::vector<int> nums(kSize);
  std::iota(nums.begin(), nums.end(), 0);

  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(nums.begin(), nums.end(), g);

  Utils::TicToc tic_count_sort;
  const std::vector<int> sorted_nums = CountSort(nums);
  LOG(INFO) << "time used in count sorting is: " << tic_count_sort.TimeCountMs()
            << " [ms].";

  Utils::TicToc tic_other_sort;
  std::sort(nums.begin(), nums.end());
  LOG(INFO) << "time used in comparison based sorting is: "
            << tic_other_sort.TimeCountMs() << " [ms].";

  for (int i = 0; i < kSize; ++i) {
    EXPECT_EQ(nums[i], sorted_nums[i]);
  }
}

TEST(LinearSortingTest, CountSortRadix) {
  std::vector<int> nums;
  for (int i = 10; i < 100; ++i) {
    nums.push_back(i);
  }
  const int n = nums.size();

  std::vector<NumberInfo> number_infos;
  for (int i = 0; i < n; ++i) {
    number_infos.push_back(NumberInfo{.index = i, .digit = nums[i] % 10});
  }

  number_infos = CountSort(number_infos);
  std::vector<int> ans;
  for (const auto& number_info : number_infos) {
    ans.push_back(nums[number_info.index]);
  }

  // Regular sorting.
  std::sort(nums.begin(), nums.end(), [](int a, int b) {
    return (a % 10 < b % 10 || (a % 10 == b % 10 && a / 10 < b / 10));
  });
  EXPECT_EQ(ans.size(), n);

  for (int i = 0; i < n; ++i) {
    EXPECT_EQ(ans[i], nums[i]);
  }
}

TEST(LinearSortingTest, RadixSort) {
  std::vector<int> nums;
  constexpr int kNum = 1e6;
  for (int i = kNum; i < kNum * 10; ++i) {
    nums.push_back(i);
  }

  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(nums.begin(), nums.end(), g);

  Utils::TicToc tic_radix_sort;
  const std::vector<int> ans = RadixSort(nums);
  LOG(INFO) << "time used in radix sorting is: " << tic_radix_sort.TimeCountMs()
            << " [ms].";

  Utils::TicToc tic_other_sort;
  std::sort(nums.begin(), nums.end());
  LOG(INFO) << "time used in comparison based sorting is: "
            << tic_other_sort.TimeCountMs() << " [ms].";

  for (size_t i = 0; i < nums.size(); ++i) {
    EXPECT_EQ(nums[i], ans[i]);
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
