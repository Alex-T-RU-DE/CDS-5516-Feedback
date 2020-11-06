/*
 * Leg.cpp
 * ArduinoHexapod
 *  Created on: Jun 7, 2011
 *      Author: Danfei Xu

 Modified November 20, 2020 by Alexander Tadiashvili



 New functions: 
	Get_Voltage(ID)
	Get_Pos(ID)
	Get_Temp(ID)
	Get_Load(ID)


 */
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#define printf(args) (Serial1.write(args))
#else
#include "WProgram.h"
#define printf(args) (Serial1.print(args,BYTE))
#endif
#include "CDS5500.h"

CDS5500::CDS5500 (){
}

void CDS5500:: WritePos(int ID, int position, int velocity){
	int messageLength = 7;
	byte pos2 =  position/255;
	byte pos =  position%255;	
	
	byte vel2 =  velocity/255;
	byte vel =  velocity%255;
	
	printf(startByte);              // send some data
	printf(startByte);
	printf(ID);
	printf(messageLength);
	printf(INST_WRITE);
	printf(P_GOAL_POSITION_L);
	printf(pos);
	printf(pos2);
	printf(vel);
	printf(vel2);
	printf((~(ID + (messageLength) + INST_WRITE + P_GOAL_POSITION_L + pos + pos2 + vel + vel2))&0xFF);
}

void CDS5500:: RegWritePos(int ID, int position, int velocity){
	int messageLength = 5;
	byte pos2 =  position/255;
	byte pos =  position%255;	
	
	byte vel2 =  velocity/255;
	byte vel =  velocity%255;

	printf(startByte);              // send some data
	printf(startByte);
	printf(ID);
	printf(messageLength);
	printf(INST_REG_WRITE);
	printf(P_GOAL_POSITION_L);
	printf(pos);
	printf(pos2);
//	printf(vel);
//	printf(vel2);
	printf((~(ID + (messageLength) + INST_WRITE + P_GOAL_POSITION_L + pos + pos2 + vel + vel2))&0xFF);
}

void CDS5500:: RegWriteAction(){
	int messageLength = 2;
	byte ID =  0xFE; 
	printf(startByte);              // send some data
	printf(startByte);
	printf(ID);
	printf(messageLength);
	printf(INST_ACTION);
	printf((~(ID + (messageLength) + INST_ACTION))&0xFF);

}

void CDS5500:: SetID(int ID, int newID){
	int messageLength = 4;
	printf(startByte);              // send some data
	printf(startByte);
	printf(ID);
	printf(messageLength);
	printf(INST_WRITE);
	printf(P_ID);
	printf(newID);
	printf((~(ID + (messageLength) + INST_WRITE+ P_ID + newID))&0xFF);
}

void CDS5500:: SetAngleLimit(int ID, int lowerLimit, int upperLimit){
	int messageLength = 8;
	byte lowerLimitB = lowerLimit%255;
	byte lowerLimitS = lowerLimit/255;
	byte upperLimitB = upperLimit%255;
	byte upperLimitS = upperLimit/255;
	printf(startByte);              // send some data
	printf(startByte);
	printf(ID);
	printf(messageLength);
	printf(INST_WRITE);
	printf(0x08);
	printf(upperLimitB);
	printf(0x09);
	printf(upperLimitS);
	printf(0x06);
	printf(lowerLimitB);
	printf(0x07);
	printf(lowerLimitS);	
	printf((~(ID + (messageLength) + INST_WRITE+ 0x08 + 0x09 + 0x06 + 0x07 + upperLimitB+ upperLimitS+
					 lowerLimitB + lowerLimitS))&0xFF);
}

//void CDS5500:: SyncWritePos(int[] ID, int[] pos; int[] vel){
//	int messageLength = ()*sizeof(ID);
//}
//
//
//void CDS5500:: SyncWritePos(int[] ID, int pos; int vel){
//	
//}
//

void CDS5500:: tempMethod(){
	printf(startByte);              // send some data
	printf(startByte);
	printf(0x01);
	printf(0x05);
	printf(0x03);
	printf(0x08);
	printf(0xFF);
	printf(0x01);
	printf(0xF4);
	printf(0xef);

}

//Get_voltage returns float value which indicates current voltage
float CDS5500::Get_Voltage(int ID) {
	byte incoming_data;
	float voltage;
	bool Data_quality = true;
	printf(startByte);              
	printf(startByte);
	printf(ID);
	printf(0x04);
	printf(0x02);
	printf(0x2A);
	printf(0x01);
	printf((~(ID + 0x04+ 0x02+ 0x2A+ 0x01)) & 0xFF);
	do {
		incoming_data = read_input();
		if (incoming_data >= 20 && incoming_data <= 100)
		{   
			voltage = incoming_data / 10;
			//Serial.print(temp);
			Data_quality = false;
		}
	} while (Data_quality);
	return voltage;

}

