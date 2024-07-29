  // Unbind device from driver
        // /sys/bus/platform/devices/$device/driver -> $DRIVER:/../../../../bus/platform/drivers/xilinx-vdma
        // echo $device > /sys/bus/platform/drivers/$DRIVER/unbind

        // Bind device to platform-vfio driver
        // echo vfio-platform > /sys/bus/platform/devices/$device/driver_override;
        // echo $device > /sys/bus/platform/drivers/vfio-platform/bind;