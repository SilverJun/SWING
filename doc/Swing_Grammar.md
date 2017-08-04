# 스윙 언어 문서 v0.4

SWING언어의 문법을 정리한 문서입니다.

마지막 수정 - 2017/05/15

# 문법

문법은 스위프트의 문법과 많이 유사합니다.

특징은 문장 끝의 세미콜론 없이 개행으로 한 명령문을 처리합니다.
제어문의 조건식의 괄호가 생략가능합니다.

SWING Lexer에서 사용되어지는 정규식입니다.

```
// 식별자 - 함수명, 변수명, 타입명
Identifier ::= [a-zA-Z_][0-9a-zA-z_]*

// 수
Integer ::= [0-9][0-9]*
Hexa ::= 0x[0-9a-fA-F][0-9a-fA-F]*
Octal ::= 0o[0-7][0-7]*
Binary ::= 0b[01][01]*
Double ::= [0-9][0-9]*.[0-9][0-9]*

//문자열
Character ::= '_|[\][ntr0\'"]'

// escape 문자
Escape_sequence ::= [\]n | [\]t | [\]r | [\]0 | [\]\ | [\]' | [\]"
```

추후 EBNF로 문법을 상세히 정리할 예정입니다.

이 문서에서는 코드 하이라이팅이 비슷한 swift로 코드 하이라이팅을 했습니다. 참고바랍니다.

## 자료형

자료형은 스위프트의 자료형을 가져왔습니다. 하지만 빠른 개발을 위해 여러 정수형, 실수형 자료형을 제거했습니다.

지원하는 자료형

* Bool
* Char
* Int
* Double
* String

Unsigned 를 추가할 수 있습니다.

컬렉션 타입

* Array
* Dictionary
* Tuple

옵셔널 타입

* Optional

사용자 정의 타입

* struct
* enum
* class
* protocol

### 변수, 상수

자료형은 다음과 같이 선언가능 합니다.

```swift
var 변수명 = 값 //변수 선언
let 변수명 = 값 //상수 선언
```
var 키워드로 변수를, let키워드로 상수를 선언할 수 있습니다.
SWING은 할당하는 값의 타입을 추론해 그 값의 타입으로 변수를 생성합니다.

물론 아래와 같이 타입을 지정할 수 있습니다.

```swift
var 변수명           //불가능! 타입을 추론할 수 없음
var 변수명 = 값      //가능! 값과 같은 타입으로 생성
var 변수명:타입      //가능! 명시된 타입으로 생성, nil로 초기화
let 변수명           //불가능! 타입을 추론할 수 없음
let 변수명 = 값      //가능! 아주 정상적인 상수 선언후 값을 부여하는 과정
let 변수명:타입      //불가능! 상수는 선언과 동시에 값을 부여해야 함
```

#### 기본 자로형

> | 크기 | 용도
---|------|-----
Bool | 1Byte | 논리 연산
Char | 2Byte | 문자 표현
Int | 4Byte | 정수 표현
Double | 8Byte | 부동 소수점 표현

#### String

string은 기본 자료형으로 제공합니다.

```swift
var str:String = "test"
```

기본 정의 메소드
이름 | 반환형 | 인자 | 설명
-------|-------|-------|-------
index | Int | character | 인자가 String의 몇 번째 인덱스인지 반환합니다.
pushLast | Void | character | 인자를 String의 맨 끝에 추가합니다.
pushLast | Void | str | 인자를 String의 맨 끝에 추가합니다.
popLast | character | void | 맨 마지막 글자 하나를 반환하고 지웁니다.
insertAt | void | index, character | 해당 인덱스에 글자를 추가합니다.
insertAt | void | index, str | 해당 인덱스에 문자열을 추가합니다.
removeAt | void | index | 해당 인덱스의 문자를 지웁니다.
removeAll | void | void | String을 빈 컨테이너로 만듭니다.

##### 문자열 보간법

다른 자료형을 string으로 변환하여 문자열 연산을 하는 경우가 많다고 인식했습니다.

그래서 문자열 보간법이라는 것을 만들게 되었습니다.

```swift
var num1 = 10
var num2 = 20

output("\(num1) + \(num2) = \(num1 + num2)")
```

위 코드와 같이 문자열 내에 \() 안의 식을 평가해 값을 String으로 변환합니다.

사용자 정의 타입인 경우 StringConvertable 프로토콜로 확장해 메소드를 구현하십시오. (extension 참고)

