; ModuleID = 'SwingCompiler'
source_filename = "SwingCompiler"

declare void @output(i8*)

define i32 @main() {
entry:
  %test = alloca i32
  store i32 17, i32* %test
  %0 = load i32, i32* %test
  ret i32 %0
}