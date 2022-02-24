#include "common.hpp"
#include "logger.hpp"

namespace Logger
{
	void log::logger(Levels level, std::string value)
	{
		std::string out_string;

		auto t = std::time(nullptr);
		auto tm = *std::localtime(&t);

		std::ostringstream oss;
		oss << std::put_time(&tm, "[%d/%m/%Y - %H-%M-%S]");
		auto date = oss.str();
		switch (level)
		{
		case Levels::DEBUG:

			out_string = BLUE;

			break;

		case Levels::FATAL:
			out_string = RED;
			break;

		case Levels::INFO:
			out_string = MAGENTA;
			break;

		case Levels::WARNING:
			out_string = YELLOW;

			break;

		}

		out_string += date + ' ' + value;
		std::cout << out_string;
		std::cout << RESET;
	}
};