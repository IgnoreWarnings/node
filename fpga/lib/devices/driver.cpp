/* Driver
 *
 * Author: Pascal Bauer <pascal.bauer@rwth-aachen.de>
 *
 * SPDX-FileCopyrightText: 2023-2024 Pascal Bauer <pascal.bauer@rwth-aachen.de>
 * SPDX-License-Identifier: Apache-2.0
 */

#include <villas/fpga/devices/helpers/filewriter.hpp>
#include <villas/fpga/devices/ip_device.hpp>

std::string Driver::name() const {
  size_t pos = path.u8string().rfind('/');
  return path.u8string().substr(pos + 1);
}

void Driver::bind(const Device &device) const {
  write_to_file(device.name(), this->bind_path);
};

void Driver::unbind(const Device &device) const {
  write_to_file(device.name(), this->unbind_path);
};

void Driver::attach(const Device &device) const {
  if (device.driver().has_value()) {
    device.driver().value().unbind(device);
  }

  override(device);
  //this->bind(device);
  this->probe(device);
}

void Driver::override(const Device &device) const {
  write_to_file(this->name(),
                device.path / std::filesystem::path("driver_override"));
};

void Driver::probe(const Device &device) const {
  write_to_file(
      device.name(),
      std::filesystem::path(
          "/sys/bus/platform/drivers_probe")); // Todo: find probe path
}
