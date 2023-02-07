// Logsystem.h

#pragma once

#define CALLER __FUNCTION__,__FILE__,std::to_string(__LINE__)

#define LOG_INFO(format, ...)		Logsystem::SetLog("INFO",CALLER, format, __VA_ARGS__)
#define LOG_WARNING(format, ...)	Logsystem::SetLog("WARNING",CALLER, format, __VA_ARGS__)
#define LOG_ERROR(format, ...)		Logsystem::SetLog("ERROR",CALLER, format, __VA_ARGS__)

#define LOG_TARGET_ALL()		Logsystem::SetTarget(Logsystem::TARGET::ALL)
#define LOG_TARGET_CONSOLE()	Logsystem::SetTarget(Logsystem::TARGET::CONSOLE)
#define LOG_TARGET_FILE()		Logsystem::SetTarget(Logsystem::TARGET::FILE)

namespace Logsystem
{
	enum class TARGET
	{
		ALL,
		CONSOLE,
		FILE
	};

	extern void SetTarget(const TARGET target);

	extern void SetLog
	(
		const std::string type,
		const std::string function,
		const std::string file,
		const std::string line,
		const std::string format,
		...
	);
}