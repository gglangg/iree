// clhuang

#ifndef IREE_BUILTINS_UKERNEL_ARCH_RISCV_64_COMMON_RISCV_64_H_
#define IREE_BUILTINS_UKERNEL_ARCH_RISCV_64_COMMON_RISCV_64_H_

#include "iree/builtins/ukernel/common.h"
#include "iree/builtins/ukernel/matvec.h"

IREE_UK_ATTRIBUTE_ALWAYS_INLINE static inline void iree_uk_matvec_64(
    void* IREE_UK_RESTRICT out_tile, const void* IREE_UK_RESTRICT lhs_panel,
    const void* IREE_UK_RESTRICT rhs_panel,
    const iree_uk_matvec_params_t* params, int M0);

#endif  // IREE_BUILTINS_UKERNEL_ARCH_RISCV_64_COMMON_RISCV_64_H_