```swift
extension MyStruct : StringConvertable
{
    func toString() -> String {
        // do something
        return result
    }
}
```
### 컬렉션 타입

#### Array

SWING에서의 Array는 C++의 std::vector와 같이 구성되어 있습니다.

아래와 같이 배열을 선언할 수 있습니다.

```swift
var 이름:Array<타입>()
var 이름:[타입] = []          //위의 형식의 축약형태입니다.
var 이름 = [타입]()
```

기본 정의 메소드
이름 | 반환형 | 인자 | 설명
-------|-------|-------|-------
index | Int | T | 인자가 Array의 몇 번째 인덱스인지 반환합니다.
pushLast | Void | T | 인자를 Array의 맨 끝에 추가합니다.
popLast | T | void | 맨 마지막 원소 하나를 반환하고 지웁니다.
insertAt | void | index, T | 해당 인덱스에 원소를 추가합니다.
removeAt | void | index | 해당 인덱스의 원소를 지웁니다.
removeAll | void | void | Array를 빈 컨테이너로 만듭니다.

#### Dictionary

Dictionary는 키와 값이 있는 컬랙션 타입입니다.

```swift
var 이름:Dictionary<키 타입,값 타입>()
var 이름:[키 타입:값 타입] = [:]              //위의 형식의 축약형태입니다.
var 이름 = [키 타입:값 타입]()
```

기본 정의 메소드
이름 | 반환형 | 인자 | 설명
-------|-------|-------|-------
insertValue | void | key, value | 해당 키에 해당하는 값을 추가합니다.
removeValue | void | key | 해당 키에 해당하는 값을 지웁니다.
removeAll | void | void | Dictionary를 빈 컨테이너로 만듭니다.

#### Tuple

Tuple은 다른자료형끼리 여러 개의 쌍을 이루는 형식의 컬랙션 타입입니다.

```swift
var 이름:Tuple<이름:타입, 이름:타입 ...>()
```

각 이름을 통해 해당 값에 접근할 수 있습니다.

### 옵셔널 타입

옵셔널 타입은 값이 있을 수도 있고 없을 수도 있는 값이라는 것을 명시적으로 선언해 의도치 않는 에러를 줄이는데 효과적인 타입입니다.

```swift
var phone:String?   //옵셔널타입선언, nil값이 될 수 있음
```

옵셔널 타입으로 선언하는 방법은 타입을 설정할 때 ?를 붙여 선언하면 됩니다.

변수를 설정할 때 옵셔널 선언 없이 nil값이 할당되면 에러가 나옵니다.

## 연산자

다음과 같은 연산자를 지원합니다.

### 할당연산자

연산자 | 사용 예 | 결과
----|-------|-----
= | a = b | a 에 b를 할당, 반환값 없음!

### 산술연산자

연산자 | 사용 예 | 결과값
----|-------|-----
+ | a + b | a와 b를 더한 값
- | a - b | a에 b를 뺀 값
* | a * b | a와 b를 곱한 값
/ | a / b | a에 b를 나눴을 때 몫
% | a % b | a에 b를 나눴을 때 나머지
** | a ** b | a의 b제곱
    
나머지 연산자인 %는 실수형에도 연산이 가능합니다.

### 비교연산자

a 와 b를 비교했을 때 a의 입장에서 설명하면 아래와 같이 설명할 수 있습니다.

비교 연산자의 반환값은 오직 Bool형입니다. 다른 타입이 될 수 없습니다.

연산자 | 사용 예 | 설명
----|-------|-------
> | a > b | 크다
< | a < b | 작다
>= | a >= b | 크거나 같다
<= | a <= b | 작거나 같다
== | a == b | 같다
!= | a != b | 같지 않다

### 논리연산자

논리 연산자의 반환값은 오직 Bool형입니다. 다른 타입이 될 수 없습니다.

연산자 | 사용 예 | 설명
----|-------|-------
&& | a && b | a 그리고 b
\|\| | a \|\| b | a 또는 b
! | !a | a가 아니다

### 비트연산자

연산자 | 사용 예 | 결과
----|-------|-----
& | a & b | a와 b를 비트단위 AND연산
\| | a \| b | a와 b를 비트단위 OR연산
~ | ~a | a를 비트단위 NOT연산
^ | a ^ b | a와 b를 비트단위 XOR연산
<< | a << b | a를 b만큼 왼쪽으로 비트단위 SHIFT연산
>> | a >> b | a를 b만큼 오른쪽으로 비트단위 SHIFT연산

