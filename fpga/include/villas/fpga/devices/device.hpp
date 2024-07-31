/* Device
 *
 * Author: Pascal Bauer <pascal.bauer@rwth-aachen.de>
 *
 * SPDX-FileCopyrightText: 2023-2024 Pascal Bauer <pascal.bauer@rwth-aachen.de>
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <filesystem>
#include <optional>
#include <villas/fpga/devices/driver.hpp>

class Device {
public:
  const std::filesystem::path path;

public:
  Device(const std::filesystem::path path) : path(path){};

  std::string name() const {
    size_t pos = path.u8string().rfind('/');
    return path.u8string().substr(pos + 1);
  }

  std::optional<Driver> driver() const {
    std::filesystem::path driver_symlink =
        std::filesystem::path(this->path.u8string() + "/driver");

    std::filesystem::path driver_path;
    try {
      driver_path = std::filesystem::read_symlink(driver_symlink);
    } catch (std::filesystem::filesystem_error &e) {
      return std::nullopt;
    }

    driver_path = std::filesystem::absolute(driver_path);
    return Driver(driver_path);
  };
};
