#pragma once
#include <string>
#include <time.h>

struct Timetable
{
	std::string ServerName;

	tm StartTime;
	tm EndTime;

	Timetable(string server)
	{
		ServerName = server;
		StartTime.tm_hour = 0;
		StartTime.tm_min = 0;
		EndTime.tm_hour = 24;
		EndTime.tm_min = 59;
	}

	bool IsInTimePeriod()
	{
		__time64_t long_time;
		_time64(&long_time);
		tm ltm;
		localtime_s(&ltm, &long_time);

		int startmins = StartTime.tm_hour * 60 + StartTime.tm_min;
		int endmins = EndTime.tm_hour * 60 + EndTime.tm_min;
		int currmins = ltm.tm_hour * 60 + ltm.tm_min;


		return ((startmins <= currmins) && (currmins <= endmins));
	}
};
