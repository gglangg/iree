// Copyright 2024 The IREE Authors
//
// Licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "iree/builtins/ukernel/arch/riscv_64/common_riscv_64.h"
#include "iree/builtins/ukernel/arch/riscv_64/mmt4d_riscv_64_internal.h"

IREE_UK_ATTRIBUTE_ALWAYS_INLINE static inline void
iree_uk_mmt4d_tile_f32f32f32_1x8x1_to_4x8x1_riscv_64_rvv_base(
    void* IREE_UK_RESTRICT out_tile, const void* IREE_UK_RESTRICT lhs_panel,
    const void* IREE_UK_RESTRICT rhs_panel,
    const iree_uk_mmt4d_params_t* params, int M0) {
  IREE_UK_ASSERT(M0 >= 1 && M0 <= 4 && iree_uk_is_po2_u32(M0));
  const float* IREE_UK_RESTRICT lhs_ptr = lhs_panel;
  const float* IREE_UK_RESTRICT rhs_ptr = rhs_panel;
  float* IREE_UK_RESTRICT out_ptr = out_tile;

  vfloat32m2_t acc_0, acc_1, acc_2, acc_3;

  size_t vlmax = __riscv_vsetvlmax_e32m1();
  unsigned long vlenb = __riscv_vlenb();

  if (params->flags & IREE_UK_FLAG_MMT4D_ACCUMULATE) {
    if (M0 == 1) {
      acc_0 = __riscv_vle32_v_f32m2(out_ptr, 8);
    } else if (M0 == 2) {
      acc_0 = __riscv_vle32_v_f32m2(out_ptr, 8);
      acc_1 = __riscv_vle32_v_f32m2(out_ptr + 8, 8);
    } else {
      acc_0 = __riscv_vle32_v_f32m2(out_ptr, 8);
      acc_1 = __riscv_vle32_v_f32m2(out_ptr + 8, 8);
      acc_2 = __riscv_vle32_v_f32m2(out_ptr + 16, 8);
      acc_3 = __riscv_vle32_v_f32m2(out_ptr + 24, 8);
    }
  } else {
    if (M0 == 1) {
      acc_0 = __riscv_vfmv_v_f_f32m2(0, 8);
    } else if (M0 == 2) {
      acc_0 = __riscv_vfmv_v_f_f32m2(0, 8);
      acc_1 = __riscv_vfmv_v_f_f32m2(0, 8);
    } else {
      acc_0 = __riscv_vfmv_v_f_f32m2(0, 8);
      acc_1 = __riscv_vfmv_v_f_f32m2(0, 8);
      acc_2 = __riscv_vfmv_v_f_f32m2(0, 8);
      acc_3 = __riscv_vfmv_v_f_f32m2(0, 8);
    }
  }

  for (int k = 0; k < params->K; ++k) {
    vfloat32m2_t rhs = __riscv_vle32_v_f32m2(rhs_ptr, 8);
    rhs_ptr += 8;
    if (M0 == 1) {
      acc_0 = __riscv_vfmacc_vf_f32m2(acc_0, *lhs_ptr++, rhs, 8);
    } else if (M0 == 2) {
      acc_0 = __riscv_vfmacc_vf_f32m2(acc_0, *lhs_ptr++, rhs, 8);
      acc_1 = __riscv_vfmacc_vf_f32m2(acc_1, *lhs_ptr++, rhs, 8);
    } else {
      acc_0 = __riscv_vfmacc_vf_f32m2(acc_0, *lhs_ptr++, rhs, 8);
      acc_1 = __riscv_vfmacc_vf_f32m2(acc_1, *lhs_ptr++, rhs, 8);
      acc_2 = __riscv_vfmacc_vf_f32m2(acc_0, *lhs_ptr++, rhs, 8);
      acc_3 = __riscv_vfmacc_vf_f32m2(acc_1, *lhs_ptr++, rhs, 8);
    }
  }

  if (M0 == 1) {
    __riscv_vse32_v_f32m2(out_ptr, acc_0, 8);
  } else if (M0 == 2) {
    __riscv_vse32_v_f32m2(out_ptr, acc_0, 8);
    out_ptr += 8;
    __riscv_vse32_v_f32m2(out_ptr, acc_1, 8);
  } else {
    __riscv_vse32_v_f32m2(out_ptr, acc_0, 8);
    out_ptr += 8;
    __riscv_vse32_v_f32m2(out_ptr, acc_1, 8);
    out_ptr += 8;
    __riscv_vse32_v_f32m2(out_ptr, acc_2, 8);
    out_ptr += 8;
    __riscv_vse32_v_f32m2(out_ptr, acc_3, 8);
  }
}

IREE_UK_MMT4D_TILE_FUNC_IMPL_FOR_M0(
    iree_uk_mmt4d_tile_f32f32f32_1x8x1_to_4x8x1_riscv_64_rvv_base,
    iree_uk_mmt4d_tile_f32f32f32_1x8x1_riscv_64_rvv_base, 1)
