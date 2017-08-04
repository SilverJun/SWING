; ModuleID = 'SwingCompiler'
source_filename = "SwingCompiler"

@0 = private unnamed_addr constant [25 x i8] c"Hello Swing! PLEASE!!!!!\00"

declare void @output(i8*)

define i32 @test() {
entry:
  ret i32 1
}

define i32 @main() {
entry:
  %0 = call i32 @test()
  call void @output(i8* getelementptr inbounds ([25 x i8], [25 x i8]* @0, i64 0, i64 0))
  ret i32 0
}
