## 训练营之三

---

​	这周前半部分算是把python中的外星人游戏照打了出来，也多多少少学到了小型python项目的简单构架，接下来就要进入maplotslib等第三方库的学习了。

---

​	这周的大组作业是泛式队列，队列不难，把握好先进先出的思路就好，重点是简单泛式的实现。C中的泛式的最终形态大概就是python的变量形式，不过这次我只是简单引用memcpy复制内存实现可对接多种数据类型（int,  float , char 和str，其中str有长度限制，太长会崩溃，目前无解决思路）。其他的思路是利用宏来实现，不过个人感觉难度较大。

​	这次的泛式实现思路：

1. 队列的数据类型必须是空类型指针，如此才能兼容多种类型。
2. 必须获取入队元素的地址，以及其在内存中占用的空间（也就是它的类型， 但字符串较为复杂， 需要获取字符串的长度）。
3. 利用memcpy（队列数据域地址， 入队元素地址，元素长度）将内存完全复制到队列中。
4. 在遍历时，只须相应地转换指针类型即可将其打印出来



​	还有几个小注意点，一个是循环队列的基本思路是利用取余的特性，出入队时只要加上相应的值再把超出循环的部分去掉即可；二是野指针问题，最初我以为申请指针数组后，数组元素会自动分配内存，但实际上并没有，还是要自己手动分配。	

​	我发现在这样比较麻烦的小作业里，模块化的思想非常重要，特别是在**调试**和**复用**这两方面，低耦合性的模块非常有用。



​	下次作业大概就是树了，不知道重点会出什么呢？表达式树？平衡树？如果是后者的话，我就可以休闲一点了。

----

#### memcpy笔记

- 描述

C 库函数 **void \*memcpy(void \*str1, const void \*str2, size_t n)** 从存储区 **str2** 复制 **n** 个字符到存储区 **str1**。

- 声明

下面是 memcpy() 函数的声明。

```
void *memcpy(void *str1, const void *str2, size_t n)
```

- 参数
  - **str1** -- 指向用于存储复制内容的目标数组，类型强制转换为 void* 指针。
  - **str2** -- 指向要复制的数据源，类型强制转换为 void* 指针。
  - **n** -- 要被复制的字节数。

- 返回值

该函数返回一个指向目标存储区 str1 的指针。

- 实例

下面的实例演示了 memcpy() 函数的用法。

```c
// 将字符串复制到数组 dest 中 
#include <stdio.h> 
#include <string.h>   
int main () {
	const char src[50] = "http://www.runoob.com";
	char dest[50];      
	memcpy(dest, src, strlen(src)+1);    
	printf("dest = %s\n", dest);        
	return(0); 
}
```

​	注：字符串只要按图中的思路复制就行，不过不安全，容易溢出；其他数据类型直接使用sizeof语句求出长度即可。

---

##### 生成器浅析

###### 简单输出斐波那契數列前 N 个数



- 方法 1. 

```python
def fab(max): 
	n, a, b = 0, 0, 1 
	while n < max: 
		print b a, b = b, a + b 
		n = n + 1
```



- 方法2

```python
def fab(max): 
   n, a, b = 0, 0, 1 
   L = [] 
   while n < max: 
       L.append(b) 
       a, b = b, a + b 
       n = n + 1 
   return L
```



- 方法3（生成器）

```python
def fab(max): 
    n, a, b = 0, 0, 1 
    while n < max: 
        yield b 
        # print b 
        a, b = b, a + b 
        n = n + 1 
```

​	简单地讲，yield 的作用就是把一个函数变成一个 generator，带有 yield 的函数不再是一个普通函数，Python 解释器会将其视为一个 generator，调用 fab(5) 不会执行 fab 函数，而是返回一个 iterable 对象！在 for 循环执行时，每次循环都会执行 fab 函数内部的代码，执行到 yield b 时，fab 函数就返回一个迭代值，下次迭代时，代码从 yield b 的下一条语句继续执行，而函数的本地变量看起来和上次中断执行前是完全一样的，于是函数继续执行，直到再次遇到 yield。

​	同时也可以手动调用 fab(5) 的 next() 方法（因为 fab(5) 是一个 generator 对象，该对象具有 next() 方法），这样我们就可以更清楚地看到 fab 的执行流程：

##### 清单 6. 执行流程

```python
>>> f = fab(5) 
>>> f.next() 
1 
>>> f.next() 
1 
>>> f.next() 
2 
>>> f.next() 
3 
>>> f.next() 
5 
>>> f.next() 
Traceback (most recent call last): 
 File "<stdin>", line 1, in <module> 
StopIteration
```

​	当函数执行结束时，generator 自动抛出 StopIteration 异常，表示迭代完成。在 for 循环里，无需处理 StopIteration 异常，循环会正常结束。

我们可以得出以下结论：

​	一个带有 yield 的函数就是一个 generator，它和普通函数不同，生成一个 generator 看起来像函数调用，但不会执行任何函数代码，直到对其调用 next()（在 for 循环中会自动调用 next()）才开始执行。虽然执行流程仍按函数的流程执行，但每执行到一个 yield 语句就会中断，并返回一个迭代值，下次执行时从 yield 的下一个语句继续执行。看起来就好像一个函数在正常执行的过程中被 yield 中断了数次，每次中断都会通过 yield 返回当前的迭代值。

​	yield 的好处是显而易见的，把一个函数改写为一个 generator 就获得了迭代能力，比起用类的实例保存状态来计算下一个 next() 的值，不仅代码简洁，而且执行流程异常清晰。