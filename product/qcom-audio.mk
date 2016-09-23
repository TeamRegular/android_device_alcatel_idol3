# Audio
PRODUCT_PACKAGES += \
    audiod \
    audio.primary.msm8916 \
    libqcompostprocbundle \
    libqcomvisualizer \
    libqcomvoiceprocessing

PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/audio/acdb/MTP_Bluetooth_cal.acdb:system/etc/acdbdata/MTP/MTP_Bluetooth_cal.acdb \
    $(LOCAL_PATH)/audio/acdb/MTP_General_cal.acdb:system/etc/acdbdata/MTP/MTP_General_cal.acdb \
    $(LOCAL_PATH)/audio/acdb/MTP_Global_cal.acdb:system/etc/acdbdata/MTP/MTP_Global_cal.acdb \
    $(LOCAL_PATH)/audio/acdb/MTP_Handset_cal.acdb:system/etc/acdbdata/MTP/MTP_Handset_cal.acdb \
    $(LOCAL_PATH)/audio/acdb/MTP_Hdmi_cal.acdb:system/etc/acdbdata/MTP/MTP_Hdmi_cal.acdb \
    $(LOCAL_PATH)/audio/acdb/MTP_Headset_cal.acdb:system/etc/acdbdata/MTP/MTP_Headset_cal.acdb \
    $(LOCAL_PATH)/audio/acdb/MTP_Speaker_cal.acdb:system/etc/acdbdata/MTP/MTP_Speaker_cal.acdb \
    $(LOCAL_PATH)/audio/tfa9897/AAC/seltech_bottom.cnt:system/etc/tfa9897/AAC/seltech_bottom.cnt \
    $(LOCAL_PATH)/audio/tfa9897/AAC/seltech_stereo.cnt:system/etc/tfa9897/AAC/seltech_stereo.cnt \
    $(LOCAL_PATH)/audio/tfa9897/AAC/seltech_top.cnt:system/etc/tfa9897/AAC/seltech_top.cnt \
    $(LOCAL_PATH)/audio/tfa9897/LC/seltech_bottom.cnt:system/etc/tfa9897/LC/seltech_bottom.cnt \
    $(LOCAL_PATH)/audio/tfa9897/LC/seltech_stereo.cnt:system/etc/tfa9897/LC/seltech_stereo.cnt \
    $(LOCAL_PATH)/audio/tfa9897/LC/seltech_top.cnt:system/etc/tfa9897/LC/seltech_top.cnt \
    $(LOCAL_PATH)/audio/tfa9897/seltech_bottom.cnt:system/etc/tfa9897/seltech_bottom.cnt \
    $(LOCAL_PATH)/audio/tfa9897/seltech_stereo.cnt:system/etc/tfa9897/seltech_stereo.cnt \
    $(LOCAL_PATH)/audio/tfa9897/seltech_top.cnt:system/etc/tfa9897/seltech_top.cnt \
    $(LOCAL_PATH)/audio/audio_effects.conf:system/vendor/etc/audio_effects.conf \
    $(LOCAL_PATH)/audio/audio_policy.conf:system/etc/audio_policy.conf \
    $(LOCAL_PATH)/audio/mixer_paths_mtp.xml:system/etc/mixer_paths_mtp.xml

# Permissions
#PRODUCT_COPY_FILES += \
#    frameworks/native/data/etc/android.hardware.audio.low_latency.xml:system/etc/permissions/android.hardware.audio.low_latency.xml

# Properties
PRODUCT_PROPERTY_OVERRIDES += \
    ro.qc.sdk.audio.fluencetype=fluence \
    persist.audio.fluence.voicecall=true \
    persist.audio.fluence.voicerec=false \
    persist.audio.fluence.speaker=false

# Properties
PRODUCT_PROPERTY_OVERRIDES += \
    audio.deep_buffer.media=true \
    audio.offload.buffer.size.kb=64 \
    audio.offload.gapless.enabled=true \
    audio.offload.min.duration.secs=30 \
    audio.offload.pcm.16bit.enable=false \
    audio.offload.pcm.24bit.enable=false \
    audio.offload.video=true \
    av.streaming.offload.enable=true \
    use.voice.path.for.pcm.voip=true \
    voice.conc.fallbackpath=deep-buffer