### 범위연산자

연산자 | 사용 예 | 결과
----|-------|-----
(a...b) | (1...5) | 1 <= x <= 5 범위를 반환
(a..<b) | (1..<5) | 1 <= x < 5 범위를 반환

범위연산자는 For문과 잘 사용되어 집니다.

### 옵셔널 연산자

연산자 | 예 | 설명 | 결과
------|------|------|-----
! | a! | 옵셔널 강제 추출 | a의 값을 강제로 추출, nil일때는 런타임 에러
? | a? | 옵셔널 바인딩 | a의 값을 안전하게 추출. nil값을 반환할 수 있음

### 사용자 정의 연산자

프로그래머가 연산자를 정의할 수 있습니다. SWING이 지원하는 기호를 조합해 연산자를 만들 수 있습니다. 인자를 3개 이상 선언할 수 없습니다.

연산자는 전위, 후위, 중위 연산자를 선언할 수 있으며 중위 연산자는 우선순위를 설정해야 합니다.

중위 연산자인 경우, 연산자 우선순위를 설정해야 하고 두 인자의 타입이 같아야 합니다. 반환타입은 자동으로 두 인자의 타입으로 설정됩니다. 우선순위는 항상 높습니다.

전위, 후위 연산자는 반환타입과 인자를 설정해야 하며 타입이 달라도 됩니다.

이는 타입 안정성을 보장하기 위함입니다.

연산자 우선순위를 설정할 수 있습니다.

현재 SWING의 연산자들은 아래와 같은 연산자 우선순위를 가지고 있으며, 숫자가 낮을수록 연산자 우선순위가 낮은 것입니다.

Int형 값을 적어도 되고, 아래 PrecedenceLevel을 문자로 적어도 됩니다.

```
PrecedenceLevel
{
	Precedence_Min = 1,
	Precedence_Assignment = 2,
	Precedence_Relational = 10,
	Precedence_Logical = 20,
	Precedence_Default = 30,
	Precedence_Bitwise = 40,
	Precedence_Additive = 50,
	Precedence_Multiplicative = 60,
	Precedence_Max = 100
};
```


```swift
prefix operator name(argument) -> type {
    //...
}
```
```swift
postfix operator name(argument) -> type {
    //...
}
```
```swift
infix operator name(argument1, argument2):PrecedenceLevel -> type {
    //...
}
```

## 제어문

제어문은 if, else, guard, switch, while, for를 제공합니다.

각 제어문의 조건식에 괄호가 요구되지 않습니다.
if문과 블럭 사이의 표현식을 평가하여 올바른 결과값을 도출합니다.
괄호를 사용해도 무관합니다.

### if else문
if else의 형태입니다.
```swift
if condition {
    //작업...
}
else {
    //작업...
}
```

if else는 중첩이 가능하며 아래와 같이 사용할 수 있습니다.
```swift
if n == 1 {
    DoSomething1()
}
else if n == 2 {
    DoSomething2()
}
else {
    DoSomethingelse()
}
```

### guard문
SWING언어에도 guard문을 사용할 수 있습니다.  
guard문을 통해 함수나 메소드의 시작에서 특정 변수의 값을 체크해서 조건을 충족시키지 못할 시, 필요한 조취를 빠르게 취할 수 있게 해줍니다.

다음은 guard문 형태입니다.
```swift
guard condition else { 
    //작업... 
}
```

guard문은 condition이 참이면 지나가지만 참이 아닐경우 else의 block을 실행합니다. 용례를 살펴보죠.
```swift
func inputHandling(var data: int) -> void {
    guard data > 0 else { 
        output("값이 양수여야 합니다.")
        return 
    }
    guard data < 100 else { 
        output("값이 100보다 작아야 합니다.")
        return 
    }

    //.... 필요한 작업
}
```
### switch문

switch문은 c/c++언어와 거의 동일합니다. 하지만 SWING은 string이 기본 자료형이기 때문에 switch문에 string형을 사용할 수 있습니다.
switch문의 변수를 각 case와 비교해 같을때 해당 case를 실행합니다.

switch문의 형태입니다.

```swift
switch variable {
case value1:
    //작업...
    break

default:
    //작업...
}
```

범위 연산자도 case로 사용될 수 있습니다.

