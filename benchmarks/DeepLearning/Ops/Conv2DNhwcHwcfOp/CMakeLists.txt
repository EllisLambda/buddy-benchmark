add_buddy_ops_benchmark(conv-2d-nhwc-hwcf-benchmark
  MLIR Conv2DNhwcHwcf.mlir
  BITCODE conv-2d-nhwc-hwcf.o
  LIBRARY Conv2DNhwcHwcf
  OPTIONS
    -convert-linalg-to-loops 
    -convert-scf-to-cf 
    -convert-linalg-to-llvm 
    -lower-affine 
    --finalize-memref-to-llvm
    --llvm-request-c-wrappers
    -convert-func-to-llvm 
    -reconcile-unrealized-casts
  SOURCE Main.cpp MLIROptBenchmark.cpp
)
