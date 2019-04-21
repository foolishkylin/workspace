#### QG训练营之五

---

​	本周也是数据挖掘组开展中期考核的一周，在这一周里，我学习了kmeans算法、kNN算法及其优化，至于线性回归，我在之前就用c实现过以此，现在也用numpy优化了一下，但还是不能解决奇异矩阵的问题，接下来我打算学习一下岭回归。

---



​	kNN的伪代码：

​	计算训练集内的点与目标点的距离，并排序（升序） 
​	对于排序中的前 k 个点： 

 		计算各个标签出现的频率 
	返回频率最高的标签 

> 在演示的时候，似乎我的kNN算法实现略有偏差，应该把数据集拆成两部分，一部分用来训练，另一部分用来测试，不管思路还是差不多的。

---

​	kmeans的伪代码：

​	创建 k 个随机聚点 

​	当聚点需要变化时： 

​		对每个数据集内的点 

 		 	计算与 k 个聚点的距离 

  			重新分配点所属的簇 

 			以簇的中心点更新聚点 

​	返回聚点与簇集

> 由于聚点的随机生成，导致聚点可能会收敛于局部最优而非全局最优，为了减弱这个影响， 均分kmeans的优化自然而然地产生了。

​	均分kmeasn：

​			将数据集所有点视为一个簇 
​			簇集数小于 k 时 

 					对于每个簇 

  						进行二分 kmeans（k 为 2 的 kmean） 

  						计算分类前后的总误差 

 					选择误差最小的二分方法进行划分 

 		更新聚点 
		 返回聚点与簇 

> 不过实测的时候，均分kmeans并没有比kmeans好多少，可能是我的实现有问题，有待优化。

---

本周、也是最后一周，这次的大组作业比较简单，就是二叉树的简单构建与应用，也没涉及到平衡、哈夫曼等等。

​		我认为主要的难点在于层次遍历与非递归遍历两个地方，一个是用队列，另外一个是用栈，但其实和广搜、深搜差不多了。

层次遍历：

```c
Status LevelOrderTraverse(BiTree T, Status (*visit)(TElemType e))
{
    Queue Q;
	Q.next = 0;
    if (T)
    {
        visit(T->data);
        EnQueue(&Q, T);
    }
    while(!IsEmpty(&Q))
    {
        T = DeQueue(&Q);
        if (T->lchild)
        {
            visit(T->lchild->data);
            EnQueue(&Q, T->lchild);
        }
        if (T->rchild)
        {
            visit(T->rchild->data);
            EnQueue(&Q, T->rchild);
        }
    }
}
```

非递归中序遍历:

```c
Status InOrderTraverse_cycle(BiTree T, Status (*visit)(TElemType e))
{
    Stack S;
    S.next = 0;
    while (T || !StackIsEmpty(&S))
    {
        while (T)
        {
            Push(&S, T);
            T = T->lchild;
        }
        while (!StackIsEmpty(&S))
        {
            T = Top(&S);
            visit(T->data);
            Pop(&S);
            T = T->rchild;
        }
    }
}
```

这两点解决之后，基本上就不难了，至于表达式求值部分，在实现栈求值之后已经不算难了。

具体代码：

```c
int pos = 0;

Status CreateBiTree(BiTree *T, char* definition)
{
    while (definition[pos] == ' ')
        pos++;
    char x = definition[pos++];

    *T = (BiTree) malloc (sizeof(BiTNode));
    (*T)->data = x;
    (*T)->lchild = (*T)->rchild = NULL;

    if (!isNum(x))
    {
		CreateBiTree(&((*T)->lchild), definition);
    	CreateBiTree(&((*T)->rchild), definition);
    }

    return SUCCESS;
}

double Value(BiTree T)
{
    if (isNum(T->data))
        return make_num(T->data);
    else
        return cal(Value(T->lchild), Value(T->rchild), T->data);
}
```

​		当然，在进行计算之前，要判断一下表达式是否正确，并且这里只能求个位数，如果想求多位的话也不难，只要修改一下表达式字符串的分割，然后应用atof（）转换即可。