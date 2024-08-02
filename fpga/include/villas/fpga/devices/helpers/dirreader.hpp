/* Directory Reader
 *
 * Author: Pascal Bauer <pascal.bauer@rwth-aachen.de>
 *
 * SPDX-FileCopyrightText: 2023-2024 Pascal Bauer <pascal.bauer@rwth-aachen.de>
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once
std::vector<std::string> read_names_in_directory(const std::string &name) {
  DIR *directory = opendir(name.c_str());

  struct dirent *dp;
  std::vector<std::string> names;
  dp = readdir(directory);
  while (dp != NULL) {
    auto name = std::string(dp->d_name);
    if (name != "." && name != "..") {
      names.push_back(name);
    }
    dp = readdir(directory);
  }
  closedir(directory);
  return names;
}