#pragma once
#include <string>
#include <cassert>
#include <fstream>

#ifdef _DEBUG
#define INFO_LOG(message)					{ if (kiko::g_logger.Log(kiko::Loglevel::Info, __FILE__, __LINE__))		{ kiko::g_logger << " " << message << "\n"; } }
#define WARNING_LOG(message)				{ if (kiko::g_logger.Log(kiko::Loglevel::Warning, __FILE__, __LINE__))	{ kiko::g_logger << " " << message << "\n"; } }
#define ERROR_LOG(message)					{ if (kiko::g_logger.Log(kiko::Loglevel::Error, __FILE__, __LINE__))	{ kiko::g_logger << " " << message << "\n"; } }
#define ASSERT_LOG(condition, message)		{ if (!condition && kiko::g_logger.Log(kiko::Loglevel::Assert, __FILE__, __LINE__))	{ kiko::g_logger << " " << message << "\n"; } assert(condition); }
#else
#define INFO_LOG(message)					{}
#define WARNING_LOG(message)				{}
#define ERROR_LOG(message)					{}
#define ASSERT_LOG(condition, message)		{}
#endif // debug

namespace kiko {
	enum Loglevel {
		Info,
		Warning,
		Error,
		Assert
	};

	class Logger {
	public:
		Logger(Loglevel logLevel, std::ostream* ostream, const std::string filename = "") :
			m_logLevel{ logLevel },
			m_ostream{ ostream }
		{
			if (!filename.empty()) m_fstream.open(filename);
		};

		bool Log(Loglevel logLevel, const std::string filename, int line);

		template<typename T>
		Logger& operator << (T value);

	private:
		Loglevel m_logLevel;
		std::ostream* m_ostream = nullptr;
		std::ofstream m_fstream;
	};

	extern Logger g_logger;

	template<typename T>
	inline Logger& Logger::operator<<(T value)
	{
		if (m_ostream) *m_ostream << value;
		if (m_fstream.is_open())
		{
			m_fstream << value;
			m_fstream.flush();
		}
		return *this;
	}
}