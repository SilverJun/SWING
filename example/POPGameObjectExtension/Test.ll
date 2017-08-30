; ModuleID = 'SwingCompiler'
source_filename = "main.swing"

%SilverJun = type { i32, i32, i32, i32, i32 }

@0 = private unnamed_addr constant [13 x i8] c"Player id : \00"
@1 = private unnamed_addr constant [2 x i8] c"\0A\00"
@2 = private unnamed_addr constant [18 x i8] c"Attack Damage is \00"
@3 = private unnamed_addr constant [2 x i8] c"\0A\00"
@4 = private unnamed_addr constant [13 x i8] c"before move \00"
@5 = private unnamed_addr constant [3 x i8] c", \00"
@6 = private unnamed_addr constant [2 x i8] c"\0A\00"
@7 = private unnamed_addr constant [12 x i8] c"after move \00"
@8 = private unnamed_addr constant [3 x i8] c", \00"
@9 = private unnamed_addr constant [2 x i8] c"\0A\00"

declare void @output(i8*)

declare void @outputInt(i32)

declare void @outputFloat(float)

declare void @outputDouble(double)

define i32 @main() {
entry:
  %player = alloca %SilverJun
  call void @SilverJun.init(%SilverJun* %player, i32 1)
  call void @SilverJun.attack(%SilverJun* %player)
  call void @SilverJun.move(%SilverJun* %player, i32 10, i32 20)
  ret i32 0
}

define void @SilverJun.init(%SilverJun* %self, i32 %id) {
entry:
  %self1 = alloca %SilverJun*
  store %SilverJun* %self, %SilverJun** %self1
  %id2 = alloca i32
  store i32 %id, i32* %id2
  %0 = load %SilverJun*, %SilverJun** %self1
  %1 = getelementptr inbounds %SilverJun, %SilverJun* %0, i32 0, i32 0
  %2 = getelementptr inbounds %SilverJun, %SilverJun* %0, i32 0, i32 1
  %3 = getelementptr inbounds %SilverJun, %SilverJun* %0, i32 0, i32 2
  %4 = getelementptr inbounds %SilverJun, %SilverJun* %0, i32 0, i32 3
  %5 = getelementptr inbounds %SilverJun, %SilverJun* %0, i32 0, i32 4
  %6 = getelementptr inbounds %SilverJun, %SilverJun* %0, i32 0, i32 0
  %7 = load i32, i32* %id2
  store i32 %7, i32* %6
  store i32 100, i32* %2
  store i32 10, i32* %3
  store i32 10, i32* %4
  store i32 5, i32* %5
  call void @output(i8* getelementptr inbounds ([13 x i8], [13 x i8]* @0, i32 0, i32 0))
  %8 = getelementptr inbounds %SilverJun, %SilverJun* %0, i32 0, i32 0
  %9 = load i32, i32* %8
  call void @outputInt(i32 %9)
  call void @output(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @1, i32 0, i32 0))
  ret void
}

define void @SilverJun.attack(%SilverJun* %self) {
entry:
  %self1 = alloca %SilverJun*
  store %SilverJun* %self, %SilverJun** %self1
  %0 = load %SilverJun*, %SilverJun** %self1
  %1 = getelementptr inbounds %SilverJun, %SilverJun* %0, i32 0, i32 0
  %2 = getelementptr inbounds %SilverJun, %SilverJun* %0, i32 0, i32 1
  %3 = getelementptr inbounds %SilverJun, %SilverJun* %0, i32 0, i32 2
  %4 = getelementptr inbounds %SilverJun, %SilverJun* %0, i32 0, i32 3
  %5 = getelementptr inbounds %SilverJun, %SilverJun* %0, i32 0, i32 4
  call void @output(i8* getelementptr inbounds ([18 x i8], [18 x i8]* @2, i32 0, i32 0))
  %6 = load i32, i32* %5
  call void @outputInt(i32 %6)
  call void @output(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @3, i32 0, i32 0))
  ret void
}

define void @SilverJun.move(%SilverJun* %self, i32 %x, i32 %y) {
entry:
  %self1 = alloca %SilverJun*
  store %SilverJun* %self, %SilverJun** %self1
  %x2 = alloca i32
  store i32 %x, i32* %x2
  %y3 = alloca i32
  store i32 %y, i32* %y3
  %0 = load %SilverJun*, %SilverJun** %self1
  %1 = getelementptr inbounds %SilverJun, %SilverJun* %0, i32 0, i32 0
  %2 = getelementptr inbounds %SilverJun, %SilverJun* %0, i32 0, i32 1
  %3 = getelementptr inbounds %SilverJun, %SilverJun* %0, i32 0, i32 2
  %4 = getelementptr inbounds %SilverJun, %SilverJun* %0, i32 0, i32 3
  %5 = getelementptr inbounds %SilverJun, %SilverJun* %0, i32 0, i32 4
  call void @output(i8* getelementptr inbounds ([13 x i8], [13 x i8]* @4, i32 0, i32 0))
  %6 = load i32, i32* %3
  call void @outputInt(i32 %6)
  call void @output(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @5, i32 0, i32 0))
  %7 = load i32, i32* %4
  call void @outputInt(i32 %7)
  call void @output(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @6, i32 0, i32 0))
  %8 = load i32, i32* %3
  %9 = load i32, i32* %x2
  %10 = add i32 %8, %9
  store i32 %10, i32* %3
  %11 = load i32, i32* %4
  %12 = load i32, i32* %y3
  %13 = add i32 %11, %12
  store i32 %13, i32* %4
  call void @output(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @7, i32 0, i32 0))
  %14 = load i32, i32* %3
  call void @outputInt(i32 %14)
  call void @output(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @8, i32 0, i32 0))
  %15 = load i32, i32* %4
  call void @outputInt(i32 %15)
  call void @output(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @9, i32 0, i32 0))
  ret void
}
