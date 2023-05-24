# 词法分析

## 需求描述
构造一个小 (Mini) 语言的词法分析程序:

- 设计一个包含简单算术表达式、赋值语句、IF语句的小语言的文法
- 根据此文法, 构造一词法分析程序. 输入以#为结束符的源程序, 输出为各类单词表和单词串文件
- 源程序和输出的单词串均以文件的形式存放
- 单词的自身值均为其对应的表的指针, 如标识符表的指针、常数表的指针等
- 词法错误类型: 词法中未定义的宇符及任何不符合词法单元定义的宇符

## 形式化语言描述

1. 构建的语言: Mini-C 语言

2. 关键字表

    |  main   |  int   |   long    |    bool    |    if     |   else   |
    | :-----: | :----: | :-------: | :--------: | :-------: | :------: |
    | **for** | **do** | **while** | **return** | **false** | **true** |

3. 符号表

    |   >   |   <   |   =   |  <=   |  >=   |  ==   |  !=   |   ;   |     ,     |            |
    | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :-------: | :--------: |
    | **+** | **-** | ***** | **/** | **(** | **)** | **{** | **}** | **digit** | **string** |

4. 数字和字符串文法

    letter &RightArrow; letter ( letter | digit ) ^*^

    letter &RightArrow; a | b | ... | z | A | B | ... | Y | Z

    digit &RightArrow; digit ^+^

    digit &RightArrow; 0 | 1 | ... | 9



## 标识符编码

| 标识符 | 编码 | 标识符 | 编码 |
| :----: | :--: | :----: | :--: |
|  main  |  0   |   ==   |  16  |
|  int   |  1   |   !=   |  17  |
|   if   |  2   |   +    |  18  |
|  else  |  3   |   -    |  19  |
| while  |  4   |   *    |  20  |
|   do   |  5   |   /    |  21  |
|  for   |  6   |   (    |  22  |
|  long  |  7   |   )    |  23  |
|  bool  |  8   |   {    |  24  |
|   <    |  9   |   }    |  25  |
|   >    |  10  | digit  |  26  |
|   =    |  11  | string |  27  |
|   ;    |  12  | return |  28  |
|   ,    |  13  | false  |  29  |
|   <=   |  14  |  true  |  30  |
|   >=   |  15  |        |      |



## 编译和使用
1. 编译

    ~~~bash
    g++ -g -std=c++11 lexical-analysis.cpp
    ~~~

2. 运行

    - 打印提示信息

        ~~~bash
        ./a.out
        ~~~

    - 分析程序

        ~~~bash
        ./a.out <inputfile> <outputfile>
        ~~~



## 测试样例
1. 正确程序

    ~~~cpp
    int main () {
        int a = 4, b = 5;
        if (a == b) {
            int alower = 3;
            b = alower * 100 / 2 - 8;
        } else if (a != b) {
            bool flag = false;
            flag = true;
        }
        do {
            long c = 99999239;
            for (int i = 0; i <= a; i = i + 1) {
                c -= 1;
            }
        } while (a > b) ;
        return 0;
    }
    #
    ~~~

2. 错误程序

    ~~~c
    int main () {
        int i, j, k;
        long a = ?;
        return 0;
    }
    #
    ~~~
