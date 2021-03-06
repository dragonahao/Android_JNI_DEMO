# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

#local path ， jni dir 
 
LOCAL_PATH := $(call my-dir)
SRC_PATH := ../../NativeCode/src
#clear temp vars
include $(CLEAR_VARS)
# 添加对log库的支持 should after include $(CLEAR_VARS)
LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -llog
#  注：若生成static的.a，只需添加 LOCAL_LDLIBS:=-llog 
 

#LOCAL_MODULE    := hello-jni
#LOCAL_SRC_FILES := $(SRC_PATH)/hello-jni.c

LOCAL_MODULE    := controller-jni
LOCAL_SRC_FILES := $(SRC_PATH)/controller.c       

include $(BUILD_SHARED_LIBRARY)
