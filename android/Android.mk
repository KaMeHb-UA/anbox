LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional
LOCAL_AIDL_INCLUDES := $(LOCAL_PATH)/src/java
LOCAL_SRC_FILES := $(call all-java-files-under, java)
LOCAL_JAVA_LIBRARIES := telephony-common
# Block certain packages from being installed
LOCAL_OVERRIDES_PACKAGES := \
	SystemUI \
	Home \
	Launcher2 \
	Calculator \
	BasicDreams \
	Calendar \
	PrintSpooler \
	WallpaperCropper
LOCAL_PACKAGE_NAME := anboxd
LOCAL_CERTIFICATE := platform
LOCAL_PRIVILEGED_MODULE := true

include $(BUILD_PACKAGE)

include $(call all-makefiles-under,$(LOCAL_PATH))