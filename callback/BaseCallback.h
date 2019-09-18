/*
 * BaseCallback.h
 *
 *  Created on: 18 Sep 2019
 *      Author: root
 */

#ifndef SRC_SIMPLESERIAL_CALLBACK_BASECALLBACK_H_
#define SRC_SIMPLESERIAL_CALLBACK_BASECALLBACK_H_

#include <stdint.h>
#include <vector>

namespace SimpleSerialName
{


class BaseCallback {
public:
	BaseCallback() = default;
	virtual ~BaseCallback() = default;
	virtual void callback(std::vector<uint8_t>&) = 0;
};

};

#endif /* SRC_SIMPLESERIAL_CALLBACK_BASECALLBACK_H_ */
