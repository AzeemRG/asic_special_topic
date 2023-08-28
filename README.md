# ASIC_CLASS (VLSI Physical Design for ASICs)
This repository will help to understand asic flow
(GUIDE : Kunal Ghosh)

# Introduction to Course 

## Risc-V Architecture 

RISC-V is an open-source instruction set architecture (ISA) designed to be highly flexible, extensible, 
and customizable.
An instruction set architecture defines the set of instructions that a computer processor can execute,
along with the format of those instructions and the underlying hardware organization.

## Application to Hardware

High Level Language (C,Python etc) ---> Compiler ---> Instruction Set Architecture ---> Assembler --- > Hardware 
Instruction Set Architecture(ISA) is were our course concentrates , ISA depends on Hardware , Eg : A risc-v hardware will have risc-v isa , An intel x86 hardware will support x86 ISA 
So complier gives .exe (executable file) to Assembler which further generates the binary form which is given to hardware 

# Software requirements 
Ubuntu 20+

RAM = 6gb

Disc Space= 200gb

# Installation
1. Install Prerequisites:
```
sudo apt update
sudo apt install autoconf automake autotools-dev curl python3 libmpc-dev libmpfr-dev libgmp-dev gawk build-essential bison flex texinfo gperf libtool patchutils bc zlib1g-dev libexpat-dev git

```
2. Clone the RISC-V GNU Toolchain Repository:
```
git clone --recursive https://github.com/riscv/riscv-gnu-toolchain

```
3. Build and Install the Toolchain:
```
cd riscv-gnu-toolchain
./configure --prefix=/opt/riscv
make

```
4. Update Your Path:
   
```

echo 'export PATH=$PATH:/opt/riscv/bin' >> ~/.bashrc
source ~/.bashrc

```
5. Test the Installation:
   
```
riscv64-unknown-elf-gcc --version

```

# Course

<details>
<summary> # DAY 1: Introduction to RISCV ISA and GNU Compiler Toolchain</summary>
<br>
	
## Create a simple C code that counts sum of number from 1 to n 

```
#include<stdio.h>

int main(){
	int i, sum=0, n=26;
	for (i=1;i<=n; ++i) {
	sum +=i;
	}
	printf("Sum of numbers from 1 to %d is %d \n",n,sum);
	return 0;
}

```

### Using RiscV complier 
use command ``` riscv64-unknown-elf-gcc -O1 -mabi=lp64 -march=rv64i -o sumton.o sumton.c ```

