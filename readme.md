# Memory Allocation
## A project made by students of Shubra Faculty of Engineering
### the project aims to simulate the difference between multiple memory allocation algorithms (ie. Best Fit, First Fit, & Worst Fit)

## Installation
1. Make sure to use Linux Based OS
1. Install gcc
2. install json-c using ``` sudo apt install libjson-c-dev ```
3. run ```make all``` to complie and link o files
4. run ```memory_management -f "process.json" -bf ```  

## Arguments
| Argument | Description                                                    |
| -------- | -------------------------------------------------------------- |
| -f       | path to json file that describes the sequence of the processes |
| -bf      | best fit algorithm                                             |
| -ff      | first fit algorithm                                            |
| -wf      | worst fit algoritm                                             |
|          |                                                                |

**You can only use one of the algoritm**


## Process File Description
- The sequence of processes should be under **processes** field
- There're two types of object inside **processes** array

## Process Type
### 1. allocate
| Field | Description                                         |
| ----- | --------------------------------------------------- |
| name  | the unique name of new allocated memory             |
| size  | the size of new allocated memory inside the process |
|       |                                                     |
###  2. free
| Field | Description                                 |
| ----- | ------------------------------------------- |
| name  | the unqiue name of already allocated memory |
|       |                                             |

**name field should be unqiue for each proccess**
    