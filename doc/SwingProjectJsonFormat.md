```json
{
    "ProjectName": "Project Name",
    "ProjectPath": "ProjectFile Path",
    "BinaryOutputPath": "Binary Output Folder Path",
    "BinaryFileName": "Output Binary File Name",
    "SourceFilePath": "Sources Path",
    "SourceList": ["SourceFile Paths"]
}
```

## Swing Project Json Properties

키 | 값 | 설명
----|----|----
ProjectName | 프로젝트 이름 | 프로젝트 파일의 이름, 프로젝트 이름입니다.
ProjectPath | 프로젝트 위치 | 프로젝트 파일이 존재하는 폴더, /를 생략한 문자열입니다.
BinaryOutputPath | 바이너리파일 출력 위치 | 바이너리 파일을 생성할 때, 파일이 생성될 위치입니다. 기본 ProjectPath입니다.
BinaryFileName | 바이너리 파일 이름 | 실행파일의 이름입니다. 기본 ProjectName입니다.
SourceFilePath | 소스파일 위치 | 소스파일이 존재하는 위치입니다. 파일을 생성할 때, 참조할 때 쓰입니다. 기본 ProjectPath입니다.
SourceList | 소스파일 배열 | 컴파일할 소스들의 위치를 저장한 값입니다.
