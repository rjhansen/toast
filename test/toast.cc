#include "toast.h"
#include <algorithm>
#include <array>
#include <gtest/gtest.h>
#include <random>
#include <string>
#include <vector>

using std::array;
using std::string;
using std::vector;
using std::ranges::fill;
using std::ranges::fill_n;
using std::ranges::shuffle;

using namespace engineering::hansen::toast;

namespace {
static std::mt19937 rng = std::mt19937{std::random_device{}()};
}

TEST(QuickSort, vector_ints) {
  vector unsorted_int{4, 3, 2, 1};
  vector<int> sorted_int;
  shuffle(unsorted_int, rng);
  quicksort(unsorted_int.cbegin(), back_inserter(sorted_int),
            unsorted_int.size());
  for (size_t i = 0; i < sorted_int.size(); i++)
    EXPECT_EQ(sorted_int.at(i), i + 1);
  for (size_t i = 0; i < sorted_int.size() - 1; i++)
    EXPECT_LE(sorted_int.at(i), sorted_int.at(i + 1));
}

TEST(QuickSort, proper_array_floats) {
  array<float, 4> unsorted_float{3.14159, 2.71828, 1.414, 99.9};
  array<float, 4> sorted_float{0.0, 0.0, 0.0, 0.0};
  shuffle(unsorted_float.begin(), unsorted_float.end(), rng);
  fill(sorted_float, 0);
  quicksort(unsorted_float.cbegin(), sorted_float.begin(),
            unsorted_float.size());
  for (size_t i = 0; i < sorted_float.size() - 1; i++)
    EXPECT_LE(sorted_float.at(i), sorted_float.at(i + 1));
}

TEST(QuickSort, c_array_strings) {
  string unsorted_string[] = {"world", "hello"};
  string sorted_string[2] = {"", ""};
  shuffle(unsorted_string, unsorted_string + 2, rng);
  fill_n(sorted_string, 2, "");
  quicksort(unsorted_string, sorted_string, 2);
  for (size_t i = 0; i < 1; i++)
    EXPECT_LE(sorted_string[i], sorted_string[i + 1]);
}

TEST(MergeSort, vector_ints) {
  vector unsorted_int{4, 3, 2, 1};
  vector<int> sorted_int;
  shuffle(unsorted_int.begin(), unsorted_int.end(), rng);
  mergesort(unsorted_int.cbegin(), back_inserter(sorted_int),
            unsorted_int.size());
  for (size_t i = 0; i < sorted_int.size(); i++)
    EXPECT_EQ(sorted_int.at(i), i + 1);
  for (size_t i = 0; i < sorted_int.size() - 1; i++)
    EXPECT_LE(sorted_int.at(i), sorted_int.at(i + 1));
}

TEST(MergeSort, proper_array_floats) {
  array<float, 4> unsorted_float{3.14159, 2.71828, 1.414, 99.9};
  array<float, 4> sorted_float{0.0, 0.0, 0.0, 0.0};
  shuffle(unsorted_float.begin(), unsorted_float.end(), rng);
  fill(sorted_float, 0);
  mergesort(unsorted_float.cbegin(), sorted_float.begin(),
            unsorted_float.size());
  for (size_t i = 0; i < sorted_float.size() - 1; i++)
    EXPECT_LE(sorted_float.at(i), sorted_float.at(i + 1));
}

TEST(MergeSort, c_array_strings) {
  string unsorted_string[] = {"world", "hello"};
  string sorted_string[2] = {"", ""};

  shuffle(unsorted_string, unsorted_string + 2, rng);
  fill_n(sorted_string, 2, "");
  mergesort(unsorted_string, sorted_string, 2);
  for (size_t i = 0; i < 1; i++)
    EXPECT_LE(sorted_string[i], sorted_string[i + 1]);
}
