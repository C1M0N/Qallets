//
// Created by Yukio on 15/10/2023.
//

#include "../../include/tool/Math.h"

int LsKu::Math::Rand(int randMin, int randMax) {
  std::random_device rd;                                   // 用于获得真随机数的种子
  std::mt19937 gen(rd());                                  // 使用Mersenne Twister伪随机数生成器
  std::uniform_int_distribution<> dist(randMin, randMax);  // 均匀分布的随机数，范围从randMin到randMax
  return dist(gen);
}

int LsKu::Math::Facto(int n){
  int result = 1;
  for (int i = 1;i <= n;i++){
    result *= i;
  }
  return result;
}

int LsKu::Math::Arra(int n, int m){
  int result;
  result = Facto(n) / Facto(n - m);
  return result;
}

int LsKu::Math::Comb(int n, int m) {
  int result;
  result = Arra(n, m) / Facto(m);
  return result;
}

