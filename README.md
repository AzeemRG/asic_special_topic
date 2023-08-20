# ASIC CLASS (VLSI Physical Design for ASICs)
This repo helps to understand asic flow 
Guide : Kunal Gosh

#Installation of Riscv tool chain 
...
To install the RISC-V toolchain on Ubuntu, follow these steps (read about these steps before running):
1. Install Prerequisites:
Before you can build the RISC-V toolchain, you'll need to install some software dependencies:
sudo apt update
sudo apt install autoconf automake autotools-dev curl python3 libmpc-dev libmpfr-dev libgmp-dev gawk build-essential bison flex texinfo gperf libtool patchutils bc zlib1g-dev libexpat-dev git2. Clone the RISC-V GNU Toolchain Repository:
git clone --recursive https://github.com/riscv/riscv-gnu-toolchain3. Build and Install the Toolchain:
Navigate into the toolchain directory and initiate the build:
cd riscv-gnu-toolchain
./configure --prefix=/opt/riscv
make4. Update Your Path:
After installing, you'll want to add the toolchain binaries to your PATH:
echo 'export PATH=$PATH:/opt/riscv/bin' >> ~/.bashrc
source ~/.bashrc5. Test the Installation:
Check the version of the GCC compiler:
riscv64-unknown-elf-gcc --versionThis should output details about the RISC-V GCC compiler, which means you have successfully installed the toolchain.
...

#Course
#Day 1
##
