### QG训练营之四

----

###### 4/13 周六

- 早

  早上忙着赶课内作业，本来想着速战速决，但没想到电工作业出乎意料的难。鏖战一番，搞定。

- 中

  开始着手排序作业，插入自然是不用说，已经实现了好几回，秒杀之。接下来就是我所陌生的归并排序，先前我只是稍微了解过归并的分治思想，但并没有实际实现过，一番搜索+思索后，终于搞懂了何为归并。

  归并的核心思路在于两个字串的有序合并。

  代码实现：

  ```c
  	left_end = mid - 1;
      pos = begin;
      number = end - begin + 1;
  
      while(begin <= left_end && mid <= end)
      {
          if (a[begin] <= a[mid])
              temp[pos++] = a[begin++]; /* copy the left array */
          else
              temp[pos++] = a[mid++];   /* copy the right array */
      }
  
      while(begin <= left_end)
          temp[pos++] = a[begin++];     /* deal with the last */
      while(mid <= end)
          temp[pos++] = a[mid++];
  
      for(i = 0; i < number; i++, end--)
          a[end] = temp[end];           /* copy the array to a[] */
  ```

  接下来就是类似于快排的划分子区了，每一次都把字串二分直到不可再分为止，然后不断合并就能获得结果。

  缺点在于空间复杂度较高，使用于外部数据排序。

