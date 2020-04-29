# OSproject1
OS midterm project for OS, CSIE, NTU

made by b07902078 沈韋辰 2020.4.30

# Usage
``` make init ``` - clean the old programs and data

``` make all ``` - compile all the code except system call

``` make syscall ``` - compile in the environment which has install these system call

# io_generator
 ```make all```  **Before use these script !**
* no install system call environment
  - ```./dev-time-measurement.sh ``` -run the base case

  - ```./dev-output.sh ``` -run all the 20 cases
* install system call environment
  - ```./vm-time-measurement.sh ``` -run the base case

  - ```./vm-output.sh ```-run all the 20 cases
