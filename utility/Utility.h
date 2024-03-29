/*
 * Utility.h
 *
 *  Created on: 17 Sep 2019
 *      Author: root
 */

#ifndef UTILITY_UTILITY_H_
#define UTILITY_UTILITY_H_

#include <stdint.h>
#include <string>
#include <vector>
#include <memory>

namespace SimpleSerialName
{
	constexpr uint8_t hexmap[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

class Utility
{
public:
	//Static class No constructor move or copy
	Utility() = delete;
	Utility& operator=(const Utility& ) = delete;
	Utility (const Utility &) = delete;
	~Utility() = delete;
	static std::string hexStr(const uint8_t *data, int len);
	static std::vector<uint16_t> convertU8toU16(const std::vector<uint8_t>&);
};

};//End of namespace

#endif /* UTILITY_UTILITY_H_ */
