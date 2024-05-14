// Copyright 2023 The IREE Authors
//
// Licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#ifndef IREE_BUILTINS_UKERNEL_ARCH_RISCV_64_COMMON_RISCV_64_H_
#define IREE_BUILTINS_UKERNEL_ARCH_RISCV_64_COMMON_RISCV_64_H_

#ifdef __riscv_v_intrinsic
#include <riscv_vector.h>
#endif /* __riscv_v_intrinsic */

#include "iree/builtins/ukernel/common.h"
#include "iree/schemas/cpu_data.h"

#if defined(IREE_DEVICE_STANDALONE)
// Standalone builds (e.g. bitcode) use our own Clang, supporting everything.
#define IREE_UK_BUILD_RISCV_64_RVV_BASE
#else
// Compiling with the system toolchain. Include the configured header.
#include "iree/builtins/ukernel/arch/riscv_64/config_riscv_64.h"
#endif

static inline bool iree_uk_cpu_riscv_64(const iree_uk_uint64_t* cpu_data) {
  (void)cpu_data;
  return true;
}

static inline bool iree_uk_cpu_riscv_64_rvv_base(
    const iree_uk_uint64_t* cpu_data) {
  return iree_uk_all_bits_set(cpu_data[0], IREE_CPU_DATA0_RISCV_64_RVV);
}

static inline unsigned int log2_vlenb(unsigned long vlenb) { // 128bit=16byte
  unsigned int log2_vlenb = 0;  // This will store the logarithm base 2 of vlenb
                                // Calculate log2(vlenb) using bit manipulation
  log2_vlenb = (vlenb & 0x400)   ? 10 
               : (vlenb & 0x200) ? 9
               : (vlenb & 0x100) ? 8
               : (vlenb & 0x80)  ? 7
                                : 0;  // We only handle up to 1024, 7 is for 128

  IREE_UK_ASSERT(log2_vlenb != 0);
  return log2_vlenb;
}

// static inline matmul_f32f32f32(const float* IREE_UK_RESTRICT lhs_ptr,
//                                const float* IREE_UK_RESTRICT rhs_ptr,
//                                const float* IREE_UK_RESTRICT out_tile, int M0,
//                                int N0, int K0) {
//   size_t vlmax = __riscv_vsetvlmax_e32m1();
//   for (int i = 0; i < N0; ++i) {
//     for (int j = 0; j < M0; ++j) {
//       double* ptr_a = &a[i][0];
//       double* ptr_b = &b[j][0];
//       int k = o;
//       vfloat64m1_t vec_s = __riscv_vfmv_v_f_f64m1(0, vlmax);
//       vfloat64m1_t vec_zero = __riscv_vfmv_v_f_f64m1(0, vlmax);
//       for (size_t vl; k > 0; k -= vl, ptr_a += vl, ptr_b += vl) {
//         vl = __riscv_vsetvl_e64m1(k);

//         vfloat64m1_t vec_a = __riscv_vle64_v_f64m1(ptr_a, vl);
//         vfloat64m1_t vec_b = __riscv_vle64_v_f64m1(ptr_b, vl);

//         vec_s = __riscv_vfmacc_vv_f64m1(vec_s, vec_a, vec_b, vl);
//       }

//       vfloat64m1_t vec_sum;
//       vec_sum = __riscv_vfredusum_vs_f64m1_f64m1(vec_s, vec_zero, vlmax);
//       double sum = __riscv_vfmv_f_s_f64m1_f64(vec_sum);
//       c[i][j] = sum;
//     }
//   }
// }

#endif  // IREE_BUILTINS_UKERNEL_ARCH_RISCV_64_COMMON_RISCV_64_H_
