/*
 * File: time_support.h
 * Copyright (c) 2023 Loupe
 * https://loupe.team
 * 
 * This file is part of OMBSON, licensed under the MIT License.
 * 
 */

#pragma once 

#include "status_with.h"
#include "cstdint.h"
#include "string_data.h"
#if defined(__GNUC__) && (__GNUC__ > 5)
#include <ctime>
#endif
namespace _bson { 

    struct Date_t {
        // TODO: make signed (and look for related TODO's)
        unsigned long long millis;
        Date_t(): millis(0) {}
        Date_t(unsigned long long m): millis(m) {}
        operator unsigned long long&() { return millis; }
        operator const unsigned long long&() const { return millis; }
        std::string toString() const;
        time_t toTimeT() const;
        int64_t asInt64() const {
            return static_cast<int64_t>(millis);
        }
    };

    StatusWith<Date_t> dateFromISOString(const StringData& dateString);

	//#if defined BOOST_CHRONO_INTERNAL_TIMEGM
	
	inline int32_t is_leap(int32_t year)
	{
		if(year % 400 == 0)
			return 1;
		if(year % 100 == 0)
			return 0;
		if(year % 4 == 0)
			return 1;
		return 0;
	}
	inline int32_t days_from_0(int32_t year)
	{
		year--;
		return 365 * year + (year / 400) - (year/100) + (year / 4);
	}
	inline int32_t days_from_1970(int32_t year)
	{
		static const int days_from_0_to_1970 = days_from_0(1970);
		return days_from_0(year) - days_from_0_to_1970;
	}
	inline int32_t days_from_1jan(int32_t year,int32_t month,int32_t day)
	{
		static const int32_t days[2][12] =
			{
			{ 0,31,59,90,120,151,181,212,243,273,304,334},
			{ 0,31,60,91,121,152,182,213,244,274,305,335}
			};
	
		return days[is_leap(year)][month-1] + day - 1;
	}
	
	inline time_t timegm(std::tm const *t)
	{
		int year = t->tm_year + 1900;
		int month = t->tm_mon;
		if(month > 11)
		{
			year += month/12;
			month %= 12;
		}
		else if(month < 0)
		{
			int years_diff = (-month + 11)/12;
			year -= years_diff;
			month+=12 * years_diff;
		}
		month++;
		int day = t->tm_mday;
		int day_of_year = days_from_1jan(year,month,day);
		int days_since_epoch = days_from_1970(year) + day_of_year ;
	
		time_t seconds_in_day = 3600 * 24;
		time_t result = seconds_in_day * days_since_epoch + 3600 * t->tm_hour + 60 * t->tm_min + t->tm_sec;
	
		return result;
	}
	//#endif

}