```swift
switch variable {
case (1...10):
    //작업...
    break

default:
    //작업...
}
```

### while문

일반적인 while문과 동일합니다. condition이 참일 때 반복합니다.

while문의 형태입니다.

```swift
while condition {
    //작업...
}
```

### for문

for문은 여러가지 형태로 지원됩니다.

1. 초기화, 조건식, 증감문으로 구성된 일반적인 for문
2. 컨테이너를 순회하는 for-in문
3. 정해진 반복 범위를 순회하는 for-in문

우선 1번의 형태입니다.

가장 기본적인 형태입니다.
```swift
for initial; condition; increament {
    //작업...
}
```

2번의 형태입니다.

기본적으로 제공하는 array와 dictionary를 순회할 때 사용할 수 있습니다. 컨테이너의 처음부터 끝까지 순회하는 반복문입니다.
```swift
for element in container {
    //작업
}
```

3번의 형태입니다.

```swift
for i in 1...5 {
    //작업...
}
```
이 형태의 반복문은 swift에서 가져왔습니다. 매우 멋진 형태의 반복문이죠.

i는 for문에서만 유효한 임시 변수이고 1에서 5로 증가하면서 반복하는 반복문입니다.

## 함수

함수를 통해 사용자가 원하는 프로그램 코드를 묶을 수 있고 재사용 할 수 있습니다.

```swift
func FunctionName(Arg1:Type, Arg2:Type) -> ReturnType {
    //작업...
}
```

## 프로토콜 지향 프로그래밍

### Reference Type, Value Type

Reference Type과 Value Type이라는 개념이 존재합니다. 참조 타입과 값 타입 입니다. C#의 ObjectType, ValueType와 유사합니다.

참조 타입은 대상의 참조를 통해 값을 저장하는 타입입니다.

값 타입은 실체 값을 통해 값을 저장하는 타입입니다.

> | 값 타입 | 참조 타입
---------|----------|-----------
저장하는 값 | 대상의 실체 | 대상의 참조 값
복사 방식 | 대상 얕은 복사 | 참조값 복사
대상 | struct, enum, protocol | class

SWING의 모든 자료형은 값 타입이며 SWING은 값 타입을 더 많이 사용합니다.

값 타입과 참조 타입은 서로 적재적소에 사용될때 가장 큰 효율과 안전성을 발휘합니다.

값 타입을 사용하면 좋은 상황
* 작은 데이터 위주의 저장
* 대상의 생성과 대입이 잦은 경우

값 타입은 데이터 위주의 타입일 때 사용하면 좋습니다. 데이터 위주의 저장이 주요 목적이라면 레퍼런스 형식의 값 저장보다 실체가 있는 저장이 불러오는 속도나 읽기 속도면에서 앞설 수 있습니다. 객체생성에서도 동적 메모리 할당이 필요한 참조 타입 보다 빠를 수 있으며 값을 복사해 의도치 않는 값 변경을 막아 데이터의 안정성을 향상 시킬 수 있는 효과를 얻을 수 있습니다.

참조 타입을 사용하면 좋은 상황
* 객체를 표현해야 하는 경우
* 데이터의 규모가 클 때

참조 타입은 표현하는 데이터가 클 때나 객체를 표현해야 하는 경우에 사용하면 좋습니다. 데이터의 규모가 클 때는 레퍼런스 형식의 복사가 더 효율적일 수 있으며 객체를 정의하여 사용하는 것이 의도 될 때에는 참조 타입을 사용하는 것이 좋습니다.

위와 같은 특성을 고려하여 값 타입과 참조 타입을 서로 잘 활용해야 질 좋은 소프트웨어를 개발할 수 있습니다.

### struct

struct를 사용해 사용자 정의 타입을 선언할 수 있습니다. 대부분의 언어에서와 유사한 문법을 가집니다.

```swift
struct name {
    // do something...
}
```

SWING의 struct는 다음과 같은 특징을 가지고 있습니다.

* 상속될 수 없으며 상속 받을 수 없습니다.
* 값타입입니다.
* 이니셜라이즈/디이니셜라이즈를 정의할 수 있습니다.
* 캡슐화를 지원합니다.
* 정보은닉을 지원합니다.
* 프로토콜을 준수할 수 있습니다.
* 다형성을 지원합니다. (프로토콜 활용)

### enum

enum을 사용해 특별한 상황에 대해 여러가지 케이스를 만들어 처리할 수 있습니다.

