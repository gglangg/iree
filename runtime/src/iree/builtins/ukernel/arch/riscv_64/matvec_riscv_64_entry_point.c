// clhuang: matvec implement in riscv
// TODO: enable rvv intrinsic

#include "iree/builtins/ukernel/arch/riscv_64/common_riscv_64.h"
#include "iree/builtins/ukernel/arch/riscv_64/common_riscv_64_entry_point.h"
#include "iree/builtins/ukernel/matvec.h"

IREE_UK_MATVEC_TILE_FUNC_DECL(iree_uk_matvec_tile_i16i16i16_riscv_64)

// Architecture-specific implementation.
iree_uk_matvec_tile_func_t iree_uk_matvec_select_tile_func_arch(
    const iree_uk_matvec_params_t* params) {
  return iree_uk_matvec_tile_i16i16i16_riscv_64;
}

void iree_uk_matvec_tile_i16i16i16_riscv_64(
    void* IREE_UK_RESTRICT out_tile, const void* IREE_UK_RESTRICT lhs_panel,
    const void* IREE_UK_RESTRICT rhs_panel,
    const iree_uk_matvec_params_t* params) {}
