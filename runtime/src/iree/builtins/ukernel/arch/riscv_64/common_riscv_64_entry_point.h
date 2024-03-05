// clhuang

#ifndef IREE_BUILTINS_UKERNEL_ARCH_RISCV_64_COMMON_RISCV_64_ENTRY_POINT_H_
#define IREE_BUILTINS_UKERNEL_ARCH_RISCV_64_COMMON_RISCV_64_ENTRY_POINT_H_

#include "iree/builtins/ukernel/common.h"
#include "iree/schemas/cpu_data.h"

#if defined(IREE_DEVICE_STANDALONE)
// Standalone builds (e.g. bitcode) use our own Clang, supporting everything.
#define IREE_UK_BUILD_RISCV_64_BASE
#else
// Compiling with the system toolchain. Include the configured header.
#include "iree/builtins/ukernel/arch/riscv_64/config_riscv_64.h"
#endif

#if defined(IREE_UK_BUILD_RISCV_64_BASE)
// clhuang: TODO: fix cpu spec.
static inline bool iree_uk_cpu_supports_base(const iree_uk_uint64_t* cpu_data) {
  return true;  // iree_uk_all_bits_set(cpu_data[0],
                // IREE_CPU_DATA0_RISCV_64_BASE);
}
#endif  // IREE_UK_BUILD_RISCV_64_BASE

#endif  // IREE_BUILTINS_UKERNEL_ARCH_RISCV_64_COMMON_RISCV_64_ENTRY_POINT_H_
