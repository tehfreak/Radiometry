/*
 * SDC.h
 *
 * Created: 14.03.2015 22:31:45
 *  Author: Disgust
 */ 


#ifndef SDC_H_
#define SDC_H_

#define USE_SPI
//#define USE_SDIO

#include <util/crc16.h>

#if defined(USE_SPI)
	#include "../SPI/spi_device.h"
#endif

typedef enum {
	INACTIVE,
	IDLE,
	READY,
	IDENTIFICATION,
	STAND_BY,
	TRANSFER,
	SENDING_DATA,
	RECEIVE_DATA,
	PROGRAMMING,
	DISCONNECT
} card_state_t;

typedef enum {
	UNCKNOWN,
	SD_v1,
	SD_v2_BLOCK_ADDR,
	SD_v2_BYTE_ADDR,
	MMC_v3
	} card_type_t;

typedef struct {
	spiDevice_t * spiCard;
	PORT_t CtrlPort;
	uint8_t PwrPin;
	uint8_t PresPin;
	card_type_t type;
	card_state_t state;
	} card_t;

// enum {
// 	CHECK_FUNC= 0,
// 	SWITCH_FUNC= 1
// 	} MODE_FUNC;

// typedef enum {
// 	
// 	} error_t;

	
typedef enum {
	INACTIVE_MODE,
	CARD_IDENTIFICATION_MODE,
	DATA_TRANSFER_MODE
	} card_opmode_t;


