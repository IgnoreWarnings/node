/* Filewriter
 *
 * Author: Pascal Bauer <pascal.bauer@rwth-aachen.de>
 *
 * SPDX-FileCopyrightText: 2023-2024 Pascal Bauer <pascal.bauer@rwth-aachen.de>
 * SPDX-License-Identifier: Apache-2.0
 */

#include <fstream>
#include <iostream>
#include <filesystem>

void write_to_file(std::string data, const std::filesystem::path file) {
  std::ofstream outputFile(file.u8string());

  if (outputFile.is_open()) {
    // Write to file
    outputFile << file;
    outputFile.close();
  } else {
    throw std::filesystem::filesystem_error("Cannot open outputfile", std::error_code());
  }
}