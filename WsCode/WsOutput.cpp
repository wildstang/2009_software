//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : WildStang 2009
//  @ File Name : WsOutput.cpp
//  @ Date : 1/24/2009
//  @ Author : 
//
//


#include "WsOutput.h"

WsOutput::WsOutput()
{
    setEnabled(true);
    setDebug(false);
}

WsOutput::~WsOutput()
{
}

void WsOutput::setEnabled(bool enable)
{
    a_enabled = enable;
}

void WsOutput::setDebug(bool debug)
{
    a_debug = debug;
}
