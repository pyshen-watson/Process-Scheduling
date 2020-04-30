# 2020	OS Project 1 - Process Scheduling   
資工二 b07902078 沈韋辰

# 1. Kernel Version
Kernel的部分本次選用linux4.10.13，在數次嘗試中發現，太新的版本會有一些不知名的bug
# 2. Design
每筆資料的處理方式如下:
``` ./scheduler``` 
=> ```./FIFO``` or ```./RR``` or ```./SJF``` or ```./PSJF```
=> ```fork()``` 
=> ```run the process```
=> ```send a signal to parent```

### (1) Initialization 
![](https://i.imgur.com/A2noGbg.png)
- PCB: store ready, run time, pid, etc.
-  USE_CPU(x): set the cpu affinity
- qsort(..): sort the process by ready time
- signal_routine: my signal handler
- enable: a lock to determine whether CPU is available
- finish: counter of the finished task
### (2-1) fork()-child
![](https://i.imgur.com/oh7AZkd.png)
- USE_CPU(1): child use another CPU
- unit_time(): do 1000000 times for-loop
- SIGFNS: the process has finished
- SIGTERM: the process hasn't finished
### (2-2) fork()-parent
![](https://i.imgur.com/ANBmksZ.png)
- when we first run this process, store the PID.
### (3) signal handler
![](https://i.imgur.com/tfdOOEe.png)
- SYSCALL_AVAILABLE: defined if run in syscall installed environment
### (4-1) system call - pjtimer
![](https://i.imgur.com/vBYmsoc.png)
### (4-2) system call - pjprint
![](https://i.imgur.com/4C5R5az.png)
- [Project1] tag - 紀錄process完成
- [RELEASE] tag - 另有特殊用途，將由下則說明
### (4-3) system call - append on the end of policy
- 此為本人在作業中發生的一個問題: 同時發出stderr和sys_pjprint時，兩者得到的數據不同，似乎平移了一個進程。
- 經過本人多次實驗後發現，每個policy發出的最後一個printk會被block住，直到下一個case呼叫時，上一個case的最後一個printk message則會被呼叫，並且會讓之後的訊息全部被往後推一個進程，連帶影響後續的結果。
(下圖的上半部stderr, 下半部則是dmesg，可見兩者的PID有錯位發生)
![](https://i.imgur.com/OlYvKXc.png)
- 然而，printk為Non-blocking的system call，因此其無法正常運作的原因仍不明(maybe: kernel version, race condition, etc)
- 但實做上，我們可以在pjprint內加一個用來release那個無法成功的printk，類似用自身卡位使得每次做出N+1個printk，這樣最後輸出的release反而成為下一個的第一個
- 我們會將下面這個system call 家在所有policy的最後一行
![](https://i.imgur.com/mk0OK3b.png)


而每個Policy大致相同，只有以下部分有所區別:
## a. First in, first served (FCFS)
![](https://i.imgur.com/4KCr5hb.png)
- 目標: 先進來的先跑
- 直接把pcb當作ready queue, 當process離開queue時，enable就設成FALSE(鎖門)
- enable設成TRUE(開門)的方式是使用signal handler來開鎖
## b. Round Robin (RR)
![](https://i.imgur.com/z9wUX9g.png)
- 上半部(continue之前): polling一輪去找下個ready的process。為了以防陷入無限迴圈，用invalid去紀錄有幾個現在不能跑(跑完or還沒ready)
- 下半部(continue之後) 每次能跑的上限時間是給定的time slice，跑完後計算尚需的時間。
- 整體: SIGFNS和SIGTERM都可以開鎖，但SIGFNS會去increase finish的數量。
## c. Shortest Job First (SJF)
![](https://i.imgur.com/VCC8kMU.png)
- 用一個heap來maintain processes，heap的最上面都是run time最小的(runtime一樣的話就看誰先來)
- 只要ready time到了可以就insert到heap裡，每次開鎖時就extract一個去跑。
## d. Preemptive Shortest Job First (PSJF)
![](https://i.imgur.com/VKhrWHW.png)
- 上半部 (while-loop): 跟SJF一樣，用一個heap去排ready的processes.
- 下半部 (大if裡面): 當enable且heap不為空時，就從頂端拿一個來跑一段時間(time slice 與 run time較小的那個):
1.	跑完了 => do nothing
2.	還沒跑完，heap有人 => 把自己放到yet，下一個extract後再把自己insert進去
3.	還沒跑完，heap沒人 => 沒人也要跑那就可以繼續跑

# 3. Comparison
每一筆測資都有.txt, stdout.txt 和 dmesg.txt (如下圖由左到右為TIME_MEASUREMENT的這三筆資料)
![](https://i.imgur.com/5KQpPJ4.png)

由於為了節省空間，下方的每個比較將使用以下這個我自己寫的table以方便比較，如:
![](https://i.imgur.com/M5q8d02.png)
(其中time interval為end time - start time)
## TIME_MEASUREMENT
![](https://i.imgur.com/uWr26cL.png)
平均500個unit time是 0.14776906967163086 s = 147769069.67163086 ns
因此之後我們考慮一個unit time = **295538.1393432617 ns** 

![](https://i.imgur.com/9ZX0Vd9.png)

## a. First in, first served (FCFS)
- FIFO_1.txt
 ![](https://i.imgur.com/zLjIFfS.png)
     - 理論值(Unit time): 500 500 500 500 500
     - 實際值(Unit time): 574 466 470 508 446

- FIFO_2.txt
![](https://i.imgur.com/cT1tuew.png)
    - 理論值(Unit time): 80000 5000 1000 1000
     - 實際值(Unit time): 72019 4470 907 974
- FIFO_3.txt
![](https://i.imgur.com/DEyz2dR.png)
    - 理論值(Unit time): 8000 5000 3000 1000 1000 1000 4000
     - 實際值(Unit time): 7352 4691  2765 911 928 908 3660
- FIFO_4.txt
![](https://i.imgur.com/Tv5TCsf.png)
    - 理論值(Unit time): 2000 500 200 500
     - 實際值(Unit time): 1820 463 194 447
- FIFO_5.txt
![](https://i.imgur.com/1Ew9sO8.png)
    - 理論值(Unit time): 8000 5000 3000 1000 1000 1000 4000
     - 實際值(Unit time): 7241 4529 2696 894 909 893 3572
## b. Round Robin (RR)
- RR_1.txt
![](https://i.imgur.com/9yK1SAn.png)

- RR_2.txt
![](https://i.imgur.com/LPyvPsa.png)

- RR_3.txt
![](https://i.imgur.com/mfDwy3Q.png)

- RR_4.txt
![](https://i.imgur.com/Rjs4TPa.png)

- RR_5.txt
![](https://i.imgur.com/NNfi8Vj.png)


## c. Shortest Job First (SJF)
- SJF_1.txt
![](https://i.imgur.com/M3bb2nT.png)

- SJF_2.txt
![](https://i.imgur.com/kjhQYFG.png)

- SJF_3.txt
![](https://i.imgur.com/OzwpQV5.png)

- SJF_4.txt
![](https://i.imgur.com/GEwZpBz.png)

- SJF_5.txt
![](https://i.imgur.com/nDw7IFc.png)

## d. Preemptive Shortest Job First (PSJF)
- PSJF_1.txt
![](https://i.imgur.com/3gLCJHs.png)

- PSJF_2.txt
![](https://i.imgur.com/OqKv3Ok.png)

- PSJF_3.txt
![](https://i.imgur.com/EVVvYaQ.png)

- PSJF_4.txt
![](https://i.imgur.com/IR6dlaf.png)

- PSJF_5.txt
![](https://i.imgur.com/3ofXOGw.png)

# 4. Conclusion
- Q1. 為什麼各個結果所耗費的unit time會比理論值小?
    - A1.1 可能因為當初生成的unit time比理論上還大一些
    - A1.2 此外，排程器上的counter基本上無法和child process上的counter同步，scheduler 還要忙signal handle, system call, heap maintain 之類的是，當counter跑到一定時間後，這些差異就會很明顯了
- Q2. 為什麼生成的unit time會比理論值大?
    - A2.1 除了排程外，系統也同時在做別的事
    - A2.2 VM上仍無可避免有其他程式在運行，當他們跟我們的行程context switch時，也會產生許多overhead
    - A2.3 同時，CPU也在處裡I/O，這些interrupt會讓overhead更大
