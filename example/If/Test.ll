; ModuleID = 'SwingCompiler'
source_filename = "main.swing"

@0 = private unnamed_addr constant [14 x i8] c"test is 10! \0A\00"

declare void @output(i8*)

define i32 @main() {
entry:
  %test = alloca i32
  store i32 10, i32* %test
  %0 = load i32, i32* %test
  %1 = icmp eq i32 %0, 10
  %2 = icmp eq i1 %1, true
  br i1 %2, label %if.then, label %if.end

if.end:                                           ; preds = %if.then, %entry
  ret i32 0

if.then:                                          ; preds = %entry
  call void @output(i8* getelementptr inbounds ([14 x i8], [14 x i8]* @0, i32 0, i32 0))
  br label %if.end
}
