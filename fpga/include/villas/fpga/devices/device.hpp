/* Device
 *
 * Author: Pascal Bauer <pascal.bauer@rwth-aachen.de>
 *
 * SPDX-FileCopyrightText: 2023-2024 Pascal Bauer <pascal.bauer@rwth-aachen.de>
 * SPDX-License-Identifier: Apache-2.0
 */

#include <filesystem>
#include <regex>
#include <stdexcept>
#include <string>

class Device {
public:
  const std::filesystem::path path;

public:
  Device(const std::filesystem::path path) : path(path){};
};

class IpDevice : public Device {
public:
  static IpDevice from(const std::filesystem::path path) {
    // Split the string at last slash
    size_t pos = path.u8string().rfind('/');
    std::string device_name = path.u8string().substr(pos + 1);

    if (!std::regex_match(device_name, std::regex(R"([0-9A-Fa-f]+\..*)"))) {
      throw std::runtime_error(
          "Name \"" + device_name +
          "\" doesnt match format of \"[adress in hex].[name]\". ");
    }

    return IpDevice(path);
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
    size_t pos = path.u8string().find('.');
    return devicetree_name().substr(pos + 1);
  }

  size_t addr() const {
    size_t pos = path.u8string().find('.');
    std::string addr_hex = devicetree_name().substr(0, pos);

    // convert from hex string to number
    std::stringstream ss;
    ss << std::hex << addr_hex;
    size_t addr = 0;
    ss >> addr;

    return addr;
  }
};
