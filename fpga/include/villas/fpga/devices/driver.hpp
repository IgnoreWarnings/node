/* Driver
 *
 * Author: Pascal Bauer <pascal.bauer@rwth-aachen.de>
 *
 * SPDX-FileCopyrightText: 2023-2024 Pascal Bauer <pascal.bauer@rwth-aachen.de>
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

class Device;

class Driver {
public:
  const std::filesystem::path path;

public:
  Driver(const std::filesystem::path path) : path(path) {};
  void unbind(const Device &device) const {
    // Unbind device from driver
    // echo $device > /sys/bus/platform/drivers/$DRIVER/unbind
  };
  void bind(const Device &device) const {
    // Bind device to platform-vfio driver
    // echo vfio-platform > /sys/bus/platform/devices/$device/driver_override;
    // echo $device > /sys/bus/platform/drivers/vfio-platform/bind;
  };
};
