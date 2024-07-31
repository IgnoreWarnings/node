/* Driver
 *
 * Author: Pascal Bauer <pascal.bauer@rwth-aachen.de>
 *
 * SPDX-FileCopyrightText: 2023-2024 Pascal Bauer <pascal.bauer@rwth-aachen.de>
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <fstream>
#include <iostream>

class Device;

class Driver {
private:
  static constexpr char UNBIND_DEFAULT[] = "/unbind";
  static constexpr char BIND_DEFAULT[] = "/bind";

public:
  const std::filesystem::path path;

private:
  const std::filesystem::path unbind_path;
  const std::filesystem::path bind_path;

public:
  Driver(const std::filesystem::path path)
      : Driver(path, std::filesystem::path(path.u8string() + UNBIND_DEFAULT),
               std::filesystem::path(path.u8string() + BIND_DEFAULT)) {}

  Driver(const std::filesystem::path path,
         const std::filesystem::path unbind_path,
         const std::filesystem::path bind_path)
      : path(path), unbind_path(unbind_path), bind_path(bind_path){};

  void attach(const Device &device) const;
  void unbind(const Device &device) const;
  void override(const Device &device) const;
  std::string name() const;
};
