# Firmware
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/touch/ft_fw.bin:system/etc/firmware/ft_fw.bin

# Permissions
PRODUCT_COPY_FILES += \
    frameworks/native/data/etc/android.hardware.touchscreen.multitouch.jazzhand.xml:system/etc/permissions/android.hardware.touchscreen.multitouch.jazzhand.xml
