/* Driver
 *
 * Author: Pascal Bauer <pascal.bauer@rwth-aachen.de>
 *
 * SPDX-FileCopyrightText: 2023-2024 Pascal Bauer <pascal.bauer@rwth-aachen.de>
 * SPDX-License-Identifier: Apache-2.0
 */

#include <villas/fpga/devices/filewriter.hpp>
#include <villas/fpga/devices/ip_device.hpp>

void Driver::unbind(const Device &device) const {
  write_to_file(device.name(), this->unbind_path);
};

void Driver::bind(const Device &device) const {
  write_to_file("vfio-platform",
                std::filesystem::path(
                    device.path.u8string() +
                    "/driver_override")); // TODO: make this a seperate method
  write_to_file(device.name(), this->bind_path); 
};
