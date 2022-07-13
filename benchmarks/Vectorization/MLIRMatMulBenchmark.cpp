//===- MLIRMatMulBenchmark.cpp --------------------------------------------===//
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

#include "Utils/Container.h"
#include <benchmark/benchmark.h>

using namespace cv;
using namespace std;

// Declare the matmul C interface.
extern "C" {
void _mlir_ciface_mlir_matmul(MemRef<float, 2> *input1,
                              MemRef<float, 2> *input2,
                              MemRef<float, 2> *output);
}

// Define input and output array.
float inputArrayMLIRMatMul1[4] = {1, 2, 3, 4};
float inputArrayMLIRMatMul2[4] = {1, 2, 3, 4};
float outputArrayMLIRMatMul[4] = {0};

intptr_t sizesInputArrayMLIRMatMul1[2] = {2, 2};
intptr_t sizesInputArrayMLIRMatMul2[2] = {2, 2};
intptr_t sizesOutputArrayMLIRMatMul[2] = {2, 2};

static void MLIR_MatMul(benchmark::State &state) {
  // Define the MemRef descriptor for input1, input2, and output.
  MemRef<float, 2> inputMLIRMatMul1(inputArrayMLIRMatMul1,
                                    sizesInputArrayMLIRMatMul1);
  MemRef<float, 2> inputMLIRMatMul2(inputArrayMLIRMatMul2,
                                    sizesInputArrayMLIRMatMul2);
  MemRef<float, 2> outputMLIRMatMul(outputArrayMLIRMatMul,
                                    sizesOutputArrayMLIRMatMul);

  for (auto _ : state) {
    for (int i = 0; i < state.range(0); ++i) {
      _mlir_ciface_mlir_matmul(&inputMLIRMatMul1, &inputMLIRMatMul2,
                               &outputMLIRMatMul);
    }
  }
}

// Register benchmarking function.
BENCHMARK(MLIR_MatMul)->Arg(1);

// Generate result image.
void generateResultMLIRMatMul() {
  // Define the MemRef descriptor for input1, intput2, and output.
  MemRef<float, 2> input1(inputArrayMLIRMatMul1, sizesInputArrayMLIRMatMul1);
  MemRef<float, 2> input2(inputArrayMLIRMatMul2, sizesInputArrayMLIRMatMul2);
  MemRef<float, 2> output(outputArrayMLIRMatMul, sizesOutputArrayMLIRMatMul);
  // Run the 2D matmul.
  _mlir_ciface_mlir_matmul(&input1, &input2, &output);
  // Print the output.
  cout << "--------------------------------------------------------" << endl;
  cout << "MLIR_MatMul: MLIR MatMul Operation + Nested Loop" << endl;
  cout << "--------------------------------------------------------" << endl;
  cout << "[ ";
  for (size_t i; i < output.getSize(); i++) {
    cout << output.getData()[i] << " ";
  }
  cout << "]" << endl;
}