// SD Card Commands
#if defined(USE_SPI)

	#define CMD0	0b000000
		#define cmd0_arg(STUFF)		(uint32_t)(STUFF)			// GO_IDLE_STATE
	#define CMD1	0b000001
		#define cmd1_arg(HCS)	(uint32_t)(0x0000|(HCS << 30))		// SEND_OP_COND
	#define CMD6	0b000110
		#define cmd6_arg(MODE_FUNC)	(uint32_t)(0x0000|(MODE_FUNC << 31)|\
									(FUNCGRP_6 << 20)|(FUNCGRP_5 << 16)|\
									(FUNCGRP_4 << 12)|(FUNCGRP_3 << 8)|\
									(FUNCGRP_2 << 4)|FUNCGRP_1)	// SWITCH_FUNC
	#define CMD8	0b001000
		#define cmd8_arg(VHS,CH_PTRN)	(uint32_t)(0x0000|(VHS << 8)|CH_PTRN)	// SEND_IF_COND
	#define CMD9	0b001001
		#define cmd9_arg(STUFF)		(uint32_t)(STUFF)			// SEND_CSD
	#define CMD10	0b001010
		#define cmd10_arg(STUFF)	(uint32_t)(STUFF)			// SEND_CID
	#define CMD12	0b001100
		#define cmd12_arg(STUFF)	(uint32_t)(STUFF)			// STOP_TRANSMISSION
	#define CMD13	0b001101
		#define cmd13_arg(STUFF)	(uint32_t)(STUFF)			// SEND_STATUS
	#define CMD16	0b010000
		#define cmd16_arg(BLK_LENGTH)	(uint32_t)(BLK_LENGTH)		// SET_BLOCKLEN
	#define CMD17	0b010001
		#define cmd17_arg(ADDR)		(uint32_t)(ADDR)			// READ_SINGLE_BLOCK
	#define CMD18	0b010010
		#define cmd18_arg(ADDR)		(uint32_t)(ADDR)			// READ_MULTIPLE_BLOCK
	#define CMD24	0b011000
		#define cmd24_arg(ADDR)		(uint32_t)(ADDR)			// WRITE_BLOCK
	#define CMD25	0b011001
		#define cmd25_arg(ADDR)		(uint32_t)(ADDR)			// WRITE_MULTIPLE_BLOCK
	#define CMD27	0b011011
		#define cmd27_arg(STUFF)	(uint32_t)(STUFF)			// PROGRAM_CSD
	#define CMD28	0b011100
		#define cmd28_arg(ADDR)		(uint32_t)(ADDR)			// SET_WRITE_PROT
	#define CMD29	0b011101
		#define cmd29_arg(ADDR)		(uint32_t)(ADDR)			// CLR_WRITE_PROT
	#define CMD30	0b011110
		#define cmd30_arg(ADDR)		(uint32_t)(ADDR)			// SEND_WRITE_PROT
	#define CMD32	0b100000
		#define cmd32_arg(ADDR)		(uint32_t)(ADDR)			// ERASE_WR_BLK_START
	#define CMD33	0b100001
		#define cmd33_arg(ADDR)		(uint32_t)(ADDR)			// ERASE_WR_BLK_END
	#define CMD38	0b100110
		#define cmd38_arg(STUFF)	(uint32_t)(STUFF)			// ERASE
	#define CMD42	0b101010
		#define cmd42_arg()			(uint32_t)(0x0000)			//LOCK_UNLOCK
	#define CMD55	0b110111
		#define cmd55_arg(STUFF)	(uint32_t)(STUFF)			// APP_CMD
	#define CMD56	0b111000
		#define cmd56_arg(STUFF,RD_WR)	(uint32_t)((STUFF << 1)|RD_WR)		// GEN_CMD
	#define CMD58	0b111010
		#define cmd58_arg(STUFF)	(uint32_t)(STUFF)			// READ_OCR
	#define CMD59	0b111011
		#define cmd59_arg(STUFF, CRC_OPT)	(uint32_t)((STUFF << 1)|CRC_OPT)
	
	// App specific
	#define ACMD13	
		#define acmd13_arg(STUFF)	(uint32_t)(STUFF)			// SD_STATUS
	#define ACMD18
	#define ACMD22	
		#define acmd22_arg(STUFF)	(uint32_t)(STUFF)			// SEND_NUM_WR_BLOCKS
	#define ACMD23	
		#define acmd23_arg(STUFF,NUM_OF_BLKS)	(uint32_t)((STUFF << 23)|NUM_OF_BLKS)	// SET_WR_BLOCK_ERASE_COUNT
	#define ACMD25
	#define ACMD26
	#define ACMD38
	#define ACMD41	0b101001	
		#define acmd41_arg(HCS)	(uint32_t)(0x0000|(HCS << 30))	// APP_SEND_OP_COND
	#define ACMD42	
		#define acmd42_arg(STUFF,SET_CD)	(uint32_t)((STUFF << 1)|SET_CD)	// SET_CLR_CARD_DETECT
	#define ACMD43
	#define ACMD44
	#define ACMD45
	#define ACMD46
	#define ACMD47
	#define ACMD48
	#define ACMD49
	#define ACMD51	
		#define acmd51_arg(STUFF)	(uint32_t)(STUFF)				// SEND_SCR
	

#elif defined(USE_SDIO)
	#define CMD2					// ALL_SEND_CID
	#define CMD3					// SEND_RELATIVE_ADDR
	#define CMD4					// SET_DSR
	#define CMD5
	#define CMD7					// SELECT/DESELECT_CARD
	#define CMD11
	#define CMD15					// GO_INACTIVE_STATE
	#define CMD19					// SEND_TUNING_BLOCK
	#define CMD20					// SPEED_CLASS_CONTROL
	#define CMD23					// SET_BLOCK_COUNT
	#define CMD26
	#define CMD39
	#define CMD40
	#define CMD52
	#define CMD53
	#define CMD54
	
	// App specific
	#define ACMD6	// SET_BUS_WIDTH
#endif

// Card registers
struct  
{
	
} CID_REG;


// Data packet
typedef struct {
	uint8_t token;
	uint8_t * data;
	uint16_t crc;
	}SDC_Packet_t;
	

typedef union {
	struct {
		uint8_t cmd;
		SDC_Packet_t packet;
		};
		
	}SDC_Message_t;

// Data response tokens
	
	// Additional types for handling responses
