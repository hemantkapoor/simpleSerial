/*
 * Utility.cpp
 *
 *  Created on: 17 Sep 2019
 *      Author: root
 */
#include "Utility.h"

using namespace SimpleSerialName;

std::string Utility::hexStr(const uint8_t *data, int len)
{
  std::string s(len * 2, ' ');
  for (int i = 0; i < len; ++i) {
	s[2 * i]     = hexmap[(data[i] & 0xF0) >> 4];
	s[2 * i + 1] = hexmap[data[i] & 0x0F];
  }
  return s;
}

std::vector<uint16_t> Utility::convertU8toU16(const std::vector<uint8_t>& inputData)
{
	std::vector<uint16_t> retVal;
	uint8_t index(0);
	uint16_t value(0);
	for (auto data : inputData)
	{
		if (index == 0)
		{
			value = 0;
			value = data << 8;
			++index;
		}
		else
		{
			value = value | data;
			retVal.push_back(value);
			index = 0;
		}
	}
	return retVal;
}
