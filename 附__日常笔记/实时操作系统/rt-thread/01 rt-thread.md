rt-thread、uCOS 的内核调度算法采用位图 (bitmap) 的调度算法。这个算法的好处是可以实现 O (1) 调度（注，O (1) 定义，可以参考《数据结构与算法分析》），大致来说，就是每次调度的时间是恒定的：无论当前的系统中存在多少个线程，多少个优先级，rt-thread 的调度函数总是可以在一个恒定的时间内选择出最高优先级的那个线程来执行。

rt-thread 内核调度算法涉及的源码文件主要是 `scheduler.c`。入口在 `components.c` 中, 宏定义在 `rtconfig.h` 中。

# 01 [正点原子板 Nano 入门环境搭建](https://www.rt-thread.org/document/site/docs/applicationnote/apollo_nano_start/)

## 安装 rt-thread 包
>如果 MDK 安装 rt-thread 的 Pake 不成功, 最好重新装一个最新版本的 MDK！ [下载 MDK5.23](https://pan.baidu.com/s/1c20eQpM)  密码：w7qc

[rtthread.2.1.1.pack](http://www.rt-thread.org/download/mdk/rt-thread.rtthread.2.1.1.pack) MDK 离线安装包下载！

> Kernel 文件包括：

```
clock.c
components.c
device.c
idle.c
ipc.c
irq.c
kservice.c
mem.c
object.c
scheduler.c
thread.c
timer.c
```

> Cortex-M 芯片内核移植代码：

```
cpuport.c
context_rvds.s
```

> 应用代码及配置文件：

```
board.c
rtconfig.h
```

## 修改源码适配开发板
> [源码和文档百度云下载](http://pan.baidu.com/s/1sl4sWjj)

修改方法见 [正点原子板 Nano 入门环境搭建 第三步](https://www.rt-thread.org/document/site/docs/applicationnote/apollo_nano_start/#_1)

## RT-Thread 程序执行流程分析

### RT-Thread 入口
在 `components.c`文件的 140 行看到 `#ifdef RT_USING_USER_MAIN` 宏定义判断，这个宏是定义在 `rtconfig.h` 文件内的，而且处于开启状态。同时可以在 146 行看到 `#if defined (__CC_ARM)` 的宏定义判断，`__CC_ARM` 就是指 keil 的交叉编译器名称。

这里可以看到定义了 2 个函数：`$$Sub$$main()` 和 `$$Super$$main()` 函数；这里通过 `$$Sub$$main()` 函数在程序就如主程序之前插入一个例程，实现在不改变源代码的情况下扩展函数功能。链接器通过调用 $$Sub$$Main() 函数取代 main()，然后通过 $$Super$$main 再次回到 main()。

```
#if defined (__CC_ARM)
extern int $Super$$main(void);

/* re-define main function */

int $Sub$$main(void)
{
    rt_hw_interrupt_disable();
    rtthread_startup();
    return 0;
}
```

在 $$Sub$$main 函数内调用了 `rt_hw_interrutp_disable()` 和 `rtthread_startup()` 两个函数。熟悉 RT-Thread 开发流程的，一看就知道这是标准的 RT-Thread 的启动入口。 其中，`rt_hw_interrupt_disable()` 是关中断操作；`rtthread_startup()` 完成了 systick 配置、timer 初始化 / 启动、idle 任务创建、应用线程初始化、调度器启动等工作。

```
int rtthread_startup(void)
{
    rt_hw_interrupt_disable();

    /* board level initalization
     * NOTE: please initialize heap insideboard initialization.
     */
    rt_hw_board_init();

    /* show RT-Thread version */
    rt_show_version();

    /* timer system initialization */
    rt_system_timer_init();

    /* scheduler system initialization */
    rt_system_scheduler_init();

    /* create init_thread */
    rt_application_init();

    /* timer thread initialization */
    rt_system_timer_thread_init();

    /* idle thread initialization */
    rt_thread_idle_init();

    /* start scheduler */
    rt_system_scheduler_start();

    /* never reach here */
    return 0;
}
```

> 几个函数说明如下：

| 函数名    | 描述     |
| :------------- | :------------- |
| rt_hw_board_init        | 板级硬件初始化  |
| rt_system_timer_init()  | timer 初始化    |
| rt_application_init()   | 应用线程初始化   |
| rt_system_timer_thread_init()  |   timer 启动   |
| rt_thread_idle_init()   | idle 任务创建   |
| rt_system_scheduler_start()	 | 调度器启动  |

### 应用线程入口

rt_application_init()源码如下：

```
void rt_application_init(void)
{
    rt_thread_t tid;

#ifdef RT_USING_HEAP
    tid = rt_thread_create("main",main_thread_entry, RT_NULL,
    RT_MAIN_THREAD_STACK_SIZE,RT_THREAD_PRIORITY_MAX / 3, 20);
    RT_ASSERT(tid != RT_NULL);
#else
    rt_err_t result;
    tid = &main_thread;
    result = rt_thread_init(tid,"main", main_thread_entry, RT_NULL,main_stack, sizeof(main_stack),RT_THREAD_PRIORITY_MAX / 3, 20);
    RT_ASSERT(result == RT_EOK);
#endif
    rt_thread_startup(tid);
}
```

应用线程创建了一个名为 `main_thread_entry` 的任务，并且已经启动了该任务。

man_thread_entry 任务:

```
/* the system main thread */
void main_thread_entry(void*parameter)
{
    extern int main(void);
    extern int $Super$$main(void);

    /* RT-Thread components initialization */
    rt_components_init();

    /* invoke system main function */
#if defined (__CC_ARM)
    $Super$$main(); /* for ARMCC. */
#elif defined(__ICCARM__) ||defined(__GNUC__)
    main();
#endif
}
```

`man_thread_entry` 任务完成了 2 个工作：调用 `rt_components_init()`、进入应用代码真正的 main 函数。


### RT-Thread 的初始化及其启动如下图所示

![](http://oygqszutp.bkt.clouddn.com/QIniuyun_Store/study/RT-Thread/01%20RT-Thread%20%E5%88%9D%E5%A7%8B%E5%8C%96%E5%8F%8A%E5%90%AF%E5%8A%A8.png)


main()函数其实只是 RT-Thread 的一个任务，该任务的优先级为RT_THREAD_PRIORITY_MAX / 3，任务栈为RT_MAIN_THREAD_STACK_SIZE。