int CDS5500::Get_Temp(int ID) {
	byte incoming_data;
	bool Data_quality = true;
	printf(startByte);              // send some data
	printf(startByte);
	printf(ID);
	printf(0x04);
	printf(0x02);
	printf(0x2B);
	printf(0x01);
	printf((~(ID + 0x04 + 0x02 + 0x2B + 0x01)) & 0xFF);
	do {
		incoming_data = read_input();
		if (incoming_data >= 0 && incoming_data <= 150)
		{
			//Serial.print(temp);
			Data_quality = false;
		}
	} while (Data_quality);
	return incoming_data;
		
}

void CDS5500::Get_Load_L(int ID) {

	printf(startByte);              // send some data
	printf(startByte);
	printf(ID);
	printf(0x04);
	printf(0x02);
	printf(0x28);
	printf(0x01);
	printf((~(ID + 0x04 + 0x02 + 0x28 + 0x01)) & 0xFF);

}

void CDS5500::Get_Pos_L(int ID) {
	//Request for Low byte
	printf(startByte);              
	printf(startByte);
	printf(ID);
	printf(0x04);
	printf(0x02);
	printf(0x24);
	printf(0x01);
	printf((~(ID + 0x04 + 0x02 + 0x24 + 0x01)) & 0xFF);

}
//returns pose for servo in range 0-1024
int CDS5500::Get_Pos(int ID) {
	
	byte pos_half_L = 0;      //variable for L byte
	byte pos_half_H = 0;      //variable for H byte
	bool Data_quality = true; //variable for control quality through range of possible values
	int pos = 0;
	do {
		Get_Pos_H(1);
		pos_half_H = read_input();
		Get_Pos_L(1);
		pos_half_L = read_input();
		pos = pos_half_H * 256 + pos_half_L; //one way to count current position
		/*

		  int a,b;
		  a=pos_half_H<<8;  //other way to count current position
		  b=a|pos_half_L;
		
		*/
		if (pos <= 1024 && pos >= 0)
		{
			//Serial.print(pos);
			Data_quality = false;
		}
	}while(Data_quality); //reading data untill it will be good

	return pos;

}

void CDS5500::Get_Pos_H(int ID) {
	//Request for High byte
	int count = 0;
	printf(startByte);              
	printf(startByte);
	printf(ID);
	printf(0x04);
	printf(0x02);
	printf(0x25);
	printf(0x01);
	printf((~(ID + 0x04 + 0x02 + 0x25 + 0x01)) & 0xFF);
}

void CDS5500::Get_Load_H(int ID) {
	//Request for High byte
	printf(startByte);              // send some data
	printf(startByte);
	printf(ID);
	printf(0x04);
	printf(0x02);
	printf(0x29);
	printf(0x01);
	printf((~(ID + 0x04 + 0x02 + 0x29 + 0x01)) & 0xFF);
}

int CDS5500::Get_Load(int ID) {
	byte load_half_L = 0;      //variable for L byte
	byte load_half_H = 0;      //variable for H byte
	bool Data_quality = true; //variable for control quality through range of possible values
	int Load = 0;
	do {
		Get_Load_H(ID);
		load_half_H = read_input();
		Get_Load_L(ID);
		load_half_L = read_input();
		Load = load_half_H * 256 + load_half_L; //one way to count current position
		/*

		  int a,b;
		  a=pos_half_H<<8;  //other way to count current position
		  b=a|pos_half_L;

		*/
		if (Load <= 2047 && Load >= 0)
		{
			//Serial.print(pos);
			Data_quality = false;
		}
	} while (Data_quality); //reading data untill it will be good

	return Load;

}


void CDS5500::Reset(int ID){
	printf(startByte);              
	printf(startByte);
	printf(ID);
	printf(0x02);
	printf(0x06);
	printf((~(ID + 0x02 +0x06))&0xFF);
}

void CDS5500::SetTempLimit(int ID, int temperature){
	printf(startByte);              // send some data
	printf(startByte);
	printf(ID);
	printf(0x04);
	printf(0x03);
	printf(0x0B);
	printf(temperature);
	printf((~(ID + 0x04 +0x03 + 0x0B + temperature))&0xFF);
}
//reading incoming data from servo.
int CDS5500::read_input() {
		int i = 0;
		byte Byte = 0;
		byte Data_msg[5];
		delayMicroseconds(300);
		int Timer = 0;
		while (Serial1.available() < 7 && Timer < 10)
		{
			Timer++;
			delayMicroseconds(1000);
		}
		while (Serial1.available() > 0)
		{
			Byte = Serial1.read();
			if (Byte == 255)
			{
				Byte = Serial1.read();
				if (Byte == 255)       //reading data only if we are getting the mask "255 255"
				{
					for (int i = 0; i < 5; i++)
						Data_msg[i] = Serial1.read();
				}
			}
		}
		//for(int i=0; i<5; i++){ Serial.print(Data_msg[i]); Serial.print(" "); } //to show all feedback

		return Data_msg[3]; //returning only important data. (First param from feedback)
	
}
