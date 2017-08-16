; ModuleID = 'SwingCompiler'
source_filename = "SwingCompiler"

%MyStruct = type { i32, i32 }

declare void @output(i8*)

define i32 @main() {
entry:
  %test = alloca %MyStruct
  %Num = alloca i32
  %0 = load i32, i32* %Num
  store i32 1234, i32* %Num
  %1 = getelementptr inbounds %MyStruct, %MyStruct* %test, i32 0, i32 0
  %2 = load i32, i32* %1
  %3 = getelementptr inbounds %MyStruct, %MyStruct* %test, i32 0, i32 0
  %4 = load i32, i32* %Num
  store i32 %4, i32* %3
  %5 = getelementptr inbounds %MyStruct, %MyStruct* %test, i32 0, i32 1
  %6 = load i32, i32* %5
  %7 = getelementptr inbounds %MyStruct, %MyStruct* %test, i32 0, i32 1
  %8 = getelementptr inbounds %MyStruct, %MyStruct* %test, i32 0, i32 0
  %9 = load i32, i32* %8
  store i32 %9, i32* %7
  %10 = getelementptr inbounds %MyStruct, %MyStruct* %test, i32 0, i32 1
  %11 = load i32, i32* %10
  ret i32 %11
}
