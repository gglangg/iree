// Copyright 2024 The IREE Authors
//
// Licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

// Ordering matters when multiple lines have the same types and tile shape and
// are supported by the CPU. In that case, the last-enumerated line overrides
// preceding lines. Always go from oldest to shiniest code path.

// clhuang: riscv_64 support type
// uint 8 16 32 64
// int 8 16 32 64
// float 16 32 64


IREE_UK_MMT4D_TILE(riscv_64, f32, f32, f32, 1, 8, 1, _rvv_base)
IREE_UK_MMT4D_TILE(riscv_64, f32, f32, f32, 2, 8, 1, _rvv_base)
IREE_UK_MMT4D_TILE(riscv_64, f32, f32, f32, 4, 8, 1, _rvv_base)
IREE_UK_MMT4D_TILE(riscv_64, f16, f16, f32, 1, 8, 1, _rvv_base)
IREE_UK_MMT4D_TILE(riscv_64, f16, f16, f32, 2, 8, 1, _rvv_base)
IREE_UK_MMT4D_TILE(riscv_64, f16, f16, f32, 4, 8, 1, _rvv_base)
IREE_UK_MMT4D_TILE(riscv_64, f16, f16, f32, 8, 8, 1, _rvv_base)
IREE_UK_MMT4D_TILE(riscv_64, f16, f16, f16, 1, 8, 1, _rvv_base)
IREE_UK_MMT4D_TILE(riscv_64, f16, f16, f16, 2, 8, 1, _rvv_base)
IREE_UK_MMT4D_TILE(riscv_64, f16, f16, f16, 4, 8, 1, _rvv_base)
IREE_UK_MMT4D_TILE(riscv_64, f16, f16, f16, 8, 8, 1, _rvv_base)

IREE_UK_MMT4D_TILE(riscv_64, s8, s8, s32, 1, 8, 1, _rvv_base)
IREE_UK_MMT4D_TILE(riscv_64, s8, s8, s32, 2, 8, 1, _rvv_base)
IREE_UK_MMT4D_TILE(riscv_64, s8, s8, s32, 4, 8, 1, _rvv_base)
IREE_UK_MMT4D_TILE(riscv_64, s8, s8, s32, 8, 8, 1, _rvv_base)
IREE_UK_MMT4D_TILE(riscv_64, s8, s4, s32, 1, 16, 2, _rvv_base)
IREE_UK_MMT4D_TILE(riscv_64, s8, s4, s32, 2, 16, 2, _rvv_base)
IREE_UK_MMT4D_TILE(riscv_64, s8, s4, s32, 4, 16, 2, _rvv_base)
