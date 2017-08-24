; ModuleID = 'SwingCompiler'
source_filename = "main.swing"

declare void @output(i8*)

declare void @outputInt(i32)

declare void @outputFloat(float)

declare void @outputDouble(double)

define i32 @TestFunc1(i32 %Num1) {
entry:
  %Num11 = alloca i32
  store i32 %Num1, i32* %Num11
  %0 = load i32, i32* %Num11
  ret i32 %0
}

define i32 @main() {
entry:
  %test = alloca i32
  %0 = call i32 @TestFunc1(i32 10)
  store i32 %0, i32* %test
  %1 = load i32, i32* %test
  %2 = call i32 @TestFunc1(i32 %1)
  ret i32 %2
}
