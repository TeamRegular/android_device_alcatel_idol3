#!/system/bin/sh

setprop ro.cm.curef `/system/xbin/strings /dev/block/bootdevice/by-name/traceability | /system/xbin/grep '6045' | /system/xbin/cut -c4-8`
