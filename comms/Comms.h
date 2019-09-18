/*
 * Comms.h
 *
 *  Created on: 17 Sep 2019
 *      Author: root
 */

#ifndef COMMS_COMMS_H_
#define COMMS_COMMS_H_

#include <string>
#include <memory>
#include <vector>
#include <algorithm>
#include <stdint.h>

namespace SimpleSerialName
{
	const uint32_t MAX_MESSGE_LENGTH = 500;

class BaseCallback;

class Comms
{
public:
	Comms() = delete;
	Comms(const std::string& path);
	virtual ~Comms();

	bool startComms();
	void processRead();
	bool transmitData(std::vector<uint8_t>& data);
	void stopRead() { m_stopRead = true; }
	void addCallback(std::shared_ptr<BaseCallback> newCallBack) { m_callBackList.push_back(newCallBack);}
	void removeCallback(std::shared_ptr<BaseCallback> newCallBack)
	{
		m_callBackList.erase(std::remove(begin(m_callBackList), end(m_callBackList), newCallBack), end(m_callBackList));
	}

private:
	std::string m_path;
	bool m_commPortOpen = false;
	bool m_stopRead = false;
	int m_fileDescriptor = -1;

	uint8_t m_rxMessage[MAX_MESSGE_LENGTH];
	std::vector<std::shared_ptr<BaseCallback>> m_callBackList;
};

};//End of namespace

#endif /* COMMS_COMMS_H_ */
