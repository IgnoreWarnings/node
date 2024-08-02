/* Device Tree Reader
 *
 * Author: Pascal Bauer <pascal.bauer@rwth-aachen.de>
 *
 * SPDX-FileCopyrightText: 2023-2024 Pascal Bauer <pascal.bauer@rwth-aachen.de>
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <dirent.h>
#include <sys/types.h>
#include <vector>
#include <stdexcept>

#include <filesystem>

#include <villas/fpga/devices/ip_device.hpp>
#include <villas/fpga/devices/helpers/dirreader.hpp>

class IpDeviceReader {
public:
  static constexpr char PLATFORM_DEVICES_DIRECTORY[] =
      "/sys/bus/platform/devices";

  const std::vector<std::string> devicetree_names;
  std::vector<IpDevice> devices;

  IpDeviceReader(const char *devices_directory)
      : devicetree_names(read_names_in_directory(devices_directory)) {
    for (auto devicetree_name : this->devicetree_names) {
      auto path_to_device = std::filesystem::path(
          devices_directory + std::string("/") + devicetree_name);
      try {
        auto device = IpDevice::from(path_to_device);
        this->devices.push_back(device);
      } catch (std::runtime_error& e){}
    }
  }
};
