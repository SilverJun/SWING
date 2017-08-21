; ModuleID = 'SwingCompiler'
source_filename = "SwingCompiler"

@0 = private unnamed_addr constant [14 x i8] c"test is 10! \0A\00"
@1 = private unnamed_addr constant [14 x i8] c"test is 20! \0A\00"
@2 = private unnamed_addr constant [21 x i8] c"test is no 10, 20! \0A\00"

declare void @output(i8*)

define i32 @main() {
entry:
  %test = alloca i32
  store i32 10, i32* %test
  %0 = load i32, i32* %test
  %1 = icmp eq i32 %0, 10
  %2 = icmp eq i1 %1, true
  br i1 %2, label %if.then, label %if.else

if.end:                                           ; preds = %if.end1, %if.then
  ret i32 0

if.then:                                          ; preds = %entry
  call void @output(i8* getelementptr inbounds ([14 x i8], [14 x i8]* @0, i32 0, i32 0))
  br label %if.end

if.else:                                          ; preds = %entry
  %3 = load i32, i32* %test
  %4 = icmp eq i32 %3, 20
  %5 = icmp eq i1 %4, true
  br i1 %5, label %if.then2, label %if.else3

if.end1:                                          ; preds = %if.else3, %if.then2
  br label %if.end

if.then2:                                         ; preds = %if.else
  call void @output(i8* getelementptr inbounds ([14 x i8], [14 x i8]* @1, i32 0, i32 0))
  br label %if.end1

if.else3:                                         ; preds = %if.else
  call void @output(i8* getelementptr inbounds ([21 x i8], [21 x i8]* @2, i32 0, i32 0))
  br label %if.end1
}
