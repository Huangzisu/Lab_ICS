

<h1><center>   Report - shell lab </center>

<p  align = "right">黄子骕21307130013</p>

## eval()

- 功能：通过这个函数我们需要解析命令并且做出相应的操作
  - 若为内置命令，则直接执行
  - 若非内置命令，则 fork 一个子进程运行（区分 foreground 与 background 的情况）
- 实现：（按顺序进行以下操作）
  1. 调用 parseline 函数来解析命令，并通过其返回值来确定 job_state 为 BG 还是 FG
  2. 判断是否输入命令是否为空，若空则返回，此处若不做处理，则当输出空指令时会出现错误
  3. 调用 builtin_cmd 函数来对内置命令进行处理
  4. 若非内置命令，则 ：
     1. 将 SIGCHLD 信号阻塞，放置子进程在父进程前结束而出现问题
     2. fork 一个子进程，并对取消这个子进程对 SIGCHLD 的
        1. 调用 setpgid 令他分为一个单独进程组
        2. 调用 execve 运行程序
     3. 阻塞所有信号，防止在 addjob 与 deletejob 由于程序运行顺序而出现错误
     4. 调用 addjob 将新进程加入 joblist
     5. 接触信号阻塞
     6. 判断 job 的状态来进行后续操作
        - 若为 FG，则调用 waitfg 等待其结束
        - 若为 BG，则提示运行信息

## buildin_cmd()

- 功能：执行内置命令
- 实现：
  - 若命令为 `jobs` 则调用 listjobs 函数
  - 若命令为 `bg` 或 `fg` 则调用 do_bgfg函数
  - 若命令为 `quit` 则 exit(0) 退出

## do_bgfg()

- 功能：执行 bg  与 fg 命令
- 实现：
  1. 检查命令是否完整，是否输出了 jid 或 pid
  2. 根据输入的 id 类型进行操作（二者类似）
     1. 读取 id 并判断是否有效
     2. 找到 id 对应的 job
  3. 根据命令进行操作
     - 若为 `bg` 命令，则将 job_state 设置为 BG， 并给对应进程组发送 SIGCONT 信号继续运行，同时输出命令信息
     - 若为 `fg` 命令，则将 job_state 设置为 FG，并给对应进程组发送 SIGCONT 信号继续运行，并调用 waitfg 等待前台任务执行完毕

## waitfg()

- 功能：等待前台任务结束
- 实现：
  - 利用 while 循环不断判断该 pid 是否为 前台任务的 pid，若是则挂起，若不是则返回

## sigchld_handler()

- 功能：对 SIGCHLD 信号的处理函数
- 实现：（注意保存与恢复 errno ）
  - 利用 while 循环，调用 waitpid 尽可能收割更多的子进程（令 pid == -1，使等待集合为所有子进程；令 option 为 WNOHANG | WUNTRACED，使得也可以检查被停止的子进程且当没有子进程被停止或被终止是不会一直卡在这个循环中）
    1. 屏蔽所有信号，防止竞争
    2.  根据不同的退出状态进行操作
       - 若 WIFEXITED(status) 为真，则表明正常终止，则调用 deletejob 在 joblist 中删除该 job
       - 若 WIFSIGNALED(status) 为真，则表明由于一个未被捕获的信号终止，则打印该终止信号信息并 deletejob
       - 若 WIFSTOPPED(status) 为真，则表明被停止，此时更改 job_state 为 ST，并打印信息
    3. 恢复信号

## sigint_handler() 与 sigstp_handler()

- 功能：向前台任务进程组发送相应信号
- 实现：
  - 利用 kill 函数向所有前台进程发送信号（注意保存与恢复 errno ）

## 总结

注意几项原则：

- 访问全局变量时要阻塞所有信号
- 处理一些有先后顺序的操作时，放置由于运行先后出现错误，也要阻塞所有信号

























