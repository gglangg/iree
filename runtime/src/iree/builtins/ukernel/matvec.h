#ifndef IREE_BUILTINS_UKERNEL_MATVEC_H_
#define IREE_BUILTINS_UKERNEL_MATVEC_H_

#include "iree/builtins/ukernel/common.h"
#include "iree/builtins/ukernel/matvec_internal.h"

typedef void (*iree_uk_matvec_tile_func_t)(
    void* IREE_UK_RESTRICT out_tile, const void* IREE_UK_RESTRICT lhs_panel,
    const void* IREE_UK_RESTRICT rhs_panel,
    const iree_uk_matvec_params_t* params);

#endif  // IREE_BUILTINS_UKERNEL_MMT4D_H_
