// REQUIRES: gpu
// Disable fallback assert here so, that build process isn't affected
// RUN: %{build} -DSYCL_DISABLE_FALLBACK_ASSERT=1 -o %t1.out %debug_option
// RUN: env SYCL_UR_TRACE=2 SYCL_PROGRAM_COMPILE_OPTIONS=-DENV_COMPILE_OPTS SYCL_PROGRAM_LINK_OPTIONS=-DENV_LINK_OPTS SYCL_PROGRAM_APPEND_COMPILE_OPTIONS=-DENV_APPEND_COMPILE_OPTS SYCL_PROGRAM_APPEND_LINK_OPTIONS=-DENV_APPEND_LINK_OPTS %{run} %t1.out | FileCheck %s
// Check that options are overrided
// RUN: %{build} -Wno-error=unused-command-line-argument -DSYCL_DISABLE_FALLBACK_ASSERT=1 -Xsycl-target-linker=spir64 -DBAR -Xsycl-target-frontend=spir64 -DBAR_COMPILE -o %t2.out
// RUN: env SYCL_UR_TRACE=2 SYCL_PROGRAM_COMPILE_OPTIONS=-DENV_COMPILE_OPTS SYCL_PROGRAM_LINK_OPTIONS=-DENV_LINK_OPTS SYCL_PROGRAM_APPEND_COMPILE_OPTIONS=-DENV_APPEND_COMPILE_OPTS SYCL_PROGRAM_APPEND_LINK_OPTIONS=-DENV_APPEND_LINK_OPTS %{run} %t2.out | FileCheck %s
// UNSUPPORTED: hip

// Depends on SPIR-V Backend & run-time drivers version.
// XFAIL: spirv-backend && gpu
// XFAIL-TRACKER: CMPLRLLVM-64705

#include "kernel-bundle-merge-options.hpp"

// CHECK: <--- urProgramBuild{{.*}}{{[^bar]*}}-DENV_COMPILE_OPTS -DENV_APPEND_COMPILE_OPTS{{[^bar]*}}-DENV_LINK_OPTS -DENV_APPEND_LINK_OPTS{{[^bar]*}}

// CHECK: <--- urProgramCompile{{.*}}{{[^bar]*}}-DENV_COMPILE_OPTS -DENV_APPEND_COMPILE_OPTS{{[^bar]*}}

// CHECK: <--- urProgramLink{{.*}}{{[^bar]*}}-DENV_LINK_OPTS -DENV_APPEND_LINK_OPTS{{[^bar]*}}
