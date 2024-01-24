// clhuang
#include "iree/builtins/ukernel/arch/riscv_64/common_riscv_64.h"
#include "iree/builtins/ukernel/matvec.h"

IREE_UK_ATTRIBUTE_ALWAYS_INLINE static inline void iree_uk_matvec_64(
    void* IREE_UK_RESTRICT out_tile, const void* IREE_UK_RESTRICT lhs_panel,
    const void* IREE_UK_RESTRICT rhs_panel,
    const iree_uk_matvec_params_t* params, int M0) {}