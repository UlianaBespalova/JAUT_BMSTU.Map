# JAUT_BMSTU.Map
Проект по курсу Углубленное программирование на C/C++ (Mail.ru Group) 


## Installation (linux/ubuntu)

0. Prepare
   ```bash
   sudo apt-get update && sudo apt-get -y upgrade
   ```

1. `C++` & `Cmake`
   ```bash
   sudo apt install g++ gdb cmake
   ```

2. `Qt5`
   ```bash
   sudo apt-get install qt5-default
   ```
3. `Boost`
   ```bash
   sudo apt-get install libboost-all-de
   ```
4. [`GTest`](https://github.com/google/googletest/blob/main/googletest/README.md)
   ```bash
   cd ~
   git clone https://github.com/google/googletest.git -b release-1.11.0
   cd googletest        # Main directory of the cloned repository.
   mkdir build          # Create a directory to hold the build output.
   cd build
   cmake ..             # Generate native build scripts for GoogleTest.
   make
   sudo make install    # Install in /usr/local/ by default
   ```

Full:
```bash
sudo apt-get update && sudo apt-get -y upgrade   # updates
sudo apt install g++ gdb cmake                   # c++ & cmake
sudo apt-get install qt5-default                 # Qt5
sudo apt-get install libboost-all-de             # boost

# gtest
cd ~
git clone https://github.com/google/googletest.git -b release-1.11.0
cd googletest        # Main directory of the cloned repository.
mkdir build          # Create a directory to hold the build output.
cd build
cmake ..             # Generate native build scripts for GoogleTest.
make
sudo make install    # Install in /usr/local/ by default
```