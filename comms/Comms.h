/*
 * Comms.h
 *
 *  Created on: 17 Sep 2019
 *      Author: root
 */

#ifndef COMMS_COMMS_H_
#define COMMS_COMMS_H_

#include <stdint.h>
#include <string>
#include <memory>
#include <vector>
#include <algorithm>
#include <mutex>

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
	bool transmitData(std::vector<uint8_t>& data);
	void addCallback(std::shared_ptr<BaseCallback> newCallBack)
	{
		std::lock_guard<std::mutex> guard(m_callBackListMutex);
		m_callBackList.push_back(newCallBack);
	}
	void removeCallback(std::shared_ptr<BaseCallback> newCallBack)
	{
		std::lock_guard<std::mutex> guard(m_callBackListMutex);
		m_callBackList.erase(std::remove(begin(m_callBackList), end(m_callBackList), newCallBack), end(m_callBackList));
	}

private:
	std::string m_path;
	bool m_commPortOpen = false;
	bool m_stopRead = false;
	int m_fileDescriptor = -1;
	void processRead();

	uint8_t m_rxMessage[MAX_MESSGE_LENGTH];
	std::vector<std::shared_ptr<BaseCallback>> m_callBackList;
	std::mutex m_callBackListMutex;
	std::unique_ptr<std::thread> m_thread;
};

};//End of namespace

#endif /* COMMS_COMMS_H_ */
