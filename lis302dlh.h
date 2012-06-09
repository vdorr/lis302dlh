
//June 6 2012
//This program is given to you without any warranty.
//The author disclaims copyright to this source code.

//based on LIS302DLH.pdf June 2009 Doc ID 15797 Rev 1

//interface
#define I2C_ADDRESS_0	0x18
#define I2C_ADDRESS_1	0x19

#define AUTO_INCREMENT	0x80

//registers
#define WHO_AM_I	0x0F

#define CTRL_REG1	0x20
#define CTRL_REG2	0x21
#define CTRL_REG3	0x22
#define CTRL_REG4	0x23
#define CTRL_REG5	0x24

#define HP_FILTER_RESET	0x25

#define REFERENCE	0x26

#define STATUS_REG	0x27

#define OUT_X_L		0x28
#define OUT_X_H		0x29
#define OUT_Y_L		0x2A
#define OUT_Y_H		0x2B
#define OUT_Z_L		0x2C
#define OUT_Z_H		0x2D

#define WHO_AM_I_VALUE	50

//CTRL_REG1
#define PM2_BIT		7
#define PM1_BIT		6
#define PM0_BIT		5
#define DR1_BIT		4
#define DR0_BIT		3
#define Zen_BIT		2
#define Yen_BIT		1
#define Xen_BIT		0

//CTRL_REG2
#define BOOT		7
#define HPM1		6
#define HPM0		5
#define FDS		4
#define HPen2		3
#define HPen1		2
#define HPCF1		1
#define HPCF0		0

//CTRL_REG3
#define IHL		7
#define PP_OD		6
#define LIR2		5
#define I2_CFG1		4
#define I2_CFG0		3
#define LIR1		2
#define I1_CFG1		1
#define I1_CFG0		0

//CTRL_REG4
#define BDU		7
#define BLE		6
#define FS1		5
#define FS0		4
#define STsign		3
#define ST		1
#define SIM		0

//CTRL_REG5
#define TurnOn1		1
#define TurnOn0		0

//STATUS_REG
#define ZYXOR		7
#define ZOR		6
#define YOR		5
#define XOR		4
#define ZYXDA		3
#define ZDA		2
#define YDA		1
#define XDA		0



