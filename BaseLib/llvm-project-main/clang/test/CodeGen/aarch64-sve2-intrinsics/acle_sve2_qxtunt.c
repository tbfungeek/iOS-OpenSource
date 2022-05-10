// NOTE: Assertions have been autogenerated by utils/update_cc_test_checks.py
// RUN: %clang_cc1 -triple aarch64-none-linux-gnu -target-feature +sve2 -fallow-half-arguments-and-returns -S -O1 -Werror -Wall -emit-llvm -o - %s | FileCheck %s
// RUN: %clang_cc1 -triple aarch64-none-linux-gnu -target-feature +sve2 -fallow-half-arguments-and-returns -S -O1 -Werror -Wall -emit-llvm -o - -x c++ %s | FileCheck %s -check-prefix=CPP-CHECK
// RUN: %clang_cc1 -DSVE_OVERLOADED_FORMS -triple aarch64-none-linux-gnu -target-feature +sve2 -fallow-half-arguments-and-returns -S -O1 -Werror -Wall -emit-llvm -o - %s | FileCheck %s
// RUN: %clang_cc1 -DSVE_OVERLOADED_FORMS -triple aarch64-none-linux-gnu -target-feature +sve2 -fallow-half-arguments-and-returns -S -O1 -Werror -Wall -emit-llvm -o - -x c++ %s | FileCheck %s -check-prefix=CPP-CHECK
// RUN: %clang_cc1 -triple aarch64-none-linux-gnu -target-feature +sve -fallow-half-arguments-and-returns -fsyntax-only -Wno-error=implicit-function-declaration -verify -verify-ignore-unexpected=error %s
// RUN: %clang_cc1 -DSVE_OVERLOADED_FORMS -triple aarch64-none-linux-gnu -target-feature +sve -fallow-half-arguments-and-returns -fsyntax-only -Wno-error=implicit-function-declaration -verify=overload -verify-ignore-unexpected=error %s

// REQUIRES: aarch64-registered-target

#include <arm_sve.h>

#ifdef SVE_OVERLOADED_FORMS
// A simple used,unused... macro, long enough to represent any SVE builtin.
#define SVE_ACLE_FUNC(A1,A2_UNUSED,A3,A4_UNUSED) A1##A3
#else
#define SVE_ACLE_FUNC(A1,A2,A3,A4) A1##A2##A3##A4
#endif

// CHECK-LABEL: @test_svqxtunt_u16(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = call <vscale x 16 x i8> @llvm.aarch64.sve.sqxtunt.nxv8i16(<vscale x 16 x i8> [[OP:%.*]], <vscale x 8 x i16> [[OP1:%.*]])
// CHECK-NEXT:    ret <vscale x 16 x i8> [[TMP0]]
//
// CPP-CHECK-LABEL: @_Z17test_svqxtunt_u16u11__SVUint8_tu11__SVInt16_t(
// CPP-CHECK-NEXT:  entry:
// CPP-CHECK-NEXT:    [[TMP0:%.*]] = call <vscale x 16 x i8> @llvm.aarch64.sve.sqxtunt.nxv8i16(<vscale x 16 x i8> [[OP:%.*]], <vscale x 8 x i16> [[OP1:%.*]])
// CPP-CHECK-NEXT:    ret <vscale x 16 x i8> [[TMP0]]
//
svuint8_t test_svqxtunt_u16(svuint8_t op, svint16_t op1)
{
  // overload-warning@+2 {{call to undeclared function 'svqxtunt'; ISO C99 and later do not support implicit function declarations}}
  // expected-warning@+1 {{call to undeclared function 'svqxtunt_s16'; ISO C99 and later do not support implicit function declarations}}
  return SVE_ACLE_FUNC(svqxtunt,_s16,,)(op, op1);
}

// CHECK-LABEL: @test_svqxtunt_u32(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = call <vscale x 8 x i16> @llvm.aarch64.sve.sqxtunt.nxv4i32(<vscale x 8 x i16> [[OP:%.*]], <vscale x 4 x i32> [[OP1:%.*]])
// CHECK-NEXT:    ret <vscale x 8 x i16> [[TMP0]]
//
// CPP-CHECK-LABEL: @_Z17test_svqxtunt_u32u12__SVUint16_tu11__SVInt32_t(
// CPP-CHECK-NEXT:  entry:
// CPP-CHECK-NEXT:    [[TMP0:%.*]] = call <vscale x 8 x i16> @llvm.aarch64.sve.sqxtunt.nxv4i32(<vscale x 8 x i16> [[OP:%.*]], <vscale x 4 x i32> [[OP1:%.*]])
// CPP-CHECK-NEXT:    ret <vscale x 8 x i16> [[TMP0]]
//
svuint16_t test_svqxtunt_u32(svuint16_t op, svint32_t op1)
{
  // overload-warning@+2 {{call to undeclared function 'svqxtunt'; ISO C99 and later do not support implicit function declarations}}
  // expected-warning@+1 {{call to undeclared function 'svqxtunt_s32'; ISO C99 and later do not support implicit function declarations}}
  return SVE_ACLE_FUNC(svqxtunt,_s32,,)(op, op1);
}

// CHECK-LABEL: @test_svqxtunt_u64(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = call <vscale x 4 x i32> @llvm.aarch64.sve.sqxtunt.nxv2i64(<vscale x 4 x i32> [[OP:%.*]], <vscale x 2 x i64> [[OP1:%.*]])
// CHECK-NEXT:    ret <vscale x 4 x i32> [[TMP0]]
//
// CPP-CHECK-LABEL: @_Z17test_svqxtunt_u64u12__SVUint32_tu11__SVInt64_t(
// CPP-CHECK-NEXT:  entry:
// CPP-CHECK-NEXT:    [[TMP0:%.*]] = call <vscale x 4 x i32> @llvm.aarch64.sve.sqxtunt.nxv2i64(<vscale x 4 x i32> [[OP:%.*]], <vscale x 2 x i64> [[OP1:%.*]])
// CPP-CHECK-NEXT:    ret <vscale x 4 x i32> [[TMP0]]
//
svuint32_t test_svqxtunt_u64(svuint32_t op, svint64_t op1)
{
  // overload-warning@+2 {{call to undeclared function 'svqxtunt'; ISO C99 and later do not support implicit function declarations}}
  // expected-warning@+1 {{call to undeclared function 'svqxtunt_s64'; ISO C99 and later do not support implicit function declarations}}
  return SVE_ACLE_FUNC(svqxtunt,_s64,,)(op, op1);
}