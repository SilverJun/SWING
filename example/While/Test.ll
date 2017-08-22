; ModuleID = 'SwingCompiler'
source_filename = "main.swing"

@0 = private unnamed_addr constant [8 x i8] c"while!\0A\00"

declare void @output(i8*)

define i32 @main() {
entry:
  %i = alloca i32
  store i32 0, i32* %i
  %sum = alloca i32
  store i32 0, i32* %sum
  br label %while.cond

while.cond:                                       ; preds = %while.loop, %entry
  %0 = load i32, i32* %i
  %1 = icmp slt i32 %0, 10
  %2 = icmp eq i1 %1, true
  br i1 %2, label %while.loop, label %while.end

while.end:                                        ; preds = %while.cond
  %3 = load i32, i32* %sum
  ret i32 %3

while.loop:                                       ; preds = %while.cond
  %4 = load i32, i32* %sum
  %5 = add i32 %4, 1
  store i32 %5, i32* %sum
  %6 = load i32, i32* %i
  %7 = add i32 %6, 1
  store i32 %7, i32* %i
  call void @output(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @0, i32 0, i32 0))
  br label %while.cond
}
