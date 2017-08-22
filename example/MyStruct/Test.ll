; ModuleID = 'SwingCompiler'
source_filename = "main.swing"

%MyStruct = type { i32, i32 }

declare void @output(i8*)

define i32 @main() {
entry:
  %test = alloca %MyStruct
  %Num = alloca i32
  store i32 1234, i32* %Num
  %0 = getelementptr inbounds %MyStruct, %MyStruct* %test, i32 0, i32 0
  %1 = load i32, i32* %Num
  store i32 %1, i32* %0
  %2 = getelementptr inbounds %MyStruct, %MyStruct* %test, i32 0, i32 1
  %3 = getelementptr inbounds %MyStruct, %MyStruct* %test, i32 0, i32 0
  %4 = load i32, i32* %3
  store i32 %4, i32* %2
  %5 = getelementptr inbounds %MyStruct, %MyStruct* %test, i32 0, i32 1
  %6 = load i32, i32* %5
  ret i32 %6
}
