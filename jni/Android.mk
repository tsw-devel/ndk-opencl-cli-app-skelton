# ==============================================================================
# 
# Android.mk for Android-NDK OpenCL CLI App skelton on Android smartphones.
#
# ==============================================================================
LOCAL_PATH := $(call my-dir)

# ------------------------------------------------------------------------------
# arm64 OpenCL lib copy
# ------------------------------------------------------------------------------
include $(CLEAR_VARS)
ifeq ($(TARGET_ARCH_ABI),arm64-v8a)
LOCAL_MODULE    := arm64-OpenCL-Library
LOCAL_SRC_FILES := vendor/lib64/libOpenCL.so
include $(PREBUILT_SHARED_LIBRARY)
endif

# ------------------------------------------------------------------------------
# arm64 OpenCL lib copy
# ------------------------------------------------------------------------------
include $(CLEAR_VARS)
ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
LOCAL_MODULE    := arm-OpenCL-Library
LOCAL_SRC_FILES := vendor/lib/libOpenCL.so
include $(PREBUILT_SHARED_LIBRARY)
endif

# ------------------------------------------------------------------------------
# Build execute binary
# ------------------------------------------------------------------------------
include $(CLEAR_VARS)
LOCAL_MODULE := cl-summary
SRC_DIR      := src
CPP_FILES    := $(wildcard $(LOCAL_PATH)/$(SRC_DIR)/*.cc)
SRC_FILES    :=
SRC_FILES    += $(subst $(LOCAL_PATH)/,, $(CPP_FILES))
$(info LOCAL_PATH:$(LOCAL_PATH))
$(info SRC_FILES:$(SRC_FILES))
C_INCLUEDS   := src/
CL_INCLUEDS  := $(LOCAL_PATH)/OpenCL-Headers 

ifeq ($(TARGET_ARCH_ABI),arm64-v8a)
LOCAL_SHARED_LIBRARIES := arm64-OpenCL-Library
LD_OPTION              := -fuse-ld=gold
else
ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
LOCAL_SHARED_LIBRARIES := arm-OpenCL-Library
else
$(error Not support abi)
endif
endif

LOCAL_SRC_FILES  := $(SRC_FILES)
LOCAL_LDLIBS     := $(LD_OPTION)
LOCAL_CPPFLAGS   := 
LOCAL_C_INCLUDES := $(C_INCLUEDS) $(CL_INCLUEDS)
#LOCAL_ALLOW_UNDEFINED_SYMBOLS := true

$(info DST:$(NDK_APP_DST_DIR))
$(info PLATFORM : $(TARGET_PLATFORM))
$(info ARCH/ABI : $(TARGET_ARCH)/$(TARGET_ARCH_ABI))
include $(BUILD_EXECUTABLE)