/* IpDevice
 *
 * Author: Pascal Bauer <pascal.bauer@rwth-aachen.de>
 *
 * SPDX-FileCopyrightText: 2023-2024 Pascal Bauer <pascal.bauer@rwth-aachen.de>
 * SPDX-License-Identifier: Apache-2.0
 */

#include <filesystem>
#include <regex>
#include <stdexcept>

#include <villas/fpga/devices/ip_device.hpp>

IpDevice IpDevice::from(const std::filesystem::path unsafe_path) {
  if (!is_path_valid(unsafe_path))
    throw std::runtime_error(
        "Path \"" + unsafe_path.u8string() +
        "\" failed validation as IpDevicePath \"[adress in hex].[name]\". ");
  return IpDevice(unsafe_path);
}

bool IpDevice::is_path_valid(const std::filesystem::path unsafe_path) {
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

std::string IpDevice::ip_name() const {
  size_t pos = name().find('.');
  return name().substr(pos + 1);
}

size_t IpDevice::addr() const {
  size_t pos = name().find('.');
  std::string addr_hex = name().substr(0, pos);

  // convert from hex string to number
  std::stringstream ss;
  ss << std::hex << addr_hex;
  size_t addr = 0;
  ss >> addr;

  return addr;
}