IREE_UK_MMT4D_TILE_FUNC_IMPL_FOR_M0(
    iree_uk_mmt4d_tile_f32f32f32_1x8x1_to_4x8x1_riscv_64_rvv_base,
    iree_uk_mmt4d_tile_f32f32f32_2x8x1_riscv_64_rvv_base, 2)
IREE_UK_MMT4D_TILE_FUNC_IMPL_FOR_M0(
    iree_uk_mmt4d_tile_f32f32f32_1x8x1_to_4x8x1_riscv_64_rvv_base,
    iree_uk_mmt4d_tile_f32f32f32_4x8x1_riscv_64_rvv_base, 4)

// Shared implementation for f16f16f16 and f16f16f32.
// In the f16f16f16 case, intermediate roundings are skipped. This function
// should only be used if IREE_UK_FLAG_MMT4D_SKIP_INTERMEDIATE_ROUNDINGS is set.
IREE_UK_ATTRIBUTE_ALWAYS_INLINE static inline void
iree_uk_mmt4d_tile_f16f16fXX_1x16x1_to_16x16x1_riscv_64_rvv_base(
    void* IREE_UK_RESTRICT out_tile, const void* IREE_UK_RESTRICT lhs_panel,
    const void* IREE_UK_RESTRICT rhs_panel,
    const iree_uk_mmt4d_params_t* params, iree_uk_type_t acc_type, int M0) {
  // TODO(clhuang)
}

IREE_UK_ATTRIBUTE_ALWAYS_INLINE
static inline void
iree_uk_mmt4d_tile_f16f16f32_1x16x1_to_16x16x1_riscv_64_rvv_base(
    void* IREE_UK_RESTRICT out_tile, const void* IREE_UK_RESTRICT lhs_panel,
    const void* IREE_UK_RESTRICT rhs_panel,
    const iree_uk_mmt4d_params_t* params, int M0) {
  iree_uk_mmt4d_tile_f16f16fXX_1x16x1_to_16x16x1_riscv_64_rvv_base(
      out_tile, lhs_panel, rhs_panel, params, IREE_UK_TYPE_FLOAT_32, M0);
}

IREE_UK_ATTRIBUTE_ALWAYS_INLINE
static inline void
iree_uk_mmt4d_tile_f16f16f16_1x16x1_to_16x16x1_riscv_64_rvv_base(
    void* IREE_UK_RESTRICT out_tile, const void* IREE_UK_RESTRICT lhs_panel,
    const void* IREE_UK_RESTRICT rhs_panel,
    const iree_uk_mmt4d_params_t* params, int M0) {
  iree_uk_mmt4d_tile_f16f16fXX_1x16x1_to_16x16x1_riscv_64_rvv_base(
      out_tile, lhs_panel, rhs_panel, params, IREE_UK_TYPE_FLOAT_16, M0);
}

IREE_UK_MMT4D_TILE_FUNC_IMPL_FOR_M0(
    iree_uk_mmt4d_tile_f16f16f32_1x16x1_to_16x16x1_riscv_64_rvv_base,
    iree_uk_mmt4d_tile_f16f16f32_1x16x1_riscv_64_rvv_base, 1)
IREE_UK_MMT4D_TILE_FUNC_IMPL_FOR_M0(
    iree_uk_mmt4d_tile_f16f16f32_1x16x1_to_16x16x1_riscv_64_rvv_base,
    iree_uk_mmt4d_tile_f16f16f32_2x16x1_riscv_64_rvv_base, 2)
IREE_UK_MMT4D_TILE_FUNC_IMPL_FOR_M0(
    iree_uk_mmt4d_tile_f16f16f32_1x16x1_to_16x16x1_riscv_64_rvv_base,
    iree_uk_mmt4d_tile_f16f16f32_4x16x1_riscv_64_rvv_base, 4)
IREE_UK_MMT4D_TILE_FUNC_IMPL_FOR_M0(
    iree_uk_mmt4d_tile_f16f16f32_1x16x1_to_16x16x1_riscv_64_rvv_base,
    iree_uk_mmt4d_tile_f16f16f32_8x16x1_riscv_64_rvv_base, 8)
IREE_UK_MMT4D_TILE_FUNC_IMPL_FOR_M0(
    iree_uk_mmt4d_tile_f16f16f32_1x16x1_to_16x16x1_riscv_64_rvv_base,
    iree_uk_mmt4d_tile_f16f16f32_16x16x1_riscv_64_rvv_base, 16)

IREE_UK_MMT4D_TILE_FUNC_IMPL_FOR_M0(
    iree_uk_mmt4d_tile_f16f16f16_1x16x1_to_16x16x1_riscv_64_rvv_base,
    iree_uk_mmt4d_tile_f16f16f16_1x16x1_riscv_64_rvv_base, 1)
IREE_UK_MMT4D_TILE_FUNC_IMPL_FOR_M0(
    iree_uk_mmt4d_tile_f16f16f16_1x16x1_to_16x16x1_riscv_64_rvv_base,
    iree_uk_mmt4d_tile_f16f16f16_2x16x1_riscv_64_rvv_base, 2)
