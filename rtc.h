/*****************************************************************************
 *   rtc.h
******************************************************************************/
#ifndef __RTC_H 
#define __RTC_H

#if     RTC_EN
typedef struct {
    uint32 RTC_Sec;     /* 秒 - [0,59] */
    uint32 RTC_Min;     /* 分 - [0,59] */
    uint32 RTC_Hour;    /* 小时 - [0,23] */
    uint32 RTC_Mday;    /* 当月天数- [1,31] */
    uint32 RTC_Mon;     /* 月 - [1,12] */
    uint32 RTC_Year;    /* 年 - [0,4095] */
    uint32 RTC_Wday;    /* 星期- [0,6] */
    uint32 RTC_Yday;    /* 当年天数 - [1,365] */
} RTCTime;

#define IMSEC		0x00000001
#define IMMIN		0x00000002
#define IMHOUR		0x00000004
#define IMDOM		0x00000008
#define IMDOW		0x00000010
#define IMDOY		0x00000020
#define IMMON		0x00000040
#define IMYEAR		0x00000080

#define AMRSEC		0x00000001  /* 闹铃秒屏蔽 */
#define AMRMIN		0x00000002  /* 屏蔽闹铃分*/
#define AMRHOUR		0x00000004  /* 闹铃小时屏蔽 */
#define AMRDOM		0x00000008  /* 屏蔽天*/
#define AMRDOW		0x00000010  /*星期奥领屏蔽*/
#define AMRDOY		0x00000020  /* 屏蔽当年天*/
#define AMRMON		0x00000040  /* 月屏蔽*/
#define AMRYEAR		0x00000080  /* 屏蔽 */

#define PREINT_RTC	0x000001C8  /* 分频整数部分,PCLK = 15Mhz */
#define PREFRAC_RTC	0x000061C0  /* 分频小数部分 PCLK = 15Mhz */
#define ILR_RTCCIF	0x01
#define ILR_RTCALF	0x02

#define CCR_CLKEN	0x01
#define CCR_CTCRST	0x02
#define CCR_CLKSRC	0x10

extern void RTCHandler (void) __irq;
extern void RTCInit( void );
extern void RTCStart( void );
extern void RTCStop( void );
extern void RTC_CTCReset( void );
extern void RTCSetTime( RTCTime );
extern RTCTime RTCGetTime( void );
extern void RTCSetAlarm( RTCTime );
extern void RTCSetAlarmMask( uint32 AlarmMask );

#endif

#endif 
/*****************************************************************************
**                            End Of File
******************************************************************************/
