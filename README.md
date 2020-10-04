
# Scheduling Algorithm

- Uncomment each scheduler block to test out each Scheduler Algorithm
- FCFS has a design flaw, while inserting a Process in ProcessBuffer, you have to specify twice, the Arrival time of Process. first arg and the other when creating new Process.
- Process ctor has following args ( PID, Process Name, Arrival Time, Expected BT, Priority = 1 _default_)
- Each scheduler has args of 'number of Processes' and other options to enable preemptive nature, if any.
- Before running a Scheduler, fill the ProcessBuffer, it is an hypothetical collection of Process arriving at different time.

## Dependancy of Classes and Objetcs

<table>
<tr>
<td  colspan="4" align="center"> Main.out </td>
</tr>
<tr>
<td> FCSF.hpp </td>
<td> RROBIN.hpp </td>
<td> SJF.hpp </td>
<td> PRIOR.hpp </td>
</tr>
<tr>
<td> Q.hpp </td>
<td> Q.hpp </td>
<td> shPQ.hpp </td>
<td> shPQ.hpp </td>
</tr>
<tr>
<td> Process.hpp </td>
<td> Process.hpp </td>
<td> Process.hpp </td>
<td> Process.hpp </td>
</tr>
</table>

## Compiling Instructions

<code>g++ -std=c++17 FCFS.cpp RROBIN.cpp SJF.cpp PRIOR.cpp Q.cpp shPQ.cpp Process.cpp main.cpp -o main</code>
