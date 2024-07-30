/* Driver
 *
 * Author: Pascal Bauer <pascal.bauer@rwth-aachen.de>
 *
 * SPDX-FileCopyrightText: 2023-2024 Pascal Bauer <pascal.bauer@rwth-aachen.de>
 * SPDX-License-Identifier: Apache-2.0
 */

class Driver {
public:
  const std::filesystem::path path;

public:
  Driver(const std::filesystem::path path) : path(path) {};
  unbind(const Device& device) const {};
  bind(const Device& device) const {};
};
