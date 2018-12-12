# Android-NDK OpenCL CLI App skelton on Smartphone with snapdragon.

## About
A skeleton project that runs the OpenCL command line program in Smartphone with snapdragon environment.  
Simple OpenCL summary output program included as sample.  
This software is released under the MIT License, see LICENSE file.


## Preparation
- Confirmation is done with Windows 10 Home 64bit.

### Install Platform Tools

Download & Install & set path  

https://developer.android.com/studio/releases/platform-tools

### Install Android NDK
Download NDK r18 & Install & set path  
https://github.com/android-ndk/ndk/wiki


### Get OpenCL Headers

Store OpenCL-Headers project under jni direcotry.

```sh
> git clone https://github.com/KhronosGroup/OpenCL-Headers.git jni\OpenCL-Headers
```


### Get libOpenCL.so
Get OpenCL Libraries(libOpenCL.so) from smartphone and store them in jni/vendor/lib, jni/vendor/lib64.
#### Example
In this example, I use Asus Zenfone 3 MAX.

- Check OpenCL path
```sh
> adb shell "find /system -name libOpenCL.so 2>/dev/null"
/system/vendor/lib/libOpenCL.so
/system/vendor/lib64/libOpenCL.so
```

- Pull libOpenCL.so from smartphone
```sh
# Get 32bit
> adb pull /system/vendor/lib/libOpenCL.so  jni\vendor\lib
# Get 64bit
> adb pull /system/vendor/lib64/libOpenCL.so jni\vendor\lib64
```

## Build - Run

### Build

```sh
> ndk-build.cmd
```

The executable file is output under libs directory.

```sh
> cd  .\libs\arm64-v8a\
```

### Deploy smartphone

```sh
> adb push .\cl-summary /data/local/tmp
> adb shell "chmod +x /data/local/tmp/cl-summary"
```

### Run

```sh
> adb shell "/data/local/tmp/cl-summary"
CL_PLATFORM_VENDOR      QUALCOMM
CL_PLATFORM_NAME        QUALCOMM Snapdragon(TM)
CL DEVICE NUM           1
CL_DEVICE_NAME  QUALCOMM Adreno(TM)
CL_DRIVER_VERSION       OpenCL 2.0 QUALCOMM build: commit #c5b7903 changeid #Ic4cf336e0a Date: 02/17/17 Fri Local Branch:  Remote Branch:  Compiler E031.31.00.03
CL_DEVICE_PROFILE       FULL_PROFILE
CL_DEVICE_VERSION       OpenCL 2.0 Adreno(TM) 505
CL_DEVICE_MAX_WORK_ITEM_SIZES           1024 1024 1024
CL_DEVICE_SVM_COARSE_GRAIN_BUFFER       true
CL_DEVICE_SVM_FINE_GRAIN_BUFFER         false
CL_DEVICE_SVM_FINE_GRAIN_SYSTEM         false
CL_DEVICE_SVM_ATOMICS                   false
```
