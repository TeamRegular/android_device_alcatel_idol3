# Copyright (C) 2015 The CyanogenMod Project
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

$(call inherit-product, device/tcl/idol3/full_idol3.mk)

# Inherit some common CM stuff.
$(call inherit-product, vendor/cm/config/common_full_phone.mk)

# Enhanced NFC
$(call inherit-product, vendor/cm/config/nfc_enhanced.mk)

# TODO move to target libinit
PRODUCT_BUILD_PROP_OVERRIDES += \
    BUILD_FINGERPRINT=TCL/6045I/idol3:5.0.2/LRX22G/v7TM4-0:user/release-keys \
    PRIVATE_BUILD_DESC="idol3-user 5.0.2 LRX22G v7TM4-0 release-keys"

PRODUCT_NAME := cm_idol3
