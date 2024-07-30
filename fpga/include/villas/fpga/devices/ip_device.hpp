/* IpDevice
 *
 * Author: Pascal Bauer <pascal.bauer@rwth-aachen.de>
 *
 * SPDX-FileCopyrightText: 2023-2024 Pascal Bauer <pascal.bauer@rwth-aachen.de>
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <filesystem>
#include <regex>
#include <stdexcept>

#include <villas/fpga/devices/device.hpp>

class IpDevice : public Device {
public:
  static IpDevice from(const std::filesystem::path unsafe_path) {
    if (!is_path_valid(unsafe_path))
      throw std::runtime_error(
          "Path \"" + unsafe_path.u8string() +
          "\" failed validation as IpDevicePath \"[adress in hex].[name]\". ");
    return IpDevice(unsafe_path);
  }

  static bool is_path_valid(const std::filesystem::path unsafe_path) {
    // Split the string at last slash
    size_t pos = unsafe_path.u8string().rfind('/');
    std::string assumed_device_name = unsafe_path.u8string().substr(pos + 1);

    // Match format of hexaddr.devicename
    if (!std::regex_match(assumed_device_name,
                          std::regex(R"([0-9A-Fa-f]+\..*)"))) {
      return false;
    }

    return true;
  }

private:
  IpDevice(const std::filesystem::path valid_path) : Device(valid_path){};

public:
  std::string devicetree_name() const {
    // Split the string at last slash
    size_t pos = path.u8string().rfind('/');
    return path.u8string().substr(pos + 1);
  }

  std::string name() const {
    size_t pos = devicetree_name().find('.');
    return devicetree_name().substr(pos + 1);
  }

  size_t addr() const {
    size_t pos = devicetree_name().find('.');
    std::string addr_hex = devicetree_name().substr(0, pos);

    // convert from hex string to number
    std::stringstream ss;
    ss << std::hex << addr_hex;
    size_t addr = 0;
    ss >> addr;

    return addr;
  }
};
