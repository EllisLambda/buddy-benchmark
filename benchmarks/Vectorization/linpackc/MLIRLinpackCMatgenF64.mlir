func.func @mlir_linpackcmatgenf64(%a:memref<?xf64>,%lda:index,%n:index,%b:memref<?xf64>,%norma:memref<f64>){
    %zero = arith.constant 0:index
    %one = arith.constant 1:index
    %3125 = arith.constant 3125:i64
    %65536= arith.constant 65536:i64
    %1325 = arith.constant 1325:i64
    %f32768 = arith.constant 32768.0:f64
    %f16384 = arith.constant 16384.0:f64
    %f0 = arith.constant 0.0:f64
  
    // Initialize norma
    memref.store %f0, %norma[] : memref<f64>

    // First loop
    %init=scf.for %j = %zero to %n step %one iter_args(%init_rec=%1325)->i64{
        %return_init=scf.for %i = %zero to %n step %one iter_args(%_init_rec=%init_rec)->i64{
            // Compute value for a[lda * j + i]
            %temp_init_muli = arith.muli %3125, %init_rec:i64 
            %temp_init = arith.remsi %temp_init_muli, %65536:i64
            %index_a_muli = arith.muli %lda, %j:index
            %index_a = arith.addi %index_a_muli, %i:index

            // Compute and store a[lda * j + i]
            %casted_init = arith.sitofp %temp_init:i64 to f64
            %ld_elem_sub = arith.subf %casted_init, %f32768:f64
            %st_elem = arith.divf %ld_elem_sub, %f16384:f64 
            memref.store %st_elem, %a[%index_a]:memref<?xf64>

            // Load and update norma if necessary
            %ld_norma = memref.load %norma[]:memref<f64>
            %cmp = "arith.cmpf" (%st_elem, %ld_norma) {predicate=2:i64} :(f64,f64)->i1
            scf.if %cmp {
                memref.store %st_elem, %norma[]:memref<f64>
            }
            scf.yield %temp_init:i64
        }
        scf.yield %return_init:i64
    }

    // Second loop
    scf.for %i = %zero to %n step %one {
        memref.store %f0, %b[%i] : memref<?xf64>
    } 

    // Third loop
    scf.for %j= %zero to %n step %one {
        scf.for %i = %zero to %n step %one {
            %a_index_muli = arith.muli %lda, %j : index
            %a_index = arith.addi %a_index_muli, %i : index

            %a_val = memref.load %a[%a_index] : memref<?xf64>
            %b_val1 = memref.load %b[%i] : memref<?xf64>
            %b_val2 = arith.addf %b_val1, %a_val : f64

            memref.store %b_val2, %b[%i] : memref<?xf64>
        }
    }
    return    
}