IREE_UK_MMT4D_TILE_FUNC_IMPL_FOR_M0(
    iree_uk_mmt4d_tile_f16f16f16_1x16x1_to_16x16x1_riscv_64_rvv_base,
    iree_uk_mmt4d_tile_f16f16f16_4x16x1_riscv_64_rvv_base, 4)
IREE_UK_MMT4D_TILE_FUNC_IMPL_FOR_M0(
    iree_uk_mmt4d_tile_f16f16f16_1x16x1_to_16x16x1_riscv_64_rvv_base,
    iree_uk_mmt4d_tile_f16f16f16_8x16x1_riscv_64_rvv_base, 8)
IREE_UK_MMT4D_TILE_FUNC_IMPL_FOR_M0(
    iree_uk_mmt4d_tile_f16f16f16_1x16x1_to_16x16x1_riscv_64_rvv_base,
    iree_uk_mmt4d_tile_f16f16f16_16x16x1_riscv_64_rvv_base, 16)

IREE_UK_ATTRIBUTE_ALWAYS_INLINE static inline void
iree_uk_mmt4d_tile_s8s8s32_1x16x2_to_8x16x2_riscv_64_rvv_base(
    void* IREE_UK_RESTRICT out_tile, const void* IREE_UK_RESTRICT lhs_panel,
    const void* IREE_UK_RESTRICT rhs_panel,
    const iree_uk_mmt4d_params_t* params, int M0) {
  // TODO(clhuang)
}

IREE_UK_MMT4D_TILE_FUNC_IMPL_FOR_M0(
    iree_uk_mmt4d_tile_s8s8s32_1x16x2_to_8x16x2_riscv_64_rvv_base,
    iree_uk_mmt4d_tile_s8s8s32_1x16x2_riscv_64_rvv_base, 1)
IREE_UK_MMT4D_TILE_FUNC_IMPL_FOR_M0(
    iree_uk_mmt4d_tile_s8s8s32_1x16x2_to_8x16x2_riscv_64_rvv_base,
    iree_uk_mmt4d_tile_s8s8s32_2x16x2_riscv_64_rvv_base, 2)
IREE_UK_MMT4D_TILE_FUNC_IMPL_FOR_M0(
    iree_uk_mmt4d_tile_s8s8s32_1x16x2_to_8x16x2_riscv_64_rvv_base,
    iree_uk_mmt4d_tile_s8s8s32_4x16x2_riscv_64_rvv_base, 4)
IREE_UK_MMT4D_TILE_FUNC_IMPL_FOR_M0(
    iree_uk_mmt4d_tile_s8s8s32_1x16x2_to_8x16x2_riscv_64_rvv_base,
    iree_uk_mmt4d_tile_s8s8s32_8x16x2_riscv_64_rvv_base, 8)

void iree_uk_mmt4d_tile_s8s8s32_16x16x2_riscv_64_rvv_base(
    void* IREE_UK_RESTRICT out_tile, const void* IREE_UK_RESTRICT lhs_panel,
    const void* IREE_UK_RESTRICT rhs_panel,
    const iree_uk_mmt4d_params_t* params) {
  // TODO(clhuang)
}

IREE_UK_ATTRIBUTE_ALWAYS_INLINE static inline void
iree_uk_mmt4d_tile_s16s16s32_1x16x2_to_16x16x2_riscv_64_rvv_base(
    void* IREE_UK_RESTRICT out_tile, const void* IREE_UK_RESTRICT lhs_panel,
    const void* IREE_UK_RESTRICT rhs_panel,
    const iree_uk_mmt4d_params_t* params, int M0) {
  // TODO(clhuang)
}

IREE_UK_MMT4D_TILE_FUNC_IMPL_FOR_M0(
    iree_uk_mmt4d_tile_s16s16s32_1x16x2_to_16x16x2_riscv_64_rvv_base,
    iree_uk_mmt4d_tile_s16s16s32_1x16x2_riscv_64_rvv_base, 1)
IREE_UK_MMT4D_TILE_FUNC_IMPL_FOR_M0(
    iree_uk_mmt4d_tile_s16s16s32_1x16x2_to_16x16x2_riscv_64_rvv_base,
    iree_uk_mmt4d_tile_s16s16s32_2x16x2_riscv_64_rvv_base, 2)
IREE_UK_MMT4D_TILE_FUNC_IMPL_FOR_M0(
    iree_uk_mmt4d_tile_s16s16s32_1x16x2_to_16x16x2_riscv_64_rvv_base,
    iree_uk_mmt4d_tile_s16s16s32_4x16x2_riscv_64_rvv_base, 4)
IREE_UK_MMT4D_TILE_FUNC_IMPL_FOR_M0(
    iree_uk_mmt4d_tile_s16s16s32_1x16x2_to_16x16x2_riscv_64_rvv_base,
    iree_uk_mmt4d_tile_s16s16s32_8x16x2_riscv_64_rvv_base, 8)
IREE_UK_MMT4D_TILE_FUNC_IMPL_FOR_M0(
    iree_uk_mmt4d_tile_s16s16s32_1x16x2_to_16x16x2_riscv_64_rvv_base,
    iree_uk_mmt4d_tile_s16s16s32_16x16x2_riscv_64_rvv_base, 16)
