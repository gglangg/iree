// // clhuang
#include "iree/builtins/ukernel/arch/riscv_64/common_riscv_64.h"
#include "iree/builtins/ukernel/arch/riscv_64/common_riscv_64_entry_point.h"

#ifdef __riscv_v_intrinsic
#include <riscv_vector.h>
#endif /* __riscv_v_intrinsic */

// Architecture-specific implementation.
IREE_UK_ATTRIBUTE_ALWAYS_INLINE static inline void
iree_uk_matvec_tile_i16i16_i16_impl_riscv_64(
    void* IREE_UK_RESTRICT out_tile, const void* IREE_UK_RESTRICT lhs_panel,
    const void* IREE_UK_RESTRICT rhs_panel,
    const iree_uk_matvec_params_t* params) {
  const iree_uk_int16_t* IREE_UK_RESTRICT lhs_ptr = lhs_panel;
  const iree_uk_int16_t* IREE_UK_RESTRICT rhs_ptr = rhs_panel;
  iree_uk_int16_t* IREE_UK_RESTRICT out_ptr = out_tile;

  size_t vlmax = __riscv_vsetvlmax_e16m1();

  for (int i = 0; i < params->M; i++) {
    size_t vl;
    const iree_uk_int16_t* lv_ptr = &lhs_ptr[i * params->N];
    const iree_uk_int16_t* rv_ptr = &rhs_ptr[0];
    vint16m1_t vec_s = __riscv_vmv_v_x_i16m1(0, vlmax);
    vint16m1_t vec_zero = __riscv_vmv_v_x_i16m1(0, vlmax);
    for (int j = params->N; j > 0; j -= vl, lv_ptr += vl, rv_ptr += vl) {
      vl = __riscv_vsetvl_e16m1(j);
      vint16m1_t vec_a = __riscv_vle16_v_i16m1(lv_ptr, vl);
      vint16m1_t vec_b = __riscv_vle16_v_i16m1(rv_ptr, vl);
      vec_s = __riscv_vmacc_vv_i16m1(vec_s, vec_a, vec_b, vl);
    }
    vint16m1_t vec_sum;
    vec_sum = __riscv_vredsum_vs_i16m1_i16m1(vec_s, vec_zero, vlmax);
    iree_uk_int16_t sum = __riscv_vmv_x_s_i16m1_i16(vec_sum);
    
    out_ptr[i] = sum ;
  }
}

IREE_UK_MATVEC_TILE_FUNC_IMPL_FOR(iree_uk_matvec_tile_i16i16_i16_impl_riscv_64,
                                  iree_uk_matvec_tile_i16i16_i16_riscv_64)