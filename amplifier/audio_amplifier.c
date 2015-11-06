/*
 * Copyright (C) 2016, The CyanogenMod Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#include <time.h>
#include <system/audio.h>
#include <platform.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <ctype.h>
#include <dlfcn.h>
#include <sys/ioctl.h>

#define LOG_TAG "idol3-tfa9897"
#include <log/log.h>

#include <hardware/audio_amplifier.h>

typedef struct tfa9897_device {
    amplifier_device_t amp_dev;
    void *lib_ptr;
    int (*init)(int);
    int (*enable)(int, int);
    int (*disable)(int);
} tfa9897_device_t;

static tfa9897_device_t *tfa9897_dev = NULL;

#define SAMPLE_RATE 48000

static int is_speaker(uint32_t snd_device) {
    int speaker = 0;

    switch (snd_device) {
        case SND_DEVICE_OUT_SPEAKER:
        case SND_DEVICE_OUT_SPEAKER_REVERSE:
        case SND_DEVICE_OUT_SPEAKER_AND_HEADPHONES:
        case SND_DEVICE_OUT_VOICE_SPEAKER:
            speaker = 1;
            break;
    }

    return speaker;
}

static int amp_enable_output_devices(hw_device_t *device, uint32_t devices, bool enable, bool disable) {
    tfa9897_device_t *tfa9897 = (tfa9897_device_t*) device;

    if (is_speaker(devices)) {
        if (enable) {
            tfa9897->enable(0, 2);
        } else {
            tfa9897->disable(1);
        }
    }
    return 0;
}

static int amp_dev_close(hw_device_t *device) {
    tfa9897_device_t *tfa9897 = (tfa9897_device_t*) device;

    if (tfa9897) {
        dlclose(tfa9897->lib_ptr);
        free(tfa9897);
    }

    return 0;
}

static int amp_init(tfa9897_device_t *tfa9897) {
    size_t i;
    int subscribe = 1;

    tfa9897->init(SAMPLE_RATE);

    return 0;
}

static int amp_module_open(const hw_module_t *module,
        __attribute__((unused)) const char *name, hw_device_t **device)
{
    if (tfa9897_dev) {
        ALOGE("%s:%d: Unable to open second instance of tfa9897 amplifier\n",
                __func__, __LINE__);
        return -EBUSY;
    }

    tfa9897_dev = calloc(1, sizeof(tfa9897_device_t));
    if (!tfa9897_dev) {
        ALOGE("%s:%d: Unable to allocate memory for amplifier device\n",
                __func__, __LINE__);
        return -ENOMEM;
    }

    tfa9897_dev->amp_dev.common.tag = HARDWARE_DEVICE_TAG;
    tfa9897_dev->amp_dev.common.module = (hw_module_t *) module;
    tfa9897_dev->amp_dev.common.version = HARDWARE_DEVICE_API_VERSION(1, 0);
    tfa9897_dev->amp_dev.common.close = amp_dev_close;

    tfa9897_dev->amp_dev.enable_output_devices = amp_enable_output_devices;

    tfa9897_dev->lib_ptr = dlopen("libtfa9897.so", RTLD_NOW);
    if (!tfa9897_dev->lib_ptr) {
        ALOGE("%s:%d: Unable to open libtfa9897: %s",
                __func__, __LINE__, dlerror());
        free(tfa9897_dev);
        return -ENODEV;
    }

    *(void **)&tfa9897_dev->init = dlsym(tfa9897_dev->lib_ptr, "tfa9897_init");
    *(void **)&tfa9897_dev->enable = dlsym(tfa9897_dev->lib_ptr, "tfa9897_SpeakerOn");
    *(void **)&tfa9897_dev->disable = dlsym(tfa9897_dev->lib_ptr, "tfa9897_SpeakerOff");

    if (!tfa9897_dev->init || !tfa9897_dev->enable || !tfa9897_dev->disable) {
        ALOGE("%s:%d: Unable to find required symbols", __func__, __LINE__);
        dlclose(tfa9897_dev->lib_ptr);
        free(tfa9897_dev);
        return -ENODEV;
    }

    if (amp_init(tfa9897_dev)) {
        dlclose(tfa9897_dev->lib_ptr);
        free(tfa9897_dev);
        return -ENODEV;
    }

    *device = (hw_device_t *) tfa9897_dev;

    return 0;
}

static struct hw_module_methods_t hal_module_methods = {
    .open = amp_module_open,
};

amplifier_module_t HAL_MODULE_INFO_SYM = {
    .common = {
        .tag = HARDWARE_MODULE_TAG,
        .module_api_version = AMPLIFIER_MODULE_API_VERSION_0_1,
        .hal_api_version = HARDWARE_HAL_API_VERSION,
        .id = AMPLIFIER_HARDWARE_MODULE_ID,
        .name = "Idol3 amplifier HAL",
        .author = "The CyanogenMod Open Source Project",
        .methods = &hal_module_methods,
    },
};
