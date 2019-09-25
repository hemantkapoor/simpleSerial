/*
 * Comms.cpp
 *
 *  Created on: 17 Sep 2019
 *      Author: root
 *
 *      Read https://www.cmrr.umn.edu/~strupp/serial.html#2_5
 */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <thread>
#include <chrono>
#include "../callback/BaseCallback.h"
#include "../../simpleDebug/SimpleDebug.h"
#include "Comms.h"

using namespace SimpleSerialName;

Comms::Comms(const std::string& path):m_path(path)
{
	m_debug = SimpleDebugName::SimpleDebug::instance();
}

Comms::~Comms()
{
	m_debug->log(SimpleDebugName::LOG, std::string(__PRETTY_FUNCTION__) + " : Closing Serial port\r\n");
	if(m_commPortOpen == true)
	{
		m_stopRead = true;
		m_thread->join();
		m_commPortOpen = false;
		close(m_fileDescriptor);
	}
}

bool Comms::startComms()
{
	if(m_commPortOpen == true)
	{
		return true;
	}
	//O_NOCTTY flag tells UNIX that this program doesn't want to be the "controlling terminal" for that port.
	//O_NDELAY flag tells UNIX that this program doesn't care what state the DCD signal line is in
	m_fileDescriptor = open(m_path.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);

	if(m_fileDescriptor == -1)
	{
		m_debug->log(SimpleDebugName::CRITICAL_ERROR, std::string(__PRETTY_FUNCTION__) + " : Error to open serial port");
		return false;
	}

	//FNDELAY option causes the read function to return 0 if no characters are available on the port
	fcntl(m_fileDescriptor, F_SETFL, FNDELAY);

	//If everything works then we start a new thread that will read serial port

	m_debug->log(SimpleDebugName::LOG, std::string(__PRETTY_FUNCTION__) + " : Serial Port " + m_path + " open \r\n");

	termios options;
	tcgetattr(m_fileDescriptor, &options);
	cfsetispeed(&options, B115200);
	cfsetospeed(&options, B115200);

	//Set Data Size
	options.c_cflag &= ~CSIZE; /* Mask the character size bits */
	options.c_cflag |= CS8;    /* Select 8 data bits */

	//No parity (8N1):
	options.c_cflag &= ~PARENB;
	options.c_cflag &= ~CSTOPB;
	options.c_cflag &= ~CSIZE;
	options.c_cflag |= CS8;

	//Disable HW control
	options.c_cflag &= ~CRTSCTS;

	//We expect Raw Data
	options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

	options.c_oflag = 0;                // no remapping, no delays


	/*
	 * Enable the receiver and set local mode...
	 */

	options.c_cflag |= (CLOCAL | CREAD);

	options.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

	/*
	 * Set the new options for the port...
	 */

	tcsetattr(m_fileDescriptor, TCSANOW, &options);

	//Start Receive thread
	m_stopRead = false;
	m_thread = std::make_unique<std::thread>(&SimpleSerialName::Comms::processRead, this);

	m_commPortOpen = true;

	return true;

}

void Comms::processRead()
{
	while(m_stopRead == false)
	{
		//For now just read the data and sleep
		auto nbytes = read(m_fileDescriptor,m_rxMessage,MAX_MESSGE_LENGTH);

		if(nbytes > 0)
		{
			std::vector<uint8_t> serialData;
			std::copy( m_rxMessage, m_rxMessage + nbytes, std::back_inserter(serialData));
			std::lock_guard<std::mutex> guard(m_callBackListMutex);
			//Now perform callback
			for(auto currentIterator : m_callBackList)
			{
				currentIterator->callback(serialData);
			}
		}
		//Read every 500 milliseconds
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}

bool Comms::transmitData(const std::vector<uint8_t> data)
{
	if(m_commPortOpen == false)	{ return false; }
	auto dataWritten = write(m_fileDescriptor,data.data(), data.size());
	if(dataWritten > 0) { return true; }
	return false;
}
