#pragma once
#ifndef _CANANALYSIS_H_
#define _CANANALYSIS_H_

#include <stdio.h>
#include <tchar.h>
#include <math.h>
#include <string>
using namespace std;

const int  RADAR_FR = 0x00000739;
const int  RADAR_LR = 0x00000736;
const int  POSITION = 0x00000707;
const int  CAR_ANGLE = 0x00000701;
const int WAIT_TIME = 4000;

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;

typedef union WtoB
{
    unsigned short w;
    BYTE b[2];
}wtob;

union ulf
{
	unsigned long ul;
	float f;
};

typedef struct _CANRadarMessage
{
    int iSerialNumber = 0;
    float fTimeStamp = 0;
    int iTransformDirection = 0; // 0 接受； 1 发送
    int iFrameID = 0;
    int iFrameType = 0; // 0 标准帧； 1 扩展帧
    int iFrameFormat = 0; // 0 数据帧； 1 远程帧
    int iFrameLength = 0x08;
    char cFrameData[8] = {0};
}CANRadarMessage;

typedef struct _CANRadarMessage739
{
    int F1 = 0;
    int F2 = 0;
    int F3 = 0;
    int F4 = 0;
    int R1 = 0;
    int R2 = 0;
    int R3 = 0;
    int R4 = 0;
}CANRadarMessage739;

typedef struct _CANRadarMessage736
{
    int FL = 0;
    int FR = 0;
    int RL = 0;
    int RR = 0;
}CANRadarMessage736;

typedef struct _CANRadarMessage707
{
    float X = 0.0;
    float Y = 0.0;
}CANRadarMessage707;

typedef struct _CANRadarMessage701
{
    float Angle = 0.0;
}CANRadarMessage701;

int Str2StructData(string str, CANRadarMessage &RadarMessage);

int Char2Int (char c);

void StrctData736(CANRadarMessage RadarMessage, CANRadarMessage736 &MessageOut);
void StrctData739(CANRadarMessage RadarMessage, CANRadarMessage739 &MessageOut);
void StrctData707(CANRadarMessage RadarMessage, CANRadarMessage707 &MessageOut);
void StrctData701(CANRadarMessage RadarMessage, CANRadarMessage701 &MessageOut);

//void StructValueTransformFR(CANRadarMessage739 &RadarMessage739);
//void StructValueTransformLR(CANRadarMessage736 &RadarMessage736);
//
//void StructValueTransformPO(CANRadarMessage707 &RadarMessage707);
//void StructValueTransformAN(CANRadarMessage701 &RadarMessage701);

int Str2StructData(string str, CANRadarMessage &RadarMessage)
{
	if (" " == str)
	{
		return -1;
	}

	char cBuff[15][64] = { "" };
	int ret;
	ret = sscanf(str.c_str(), "%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s", cBuff[0],
		cBuff[1], cBuff[2], cBuff[3], cBuff[4], cBuff[5], cBuff[6], cBuff[7], cBuff[8],
		cBuff[9], cBuff[10], cBuff[11], cBuff[12], cBuff[13], cBuff[14]);
	if (ret != 15)
	{
		return -1;
	}
	RadarMessage.iSerialNumber = atoi(cBuff[0]);
	RadarMessage.fTimeStamp = atof(cBuff[1]);
	RadarMessage.iTransformDirection = atoi(cBuff[2]);
	RadarMessage.iFrameID = 256 * Char2Int(cBuff[3][7]) + 16 * Char2Int(cBuff[3][8]) + Char2Int(cBuff[3][9]);//atoi(cBuff[3]);
	RadarMessage.iFrameType = atoi(cBuff[4]);
	RadarMessage.iFrameFormat = atoi(cBuff[5]);
	RadarMessage.iFrameLength = 8;
	for (int i = 0; i < RadarMessage.iFrameLength; i++)
	{
		RadarMessage.cFrameData[i] = cBuff[7 + i][1] + cBuff[7 + i][2];
	}

	return 0;
}

int Char2Int(char c)
{
	int b = 0;

	if (c >= '0' && c <= '9')
	{
		return b = c - '0';
	}
	if (c >= 'a' && c <= 'f')
	{
		return b = c - 'a' + 10;
	}
	if (c >= 'A' && c <= 'F')
	{
		return b = c - 'A' + 10;
	}

	return -1;
}

// typedef struct _CANRadarMessage739
// {
//     int ID = 0;
//     int F1 = 0;
//     int F2 = 0;
//     int F3 = 0;
//     int F4 = 0;
//     int R1 = 0;
//     int R2 = 0;
//     int R3 = 0;
//     int R4 = 0;
// }CANRadarMessage739;
// typedef struct _CANRadarMessage736
// {
//     int ID = 0;
//     int FL = 0;
//     int FR = 0;
//     int RL = 0;
//     int RR = 0;
// }CANRadarMessage736;
void StrctData736(CANRadarMessage RadarMessage, CANRadarMessage736 &MessageOut)
{
	wtob wb;
	MessageOut = {};
	wb.b[0] = RadarMessage.cFrameData[0];
	wb.b[1] = RadarMessage.cFrameData[1];
	MessageOut.FL = wb.w;
	wb.b[0] = RadarMessage.cFrameData[2];
	wb.b[1] = RadarMessage.cFrameData[3];
	MessageOut.FR = wb.w;
	wb.b[0] = RadarMessage.cFrameData[4];
	wb.b[1] = RadarMessage.cFrameData[5];
	MessageOut.RL = wb.w;
	wb.b[0] = RadarMessage.cFrameData[6];
	wb.b[1] = RadarMessage.cFrameData[7];
	MessageOut.RR = wb.w;
}
void StrctData739(CANRadarMessage RadarMessage, CANRadarMessage739 &MessageOut)
{
	MessageOut.F1 = RadarMessage.cFrameData[0];
	MessageOut.F2 = RadarMessage.cFrameData[1];
	MessageOut.F3 = RadarMessage.cFrameData[2];
	MessageOut.F4 = RadarMessage.cFrameData[3];
	MessageOut.R1 = RadarMessage.cFrameData[4];
	MessageOut.R2 = RadarMessage.cFrameData[5];
	MessageOut.R3 = RadarMessage.cFrameData[6];
	MessageOut.R4 = RadarMessage.cFrameData[7];
}
void StrctData707(CANRadarMessage RadarMessage, CANRadarMessage707 &MessageOut)
{
	char cByte[4];
	for (int i = 0; i < 4; i++)
	{
		cByte[i] = RadarMessage.cFrameData[i];
	}
	float fx = *(float *)&cByte;
	MessageOut.X = fx;
	cByte[0] = RadarMessage.cFrameData[4];
	cByte[1] = RadarMessage.cFrameData[5];
	cByte[2] = RadarMessage.cFrameData[6];
	cByte[3] = RadarMessage.cFrameData[7];
	MessageOut.Y = *(float *)&cByte;
}
void StrctData701(CANRadarMessage RadarMessage, CANRadarMessage701 &MessageOut)
{
	char cByte[4];

	for (int i = 4; i < 8; i++)
	{
		cByte[i] = RadarMessage.cFrameData[i];
	}
	float f = *(float *)&cByte;
	MessageOut.Angle = f;
}
#endif