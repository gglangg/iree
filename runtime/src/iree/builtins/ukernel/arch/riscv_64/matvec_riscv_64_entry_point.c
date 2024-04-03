// clhuang: matvec implement in riscv
// TODO: enable rvv intrinsic

#include "iree/builtins/ukernel/arch/riscv_64/common_riscv_64.h"
#include "iree/builtins/ukernel/arch/riscv_64/common_riscv_64_entry_point.h"
#include "iree/builtins/ukernel/arch/riscv_64/matvec_riscv_64_internal.h"
#include "iree/builtins/ukernel/common.h"
#include "iree/builtins/ukernel/matvec.h"

// Architecture-specific implementation.
// Tghe actual implementation is located here.
iree_uk_matvec_tile_func_t iree_uk_matvec_select_tile_func_arch(
    const iree_uk_matvec_params_t* params) {
  // if case.....__amd64
  // TODO(clhuang): should select different implementation based on the type of
  // the data.
  return iree_uk_matvec_tile_i16i16_i16_riscv_64;        
}
