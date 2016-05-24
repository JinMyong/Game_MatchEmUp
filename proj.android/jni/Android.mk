LOCAL_PATH := $(call my-dir)
CLASSES_PATH := $(LOCAL_PATH)/../../Classes

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH))

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

CPP_FILES := $(shell find $(LOCAL_PATH)/../../Classes -name *.cpp)
LOCAL_SRC_FILES := hellocpp/main.cpp \

LOCAL_CPPFLAGS := -DSDKBOX_ENABLED
LOCAL_LDLIBS := -landroid \
-llog
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
$(LOCAL_PATH)/../../Classes/Layers \
$(LOCAL_PATH)/../../Classes/Global
LOCAL_WHOLE_STATIC_LIBRARIES := PluginIAP \
sdkbox \
android_native_app_glue

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module, ./sdkbox)
$(call import-module, ./pluginiap)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
