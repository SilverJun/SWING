; ModuleID = 'SwingCompiler'
source_filename = "main.swing"

declare void @output(i8*)

declare void @outputInt(i32)

declare void @outputFloat(float)

declare void @outputDouble(double)

define i32 @main() {
entry:
  %i = alloca i32
  %sum = alloca i32
  store i32 0, i32* %sum
  store i32 0, i32* %i
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i32, i32* %i
  %1 = icmp slt i32 %0, 10
  %2 = icmp eq i1 %1, true
  br i1 %2, label %for.loop, label %for.end

for.inc:                                          ; preds = %for.loop
  %3 = load i32, i32* %i
  %4 = add i32 %3, 1
  store i32 %4, i32* %i
  br label %for.cond

for.end:                                          ; preds = %for.cond
  %5 = load i32, i32* %sum
  ret i32 %5

for.loop:                                         ; preds = %for.cond
  %6 = load i32, i32* %sum
  %7 = add i32 %6, 1
  store i32 %7, i32* %sum
  br label %for.inc
}
