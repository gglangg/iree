#ifndef IREE_BUILTINS_UKERNEL_RISCV_64_MATVEC_INTERNAL_H_
#define IREE_BUILTINS_UKERNEL_RISCV_64_MATVEC_INTERNAL_H_

#include "iree/builtins/ukernel/matvec_internal.h"

IREE_UK_MATVEC_TILE_FUNC_DECL(iree_uk_matvec_tile_i16i16_i16_riscv_64)
IREE_UK_MATVEC_TILE_FUNC_DECL(iree_uk_matvec_tile_i32i32_i32_riscv_64)
IREE_UK_MATVEC_TILE_FUNC_DECL(iree_uk_matvec_tile_f16f16_f16_riscv_64)
IREE_UK_MATVEC_TILE_FUNC_DECL(iree_uk_matvec_tile_f16f16_f16_riscv_64)


#endif  // IREE_BUILTINS_UKERNEL_RISCV_64_MATVEC_INTERNAL_H_