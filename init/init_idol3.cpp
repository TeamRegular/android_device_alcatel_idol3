/*
   Copyright (c) 2013, The Linux Foundation. All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.
   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>
#include <fcntl.h>

#include "vendor_init.h"
#include "property_service.h"
#include "log.h"
#include "util.h"

static int read_file2(const char *fname, char *data, int max_size)
{
    int fd, rc;

    if (max_size < 1)
        return 0;

    fd = open(fname, O_RDONLY);
    if (fd < 0) {
        ERROR("failed to open '%s'\n", fname);
        return 0;
    }

    rc = read(fd, data, max_size - 1);
    if ((rc > 0) && (rc < max_size))
        data[rc] = '\0';
    else
        data[0] = '\0';
    close(fd);

    return 1;
}

void init_alarm_boot_properties()
{
    char const *alarm_file = "/proc/sys/kernel/boot_reason";
    char buf[64];
    std::string tmp = property_get("ro.boot.alarmboot");

    if (read_file2(alarm_file, buf, sizeof(buf))) {
        /*
         * Setup ro.alarm_boot value to true when it is RTC triggered boot up
         * For existing PMIC chips, the following mapping applies
         * for the value of boot_reason:
         *
         * 0 -> unknown
         * 1 -> hard reset
         * 2 -> sudden momentary power loss (SMPL)
         * 3 -> real time clock (RTC)
         * 4 -> DC charger inserted
         * 5 -> USB charger insertd
         * 6 -> PON1 pin toggled (for secondary PMICs)
         * 7 -> CBLPWR_N pin toggled (for external power supply)
         * 8 -> KPDPWR_N pin toggled (power key pressed)
         */
        if (buf[0] == '3' || tmp == "true")
            property_set("ro.alarm_boot", "true");
        else
            property_set("ro.alarm_boot", "false");
    }
}

void common_properties()
{
        property_set("ro.product.device", "idol3");
        property_set("ro.build.product", "idol3");
}

void dualsim_properties(char const multisim_config[])
{
    property_set("persist.radio.multisim.config", multisim_config);
}

void gsm_properties(char const default_network[])
{
    property_set("ro.telephony.default_network", default_network);
}

void vendor_load_properties()
{
    std::string curef_version;
    std::string;

    device = property_get("ro.cm.device");
    if (device != idol3)
        return;

    curef_version = property_get("ro.cm.curef");

    if (curef_version == "6045I")) {
        /* 6045I (North America) */
        common_properties();
        dualsim_properties("single");
        gsm_properties("9");
        property_set("ro.build.fingerprint", "TCL/6045I/idol3:6.0.1/MMB29M/v7VAB-0:user/release-keys");
        property_set("ro.build.description", "idol3-user 6.0.1 MMB29M v7VAB-0 release-keys");
        property_set("ro.product.model", "6045I");
    } else if (curef_version == "6045B")) {
        /* 6045B */
        common_properties();
        dualsim_properties("single");
        gsm_properties("9");
        property_set("ro.build.fingerprint", "TCL/6045B/idol3:5.0.2/LRX22G/v7SQX-0:user/release-keys");
        property_set("ro.build.description", "idol3-user 5.0.2 LRX22G v7SQX-0 release-keys");
        property_set("ro.product.model", "6045B");
    } else if (curef_version == "6045K")) {
        /* 6045K */
        common_properties();
        dualsim_properties("dsds");
        gsm_properties("9");
        property_set("ro.build.fingerprint", "TCL/6045K/idol3:6.0.1/MMB29M/v7VG6-0:user/release-keys");
        property_set("ro.build.description", "idol3-user 6.0.1 MMB29M v7VG6-0 release-keys");
        property_set("ro.product.model", "6045K");
    } else if (curef_version == "6045O")) {
        /* 6045O Cricket */
        common_properties();
        dualsim_properties("single");
        gsm_properties("9");
        property_set("ro.build.fingerprint", "TCL/6045O/idol3:5.0.2/LRX22G/v5AMB:user/release-keys");
        property_set("ro.build.description", "idol3-user 5.0.2 LRX22G v5AMB release-keys");
        property_set("ro.product.model", "6045O");
    } else if (curef_version == "6045Y")) {
        /* 6045Y */
        common_properties();
        dualsim_properties("single");
        gsm_properties("9");
        property_set("ro.build.fingerprint", "TCL/6045Y/idol3:6.0.1/MMB29M/v7VG6-0:user/release-keys");
        property_set("ro.build.description", "idol3-user 6.0.1 MMB29M v7VG6-0 release-keys");
        property_set("ro.product.model", "6045Y");
    } else {
        /* I806 */
        common_properties();
        dualsim_properties("dsds");
        gsm_properties("10");
        property_set("ro.build.fingerprint", "TCL/TCL_i806/idol3:5.0.2/LRX22G/v7TM4-0:user/release-keys");
        property_set("ro.build.description", "idol3-user 5.0.2 LRX22G v7TM4-0 release-keys");
        property_set("ro.product.model", "TCL i806");
    }

    device = property_get("ro.product.device");
    ERROR("Found curef id %s setting build properties for %s device\n", curef_version.c_str(), device.c_str());

    init_alarm_boot_properties();
}
