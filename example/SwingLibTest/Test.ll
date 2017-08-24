; ModuleID = 'SwingCompiler'
source_filename = "main.swing"

@0 = private unnamed_addr constant [21 x i8] c"Swing Library Test!\0A\00"
@1 = private unnamed_addr constant [2 x i8] c"\0A\00"
@2 = private unnamed_addr constant [2 x i8] c"\0A\00"
@3 = private unnamed_addr constant [2 x i8] c"\0A\00"

declare void @output(i8*)

declare void @outputInt(i32)

declare void @outputFloat(float)

declare void @outputDouble(double)

define i32 @main() {
entry:
  %test1 = alloca float
  store float 1.000000e+00, float* %test1
  %test2 = alloca double
  store double 1.000000e+00, double* %test2
  call void @output(i8* getelementptr inbounds ([21 x i8], [21 x i8]* @0, i32 0, i32 0))
  call void @outputInt(i32 1234)
  call void @output(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @1, i32 0, i32 0))
  %0 = load float, float* %test1
  call void @outputFloat(float %0)
  call void @output(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @2, i32 0, i32 0))
  %1 = load double, double* %test2
  call void @outputDouble(double %1)
  call void @output(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @3, i32 0, i32 0))
  ret i32 0
}
