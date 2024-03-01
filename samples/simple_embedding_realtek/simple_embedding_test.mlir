func.func @simple_mul(%arg0: tensor<99999xf32>, %arg1: tensor<99999xf32>) -> tensor<99999xf32> {
  // %0 = arith.mulf %arg0, %arg1 : tensor<99999xf32>
  %0 = stablehlo.add %arg0, %arg1 {rvv_tiling=true}: (tensor<99999xf32>, tensor<99999xf32>) -> tensor<99999xf32>
  
  return %0 : tensor<99999xf32>
}

// func.func @simple_add() -> tensor<1022xf32>  {
//   %0 = stablehlo.constant dense<1.0> : tensor<1022xf32>
//   %1 = util.unfoldable_constant dense<5.0> : tensor<1022xf32>
//   %result = stablehlo.add %0, %1 {rvv_tiling=true}: (tensor<1022xf32>, tensor<1022xf32>) -> tensor<1022xf32>
//   return %result : tensor<1022xf32>  
// }