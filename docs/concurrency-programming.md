并发：在计算机中，指在一个系统中，两个及以上的任务同时发生。
并行：是指在硬件层面上，两个任务是真正同时运行，发生着的。
并发有可能不是并行，只是CPU核心通过任务切换的方式，让其表现得像是并行的。
即使在多核心的计算机上，由于大量任务在运行着，其数量远超CPU核心的数量，
因此，还是不可避免的需要进行任务切换。

并发的方式：
- 多进程并发
- 单进程多线程并发

管理线程：
- 启动、等待/分离、线程信息