typedef struct{
	uint8_t bytes[5];
} uint40_t;

typedef union {
	struct {
		uint8_t bit7 : 1;				// always 0
		uint8_t parameter_err : 1;
		uint8_t address_err : 1;
		uint8_t erase_sequence_err : 1;
		uint8_t comm_crc_err : 1;
		uint8_t illegal_command : 1;
		uint8_t erase_rst : 1;
		uint8_t in_idle_state : 1;
	} bit;
	uint8_t reg;
} R1_t;

typedef union {
	struct {
		uint16_t reserved1		: 15;
		uint8_t volt_2v7_2v8	: 1;
		uint8_t volt_2v8_2v9	: 1;
		uint8_t volt_2v9_3v0	: 1;
		uint8_t volt_3v0_3v1	: 1;
		uint8_t volt_3v1_3v2	: 1;
		uint8_t volt_3v2_3v3	: 1;
		uint8_t volt_3v3_3v4	: 1;
		uint8_t volt_3v4_3v5	: 1;
		uint8_t volt_3v5_3v6	: 1;
		uint8_t s18a			: 1;
		uint8_t reserved2		: 4;
		uint8_t uhs2_stat		: 1;
		uint8_t ccs				: 1;
		uint8_t power_up_stat	: 1;
	} bit;
	uint32_t reg;
} ocr_reg_t;

	// R1 format
R1_t R1_response;

	// R1b format
R1_t R1b_response; // bit7 is a BUSY bit

	// R2 format
union {
	struct {
		R1_t r1;
		uint8_t out_of_range_csd_overwrite : 1;
		uint8_t erase_param : 1;
		uint8_t wp_violation : 1;
		uint8_t card_ecc_failed : 1;
		uint8_t CC_err : 1;
		uint8_t error : 1;
		uint8_t wp_erase_skip_lock_unlock_cmd_failed : 1;
		uint8_t card_is_locked : 1;
	} bit;
	uint16_t reg;
} R2_response;

	// R3 format  -  This response token is sent by the card when a READ_OCR command is received
union {
	struct {
		R1_t r1;
		ocr_reg_t OCR;
	} part;
	uint40_t full;
} R3_response;

	// R4 & R5 are in the SDIO mode
	
	// R7 format  -  This response token is sent by the card when a SEND_IF_COND command (CMD8) is received.	
union {
	struct {
		R1_t r1;
		uint8_t comm_version : 4;
		const uint16_t reserved : 1;
		uint8_t voltage_accepted : 4;
		uint8_t check_pattern;
		}parts;
	uint40_t full;
	} R7_response;


// COntrol tokens
	//Data response token
struct {
	uint8_t not_used : 3;
	uint8_t bit4 : 1;
	uint8_t status : 3;
	uint8_t bit0 : 1;
	} DT_resp_tk;

#define DATA_ACCEPTED	(0b010)
#define CRC_ERROR		(0b101)
#define WRITE_ERROR		(0b110)



// Data tokens
#define CMD17_18_24_TK		0b1111110
#define CMD25_TK			0b1111100
#define CMD25_ST_TK			0b1111101 // Stop tran for com25

//Error token
struct {
	uint8_t not_used : 4;
	uint8_t out_of_range : 1;
	uint8_t ecc_failed : 1;
	uint8_t cc_err : 1;
	uint8_t error : 1;
}Error_tk;






// Function definitions

card_t * initCardObject(spiDevice_t *, PORT_t, uint8_t, uint8_t);

void cardPowerUp(card_t *);
void cardPowerDwn(card_t *);
void cardTurnOff(card_t *);

uint8_t cardCheck(card_t *);
uint16_t cardIDread();

void SD_SoftReset();
void SD_init();
void SD_blockRead();
void SD_multBlockRead();
void SD_blockWrite();
void SD_multBlockWrite();



uint8_t readR1Response();
uint8_t readR2Response();
uint8_t readR3Response();
uint8_t readR7Response();

#endif /* SDC_H_ */