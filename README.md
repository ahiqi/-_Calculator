

2017301500117胡启海





一、文法定义

program—>block
block—>line ; block|line .block|ε
line—>def|epr|fun
def—>int id |float id
epr—>id = expr|id=-expr
fun—>wirte(id)
计算表达式
expr—> - exprB
exprB—>exprB+term|exprB-term|term
term—>term*factor|term/factor|factor
factor—>(expr)|digit| id
id—>letter(letter|digit)*
letter—>a|b|...|z|A|B|...|Z
digit—>0|1|...|9



二、代码细节


1、使用方法

1、将要计算测试的表达式写入一文本中如下是测试文档以及内部内容。


输入要求：
1)支持浮点数和整数两种类型，浮点数可以转换成整数；整数不可以转换成浮点数；
2)每个语句需要以“；”结束，以“.”表示全部输入的结束
3)变量需要先声明再使用；
4)变量名可以是由数字和字母组成，但首字符必须是字母。
5)每个表达式中使用的变量需要在之前已经有赋值。
6)输出语句使用write(a)，输出并换行，其中a为int类型或者float类型的变量名。

2、运行cmd进入命令行程序，通过cd命令进入到程序所在的文件夹内，再运行程序。
具体操作如下所示：



异常测试：
《一》、Test.txt内容如下：

	

结果显示：



《二》、Test.txt内容如下：



结果显示：


《三》、Test.txt内容如下：




显示结果如下：

