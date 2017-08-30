; ModuleID = 'SwingCompiler'
source_filename = "main.swing"

@0 = private unnamed_addr constant [16 x i8] c"Prime Number : \00"
@1 = private unnamed_addr constant [3 x i8] c", \00"

declare void @output(i8*)

declare void @outputInt(i32)

declare void @outputFloat(float)

declare void @outputDouble(double)

define i32 @main() {
entry:
  %i = alloca i32
  store i32 0, i32* %i
  %j = alloca i32
  store i32 0, i32* %j
  call void @output(i8* getelementptr inbounds ([16 x i8], [16 x i8]* @0, i32 0, i32 0))
  store i32 2, i32* %i
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i32, i32* %i
  %1 = icmp sle i32 %0, 100000
  %2 = icmp eq i1 %1, true
  br i1 %2, label %for.loop, label %for.end

for.inc:                                          ; preds = %if.end5
  %3 = load i32, i32* %i
  %4 = add i32 %3, 1
  store i32 %4, i32* %i
  br label %for.cond

for.end:                                          ; preds = %for.cond
  ret i32 0

for.loop:                                         ; preds = %for.cond
  store i32 2, i32* %j
  br label %for.cond1

for.cond1:                                        ; preds = %for.inc2, %for.loop
  %5 = load i32, i32* %j
  %6 = load i32, i32* %i
  %7 = sub i32 %6, 1
  %8 = icmp sle i32 %5, %7
  %9 = icmp eq i1 %8, true
  br i1 %9, label %for.loop4, label %for.end3

for.inc2:                                         ; preds = %if.end
  %10 = load i32, i32* %j
  %11 = add i32 %10, 1
  store i32 %11, i32* %j
  br label %for.cond1

for.end3:                                         ; preds = %if.then, %for.cond1
  %12 = load i32, i32* %i
  %13 = load i32, i32* %j
  %14 = icmp eq i32 %12, %13
  %15 = icmp eq i1 %14, true
  br i1 %15, label %if.then6, label %if.end5

for.loop4:                                        ; preds = %for.cond1
  %16 = load i32, i32* %i
  %17 = load i32, i32* %j
  %18 = srem i32 %16, %17
  %19 = icmp eq i32 %18, 0
  %20 = icmp eq i1 %19, true
  br i1 %20, label %if.then, label %if.end

if.end:                                           ; preds = %for.loop4
  br label %for.inc2

if.then:                                          ; preds = %for.loop4
  br label %for.end3

if.end5:                                          ; preds = %if.then6, %for.end3
  br label %for.inc

if.then6:                                         ; preds = %for.end3
  %21 = load i32, i32* %i
  call void @outputInt(i32 %21)
  call void @output(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @1, i32 0, i32 0))
  br label %if.end5
}
