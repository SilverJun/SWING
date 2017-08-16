; ModuleID = 'SwingCompiler'
source_filename = "SwingCompiler"

@0 = private unnamed_addr constant [13 x i8] c"Hello Swing!\00"

declare void @output(i8*)

define i32 @main() {
entry:
  call void @output(i8* getelementptr inbounds ([13 x i8], [13 x i8]* @0, i64 0, i64 0))
  ret i32 0
}
