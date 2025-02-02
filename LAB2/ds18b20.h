#ifndef DS18B20_H_
#define DS18B20_H_
//--------------------------------------------------
#include "stm32f10x.h"
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
//--------------------------------------------------
#define SKIP_ROM 						0xCC
#define ROM_SEARCH 					0xF0
#define WRITE_SCRATCHPAD		0x4E
#define READ_SCRATCHPAD 		0xBE
#define CONVERT_TEMP				0x44
#define MATCH_CODE					0x55
#define READ_ROM						0x33
#define COPY_SCRATCHPAD			0x48
#define RECALL_E						0xB8

//--------------------------------------------------
#define RESOLUTION_9BIT  0x1F
#define RESOLUTION_10BIT 0x3F
#define RESOLUTION_11BIT 0x5F
#define RESOLUTION_12BIT 0x7F
//--------------------------------------------------

void ds18b20_PortInit(void);
void ds18b20_Init(uint8_t mode, uint8_t*);
void ds18b20_ConvertTemp(uint8_t mode, uint8_t* address);
void ds18b20_ReadStratchpad(uint8_t mode, uint8_t *Data, uint8_t* address);
void ds18b20_MatchRom(uint8_t* address);
void DelayMicro(__IO uint32_t micros);
uint8_t ds18b20_Reset(void);
uint8_t Compute_CRC8 (uint8_t* data, uint8_t length);

typedef struct
{
    uint8_t ROM_code[8];    										// 64 bit ROM code
		uint8_t scratchpad_data[9] ; 								// scratchpad data
		int16_t raw_temp;														// 16 bit measured temp
		float temp; 																// converted to float temp
		uint8_t crc8_rom; 													// ROM code crc
		uint8_t crc8_data;													// scratchpad data crc
		uint8_t crc8_rom_error; 										// ROM crc error signal
		uint8_t crc8_data_error; 										// scratchpad data crc error signal
		uint8_t TH;
		uint8_t TL;
} Sensor;
//--------------------------------------------------
#endif /* DS18B20_H_ */
uint8_t Search_ROM(char command, Sensor *sensors);
void WriteTHTL(Sensor* s);
void ChangeACP(Sensor* s, uint8_t ACP);
void CopyScratchpad(Sensor* s, uint8_t mode);
void WriteScratchpad(Sensor* s, uint8_t mode);
void ReadERROM(Sensor* s, uint8_t mode);
void GPIO_Init (void);
void switch_pin (uint32_t pin_number);