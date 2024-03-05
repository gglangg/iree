// clhuang

#include "iree/builtins/ukernel/matvec.h"

IREE_UK_EXPORT void iree_uk_custom_matvec(
    const void* lhs_buffer, iree_uk_index_t lhs_offset,
    iree_uk_index_t lhs_stride0, const void* rhs_buffer,
    iree_uk_index_t rhs_offset, iree_uk_index_t rhs_stride0, void* out_buffer,
    iree_uk_index_t out_offset, iree_uk_index_t out_stride0,
    const iree_uk_uint64_t* cpu_data) {
  iree_uk_matvec_params_t params = {.lhs_buffer = lhs_buffer,
                                    .lhs_offset = lhs_offset,
                                    .lhs_stride0 = lhs_stride0,
                                    .rhs_buffer = rhs_buffer,
                                    .rhs_offset = rhs_offset,
                                    .rhs_stride0 = rhs_stride0,
                                    .out_buffer = out_buffer,
                                    .out_offset = out_offset,
                                    .out_stride0 = out_stride0,
                                    .cpu_data = cpu_data};
  iree_uk_matvec_select_tile_func_arch(&params);
}
