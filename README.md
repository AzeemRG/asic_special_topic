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
<summary># DAY 1: Introduction to RISCV ISA and GNU Compiler Toolchain</summary>
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

 Enable administrative mode using command ``` sudo -i ```

 Go to verilog_files and invoke yosys 

 ![image](https://github.com/AzeemRG/asic_special_topic/assets/128957056/397a02ee-acdb-4681-a004-c01cea50baf8)

 Read Library using command ``` read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib ```
 
 Read Design using command ``` read_verilog good_mux.v ```
 
 Go to synthesis step using command ``` synth -top good_mux ```

 good_mux.v 
 ```
module good_mux (input i0 , input i1 , input sel , output reg y);
always @ (*)
begin
	if(sel)
		y <= i1;
	else 
		y <= i0;
end
endmodule

```

 ![image](https://github.com/AzeemRG/asic_special_topic/assets/128957056/9d09fc3c-78dd-473a-9835-acd761827568)

 After complition of synthesis we will go for genrating netlist. 

 We will generate netlist using ABC tool which is present in yosys itself.
 
 Use command ``` abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib ```

 ![image](https://github.com/AzeemRG/asic_special_topic/assets/128957056/8554f392-e149-4d6f-bafa-0302caebcbc0)

To see the logic level design use command ```show ```

![image](https://github.com/AzeemRG/asic_special_topic/assets/128957056/8c5d8eed-36d1-4f96-b232-1d056c889641) 

Here is the Logc level RTL of good_mux

![image](https://github.com/AzeemRG/asic_special_topic/assets/128957056/aab789c4-bbc1-4126-8bcd-26aaac536bc5)

To see or change the netlist 

use command ``` write_verilog good_mux_netlist.v ``` and ``` !gedit good_mux_netlist.v ```

![image](https://github.com/AzeemRG/asic_special_topic/assets/128957056/75e4bf12-030a-4471-8c65-e3cdd47d4312)

Here is the netlist for the mux example used

![image](https://github.com/AzeemRG/asic_special_topic/assets/128957056/30160938-3252-44d3-8225-bcbd7384be42)

To simplify the netlist use command ``` write_verilog -noattr good_mux_net.v ``` 

![image](https://github.com/AzeemRG/asic_special_topic/assets/128957056/8d7db4ab-f826-4eba-b757-5fa9780cf1f8)

Here is the simpligied netlist

![image](https://github.com/AzeemRG/asic_special_topic/assets/128957056/0ae46adb-8f16-4ba3-9c0c-5ae050b82e5a)



 </details>
<details>
<summary> # DAY 4 : Timing libs,Heirarchial vs Flat Synthesis </summary>
<br>

# Introduction to .lib files 

 1. Definition and Purpose:
	A .lib file is a text-based file that contains information about various digital standard cells, their electrical characteristics, timing behavior, power consumption, and other important parameters. These cells are the fundamental 		building blocks of digital logic circuits. The purpose of a .lib file is to provide a comprehensive database of standard cell information that designers can use during different stages of the design process.

 2. Contents of a .lib File:
    A typical .lib file includes the following types of information:

    Cell Definitions: Each standard cell is defined with its logical functionality, pin connections, and layout information.
    
    Timing Information: This includes delay models, rise and fall times, input and output capacitances, and propagation delays for different input and output conditions.
    
    Power Characteristics: Information about power consumption, such as static power (leakage power) and dynamic power consumption for different input patterns and switching frequencies
    .
    Voltage and Temperature Dependencies: Timing and power characteristics can vary with supply voltage and temperature, so .lib files often provide models for different operating conditions.
    
    Constraints and Guidelines: Some .lib files include guidelines for using certain cells, such as recommended usage scenarios and design considerations.

 # sky130_fd_sc_hd__tt_025C_1v80.lib 

   The name "sky130_fd_sc_hd__tt_025C_1v80.lib" is the library we will use to access the examples like good_mux wtc

    sky130: Refers to the SkyWater 130nm process technology.
    
    fd: Stands for "foundry default," indicating that it's a default library for the process.
    
    sc: Likely denotes "standard cell," which are the basic building blocks of digital logic.
    
    hd: Possibly stands for "high-density," indicating a library optimized for high-density designs.
    
    tt_025C: Likely specifies the temperature at which the library's timing characteristics are characterized (in this case, 25°C).
    
    1v80: Indicates the nominal supply voltage of 1.8V.

 # Hirarchial vs Flat Synthesis 

   Hierarchical Synthesis:
    Hierarchical synthesis involves breaking down a complex design into smaller, more manageable modules or hierarchies. Each module represents a functional block of the design, and these modules can be further divided into sub-modules.         The design hierarchy often mirrors the logical and functional structure of the system being designed.

   Flat Synthesis : 
      Flat synthesis involves synthesizing the entire design as a single, monolithic entity without breaking it into smaller hierarchical modules. In a flat design, all logic is synthesized together, 
      regardless of its functional separation.

  Choosing Between Hierarchical and Flat Synthesis:

  The choice between hierarchical and flat synthesis depends on the complexity of the design, the design team's familiarity with the approach, and the tools being used. Generally:

    Hierarchical Synthesis: This approach is favored for larger designs with clear functional divisions and for designs that are expected to be reused or maintained over time.

    Flat Synthesis: This approach can be useful for smaller designs, designs with highly interconnected logic, or situations where global optimizations are crucial

  # Here are the two examples of files that shows difference between flat and Heirarchial

   Use the above commands used in Day 3 to open the files using yosys interface

  Heirarchial : multiple_modules_hier.v

  ```
    /* Generated by Yosys 0.32+51 (git sha1 6405bbab1, gcc 12.3.0-1ubuntu1~22.04 -fPIC -Os) */

module multiple_modules(a, b, c, y);
  input a;
  wire a;
  input b;
  wire b;
  input c;
  wire c;
  wire net1;
  output y;
  wire y;
  sub_module1 u1 (
    .a(a),
    .b(b),
    .y(net1)
  );
  sub_module2 u2 (
    .a(net1),
    .b(c),
    .y(y)
  );
endmodule

module sub_module1(a, b, y);
  wire _0_;
  wire _1_;
  wire _2_;
  input a;
  wire a;
  input b;
  wire b;
  output y;
  wire y;
  sky130_fd_sc_hd__and2_0 _3_ (
    .A(_1_),
    .B(_0_),
    .X(_2_)
  );
  assign _1_ = b;
  assign _0_ = a;
  assign y = _2_;
endmodule

module sub_module2(a, b, y);
  wire _0_;
  wire _1_;
  wire _2_;
  input a;
  wire a;
  input b;
  wire b;
  output y;
  wire y;
  sky130_fd_sc_hd__or2_0 _3_ (
    .A(_1_),
    .B(_0_),
    .X(_2_)
  );
  assign _1_ = b;
  assign _0_ = a;
  assign y = _2_;
endmodule

```

Here is the Logical Level RTL

![image](https://github.com/AzeemRG/asic_special_topic/assets/128957056/a864da86-6d6d-477c-8a2b-c16eb6961e24)

Flat : multiple_modules_flat.v

``` 
  /* Generated by Yosys 0.32+51 (git sha1 6405bbab1, gcc 12.3.0-1ubuntu1~22.04 -fPIC -Os) */

module multiple_modules(a, b, c, y);
  wire _0_;
  wire _1_;
  wire _2_;
  wire _3_;
  wire _4_;
  wire _5_;
  input a;
  wire a;
  input b;
  wire b;
  input c;
  wire c;
  wire net1;
  wire \u1.a ;
  wire \u1.b ;
  wire \u1.y ;
  wire \u2.a ;
  wire \u2.b ;
  wire \u2.y ;
  output y;
  wire y;
  sky130_fd_sc_hd__and2_0 _6_ (
    .A(_1_),
    .B(_0_),
    .X(_2_)
  );
  sky130_fd_sc_hd__or2_0 _7_ (
    .A(_4_),
    .B(_3_),
    .X(_5_)
  );
  assign _4_ = \u2.b ;
  assign _3_ = \u2.a ;
  assign \u2.y  = _5_;
  assign \u2.a  = net1;
  assign \u2.b  = c;
  assign y = \u2.y ;
  assign _1_ = \u1.b ;
  assign _0_ = \u1.a ;
  assign \u1.y  = _2_;
  assign \u1.a  = a;
  assign \u1.b  = b;
  assign net1 = \u1.y ;
endmodule
```

Here is the Logic Level RTL 

![image](https://github.com/AzeemRG/asic_special_topic/assets/128957056/0f53ea8e-17bf-446b-81c8-12323b4b5f4c)


# Flop-Coding Styles , Syhnthesis and Optimisations 

Flip-flops, often referred to as flops.

Here are some usage of flip flops

Memory Elements:
Flip-flops provide memory elements that can store binary values (0 or 1) over time. This ability to retain information is fundamental to building sequential logic circuits like registers and memory.

Clock Synchronization:
Flip-flops are often triggered by clock signals, allowing them to synchronize with the clock's rising or falling edges. This synchronization is vital for managing the timing and sequencing of operations within a digital system.

Sequential Logic:
Digital systems often require the ability to respond to previous inputs or states. Flip-flops enable the creation of sequential logic circuits, where the current state depends on both the current inputs and the previous states.

State Machines:
Sequential circuits built using flip-flops can implement state machines, which are used to model systems that have different operational modes and respond differently based on their current state and inputs.

Counters and Registers:
Flip-flops are the building blocks of counters and registers. Counters are used for tasks like generating clock dividers, frequency dividers, and timing events. Registers are used for temporary data storage, data manipulation, and data transfer between different parts of a circuit.

Now here are the examples of different styles.

1. DFF with Asynchronous Reset : 

     This type of DFF includes an asynchronous reset input. The primary purpose of the asynchronous reset is to allow you to immediately clear the stored value of the flip-flop to a known state (usually '0') regardless of the clock signal.
       When the reset input is asserted, the flip-flop's output is cleared, and this happens asynchronously, meaning it's not dependent on the clock signal.

  Here are the example of file from same .lib
    dff_asyncres_syncres.v
```
module dff_asyncres_syncres ( input clk , input async_reset , input sync_reset , input d , output reg q );
always @ (posedge clk , posedge async_reset)
begin
	if(async_reset)
		q <= 1'b0;
	else if (sync_reset)
		q <= 1'b0;
	else	
		q <= d;
end
endmodule
```

     
3. DFF with Aynchronous Set : 

     Similar to the DFF with asynchronous reset, a DFF with asynchronous set includes an asynchronous set input. When the set input is asserted, the flip-flop's output is immediately set to a high state (usually '1') regardless of the clock
       signal. The asynchronous set also operates independently of the clock signal and can be useful for initializing registers to a known state when certain conditions are met.

     dff_async_set.v
```
module dff_async_set ( input clk ,  input async_set , input d , output reg q );
always @ (posedge clk , posedge async_set)
begin
	if(async_set)
		q <= 1'b1;
	else	
		q <= d;
end
endmodule
```

5. DFF with Synchronous Reset:

      In this style of DFF, the reset input is synchronous, meaning the flip-flop responds to the reset signal only when a clock edge occurs. The stored value is cleared to a known state when the reset input is asserted and a clock edge
            occurs simultaneously. This ensures that the reset operation is synchronized with the clock signal, which helps avoid potential glitches and timing issues.

   dff_syncres.v
```
module dff_syncres ( input clk , input async_reset , input sync_reset , input d , output reg q );
always @ (posedge clk )
begin
	if (sync_reset)
		q <= 1'b0;
	else	
		q <= d;
end
endmodule
```

7. DFF with Asynchronous Reset and Synchronous Reset : 
        
      This style combines both asynchronous and synchronous reset behaviors. The flip-flop has both an asynchronous reset input and a synchronous reset input. The asynchronous reset clears the flip-flop's output asynchronously, similar to
         the first style. The synchronous reset, on the other hand, clears the output to a known state only when a clock edge occurs simultaneously with the reset input being asserted. This provides the benefits of both asynchronous and
          synchronous reset mechanisms.

   dff_asyncres_syncres.v
```
module dff_asyncres_syncres ( input clk , input async_reset , input sync_reset , input d , output reg q );
always @ (posedge clk , posedge async_reset)
begin
	if(async_reset)
		q <= 1'b0;
	else if (sync_reset)
		q <= 1'b0;
	else	
		q <= d;
end
endmodule
```

# Flop Synthesis , Simulation and Optimization

 1. D Flip-Flop with Asynchronous Reset
    For Simulation follow the commands
    ```
       
    cd VLSI/sky130RTLDesignAndSynthesisWorkshop/verilog_files
    iverilog dff_asyncres.v tb_dff_asyncres.v
    ./a.out
    gtkwave tb_dff_asyncres.vcd
    
    ```
   After simulation u will get a Waveform that shows the asynchronus behaviour 
    
![image](https://github.com/AzeemRG/asic_special_topic/assets/128957056/5be49254-5ff9-49cd-be98-69519f5a3eb7)

   To see the Logic Level RTL use these commands
   ``` 

cd vsd/sky130RTLDesignAndSynthesisWorkshop/verilog_files

yosys

read_liberty -lib ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

read_verilog dff_asyncres.v

synth -top dff_asyncres

dfflibmap -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

abc -liberty ../lib/sky130_fd_sc_hd__tt_025C_1v80.lib

show
```


  ![image](https://github.com/AzeemRG/asic_special_topic/assets/128957056/7032b02e-465b-4bc1-901e-f70ff9f86f6f)

Now do same for remaining three styles 

2. D Flip_Flop with Asynchronous Set 

  ![image](https://github.com/AzeemRG/asic_special_topic/assets/128957056/446cd2a0-d0b5-4d9c-84cb-7a0e213d8b68)

  ![image](https://github.com/AzeemRG/asic_special_topic/assets/128957056/219ad96b-7c34-4582-9646-5805c00df4c1)

3. D Flip-Flop with Synchronous Reset

   ![image](https://github.com/AzeemRG/asic_special_topic/assets/128957056/fe945fb0-f7fa-4c2f-aee6-c2f6bf5d93dc)


  ![image](https://github.com/AzeemRG/asic_special_topic/assets/128957056/1c0c7a11-df39-4c86-b9cc-3da0ca7b7ada)

### Optimizations

This is another example of multiplication file 

![image](https://github.com/AzeemRG/asic_special_topic/assets/128957056/c6a1fed2-aa33-4eef-9eb4-7bc8106cd682)

Invoke yosys from verilog_files directory as done earlier 

run synthesis and check for info as done earlier

![image](https://github.com/AzeemRG/asic_special_topic/assets/128957056/ed768908-5b9c-4e88-a47c-59a8ba6295a6)

Here is the Logic Level Diagram 

![image](https://github.com/AzeemRG/asic_special_topic/assets/128957056/db4b84a3-287e-4d0f-a1d8-95413a924a60)

Here is the generated netlist which is optimized 

![image](https://github.com/AzeemRG/asic_special_topic/assets/128957056/3147848f-7611-4b77-bdc8-316d6d28213c)

Similarly for other example 

![image](https://github.com/AzeemRG/asic_special_topic/assets/128957056/73bf2ba7-5b00-4c5e-8f47-ce7d2bfe552c)


![image](https://github.com/AzeemRG/asic_special_topic/assets/128957056/8a2e6ae3-fde7-43b8-bb36-e18dc5dcb4c1)

![image](https://github.com/AzeemRG/asic_special_topic/assets/128957056/e57995ad-e992-4ce9-b781-8e41cd84d3a4)

   ![image](https://github.com/AzeemRG/asic_special_topic/assets/128957056/6bfe373e-d5dc-483d-a82b-576da5032b9c)





  



    





 

 


   









