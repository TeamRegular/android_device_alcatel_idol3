# IRSC
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/configs/sec_config:system/etc/sec_config

# Permissions
PRODUCT_COPY_FILES += \
    frameworks/native/data/etc/android.hardware.telephony.gsm.xml:system/etc/permissions/android.hardware.telephony.gsm.xml \
    frameworks/native/data/etc/android.software.sip.voip.xml:system/etc/permissions/android.software.sip.voip.xml

# RIL
PRODUCT_PACKAGES += \
    libcnefeatureconfig \
    librmnetctl \
    libxml2

# RIL Properties
PRODUCT_PROPERTY_OVERRIDES += \
    DEVICE_PROVISIONED=1 \
    persist.data.qmi.adb_logmask=0 \
    persist.dbg.volte_avail_ovr=1 \
    persist.dbg.vt_avail_ovr=1 \
    persist.radio.apm_sim_not_pwdn=1 \
    persist.radio.custom_ecc=0 \
    persist.radio.manual_nw_rej_ct \
    persist.radio.mns_with_all_rat=0 \
    persist.radio.orig_num_disp=false \
    persist.radio.rat_on=combine \
    persist.radio.sib16_support=1 \
    persist.rild.nitz_long_ons_0="" \
    persist.rild.nitz_long_ons_1="" \
    persist.rild.nitz_long_ons_2="" \
    persist.rild.nitz_long_ons_3="" \
    persist.rild.nitz_plmn="" \
    persist.rild.nitz_short_ons_0="" \
    persist.rild.nitz_short_ons_1="" \
    persist.rild.nitz_short_ons_2="" \
    persist.rild.nitz_short_ons_3="" \
    rild.libargs=-d /dev/smd0 \
    rild.libpath=/vendor/lib64/libril-qc-qmi-1.so \
    ril.subscription.types=NV,RUIM

PRODUCT_PROPERTY_OVERRIDES += \
    persist.data_netmgrd_mtu=1440 \
    persist.data.netmgrd.qos.enable=true \
    ro.use_data_netmgrd=true
