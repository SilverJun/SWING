# SWING Command Line Options

```
> swing [COMMAND] [OPTION] files...
```

 커맨드 | 설명 | 결과물 | 형식
----|----|----|----
Compile | 스윙 프로젝트 파일을 컴파일합니다. | 각 파일별로 목적파일을 생성 | -compile [-opt] files...
Link | SWING 표준 라이브러리와 여러가지 목적파일을 링크합니다. | 대상 플랫폼 실행가능한 파일을 생성합니다. | -link [-out] files...
Debug | VS-code와 상호작용하여 Debug기능을 수행합니다. | 디버그를 수행합니다. 이는 멀티쓰레드로 실행되며 디버깅을 하려면 프로그램이 계속 켜져있어야 합니다. | -debug on
Create | SWING에서 사용되는 소스파일, 프로젝트 파일을 생성합니다. | 해당 소스파일 또는 프로젝트 파일을 생성합니다. | -create [source \| project] [name]

