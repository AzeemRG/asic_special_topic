# ASIC_CLASS (VLSI Physical Design for ASICs)
This repository will help to understnad asic flow
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
# DAY1
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



