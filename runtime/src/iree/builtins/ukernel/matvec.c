// clhuang

#include "iree/builtins/ukernel/matvec.h"
#include "iree/builtins/ukernel/matvec_internal.h"

IREE_UK_EXPORT void iree_uk_custom_matvec(
    const void* lhs_buffer, iree_uk_index_t lhs_offset,
    iree_uk_index_t lhs_stride0, const void* rhs_buffer,
    iree_uk_index_t rhs_offset, iree_uk_index_t rhs_stride0, void* out_buffer,
    iree_uk_index_t out_offset, iree_uk_index_t out_stride0, iree_uk_index_t M,
    iree_uk_index_t N, iree_uk_index_t OUT_D,
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
                                    .M = M,
                                    .N = N,
                                    .OUT_D = OUT_D,
                                    .cpu_data = cpu_data};

  // parse to internal matvec handler.
  iree_uk_matvec_p(&params);
}

// the function will select the tile function based on the type of the tile.
// Currently, the only type is i16i16i16.
// TODO(clhuang): add more tile function.
void iree_uk_matvec_p(const iree_uk_matvec_params_t* params) {
  iree_uk_matvec_tile_func_t tile_func =
      iree_uk_matvec_select_tile_func_arch(params);
  iree_uk_matvec_using_tile_func(params, tile_func);
}





static void iree_uk_matvec_using_tile_func(
    const iree_uk_matvec_params_t* params,
    iree_uk_matvec_tile_func_t tile_func) {
  // const iree_uk_int32_t M = params->M;
  // const iree_uk_int32_t N = params->N;
  // const iree_uk_int16_t OUT_D = params->OUT_D;
  char* out_tile =
      (char*)params->out_buffer + (params->out_offset << 4);
  const char* lhs_panel =
      (const char*)params->lhs_buffer +
      iree_uk_bits_to_bytes_exact(params->lhs_offset << 4);
  const char* rhs_panel =
      (const char*)params->rhs_buffer +
      iree_uk_bits_to_bytes_exact(params->rhs_offset << 4);

  tile_func(out_tile, lhs_panel, rhs_panel, params);
}
