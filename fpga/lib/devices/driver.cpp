/* Driver
 *
 * Author: Pascal Bauer <pascal.bauer@rwth-aachen.de>
 *
 * SPDX-FileCopyrightText: 2023-2024 Pascal Bauer <pascal.bauer@rwth-aachen.de>
 * SPDX-License-Identifier: Apache-2.0
 */

#include <villas/fpga/devices/ip_device.hpp>
#include <villas/fpga/devices/filewriter.hpp>

void Driver::unbind(const Device &device) const {
  write_to_file(device.name(), this->unbind_path);
};

void Driver::bind(const Device &device) const {
    // Bind device to platform-vfio driver
    // echo vfio-platform > /sys/bus/platform/devices/$device/driver_override;
    // echo $device > /sys/bus/platform/drivers/vfio-platform/bind;
};
