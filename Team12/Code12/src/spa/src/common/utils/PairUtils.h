#pragma once

#include <functional>
#include <string>
#include <utility>

using std::hash, std::pair;

// from boost (functional/hash):
// see http://www.boost.org/doc/libs/1_35_0/doc/html/hash/combine.html template
template <class T>
inline void hashCombine(size_t &seed, T const &v) {
  seed ^= std::hash<T>()(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

class PairUtils {
 public:
  // referenced from
  // https://stackoverflow.com/questions/32685540/
  // why-cant-i-compile-an-unordered-map-with-a-pair-as-key
  struct PairHash {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2> &p) const {
      size_t seed{0};
      hashCombine(seed, p.first);
      hashCombine(seed, p.second);
      return seed;
    }
  };
};
