// clhuang
// TODO (clhuang): hack to solve unrelated functions

#include "iree/builtins/ukernel/mmt4d_internal.h"
#include "iree/builtins/ukernel/pack_internal.h"
#include "iree/builtins/ukernel/query_tile_sizes_internal.h"
#include "iree/builtins/ukernel/unpack_internal.h"

iree_uk_pack_tile_func_t iree_uk_pack_select_tile_func_arch(
    const iree_uk_pack_params_t* params) {
  return 0;
}

iree_uk_mmt4d_tile_func_t iree_uk_mmt4d_select_tile_func_arch(
    const iree_uk_mmt4d_params_t* params) {
  return 0;
}

iree_uk_unpack_tile_func_t iree_uk_unpack_select_tile_func_arch(
    const iree_uk_unpack_params_t* params) {
  return 0;
}

bool iree_uk_query_matmul_tile_sizes_arch(
    const iree_uk_query_tile_sizes_2d_params_t* params,
    iree_uk_matmul_tile_sizes_t* out_matmul_tile_sizes) {
  return true;
}