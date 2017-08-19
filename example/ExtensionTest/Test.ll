; ModuleID = 'SwingCompiler'
source_filename = "SwingCompiler"

%MyStruct = type { i32, i32 }

declare void @output(i8*)

define i32 @main() {
entry:
  %test = alloca %MyStruct
  %0 = call i32 @protFunction(%MyStruct* %test)
  ret i32 %0
}

define i32 @protFunction(%MyStruct* %self) {
entry:
  %self1 = alloca %MyStruct*
  store %MyStruct* %self, %MyStruct** %self1
  %0 = load %MyStruct*, %MyStruct** %self1
  %1 = getelementptr inbounds %MyStruct, %MyStruct* %0, i32 0, i32 0
  %2 = getelementptr inbounds %MyStruct, %MyStruct* %0, i32 0, i32 1
  store i32 10, i32* %2
  %3 = load i32, i32* %2
  store i32 %3, i32* %1
  %4 = load i32, i32* %1
  ret i32 %4
}
