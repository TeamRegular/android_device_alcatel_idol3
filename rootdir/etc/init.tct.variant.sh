#!/system/bin/sh

setprop ro.cm.curef `/system/bin/strings /dev/block/bootdevice/by-name/traceability | /system/bin/grep '6045' | /system/bin/cut -c4-8`
