add_buddy_model_benchmark(inception-v3-benchmark
  OpenCV
  MLIR Inception.mlir
  BITCODE inception-v3-default.o
  LIBRARY InceptionV3Default
  OPTIONS
    --test-linalg-transform-patterns="test-generalize-pad-tensor"
    --linalg-bufferize 
    --convert-linalg-to-loops 
    --func-bufferize 
    --arith-bufferize 
    --tensor-bufferize 
    --finalizing-bufferize 
    --convert-vector-to-scf 
    --convert-scf-to-cf 
    --expand-strided-metadata
    --lower-affine 
    --convert-vector-to-llvm 
    -memref-expand -arith-expand 
    --convert-arith-to-llvm
    --finalize-memref-to-llvm 
    --convert-math-to-llvm
    --llvm-request-c-wrappers
    --convert-func-to-llvm
    --reconcile-unrealized-casts
  SOURCE Main.cpp InceptionBenchmark.cpp
)
