#include <algorithm>
#include <cstdio>
#include <iostream>
#include <omp.h>
#include <random>
#include <vector>

std::vector<std::mt19937> mts;
std::uniform_real_distribution<> ud(0.0, 1.0);
const int N = 128;
const int OUTER_LOOP = 100;
const int INNER_LOOP = 10000;
std::vector<double> d(N, 0.0);

void func() {
  int tid;
  const double inv = 4.0 / static_cast<double>(OUTER_LOOP * INNER_LOOP);
#pragma omp parallel for schedule(static)
  for (int i = 0; i < N; i++) {
    tid = omp_get_thread_num();
    for (int j = 0; j < INNER_LOOP; j += 1) {
      double x = ud(mts[tid]);
      double y = ud(mts[tid]);
      if (x * x + y * y < 1.0) {
        d[i] += inv;
      }
    }
  }
}

int main() {
  int n = omp_get_max_threads();
  mts.resize(n);
  for (int i = 0; i < n; i++) {
    mts[i].seed(i);
  }
  for (int i = 0; i < OUTER_LOOP; i++) {
    func();
  }
  for (int i = 0; i < N; i++) {
    std::cout << d[i] << std::endl;
  }
}
