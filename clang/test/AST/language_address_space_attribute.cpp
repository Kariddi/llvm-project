// RUN: %clang_cc1 %s -ast-dump | FileCheck %s

// Verify that the language address space attribute is
// understood correctly by clang.

void langas() {
  // CHECK: VarDecl {{.*}} x_global '__global int *'
  __attribute__((opencl_global)) int *x_global;

  // CHECK: VarDecl {{.*}} z_global '__global int *'
  [[clang::opencl_global]] int *z_global;

  // CHECK: VarDecl {{.*}} x_local '__local int *'
  __attribute__((opencl_local)) int *x_local;

  // CHECK: VarDecl {{.*}} z_local '__local int *'
  [[clang::opencl_local]] int *z_local;

  // CHECK: VarDecl {{.*}} x_constant '__constant int *'
  __attribute__((opencl_constant)) int *x_constant;

  // CHECK: VarDecl {{.*}} z_constant '__constant int *'
  [[clang::opencl_constant]] int *z_constant;

  // CHECK: VarDecl {{.*}} x_private '__private int *'
  __attribute__((opencl_private)) int *x_private;

  // CHECK: VarDecl {{.*}} z_private '__private int *'
  [[clang::opencl_private]] int *z_private;

  // CHECK: VarDecl {{.*}} x_generic '__generic int *'
  __attribute__((opencl_generic)) int *x_generic;

  // CHECK: VarDecl {{.*}} z_generic '__generic int *'
  [[clang::opencl_generic]] int *z_generic;
}
