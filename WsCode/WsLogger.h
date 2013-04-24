//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Wildstang 2009
//  @ File Name : WsLogger.h
//  @ Date : 1/17/2009
//  @ Author : 
//
//


#if !defined(_WSLOGGER_H)
#define _WSLOGGER_H

#include <stdio.h>
#include <inetLib.h>

/* logging severities */
#define LOG_LOW    1
#define LOG_MED    2
#define LOG_HIGH   3
#define LOG_ALWAYS 4

/* logging types */
#define LOG_DRIVE_INPUT 0x00000001
#define LOG_CRAB_INPUT  0x00000002

#define LOG_ALL         0xFFFFFFFF

class WsLogger
{
public:
    virtual ~WsLogger();
    static WsLogger* getInstance();
    void setSeverity(UINT32 severity);
    void setTypeMask(UINT32 type_mask);
    void print(UINT32 severity, UINT32 type, const char* fmt, ...);

protected:
    WsLogger();
    void initSendingSocket();

    UINT32 a_severity;
    UINT32 a_type_mask;

private:
    static WsLogger* ap_instance;
    int a_sockfd;
    struct sockaddr_in a_addr;
    int a_addrlen;
};

#endif  //_WSLOGGER_H
