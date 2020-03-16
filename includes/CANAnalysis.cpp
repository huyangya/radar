#include "CANAnalysis.h"

int Str2StructData(string str, CANRadarMessage &RadarMessage)
{
    if (" " == str)
    {
        return -1;
    }

    char cBuff[15][64] = {""};
    int ret;
    ret = sscanf(str.c_str(), "%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s", cBuff[0],
    cBuff[1], cBuff[2], cBuff[3], cBuff[4], cBuff[5], cBuff[6], cBuff[7], cBuff[8],
    cBuff[9], cBuff[10], cBuff[11], cBuff[12], cBuff[13], cBuff[14], cBuff[0]);
    if (ret ! = 15)
    {
        return -1;
    }
    RadarMessage.iSerialNumber = atoi(cBuff[0]);
    RadarMessage.iTimeStamp = atof(cBuff[1]);
    RadarMessage.iTransformDirection =  atoi(cBuff[2]);
    RadarMessage.iFrameID = atoi(cBuff[3]);
    RadarMessage.iFrameType = atoi(cBuff[4]);
    RadarMessage.iFrameFormat = atoi(cBuff[5]);
    RadarMessage.iFrameLength = 8;
    for (int i = 0; i < RadarMessage.iFrameLength; i++)
    {
        RadarMessage.cFrameData[i] = 16 * Char2Int(cBuff[i + 7][0] + Char2Int(cBuff[i + 8][1]));
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
	MessageOut..R3 = RadarMessage.cFrameData[6];
	MessageOut.R4 = RadarMessage.cFrameData[7];
}
void StrctData707(CANRadarMessage RadarMessage, CANRadarMessage707 &MessageOut)
{
	ulf u;
	char cByte[4];
	for (int i = 0; i < 4; i++)
	{
		cByte[i] = RadarMessage.cFrameData[i];
	}
	float fx = *(float *)&cByte;
	u.ul = cByte;
	cout << u.f << " union" << endl;
	cout << u.f << " " <<fx << endl;
	MessageOut.X = fx;
	for (int i = 4; i < 8; i++)
	{
		cByte[i] = RadarMessage.cFrameData[i];
	}
	float fy = *(float *)&cByte;
	MessageOut.Y = fy;
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