- 晚

  ​	接下来就是快排，虽然先前实现过，但一来时间过于久远，二是快排的细节比较多，debug也比较难。

  快排的关键在于主元(pivot)的归位，通过线性时间就能把主元放到有序的位置。

  代码实现：

  ```c
  int Partition(int *a, int begin, int end)
  {
      int pivot = a[begin];
      int i = begin, j = end;
      while (i < j)
      // take the ones less than the pivot before the pivot
      // and the bigger ones after the pivot
      {
          while (i < j && a[j] >= pivot) j--;
          while (i < j && a[i] <= pivot) i++;
          if(i < j) swap(a+i, a+j);
      }
      a[begin] = a[i];
      a[i] = pivot;
  
      return i;
  }
  ```

  ​	主元问题解决后，接下来只需要把主元左侧和右侧的区间再次递归重复操作，如此这般就能得出结果。

  ​	但这只是递归版本，非递归版本呢？

  ​	我用栈实现了快排 ( 虽说递归也是栈 )

  ​	思路与递归版十分相似，依旧利用了Partition函数。

  代码实现：

  ```c
  void QuickSort(int *a,int size)
  {
      Stack *S = CreatStack();
  	Push(S, 0);
  	Push(S, size - 1);
  	int left, right, mid;
  	while(!IsEmpty(S))
  	{
  		right = Top(S);
  		Pop(S);
  		left = Top(S);
  		Pop(S);
  		mid = Partition(a, left, right);
  		if (mid - 1 > left)
  		{
              Push(S, left);
              Push(S, mid - 1);
  		}
  		if (mid + 1 < right)
  		{
              Push(S, mid + 1);
              Push(S, right);
  		}
  	}
  }
  ```

  ​	快排之后是计数排序，我原以为计数排序就是桶排，但实际了解过之后才知道略有不同，桶排是直接按照count数组的下标与内容输出，而计数排序则是要求前缀和，以此来获得对应值下标。

  代码实现：

  ```c
  void CountSort(int *a, int size , int max)
  {
      int i;
      int *count = (int *) malloc ((max + 1) * sizeof(int));
      int *temp = (int *) malloc ((size + 1) * sizeof(int));
      memset(count, 0, sizeof(count) * max);
      memset(temp, 0, sizeof(temp) * size);
  
      for (i = 0; i < size; i++) count[a[i]]++;                    
      // count the index
      for (i = 1; i < max + 1; i++) count[i] += count[i - 1];        
      // calculate the sum of the prefixes
      for (i = size - 1; i >= 0; i--)
      {
          temp[count[a[i]] - 1] = a[i];                              
          // output the count result according to the index
          count[a[i]]--;
      }
      for (i = 0; i < size; i++)                                     
          // copy the result
          a[i] = temp[i];
  
      if(count != NULL)free(count);
      if(temp != NULL)free(temp);
  }
  ```

  注意，把结果导入temp时必须逆序，否则会失去稳定性。

  ​	计数排序与归并排序类似，空间复杂度较高。

  ​	紧接着是基数排序。基排才是真正利用了桶排的思想，不同的是桶排开了大量的桶去存放数据，而基排只需开进制位的桶就足以。

  ​	我所实现的基排是从个位开始比较，每一个桶都开一个链表去存放数据。

  代码实现：

  ```c
  int D, Di, data_copy, i;                     // D - current digit    Di - current digit value of data
      Bucket B;
      List tmp, list = NULL;
  
      // initialize the buckets
      for (i=0; i<Radix; i++)
           B[i].head = B[i].tail = NULL;
      for (i=0; i<size; i++)
      // initialize the list and store the data in reverse order
      {
          tmp = (List) malloc (sizeof(struct LNode));
          tmp->key = a[i];
          tmp->next = list;
          list = tmp;
      }
  
      for (D = 1; D <= MaxDigit; D++)
      {
          // take the data in buckets
          while (list)
          {
              // get the current digit
              data_copy = list->key;
              for (i = 1; i <= D; i++)
              {
                  Di = data_copy % Radix;
                  data_copy /= Radix;
              }
              // into buckets
              tmp = list; list = list->next;
              tmp->next = NULL;
              if (B[Di].head == NULL)
                  B[Di].head = B[Di].tail = tmp;
              else
              {
                  B[Di].tail->next = tmp;
                  B[Di].tail = tmp;
              }
          }
          // take the data in buckets back to the list
          list = NULL;
          for (Di = Radix - 1; Di>=0; Di--)
          {
              if (B[Di].head)
              {
                  B[Di].tail->next = list;
                  list = B[Di].head;
                  B[Di].head = B[Di].tail = NULL;
              }
          }
      }
      for (i=0; i < size; i++)
      {
          tmp = list;
          list = list->next;
          a[i] = tmp->key;
          free(tmp);
      }
  ```

  ---

  4/14 周日

  - 早

    ​	早上起来准备实现012排序和求无序数组的第K大数。

    ​	首先是012排序， 具体思路是用三个指针（广义）去指定当前位置，0该存放的位置，2该存放的位置，然后从头扫一遍，遇到0就与0指针swap，然后0指针下移，遇到2则与2指针swap，然后移动2指针，这样就能在线性时间内处理完。

    代码实现：

    ```c
    void ColorSort(int *a, int size)
    {
        int ptr1 = 0, ptr2 = size - 1, ptr_current = 0;
        for (ptr_current = 0; ptr_current <= ptr2; ptr_current++)
        {
            if (a[ptr_current] == 0)
                swap(&a[ptr_current], &a[ptr1++]);
            else if (a[ptr_current] == 2)
                swap(&a[ptr_current--], &a[ptr2--]);  
            // current pointer - 1 means to rejudge the current data
        }
    }
    
    ```

    ​	然后是寻找第K大数，首先有几种思路，最简单莫过于排序之后取下标K-1的值，但我们有更好的办法，就是用快排确定主元的方法去确定K值。

    代码实现:

    ```c
    int findKth(int *a, int n, int k)
    {
        int begin = 0, end = n - 1, index;
        while (begin < end)
        {
            index = Partition(a, begin, end);
            if (index + 1 == k)
                    break;
            else if (index + 1 < k)
                begin = index + 1;
            else if (index + 1 > k)
                end = index;
        }
        return a[index];
    }
    ```

    

  - 中

    下午马马虎虎写了一下rand函数和文件操作，把函数集整合一下。

  - 晚

    ​	晚上大概是准备去学一下KNN，或者写一写英语。

  

