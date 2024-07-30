/* Device
 *
 * Author: Pascal Bauer <pascal.bauer@rwth-aachen.de>
 *
 * SPDX-FileCopyrightText: 2023-2024 Pascal Bauer <pascal.bauer@rwth-aachen.de>
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <filesystem>
#include <villas/fpga/devices/driver.hpp>

class Device {
public:
  const std::filesystem::path path;

public:
  Device(const std::filesystem::path path) : path(path){};
  Driver driver(){
    //* /sys/bus/platform/devices/$device/driver -> $DRIVER:/../../../../bus/platform/drivers/xilinx-vdma
    this->path
    fs::read_symlink(this->path)

    return Driver(this->path);
  };
};
