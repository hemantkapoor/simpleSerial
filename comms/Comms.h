/*
 * Comms.h
 *
 *  Created on: 17 Sep 2019
 *      Author: root
 */

#ifndef COMMS_COMMS_H_
#define COMMS_COMMS_H_

#include <string>
#include <vector>
#include <stdint.h>

namespace CommsName
{
	const uint32_t MAX_MESSGE_LENGTH = 500;
};

class Comms {
public:
	Comms() = delete;
	Comms(const std::string& path);
	virtual ~Comms();

	bool startComms();
	void processRead();
	bool transmitData(std::vector<uint8_t>& data);
	void stopRead() { m_stopRead = true; }

private:
	std::string m_path;
	bool m_commPortOpen = false;
	bool m_stopRead = false;
	int m_fileDescriptor = -1;

	uint8_t m_rxMessage[CommsName::MAX_MESSGE_LENGTH];
};

#endif /* COMMS_COMMS_H_ */
