#include "Logger.h"
#include "FileIO.h"
#include <iostream>

namespace kiko {

	bool kiko::Logger::Log(Loglevel logLevel, const std::string filename, int line)
	{
		if (logLevel < m_logLevel) return false;
		switch (logLevel)
		{
		case kiko::Info:
			*this << "INFO: ";
			break;
		case kiko::Warning:
			*this << "WARNING: ";
			break;
		case kiko::Error:
			*this << "ERROR: ";
			break;
		case kiko::Assert:
			*this << "ASSERT: ";
			break;
		default:
			break;
		}

		*this << getFileName(filename) << "(" << line << ")";

		return true;
	}
}