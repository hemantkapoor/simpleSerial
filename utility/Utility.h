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
	static std::string hexStr(uint8_t *data, int len);
};

};//End of namespace

#endif /* UTILITY_UTILITY_H_ */
