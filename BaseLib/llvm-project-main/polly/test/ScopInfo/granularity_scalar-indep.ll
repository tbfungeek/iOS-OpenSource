; RUN: opt %loadPolly -polly-stmt-granularity=scalar-indep -polly-print-instructions -polly-print-scops -disable-output < %s | FileCheck %s -match-full-lines
;
; Split a block into two independent statements that share no scalar.
; This case has the instructions of the two statements interleaved, such that
; splitting the BasicBlock in the middle would cause a scalar dependency.
;
; for (int j = 0; j < n; j += 1) {
; body:
;   double valA = A[0];
;   double valB = 21.0 + 21.0;
;   A[0] = valA;
;   B[0] = valB;
; }
;
define void @func(i32 %n, double* noalias nonnull %A, double* noalias nonnull %B) {
entry:
  br label %for

for:
  %j = phi i32 [0, %entry], [%j.inc, %inc]
  %j.cmp = icmp slt i32 %j, %n
  br i1 %j.cmp, label %body, label %exit

    body:
      %valA = load double, double* %A
      %valB = fadd double 21.0, 21.0
      store double %valA, double* %A
      store double %valB, double* %B
      br label %inc

inc:
  %j.inc = add nuw nsw i32 %j, 1
  br label %for

exit:
  br label %return

return:
  ret void
}


; CHECK:      Statements {
; CHECK-NEXT:     Stmt_body
; CHECK-NEXT:         Domain :=
; CHECK-NEXT:             [n] -> { Stmt_body[i0] : 0 <= i0 < n };
; CHECK-NEXT:         Schedule :=
; CHECK-NEXT:             [n] -> { Stmt_body[i0] -> [i0, 0] };
; CHECK-NEXT:         ReadAccess :=       [Reduction Type: NONE] [Scalar: 0]
; CHECK-NEXT:             [n] -> { Stmt_body[i0] -> MemRef_A[0] };
; CHECK-NEXT:         MustWriteAccess :=  [Reduction Type: NONE] [Scalar: 0]
; CHECK-NEXT:             [n] -> { Stmt_body[i0] -> MemRef_A[0] };
; CHECK-NEXT:         Instructions {
; CHECK-NEXT:               %valA = load double, double* %A, align 8
; CHECK-NEXT:               store double %valA, double* %A, align 8
; CHECK-NEXT:         }
; CHECK-NEXT:     Stmt_body_b
; CHECK-NEXT:         Domain :=
; CHECK-NEXT:             [n] -> { Stmt_body_b[i0] : 0 <= i0 < n };
; CHECK-NEXT:         Schedule :=
; CHECK-NEXT:             [n] -> { Stmt_body_b[i0] -> [i0, 1] };
; CHECK-NEXT:         MustWriteAccess :=  [Reduction Type: NONE] [Scalar: 0]
; CHECK-NEXT:             [n] -> { Stmt_body_b[i0] -> MemRef_B[0] };
; CHECK-NEXT:         Instructions {
; CHECK-NEXT:               %valB = fadd double 2.100000e+01, 2.100000e+01
; CHECK-NEXT:               store double %valB, double* %B, align 8
; CHECK-NEXT:         }
; CHECK-NEXT: }
