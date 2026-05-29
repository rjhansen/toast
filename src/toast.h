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
          std::relation<std::iter_value_t<Src>, std::iter_value_t<Src>> Cmp =
              std::less<std::iter_value_t<Src>>>
void quicksort(Src src, Dst dst, size_t sz,
               Cmp cmp = std::less<std::iter_value_t<Src>>()) {
  static auto rng = std::random_device{};

  if (sz <= 1) {
    while (sz--)
      *dst++ = *src++;
    return;
  }

  std::vector<std::iter_value_t<Src>> data_copy(src, src + sz);
  std::shuffle(data_copy.begin(), data_copy.end(), rng);

  const auto pivot = data_copy.at(0);
  auto iter = data_copy.begin() + 1;
  --sz;
  std::vector<std::iter_value_t<Src>> less_eq, greater, sorted_leq, sorted_gtr;
  while (sz > 0) {
    if (!cmp(*iter, pivot))
      *(std::back_inserter(greater))++ = *iter++;
    else
      *(std::back_inserter(less_eq))++ = *iter++;
    --sz;
  }
  quicksort(less_eq.begin(), std::back_inserter(sorted_leq), less_eq.size());
  quicksort(greater.begin(), std::back_inserter(sorted_gtr), greater.size());
  for (const auto &i : sorted_leq)
    *dst++ = i;
  *dst++ = pivot;
  for (const auto &i : sorted_gtr)
    *dst++ = i;
}

template <std::random_access_iterator Src,
          std::output_iterator<std::iter_value_t<Src>> Dst,
          std::relation<std::iter_value_t<Src>, std::iter_value_t<Src>> Cmp =
              std::less<std::iter_value_t<Src>>>
void mergesort(Src src, Dst dst, size_t sz,
               Cmp cmp = std::less<std::iter_value_t<Src>>()) {
  /* Base case: 0- and 1-element sequences are already sorted. */
  if (sz <= 1) {
    while (sz--)
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
