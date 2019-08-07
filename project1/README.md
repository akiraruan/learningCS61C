# Flights Simulator
[项目地址](https://cs61c.org/projects/proj1/)

***
### 测试结果

[akira@akira-pc project1]$ make run  
gcc  -c -Wall -g -std=c99 timeHM.c  
gcc  -c -Wall -g -std=c99 flights.c  
gcc  -c -Wall -g -std=c99 RouteTime.c  
gcc  -o RouteTime timeHM.o flights.o RouteTime.o  
./RouteTime integration_config  

** RUNNING NEW TEST **  
***Parse and echo airports***  
SJC  
SFO  

***Parse and echo schedules***  
Adding schedule for airport SJC  
SJC  
SFO 07:00 11:00 $230  
SFO 09:30 11:30 $230  
Adding schedule for airport SFO  
SFO  
SJC 05:00 07:30 $200  
SJC 04:30 06:00 $300  
SJC 10:00 13:00 $250  

***Parse and calculate route times***  
Route SIMPLE1 will be completed by 11:00 and costs $230  
Route SIMPLE2 will be completed by 11:00 and costs $530  
Route IMPOSSIBLE cannot be completed  
  
validateFlightPath test  
NULL check total cost -1  
ACTUAL check total cost 500  

***
### 踩过的坑
* 每个未初始化的指针用之前一定要初始化
* 指针不具备保存数据多少的能力，所以要设置一个变量，用来查看这个指针指向多少值
* 在栈中定义的指针将会在方法调用结束后销毁
* 一个malloc函数搭配一个free函数
