// Copyright 2021 The IREE Authors
//
// Licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#ifndef IREE_HAL_ROCM_DIRECT_COMMAND_BUFFER_H_
#define IREE_HAL_ROCM_DIRECT_COMMAND_BUFFER_H_

#include "experimental/rocm/context_wrapper.h"
#include "experimental/rocm/dynamic_symbols.h"
#include "experimental/rocm/rocm_headers.h"
#include "experimental/rocm/tracing.h"
#include "iree/base/api.h"
#include "iree/hal/api.h"

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

typedef struct iree_arena_block_pool_t iree_arena_block_pool_t;

// ROCM Kernel Information Structure
typedef struct {
  hipFunction_t func;
  unsigned int gridDimX;
  unsigned int gridDimY;
  unsigned int gridDimZ;
  unsigned int blockDimX;
  unsigned int blockDimY;
  unsigned int blockDimZ;
  void** kernelParams;
} hip_launch_params;

// Creates a rocm direct command buffer.
iree_status_t iree_hal_rocm_direct_command_buffer_create(
    iree_hal_allocator_t* device_allocator,
    iree_hal_rocm_context_wrapper_t* context,
    iree_hal_rocm_tracing_context_t* tracing_context,
    iree_hal_command_buffer_mode_t mode,
    iree_hal_command_category_t command_categories,
    iree_hal_queue_affinity_t queue_affinity, iree_host_size_t binding_capacity,
    iree_arena_block_pool_t* block_pool,
    iree_hal_command_buffer_t** out_command_buffer);

// Returns true if |command_buffer| is a ROCM command buffer.
bool iree_hal_rocm_direct_command_buffer_isa(
    iree_hal_command_buffer_t* command_buffer);

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

#endif  // IREE_HAL_ROCM_DIRECT_COMMAND_BUFFER_H_
