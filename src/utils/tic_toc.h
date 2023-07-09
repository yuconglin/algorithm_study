#pragma once

#include <chrono>
#include <cstdlib>
#include <ctime>

namespace Utils {
class TicToc {
 public:
  TicToc() : start_(std::chrono::system_clock::now()) {}

  double TimeCountMs() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
               std::chrono::system_clock::now() - start_)
        .count();
  }

 private:
  std::chrono::time_point<std::chrono::system_clock> start_;
};
}  // namespace Utils
