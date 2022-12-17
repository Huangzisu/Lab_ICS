<h1><center> Report-cachelab </center>

<p  align = "right">黄子骕21307130013</p>

## Part A

### cache基本架构
- 对于cache，使用二维数组来实现
- line结构：最小的结构（不需要考虑line中内容）
  - valid：标记是否有效
  - tag：记录tag
  - time：记录距离上一次使用的时间，以待后续使用LRU replacement policy来替换
- set结构：由一个line结构数组
- cache结构
  - sets：一个set结构数组
  - set_size：记录每个set存放多少个line
  - set_num：记录一共有多少个set

### 所需函数的实现
- *get_opt*：根据 cachelab.pdf 中提示，在本函数中调用了 *getopt* 函数来读取命令行中的选项，其中调用 *atoi* 函数来将读到的字符串转为int
- *get_set_index*：该函数根据传入的地址返回相应的set_index
- *get_tag*：该函数根据传入的地址返回相应的tag值
- *test_miss*：该函数遍历相应的set检查是否出现miss
- *test_full*：该函数遍历相应的set，检查该set是否装满
- *update_time*：该函数用在每次有效操作之后，更新对应set中每个line的time，并将最新操作的line的time设置为0
- *find_victim*：若出现需要替换时，用此函数寻找被替换的line，其中需要遍历set比较每个line的time，time最大的即为victim
- *data_load*：该函数实现data load操作
  - 首先判断是否miss，进而出现两种情况
    - miss：累计miss次数并检查是否装满（发生eviction）
      - 装满：发生eviction，累计eviction次数，寻找victim并修改状态
      - 没装满：寻找空位并更新状态
    - hit：累计hit次数
  - 最后更新对应set中所有line的time
- *data_store*：实现data store操作，在本实验中与data load产生一样效果，因此直接调用 *data_load* 
- *data_modify*：实现data modify操作，即先data load在data store，先后调用已有函数即可
- *init_cache*：初始化cache，即使用malloc分配空间并赋初值

### main函数实现
1. 首先调用 *get_opt* 读取命令行选项参数
2. 根据相应参数初始化cache
3. 打开相应文件
4. 进入循环
   1. 读取文件中的操作
   2. 根据地址调用 *get_set_index* 与 *get_tag*，得到对应的set_index以及tag值
   3. 进入switch判断语句
      - 操作为L：调用 *data_load*
      - 操作为S：调用 *data_store*
      - 操作为M：调用 *data_modify*
      - 操作为L：不做操作
5. 调用 *printSummary*，程序结束


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
#### 结果
- miss：290 < 300 
  
### M = 64, N = 64的情况

#### 观察
- 对于 64x64 矩阵，每4行就将会进入一个新的set_index周期
- 尝试分为 8x8 小矩阵结果为miss:4612次，不太理想，我认为是由于set_index周期变为4行后，在小矩阵中写入B也会出现额外的conflict miss
- 根据新的set_index周期，尝试分为 4x4 小矩阵结果为miss:1700次，相较于 8x8 矩阵大幅缩小，但仍大于1300次
#### 实现

- 使用分块 8x8 策略，但是在读A时尽可能的一次读完一个block中全部的8个元素，一次来减少miss（注：下列A与B均表示A或B中对应的8x8小矩阵）
  1. 处理 8x8 小矩阵的上面的 4x8 矩阵，将A中的每一行放入对应的B中的一列（可以一次读完一个block全部元素，用满了这个block），此时的放置对于B主对角线上的 4x4 小矩阵（左上角）是位置正确的，对于右上角的 4x4 小矩阵位置是不正确的
  2. 处理B中左下小矩阵与右上小矩阵，将右上小矩阵中数据放入左下小矩阵中它应该在的位置，同时将A中对应的左下小矩阵映射到B中右上小矩阵来填补原来那些错误的数据
  3. 最后只剩下B中右下小矩阵没有写入数据，利用1中类似过程写入即可，此时只能用到一个block的一半

#### 结果

- miss：1230 < 1300

### M = 61, N = 64的情况

#### 观察

- 首先尝试一下直接分块为 8x8 小矩阵的情况：miss了2121次，略微超过2000次
- 再尝试一下直接分块为 16x16 小矩阵的情况：miss了1995次，已经小于2000次
- 接着尝试一下同样分块为 8x8 小矩阵，但是对每个小矩阵使用 32x32 矩阵情况的优化方式：miss了2385次，效果反而变差了
- 故最后选择16x16的直接分块计算策略

#### 实现

- 将矩阵尽量分为 16x16 的小矩阵，当不够分时就按照剩余部分的尺寸进行处理

#### 结果

- miss：1995 < 2000