```swift
enum name {
    case Case1
    case Case2

    // do something...
}
```

SWING의 enum은 특별한 상황에 대한 값을 정의하는 것 뿐만 아니라 값 타입으로 저장프로퍼티나 메소드를 가질 수 있습니다. 일반적인 모든 부분에서 struct와 동일하게 동작합니다.

enum의 케이스에 각각 해당하는 원시값을 설정할 수 있습니다. 기본 원시값은 Int이며 0부터 채워집니다. 새로운 원시값을 설정할 경우 원시값을 설정하지 않은 값은 nil로 초기화 됩니다.

```swift
enum name {
    case Case1 = "Case1"
    case Case2 = "Case2"

    // do something...
}

var case1 = name.Case1

output(case1.rawValue)   // "Case1"
```

### class

OOP에서 객체를 표현하는 수단으로 참조 타입입니다.

```swift
class name {
    // do something...
}
```

OOP에서 지원하는 모든 개념을 지원하며 단일 상속만 가능하고 프로토콜을 준수할 수 있습니다.

### protocol

POP의 핵심 개념중 하나인 Protocol입니다.

protocol은 blueprint입니다. 미리 구현할 것을 설계하고 이를 준수하여 구현하는 메커니즘입니다.

```swift
protocol name {
    // do something...
}
```

프로토콜은 다른 프로토콜을 준수할 수 없으며 메소드를 선언할 수는 있지만 정의할 수 없습니다.

프로토콜은 상속과 달리 수평확장이라 메소드가 객체

프로토콜의 기본 기능을 정의하려면 extension을 활용하세요.

### extension

extension을 사용해 타입을 확장할 수 있습니다. struct, enum, protocol, class가 대상이며 어느 때나 확장 가능합니다. SWING의 기본 자료형들은 모두 struct이므로 기본 자료형들도 확장이 가능합니다.

확장을 하게 되면 타입의 크기가 달라질 수 있습니다.

```swift
extension 대상 {
    // do something
}
```

extension을 통해 해당 타입이 특정 프로토콜을 준수할 수 있도록 설정할 수 있습니다. 프로토콜을 준수하게 되면 해당 메소드나 프로퍼티를 정의해야 합니다.

```swift
extension 대상 : 프로토콜 {
    // do something
}
```

### 프로퍼티

프로퍼티는 객체의 속성을 나타내는 것입니다. 메소드와 저장 프로퍼티, self프로퍼티가 있습니다.

#### self 프로퍼티

모든 인스턴스에는 암시적으로 self 프로퍼티를 가지고 있습니다. self 프로퍼티는 자기 자신을 참조하는 프로퍼티입니다.

#### 저장 프로퍼티

저장 프로퍼티는 변수를 담을 수 있게 해주는 틀입니다. 저장 프로퍼티를 정의해 인스턴스가 변수를 담을 수 있게 하십시오. 일반적으로 변수를 선언하는 방식과 동일하며 초기값을 설정해줄 수 있습니다.

```swift
struct ex{
    //Int형 저장 프로퍼티 Var1, 초기값은 10
    var Var1:Int = 10
}
```

#### 프로퍼티 감시자

프로퍼티 감시자는 저장 프로퍼티가 어떻게 변하는지 관찰하고 원하는 행동을 정의할 수 있습니다.

> | set | get | willSet | didSet
-----|-----|-----|-----|-----
동작 조건 | 값을 대입할 때 | 값을 불러올 때 | set을 호출하기 직전 | set을 호출한 뒤 
기본 인자 | newValue | 없음 | newValue | oldValue

```swift
struct ex{
    //Int형 저장 프로퍼티 Var1, 초기값은 10
    var percent:Double {
        set {
            percent = newValue/100
        }
        willSet {
            output("변경되기 전 퍼센트 \(percent), 변경할 값 \(newValue)")
        }
        didSet {
            output("값이 \(oldValue)에서 \(percent)로 변경되었습니다.")
        }
    }
}
```

### 접근 제한

접근제한에는 3가지가 존재합니다. 다른 언어와 거의 비슷합니다.

선언은 <code>public:</code> 와 같이 선언하면 됩니다.

> | public | inherit | private
-----|---------|---------|-----
전역 접근 | 가능 | 불가능 | 불가능
자식 | 가능 | 가능 | 불가능
기능 정의 내부 | 가능 | 가눙 | 가능
