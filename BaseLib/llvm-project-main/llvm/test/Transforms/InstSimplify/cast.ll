; NOTE: Assertions have been autogenerated by utils/update_test_checks.py
; RUN: opt -S -passes=instsimplify < %s | FileCheck %s
target datalayout = "p:32:32"

define i1 @test1(i1 %V) {
; CHECK-LABEL: @test1(
; CHECK-NEXT:  entry:
; CHECK-NEXT:    ret i1 [[V:%.*]]
;
entry:
  %Z = zext i1 %V to i32
  %T = trunc i32 %Z to i1
  ret i1 %T
}

define i8* @test2(i8* %V) {
; CHECK-LABEL: @test2(
; CHECK-NEXT:  entry:
; CHECK-NEXT:    ret i8* [[V:%.*]]
;
entry:
  %BC1 = bitcast i8* %V to i32*
  %BC2 = bitcast i32* %BC1 to i8*
  ret i8* %BC2
}

define i8* @test3(i8* %V) {
; CHECK-LABEL: @test3(
; CHECK-NEXT:  entry:
; CHECK-NEXT:    ret i8* [[V:%.*]]
;
entry:
  %BC = bitcast i8* %V to i8*
  ret i8* %BC
}

define i32 @test4() {
; CHECK-LABEL: @test4(
; CHECK-NEXT:    ret i32 4
;
  %alloca = alloca i32, align 4                                     ; alloca + 0
  %gep = getelementptr inbounds i32, i32* %alloca, i32 1            ; alloca + 4
  %bc = bitcast i32* %gep to [4 x i8]*                              ; alloca + 4
  %pti = ptrtoint i32* %alloca to i32                               ; alloca
  %sub = sub i32 0, %pti                                            ; -alloca
  %add = getelementptr [4 x i8], [4 x i8]* %bc, i32 0, i32 %sub     ; alloca + 4 - alloca == 4
  %add_to_int = ptrtoint i8* %add to i32                            ; 4
  ret i32 %add_to_int                                               ; 4
}

define i32 @test5() {
; CHECK-LABEL: @test5(
; CHECK-NEXT:    ret i32 3
;
  %alloca = alloca i32, align 4                                     ; alloca + 0
  %gep = getelementptr inbounds i32, i32* %alloca, i32 1            ; alloca + 4
  %bc = bitcast i32* %gep to [4 x i8]*                              ; alloca + 4
  %pti = ptrtoint i32* %alloca to i32                               ; alloca
  %sub = xor i32 %pti, -1                                           ; ~alloca
  %add = getelementptr [4 x i8], [4 x i8]* %bc, i32 0, i32 %sub     ; alloca + 4 - alloca - 1 == 3
  %add_to_int = ptrtoint i8* %add to i32                            ; 4
  ret i32 %add_to_int                                               ; 4
}