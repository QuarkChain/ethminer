# ethminer



> QuarkChain miner with OpenCL, CUDA and getWork support

**Ethminer** is an Ethash GPU mining worker.

I forked the Ethminer and modified the code, which can support the QuarkChain Testnet 2.0 Ethash mining. 
With this modified ethminer, you can mine the shards (0 ~ 3), which relies on an Ethash Proof of Work.
Noted that this version only support the getWork (Farm) mode. 
See [FAQ](#faq) for more details.

## Features

* OpenCL mining
* Nvidia CUDA mining
* realistic benchmarking against arbitrary epoch/DAG/blocknumber
* on-GPU DAG generation (no more DAG files on disk)
* OpenCL devices picking
* only support getWork mode



# Building from source

## Table of Contents

* [Requirements](#requirements)
    * [Common](#common)
    * [Linux](#linux)
        * [OpenCL support on Linux](#opencl-support-on-linux)
    * [macOS](#macos)
    * [Windows](#windows)
* [CMake configuration options](#cmake-configuration-options)
* [Instructions](#instructions)
    * [Windows-specific script](#windows-specific-script)


## Requirements

This project uses [CMake] package manager.

### Common

1. [CMake] >= 3.5
2. [Git](https://git-scm.com/downloads)
3. [Perl](https://www.perl.org/get.html), needed to build OpenSSL
4. [CUDA Toolkit](https://developer.nvidia.com/cuda-downloads) >= 9.0 (optional, install if you want NVidia CUDA support)

### Linux

1. GCC version >= 4.8
2. DBUS development libs if building with `-DETHDBUS`. E.g. on Ubuntu run:

```shell
sudo apt install libdbus-1-dev
```

#### OpenCL support on Linux

If you're planning to use [OpenCL on Linux](https://github.com/ruslo/hunter/wiki/pkg.opencl#pitfalls)
you have to install the OpenGL libraries. E.g. on Ubuntu run:

```shell
sudo apt-get install mesa-common-dev
```

### macOS

1. GCC version >= TBF

### Windows

1. [Visual Studio 2017](https://www.visualstudio.com/downloads/); Community Edition works fine. **Make sure you install MSVC 2015 toolkit (v140).**

## Instructions

1. Make sure git submodules are up to date:

    ```shell
    git submodule update --init --recursive
    ```

2. Create a build directory:

    ```shell
    mkdir build
    cd build
    ```

3. Configure the project with CMake. Check out the additional [configuration options](#cmake-configuration-options).

    ```shell
    cmake ..
    ```

    Note: On Windows, it's possible to have issues with VS 2017 default compilers; in that case, use the VS 2017 installer to get the VS 2015 compilers and use:

    ```shell
    cmake .. -G "Visual Studio 15 2017 Win64" -T v140
    ```

4. Build the project using [CMake Build Tool Mode]. This is a portable variant of `make`.

    ```shell
    cmake --build .
    ```

    Note: On Windows, it is possible to have compiler issues if you don't specify the build config. In that case use:

    ```shell
    cmake --build . --config Release
    ```

5. _(Optional, Linux only)_ Install the built executable:

    ```shell
    sudo make install
    ```

### Windows-specific script

Complete sample Windows batch file - **adapt it to your system**. Assumes that:

* it's placed one folder up from the ethminer source folder
* you have CMake installed
* you have Perl installed

```bat
@echo off
setlocal

rem add MSVC in PATH
call "%ProgramFiles(x86)%\Microsoft Visual Studio\2017\Community\Common7\Tools\VsMSBuildCmd.bat"

rem add Perl in PATH; it's needed for OpenSSL build
set "PERL_PATH=C:\Perl\perl\bin"
set "PATH=%PERL_PATH%;%PATH%"

rem switch to ethminer's source folder
cd "%~dp0\ethminer\"

if not exist "build\" mkdir "build\"

cmake -G "Visual Studio 15 2017 Win64" -H. -Bbuild -T v140 -DETHASHCL=ON -DETHASHCUDA=ON -DAPICORE=ON ..
cmake --build . --config Release --target package

endlocal
pause
```

## CMake configuration options

Pass these options to CMake configuration command, e.g.

```shell
cmake .. -DETHASHCUDA=ON -DETHASHCL=OFF
```

* `-DETHASHCL=ON` - enable OpenCL mining, `ON` by default.
* `-DETHASHCUDA=ON` - enable CUDA mining, `ON` by default.
* `-DAPICORE=ON` - enable API Server, `ON` by default.
* `-DETHDBUS=ON` - enable D-Bus support, `OFF` by default.
* `-DBINKERN=ON` - install AMD binary kernels, `ON` by default.






## Usage

The **ethminer** is a command line program. This means you launch it either
from a Windows command prompt or Linux console, or create shortcuts to
predefined command lines using a Linux Bash script or Windows batch/cmd file.
For a full list of available command, please run:

```sh
ethminer --help
```



# Run a cluster

I highly recommend you can use a multi-core CPU computer to [run a QuarkChain full cluster](https://github.com/QuarkChain/pyquarkchain/wiki/Run-a-Private-Cluster-on-the-QuarkChain-Testnet-2.0). 

## Port Forwarding

If you use an extra computer to run a QuarkChain cluster, you need to open TCP for port 38391 for the GPU miners.
Please follow the guidance of [Port Forwarding](https://github.com/QuarkChain/pyquarkchain/wiki/Private-Network-Setting%2C-Port-Forwarding).


# Examples connecting to QuarkChain cluster

After you build from source, run the follow command line to start GPU mining for QuarkChain.

```shell
cd ethminer/build/ethminer
```
    
If you use the CUDA GPU, please use,
```shell
ethminer -U http://$CLUSTER_IP:38391 --shard-id $SHARD_ID --cuda-devices $GPU_ID --farm-recheck $TIME
```

- `--shard-id` defines one specify shard to mine. shard id 0 ~ 3 are Ethash.
- `--cuda-devices` defines specify GPUs to mine. 
- `--farm-recheck` defines check interval in milliseconds for changed work.

Noted that if you want to mine multiple shards, please open multiple terminals.

You check the GPU id by using the 
```shell
nvidia-smi
```
## Testnet 2.4 GPU mining shardID
|Chains |Hash Algorithm |ShardID|
| ---      | ---       | --- |
| Shard 0      | Ethash               | 1 |
| Shard 1       | Ethash        | 10001 |
| Shard 2       | Ethash              | 20001 |
| Shard 3       | Ethash              | 30001 |

## AWS AMI

QuarkChain GPU Mining AMI ami-042a6b2a7c48dea80   (Region: Oregon)

## License

Licensed under the [GNU General Public License, Version 3](LICENSE).


## F.A.Q


### Can I still mine QuarkChain with my 1GB GPU?

Not really, your VRAM must be above the DAG size (Currently about 1.08 GB.) to get best performance. Without it severe hash loss will occur.


### Can I CPU Mine?

No, this version is modified just for the Ethash GPU mining. For CPU miner, please refer to [external miners](https://github.com/QuarkChain/pyquarkchain/wiki/Run-a-Private-Cluster-on-the-QuarkChain-Testnet-2.0).


### Insufficient CUDA driver

```text
Error: Insufficient CUDA driver: 9010
```

You have to upgrade your Nvidia drivers. On Linux, install `nvidia-396` package or newer.
