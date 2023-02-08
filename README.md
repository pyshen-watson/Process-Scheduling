# Process-Scheduling

|⚠️WARNING|
|---|
|This public repository is just for my personal portfolio. The content is for the course: ***Operating System, Spring 2020, CSIE, NTU***. If you are taking this course right now, any form of referring or copying is ***not allowed***. Please finish your assignment by yourself.|

|Author|OS|Language|
|--|--|--|
|沈韋辰|Ubuntu 18.04LTS|C, ShellScript|

## Document
- [Problem](Project1.pdf) 
- [Report](report.pdf)
- [Demo Video](https://youtu.be/pQ2jtsm07M4)

## Usage
``` make init ``` - clean the old programs and data

``` make all ``` - compile all the code except system call

``` make syscall ``` - compile in the environment which has install these system call

## io_generator
 ```make all```  **Before use these script !**
* no install system call environment
  - ```./dev-time-measurement.sh ``` -run the base case

  - ```./dev-output.sh ``` -run all the 20 cases
* install system call environment
  - ```./vm-time-measurement.sh ``` -run the base case

  - ```./vm-output.sh ```-run all the 20 cases
