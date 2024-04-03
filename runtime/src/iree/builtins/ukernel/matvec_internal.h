#ifndef IREE_BUILTINS_UKERNEL_MATVEC_INTERNAL_H_
#define IREE_BUILTINS_UKERNEL_MATVEC_INTERNAL_H_

#include "iree/builtins/ukernel/common.h"

// Tile kernel declarations. Prototype matches iree_uk_matvec_tile_func_t.
#define IREE_UK_MATVEC_TILE_FUNC_DECL(NAME)         \
  void NAME(void* IREE_UK_RESTRICT out_tile,        \
            const void* IREE_UK_RESTRICT lhs_panel, \
            const void* IREE_UK_RESTRICT rhs_panel, \
            const iree_uk_matvec_params_t* params);

#define IREE_UK_MATVEC_TILE_FUNC_IMPL_FOR(GENERIC_FUNC, FUNC) \
  void FUNC(void* IREE_UK_RESTRICT out_tile,                     \
            const void* IREE_UK_RESTRICT lhs_panel,              \
            const void* IREE_UK_RESTRICT rhs_panel,              \
            const iree_uk_matvec_params_t* params) {             \
    GENERIC_FUNC(out_tile, lhs_panel, rhs_panel, params);        \
  }

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
  iree_uk_index_t M;
  iree_uk_index_t N;
  iree_uk_index_t OUT_D;
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
    iree_uk_index_t out_offset, iree_uk_index_t out_stride0, iree_uk_index_t M,
    iree_uk_index_t N, iree_uk_index_t OUT_D, const iree_uk_uint64_t* cpu_data);

// Architecture-specific implementation.
// This function here is only the API, the actual implementation is located in arch/*.
iree_uk_matvec_tile_func_t iree_uk_matvec_select_tile_func_arch(
    const iree_uk_matvec_params_t* params);

static void iree_uk_matvec_using_tile_func(
    const iree_uk_matvec_params_t* params,
    iree_uk_matvec_tile_func_t tile_func);

void iree_uk_matvec_p(const iree_uk_matvec_params_t* params);

#endif  // IREE_BUILTINS_UKERNEL_MMT4D_H_
