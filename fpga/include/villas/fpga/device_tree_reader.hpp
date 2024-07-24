/* Device Tree Reader
 *
 * Author: Pascal Bauer <pascal.bauer@rwth-aachen.de>
 *
 * SPDX-FileCopyrightText: 2023-2024 Pascal Bauer <pascal.bauer@rwth-aachen.de>
 * SPDX-License-Identifier: Apache-2.0
 */

#include <regex>

#include <dirent.h>
#include <sys/types.h>
#include <vector>

#include <string_view>

class Device {
public:
  const std::string name;
  const std::size_t addr;

public:
  Device(std::string name, std::size_t addr) : name(name), addr(addr){};
  std::string devicetree_name() { return addr + "." + name; };
};

std::vector<std::string> read_names_in_directory(const std::string &name) {
  DIR *directory = opendir(name.c_str());

  struct dirent *dp;
  std::vector<std::string> names;
  dp = readdir(directory);
  while (dp != NULL) {
    names.push_back(dp->d_name);
    dp = readdir(directory);
  }
  closedir(directory);

  return names;
}

class DeviceParser {
public:
  std::string name;
  std::size_t addr;

  DeviceParser(std::string device_name) {
    // test format of device_name: [adress in hex].[name]
    if (!std::regex_match(device_name, std::regex("\\w+\\.\\w+"))) {
      this->name = "";
      this->addr = 0;
      return;
    }

    std::istringstream iss(device_name);

    // parse address
    std::string device_addr;
    std::getline(iss, device_addr, '.');

    // convert from hex to dec
    std::stringstream ss;
    ss << std::hex << device_addr;

    // store addr in attribute
    ss >> this->addr;

    // store name in attribute
    std::getline(iss, this->name, '.');
  }
};

class DeviceTreeReader {
public:
  static constexpr char PLATFORM_PATH[] = "/sys/bus/platform/devices";

  const std::vector<std::string> devicetree_names;
  std::vector<Device> devices;

  DeviceTreeReader(const char *path_to_devices)
      : devicetree_names(read_names_in_directory(path_to_devices)) {
    for (auto devicetree_name : this->devicetree_names) {
      auto parser = DeviceParser(devicetree_name);

      if (parser.addr != 0)
        devices.push_back(Device(parser.name, parser.addr));
    }
  }
};