![image](https://github.com/AzeemRG/asic_special_topic/assets/128957056/3a15f6fe-f7fb-46f0-962d-d4b3634f5978)

To get assembly code use command ``` riscv64-unknown-elf-objdump -d sumton.o | less```

as we are intrested in <main> type ```/main``` and hit enter 

![image](https://github.com/AzeemRG/asic_special_topic/assets/128957056/30197178-00f1-4f8c-915d-6400a235f868)

Here we can see number of intrustruction used with "-O1" optimization 

Now lets try with ```-Ofast``` optimization 

![image](https://github.com/AzeemRG/asic_special_topic/assets/128957056/7f436102-0f93-4b9a-80ff-38b540d7f659)

We can see number of instructions are reduced

![image](https://github.com/AzeemRG/asic_special_topic/assets/128957056/c4344940-0cc6-48ae-b8a5-572f38792582)

### Spike Simulation & Debugging
Spike simulates the execution of RISC-V instructions on a virtual processor, allowing developers to run and analyze RISC-V programs without the need for physical hardware. This simulator accurately models the behavior of a RISC-V processor according to the RISC-V Instruction Set Architecture (ISA) specifications

``` spike pk sumton.o```

![image](https://github.com/AzeemRG/asic_special_topic/assets/128957056/2b6c6ba7-0e0c-4983-9dea-2083a48692ec)


for debugging we use ``` spike -d pk sum1ton.c ```

![image](https://github.com/AzeemRG/asic_special_topic/assets/128957056/43d1db63-7342-4633-a72a-9f4e353481b4)






# Integer Number Representation
## Unsigned numbers 

Unsigned numbers play a crucial role in the RISC-V Instruction Set Architecture (ISA). In RISC-V, unsigned numbers are non-negative integers represented in binary format. They are fundamental for various arithmetic and logical operations, providing a foundation for tasks like data manipulation, memory addressing, and comparisons within the processor.

They range from  0 to 2^(N) - 1.

## Signed numbers 

They represent both positive and neagtive numbers including zero.

They range from (2^(N-1)) to 2^(N-1) - 1.


### 64-bit Number system of Unsigned Numbers

```
#include <stdio.h>
#include <math.h>

int main(){
	unsigned long long int max = (unsigned long long int) (pow(2,64) -1);
	unsigned long long int min = (unsigned long long int) (pow(2,64) *(-1));
	printf("lowest number represented by unsigned 64-bit integer is %llu\n",min);
	printf("highest number represented by unsigned 64-bit integer is %llu\n",max);
	return 0;
}
```

![image](https://github.com/AzeemRG/asic_special_topic/assets/128957056/6a021bb7-bac2-4629-80d7-c32babe93ffd)


### 64-bit Number system of Signed Numbers

```
#include <stdio.h>
#include <math.h>

int main(){
	long long int max = (long long int) (pow(2,63) -1);
	long long int min = (long long int) (pow(2,63) *(-1));
	printf("lowest number represented by signed 64-bit integer is %lld\n",min);
	printf("highest number represented by signed 64-bit integer is %lld\n",max);
	return 0;
}
```

![image](https://github.com/AzeemRG/asic_special_topic/assets/128957056/0129a96b-01d3-4e56-82d3-38425f1237c8)




</details>
<details>
<summary> # DAY 2 : Introduction to ABI and Basic Verification Flow </summary>
<br>
	
# Application Binary Interface (ABI)
## Introduction

The Application Binary Interface (ABI) serves as a bridge between software and hardware in a computer system. It defines the conventions and interfaces that enable compatibility between different software components, such as compilers, libraries, and operating systems, running on the same hardware architecture

In the context of an Instruction Set Architecture (ISA), an ABI establishes rules for function calling conventions, parameter passing, register usage, and memory layout. This standardized interface ensures seamless interaction between software layers and hardware, fostering portability and interoperability across diverse software ecosystems on a given ISA.

## Memory Allocation

Memory allocation is the process of reserving and assigning segments of a computer's memory space for various data structures and program components, enabling efficient storage and retrieval of information during program execution.

### Little Endian 

   In little-endian representation, you store the least significant byte (LSB) at the lowest memory address and the most significant byte (MSB) at the highest memory address.

   For example : 
   ```
    Decimal Value: 1311768467463790320 (0x123456789ABCDEF0 in hexadecimal)

    Little-Endian Representation (in bytes): 0xF0 0xDE 0xBC 0x9A 0x78 0x56 0x34 0x12

   ```

### Big Endian 

 In big-endian representation, you store the most significant byte (MSB) at the lowest memory address and the least significant byte (LSB) at the highest memory address.

 For example :
  ```
   Decimal Value: 1311768467463790320 (0x123456789ABCDEF0 in hexadecimal)

   Big-Endian Representation (in bytes): 0x12 0x34 0x56 0x78 0x9A 0xBC 0xDE 0xF0

```

# LOAD , ADD , STORE instruction
## Introduction 

LOAD instruction retrieves data from memory, transferring it to a register in a computer's architecture, enabling data access for computation. 
ADD instruction performs arithmetic addition on values within registers, contributing to mathematical and logical operations.
STORE instruction writes data from a register to memory, facilitating the storage of computed results or values for later use in a program.

Example for LOAD:
```
LW R1, 16(R2)
This RISC-V instruction loads a 32-bit word from memory at address R2 + 16 into register R1
```
Example for ADD:
```
ADD R3, R1, R2
The RISC-V ADD instruction adds the values in registers R1 and R2, storing the result in register R3.
```
Example for STORE:
```
SW R5, 8(R4)
This RISC-V instruction stores the value from register R5 into memory at address R4 + 8.
```

# 32-bit registers (RISC-V ISA)

![image](https://github.com/AzeemRG/asic_special_topic/assets/128957056/70ab0325-f800-4f93-818a-dd100a3100d7)

# ABI Names

Application Binary Interface (ABI) names refer to standardized conventions used to define the interface between different software components, such as compilers, libraries, and operating systems, within a given architecture. These names provide a consistent way to represent data types, function calling conventions, register usage, and more, ensuring compatibility and seamless communication across diverse software layers. ABI names play a vital role in enabling portability and interoperability in software development for specific hardware architectures like x86, ARM, or RISC-V.


![image](https://github.com/AzeemRG/asic_special_topic/assets/128957056/d29e6e30-c14a-4d13-8ad5-9f9fdc8bc94a)


# LAB for ABI function calls
## C programm using ABI function call 

create one .c and assembly file (.s)

![image](https://github.com/AzeemRG/asic_special_topic/assets/128957056/8ec712f4-da76-4761-9e01-218443667ab5)

Now use command  
``` riscv64-unknown-elf-gcc -O1 -mabi=lp64 -march=rv64i -o sum1to20.o sum1to20.c load.s ```
``` spike pk sum1to20.o ```
``` riscv64-unknown-elf-objdump -d sum1to20.o | less ```


![image](https://github.com/AzeemRG/asic_special_topic/assets/128957056/855bcd13-709b-43f0-b270-e567e7ec5d8b)

![image](https://github.com/AzeemRG/asic_special_topic/assets/128957056/27af99aa-30c0-4851-96ea-2a0371564320)




</details>
<details>
<summary> # DAY 3 : Introduction to Verilog RTL Design and Synthesis </summary>
<br>

# Introduction to Yosys and Logic Synthesis

![image](https://github.com/AzeemRG/asic_special_topic/assets/128957056/99a7c6bd-4f6c-4a3b-8935-29bba023f633)

## Yosys : Introduction and more

 ![image](https://github.com/AzeemRG/asic_special_topic/assets/128957056/5e98785c-db52-4e1e-a508-54e910c1e634)

  Yosys is a opensource framework for verilog RTL synthesis. Yosys helps convert the higher-level hardware description in a language like Verilog into a lower-level netlist representation that can be used for 
    further steps of RTL to netlist flow.

  ![image](https://github.com/AzeemRG/asic_special_topic/assets/128957056/b632ed60-2523-42e2-ab5d-72c540c3f67a)

 ##### Netlist : A netlist is a structural representation of a digital circuit, comprising interconnected gates, flip-flops, and other logic elements.
 ##### Synthesis : Synthesis is the process of transforming a high-level hardware description into a lower-level representation suitable for implementation in hardware.
 ##### RTL : (Register Transfer Level) is a hardware description abstraction capturing digital circuit behavior through sequential logic elements and data transfers between registers.
 ##### Syntthesizer :  Synthesizer is the tool that we use for converting the RTL to netlist
 ##### .lib : Collection of various Logical Modules

![image](https://github.com/AzeemRG/asic_special_topic/assets/128957056/b1648cde-bf15-4934-b385-23ff816c4792)

 Setup Time: The minimum time a data input must be stable before the clock edge, ensuring it's properly captured by a flip-flop.

 Hold Time: The minimum time a data input must remain stable after the clock edge, maintaining its validity for proper flip-flop operation.

 # Lab Work for Day 3 



 </details>
<details>
<summary> # DAY 4 : Timing libs,Heirarchial vs Flat Synthesis </summary>
<br>


 

 


   









