//#include "Alarms.h"
//#include "Externs.h"
//
//StatusType GetAlarmBase(AlarmType AlarmID, AlarmBaseRefType Info) {
//    // Check if the AlarmID is valid
//    if (AlarmID < 0 || AlarmID >= MAX_ALARMS) {
//        return E_OS_ID; // Invalid AlarmID
//    }
//
//    // Copy the alarm base information to the provided Info reference
//    *Info = Alarms[AlarmID].base;
//
//    return E_OK; // Success
//}
//
//
//StatusType GetAlarm(AlarmType AlarmID, TickRefType Tick) {
//    // Check if the AlarmID is valid
//    if (AlarmID < 0 || AlarmID >= MAX_ALARMS) {
//        return E_OS_ID; // Invalid AlarmID
//    }
//
//    // Check if the alarm is in use
//    if (Alarms[AlarmID].base == NULL) {
//        return E_OS_NOFUNC; // Alarm is not used
//    }
//
//    int CurrentTick = GetCurrentTick(); // Replace GetCurrentTick() with the actual function to get the current tick count (HARDWARE)
//    *Tick = Alarms[AlarmID].alarmValue - CurrentTick; // Replace GetCurrentTick() with the actual function to get the current tick count
//
//    return E_OK; // Success
//}
//
//
//StatusType SetRelAlarm(AlarmType AlarmID, TickType increment, TickType cycle) {
//    // Check if the AlarmID is valid
//    if (AlarmID < 0 || AlarmID >= MAX_ALARMS) {
//        return E_OS_ID; // Invalid AlarmID
//    }
//
//    // Check if the alarm is already in use
//    if (Alarms[AlarmID].base != NULL) {
//        return E_OS_STATE; // Alarm is already in use
//    }
//
//    // Check if the increment and cycle values are within admissible limits
//    if (increment < 0 || increment > Alarms[AlarmID].base->maxallowedvalue ||
//        (cycle != 0 && (cycle < Alarms[AlarmID].base->mincycle || cycle > Alarms[AlarmID].base->maxallowedvalue))) {
//        return E_OS_VALUE; // Invalid increment or cycle value
//    }
//
//    // HARDWARE FUNCTION TO CREATE ALARM WITH PARAMETERS
//    // (AlarmID, increment + currentTick, cycle,)
//
//    return E_OK; // Success
//}
//
//StatusType SetAbsAlarm(AlarmType AlarmID, TickType start, TickType cycle) {
//    // Check if the AlarmID is valid
//    if (AlarmID < 0 || AlarmID >= MAX_ALARMS) {
//        return E_OS_ID; // Invalid AlarmID
//    }
//
//    // Check if the alarm is already in use
//    if (Alarms[AlarmID].base != NULL) {
//        return E_OS_STATE; // Alarm is already in use
//    }
//
//    // Check if the start value is within admissible limits
//    if (start < 0 || start > Alarms[AlarmID].base->maxallowedvalue) {
//        return E_OS_VALUE; // Invalid start value
//    }
//
//    // HARDWARE FUNCTION TO CREATE ABSOLUTE ALARM WITH PARAMETERS
//    // (AlarmID, start, cycle)
//
//    return E_OK; // Success
//}
//
//StatusType CancelAlarm(AlarmType AlarmID) {
//    // Check if the AlarmID is valid
//    if (AlarmID < 0 || AlarmID >= MAX_ALARMS) {
//        return E_OS_ID; // Invalid AlarmID
//    }
//
//    // Check if the alarm is not in use
//    if (Alarms[AlarmID].base == NULL) {
//        return E_OS_NOFUNC; // Alarm is not in use
//    }
//
//    // HARDWARE FUNCTION TO CANCEL ALARM
//
//    return E_OK; // Success
//}
