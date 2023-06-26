add_library(linear_sorting
  linear_sorting.cc        
)

ADD_EXECUTABLE(linear_sorting_test linear_sorting_test.cc)

# the order of the dependency is important.
target_link_libraries(linear_sorting_test
  gtest pthread glog gflags linear_sorting
)

