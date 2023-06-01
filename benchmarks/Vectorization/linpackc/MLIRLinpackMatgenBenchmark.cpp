//===- MLIRLinpackMatgenBenchmark.cpp
//-----------------------------------------===//
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//===----------------------------------------------------------------------===//
//
// This file implements the benchmark for buddy-opt tool in buddy-mlir project.
//
//===----------------------------------------------------------------------===//

#include <benchmark.h>
#include <Container.h>
#include <iostream>
#include <vector>

constexpr int N = 8;

extern "C" {
void _mlir_ciface_mlir_linpackcmatgenf64(MemRef<double, 1> *a, long long lda,
                                         long long n, MemRef<double, 1> *b,
                                         MemRef<double, 1> *norma);
}

auto sizesVectorMLIRLinpackCMatgenda = std::vector<double>{N * N};
auto sizesVectorMLIRLinpackCMatgendb = std::vector<double>{N};
auto sizesVectorMLIRLinpackCMatgendnorma = std::vector<double>{1};

MemRef<double, 1> inputMLIRmatgen_daf64(sizesVectorMLIRLinpackCMatgenda,
                                        1145.14);
MemRef<double, 1> inputMLIRmatgen_dbf64(sizesVectorMLIRLinpackCMatgendb,
                                        1145.14);
MemRef<double, 1> inputMLIRmatgen_dnormaf64(sizesVectorMLIRLinpackCMatgendnorma,
                                            1145.14);

static void MLIR_MatgenF64(benchmark::State &state) {
  for (auto _ : state) {
    for (int i = 0; i < state.range(0); ++i) {
      _mlir_ciface_mlir_linpackcmatgenf64(&inputMLIRmatgen_daf64, N, N,
                                          &inputMLIRmatgen_dbf64,
                                          &inputMLIRmatgen_dnormaf64);
    }
  }
}

BENCHMARK(MLIR_MatgenF64)->Arg(1);

void generateResultMLIRLinpackCMatgen() {
  auto sizesVectorMLIRLinpackCMatgenda = std::vector<double>{N * N};
  auto sizesVectorMLIRLinpackCMatgendb = std::vector<double>{N};
  auto sizesVectorMLIRLinpackCMatgendnorma = std::vector<double>{1};

  MemRef<double, 1> inputMLIRmatgen_daf64(sizesVectorMLIRLinpackCMatgenda,
                                          1145.14);
  MemRef<double, 1> inputMLIRmatgen_dbf64(sizesVectorMLIRLinpackCMatgendb,
                                          1145.14);
  MemRef<double, 1> inputMLIRmatgen_dnormaf64(
      sizesVectorMLIRLinpackCMatgendnorma, 1145.14);
  _mlir_ciface_mlir_linpackcmatgenf64(&inputMLIRmatgen_daf64, N, N,
                                      &inputMLIRmatgen_dbf64,
                                      &inputMLIRmatgen_dnormaf64);
    std::cout << "--------------------------------------------------------"
            << std::endl;
  std::cout << "MLIR_LinpackC: MLIR Matgen Operation for 'lda = 8, n = 8'"
            << std::endl;
              std::cout << "f64roll: [ ";
  for (size_t i = 0; i < N; i++) {
    std::cout << inputMLIRmatgen_dbf64.getData()[i] << " ";
  }
  std::cout << "]" << std::endl;
}