//
// Created by Yukio on 15/10/2023.
//

#ifndef QALLETS_MATH_H
#define QALLETS_MATH_H

#include <random>

namespace LsKu {

class Math {
 public:
  static int Rand(int randMin, int randMax);
  static int Facto(int n);
  static int Arra(int n, int m);
  static int Comb(int n, int m);
};
}  // namespace LsKu

#endif  // QALLETS_MATH_H
