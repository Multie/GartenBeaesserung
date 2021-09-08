#ifndef L_TIME_H
#define L_TIME_H

#include <WiFi.h>
#include "time.h"
#include "L_debug.h"
#include "L_data.h"
#include "L_connect.h"


const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 0;
const int daylightOffset_sec = 3600;

String toStringTime(tm *time) {
    char buffer[30];
    // 00:00:00 00:00:0000
    sprintf(buffer, "%02d:%02d:%02d %02d.%02d.%04d", time->tm_hour, time->tm_min, time->tm_sec, time->tm_mday, time->tm_mon+1, time->tm_year);
    return String(buffer);
}

void addTime(tm *time, int sec=0,int min=0, int hour=0, int day=0,int mon=0,int year=0) {

    if (time->tm_year > 1900) {
        time->tm_year -= 1900;
    }
    //Debug("addTime","input",toStringTime(time));
    unsigned long timeSec = 0;
    timeSec += time->tm_sec;
    timeSec += time->tm_min  *       60;
    timeSec += time->tm_hour *     3600;
    timeSec += time->tm_mday *    86400;
    timeSec += time->tm_mon  *  2628000;
    timeSec += time->tm_year * 31556952;
    //Debug("addTime","time",String(timeSec));
    unsigned long timeAddSec = 0;
    timeAddSec += sec;
    timeAddSec += min  *       60;
    timeAddSec += hour *     3600;
    timeAddSec += day  *    86400;
    timeAddSec += mon  *  2628000;
    timeAddSec += year * 31556952;
   // Debug("addTime","addition",String(timeAddSec));
    timeSec+= timeAddSec;
    //Debug("addTime","added",String(timeSec));
    // Year
    int count = (int)floor(timeSec / 31556952);
    time->tm_year = count;
    timeSec -= count*31556952;
    // Mon
    count = (int)floor(timeSec / 2628000);
    time->tm_mon = count;
    timeSec -= count*2628000;
    // day
    count = (int)floor(timeSec / 86400);
    time->tm_mday = count;
    timeSec -= count*86400;
    // Hour
    count = (int)floor(timeSec / 3600);
    time->tm_hour = count;
    timeSec -= count*3600;
    // Min
    count = (int)floor(timeSec / 60);
    time->tm_min = count;
    timeSec -= count*60;
    // Sec
    time->tm_sec = (int)timeSec;
    //Debug("addTime","restult",toStringTime(time));
    if (time->tm_year < 1900) {
        time->tm_year += 1900;
    }
   
}   

void getCurrentTime(tm *time) {
    getLocalTime(time);
    if (time->tm_year < 1900) {
        time->tm_year += 1900;
    }
    if (time->tm_isdst) {
        addTime(time,0,0,1,0,0,0);
    }
}

struct tm timediff(tm *time1, tm *time2)
{
    tm diff;
    diff.tm_year = time1->tm_year - time2->tm_year;
    diff.tm_sec = time1->tm_year - time2->tm_year;
    diff.tm_min = time1->tm_min - time2->tm_min;
    diff.tm_hour = time1->tm_hour - time2->tm_hour;
    diff.tm_mday = time1->tm_mday - time2->tm_mday;
    diff.tm_mon = time1->tm_mon - time2->tm_mon;
    diff.tm_year = time1->tm_year - time2->tm_year;
    diff.tm_wday = time1->tm_wday - time2->tm_wday;
    diff.tm_yday = time1->tm_yday - time2->tm_yday;
    return diff;
}

bool isTimeGreatertime(tm *time1, tm *time2,bool ovYear=false,bool ovMon=false,bool ovDay=false,bool ovHour=false,bool ovMin=false,bool ovSec=false)
{
    if (time1->tm_year == time2->tm_year || ovYear)
    {
        if (time1->tm_mon == time2->tm_mon || ovMon)
        {
            if (time1->tm_mday == time2->tm_mday || ovDay)
            {
                if (time1->tm_hour == time2->tm_hour || ovHour)
                {
                    if (time1->tm_min == time2->tm_min || ovMin)
                    {
                        if (time1->tm_sec > time2->tm_sec || ovSec)
                        {
                            return true;
                        }
                        else
                        {
                            return false;
                        }
                    }
                    else if (time1->tm_min > time2->tm_min)
                    {
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
                else if (time1->tm_hour > time2->tm_hour)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else if (time1->tm_mday > time2->tm_mday)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else if (time1->tm_mon > time2->tm_mon)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (time1->tm_year > time2->tm_year)
    {
        return true;
    }
    else
    {
        return false;
    }
}


void copyTimeToTime(tm *copy,tm *paste) {
     paste->tm_year = copy->tm_year;
    paste->tm_sec = copy->tm_sec;
    paste->tm_min = copy->tm_min;
    paste->tm_hour = copy->tm_hour;
    paste->tm_mday = copy->tm_mday;
    paste->tm_mon = copy->tm_mon;
    paste->tm_year = copy->tm_year;
    paste->tm_wday = copy->tm_wday;
    paste->tm_yday = copy->tm_yday;
} 

void SyncTime()
{
    connectWifi();
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    getCurrentTime(&currentIrrigationData.Time);
    copyTimeToTime(&currentIrrigationData.Time, &currentIrrigationData.nextTimeSync);
    addTime(&currentIrrigationData.nextTimeSync,0,0,0,1,0,0);
    Debug("Time", "Sync", "complete");
}

void SetupTime()
{
    SyncTime();
    Debug("Time", "Setup", "complete");
}

void LoopTime()
{
    getCurrentTime(&currentIrrigationData.Time);
    if (isTimeGreatertime(&(currentIrrigationData.Time),&(currentIrrigationData.nextTimeSync))) {
        SyncTime();
    }
}


// bool getLocalTime(struct tm);
/*
    struct tm
    {
        int	tm_sec; // seconds after the minute	 (0-59(60)) 
        int	tm_min; // minutes after the hour (0-59)
        int	tm_hour; // hours since midnight (0-23)
        int	tm_mday; // day of the month (1-31)
        int	tm_mon; // months since January (0-11)
        int	tm_year; // years since 1900
        int	tm_wday; // days since Sunday (0-6)
        int	tm_yday; // days since January 1 (0-365)
        int	tm_isdst; // Daylight Saving Time flag
    };
*/

#endif