/* Copyright (c) 2026, Robert J. Hansen. Released under the Apache 2.0
 * license.
 *
 * This code implements a pair of bog-standard algorithms in modern
 * C++23. YOU ALMOST CERTAINLY DON'T WANT TO USE IT.
 *
 * Use std::sort instead.
 *
 * But if you need to learn C++23, you could do a lot worse...
 */

#ifndef HANSEN_TOAST
#define HANSEN_TOAST

#include <algorithm>
#include <concepts>
#include <iterator>
#include <random>
#include <vector>

namespace engineering::hansen::toast {

template <std::random_access_iterator Src,
          std::output_iterator<std::iter_value_t<Src>> Dst,
          std::strict_weak_order<std::iter_value_t<Src>, std::iter_value_t<Src>>
              Cmp = std::less<std::iter_value_t<Src>>>
void quicksort(Src src, Dst dst, std::size_t sz,
               Cmp cmp = std::less<std::iter_value_t<Src>>()) {
  thread_local static std::mt19937 rng = std::mt19937{std::random_device{}()};

  /* Basis case: for 0- and 1-element arrays, just copy the element
   * (if any) and return -- no mucking about with pivots, etc.
   */
  if (sz <= 1) {
    while (sz && sz--)
      *dst++ = *src++;
    return;
  }

  /* Inductive case: QuickSort each half of the list and splice together.
   *
   * This is a little bit memory-wasteful, as it involves making a total
   * of log2 copies of the original dataset. Optimize that before using
   * this on huge datasets.
   *
   * However, before you do that: consider carefully what you're giving
   * up. In-place sorting is inherently a mutable operation. Prefer
   * immutable data when possible.
   *
   * Note: This isn't a stable sort, due to the randomization of the
   * input array.
   */

  std::vector<std::iter_value_t<Src>> data_copy(src, src + sz);
  std::ranges::shuffle(data_copy, rng);

  const auto pivot = data_copy.at(0);
  auto iter = data_copy.begin() + 1;
  --sz;
  std::vector<std::iter_value_t<Src>> less, greater_eq, sorted_lt, sorted_ge;
  while (sz > 0) {
    if (!cmp(*iter, pivot))
      greater_eq.push_back(*iter++);
    else
      less.push_back(*iter++);
    --sz;
  }
  quicksort(less.begin(), std::back_inserter(sorted_lt), less.size(), cmp);
  quicksort(greater_eq.begin(), std::back_inserter(sorted_ge),
            greater_eq.size(), cmp);
  for (const auto &i : sorted_lt)
    *dst++ = i;
  *dst++ = pivot;
  for (const auto &i : sorted_ge)
    *dst++ = i;
}

template <std::random_access_iterator Src,
          std::output_iterator<std::iter_value_t<Src>> Dst,
          std::strict_weak_order<std::iter_value_t<Src>, std::iter_value_t<Src>>
              Cmp = std::less<std::iter_value_t<Src>>>
void mergesort(Src src, Dst dst, std::size_t sz,
               Cmp cmp = std::less<std::iter_value_t<Src>>()) {
  /* Base case: 0- and 1-element sequences are already sorted. */
  if (sz <= 1) {
    while (sz && sz--)
      *dst++ = *src++;
    return;
  }

  /* Inductive case: mergesort each half of the list and merge together.
   *
   * This is a little bit memory-wasteful, as it involves making a total
   * of log2 copies of the original dataset. Optimize that before using
   * this on huge datasets.
   *
   * However, before you do that: consider carefully what you're giving
   * up. In-place sorting is inherently a mutable operation. Prefer
   * immutable data when possible.
   *
   * Note: This IS a stable sort.
   */
  std::vector<std::iter_value_t<Src>> left, right;

  mergesort(src, std::back_inserter(left), sz / 2, cmp);
  mergesort(src + sz / 2, std::back_inserter(right), sz - (sz / 2), cmp);

  auto liter = left.cbegin();
  auto riter = right.cbegin();
  while (liter != left.cend() && riter != right.cend())
    *dst++ = !cmp(*riter, *liter) ? *liter++ : *riter++;
  while (liter != left.cend())
    *dst++ = *liter++;
  while (riter != right.cend())
    *dst++ = *riter++;
}
} // namespace engineering::hansen::toast
#endif
