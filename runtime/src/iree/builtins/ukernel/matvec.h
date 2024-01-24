#ifndef IREE_BUILTINS_UKERNEL_MATVEC_H_
#define IREE_BUILTINS_UKERNEL_MATVEC_H_

#include "iree/builtins/ukernel/common.h"

// Tile kernel declarations. Prototype matches iree_uk_matvec_tile_func_t.
#define IREE_UK_MATVEC_TILE_FUNC_DECL(NAME)         \
  void NAME(void* IREE_UK_RESTRICT out_tile,        \
            const void* IREE_UK_RESTRICT lhs_panel, \
            const void* IREE_UK_RESTRICT rhs_panel, \
            const iree_uk_matvec_params_t* params);

typedef struct iree_uk_matvec_params_t {
  const void* lhs_buffer;
  iree_uk_index_t lhs_offset;
  iree_uk_index_t lhs_stride0;
  const void* rhs_buffer;
  iree_uk_index_t rhs_offset;
  iree_uk_index_t rhs_stride0;
  void* out_buffer;
  iree_uk_index_t out_offset;
  iree_uk_index_t out_stride0;
  const iree_uk_uint64_t* cpu_data;
} iree_uk_matvec_params_t;

typedef void (*iree_uk_matvec_tile_func_t)(
    void* IREE_UK_RESTRICT out_tile, const void* IREE_UK_RESTRICT lhs_panel,
    const void* IREE_UK_RESTRICT rhs_panel,
    const iree_uk_matvec_params_t* params);

// `matvec` microkernel. Used on LLVMCPU (as well as VMVX), due to difficulty of
// code generation of matrix multiplications kernels.
IREE_UK_EXPORT void iree_uk_custom_matvec(
    const void* lhs_buffer, iree_uk_index_t lhs_offset,
    iree_uk_index_t lhs_stride0, const void* rhs_buffer,
    iree_uk_index_t rhs_offset, iree_uk_index_t rhs_stride0, void* out_buffer,
    iree_uk_index_t out_offset, iree_uk_index_t out_stride0,
    const iree_uk_uint64_t* cpu_data);

// Architecture-specific implementation.
iree_uk_matvec_tile_func_t iree_uk_matvec_select_tile_func_arch(
    const iree_uk_matvec_params_t* params);

#endif  // IREE_BUILTINS_UKERNEL_MMT4D_H_
