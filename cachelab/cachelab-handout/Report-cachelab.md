
#<center>  Report-cachelab</center>
---
<p  align = "right">黄子骕21307130013</p>

## Part A


## Part B

### cache的基本情况
- b = 5，故每一个block的大小是32bytes，而一个int的大小是4bytes，故每个block可以容纳8个元素
- s = 5，故共有32个set
- E = 1，表明是direct-mapped，每个set值容纳一个block

### Simple row-wise scan transpose方法效率低下的原因分析
- 当使用这个方法时，在对数组B进行写的时候会出现大量conflict miss：观察set_index的分布可知，对于 32x32 矩阵，每8行是一个周期，set的值进入一个新的轮回。因此在对B的一列进行写操作时，由于一列有32个元素，其中间隔为8行的元素共享同样的set_index，如block:B[0][0] ~ B[0][7]与block:B[8][0] ~ B[8][7]共享同样的set_index，这时候就会出现每写一次就一定出现conlict miss的情况
  
### M = 32, N = 32的情况

#### 观察
- 一个block有8个元素
- 矩阵中每8行会进入set_index的新周期
#### 实现
- 为了不让写入B矩阵的操作出现太多conflict miss，根据 cachelab.pdf 中提示，尝试将矩阵分快成 8x8 的小矩阵进行处理，此时对于每个 8x8 小矩阵处理时，B矩阵的写入不会因为上面的原因出现conflict miss，只会因为写入对角线上元素的时候由于A与B中元素所在block也一定共享一个set_index而出现反复conflict miss
- 为了解决对角线上元素的问题，使用8个本地变量先保存A中小矩阵的一行，再对B进行写入，这样防止了操作对角线元素时额外的conflict miss情况：假设原本一个set中已有A中block_A，由于对角线元素set_index相同，此时要写入B则必须将此block_A替换为block_B，后续要继续读取block_A中数据，又要将block_B替换为block_A
### 结果
- miss：288 < 300 
  
### M = 64, N = 64的情况

### 观察
- 对于 64x64 矩阵，每4行就将会进入一个新的set_index周期
- 尝试分为 8x8 小矩阵结果为miss:4612次，不太理想，我认为是由于set_index周期变为4行后，在小矩阵中写入B也会出现额外的conflict miss
- 根据新的set_index周期，尝试分为 4x4 小矩阵结果为miss:1700次，相较于 8x8 矩阵大幅缩小，但仍大于1300次
### 实现
- ·

