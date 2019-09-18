/*
 * Utility.cpp
 *
 *  Created on: 17 Sep 2019
 *      Author: root
 */

#include "Utility.h"

using namespace UtilityName;

std::string Utility::hexStr(uint8_t *data, int len)
{
  std::string s(len * 2, ' ');
  for (int i = 0; i < len; ++i) {
	s[2 * i]     = hexmap[(data[i] & 0xF0) >> 4];
	s[2 * i + 1] = hexmap[data[i] & 0x0F];
  }
  return s;
}

