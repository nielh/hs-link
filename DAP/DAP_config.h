#ifndef __DAP_CONFIG_H__
#define __DAP_CONFIG_H__

#include "debug.h"

//#define DEBUG(...)


#define CPU_CLOCK               SystemCoreClock       ///< Specifies the CPU Clock in Hz


//#define IO_PORT_WRITE_CYCLES    2               ///< I/O Cycles: 2=default, 1=Cortex-M0+ fast I/0


#define DAP_SWD                 1               ///< SWD Mode:  1 = available, 0 = not available

#define DAP_JTAG                0               ///< JTAG Mode: 0 = not available

#define DAP_JTAG_DEV_CNT        8               ///< Maximum number of JTAG devices on scan chain

#define DAP_DEFAULT_PORT        1               ///< Default JTAG/SWJ Port Mode: 1 = SWD, 2 = JTAG.

#define DAP_DEFAULT_SWJ_CLOCK   4000000         ///< Default SWD/JTAG clock frequency in Hz.


/// Maximum Package Size for Command and Response data.
#define DAP_PACKET_SIZE         512              ///< USB: 64 = Full-Speed, 1024 = High-Speed.

/// Maximum Package Buffers for Command and Response data.
#define DAP_PACKET_COUNT        1              ///< Buffers: 64 = Full-Speed, 4 = High-Speed.


/// Indicate that UART Serial Wire Output (SWO) trace is available.
#define SWO_UART                0               ///< SWO UART:  1 = available, 0 = not available

#define SWO_UART_MAX_BAUDRATE   115200          ///< SWO UART Maximum Baudrate in Hz

/// Indicate that Manchester Serial Wire Output (SWO) trace is available.
#define SWO_MANCHESTER          0               ///< SWO Manchester:  1 = available, 0 = not available

#define SWO_BUFFER_SIZE         4096            ///< SWO Trace Buffer Size in bytes (must be 2^n)

#define SWO_STREAM              0               ///< SWO Streaming Trace: 1 = available, 0 = not available.

/// Clock frequency of the Test Domain Timer. Timer value is returned with \ref TIMESTAMP_GET.
//#define TIMESTAMP_CLOCK         1000000U      ///< Timestamp clock in Hz (0 = timestamps not supported).
#define TIMESTAMP_CLOCK        0

/// Debug Unit is connected to fixed Target Device.
#define TARGET_DEVICE_FIXED     0               ///< Target Device: 1 = known, 0 = unknown;

#if TARGET_DEVICE_FIXED
#define TARGET_DEVICE_VENDOR    ""              ///< String indicating the Silicon Vendor
#define TARGET_DEVICE_NAME      ""              ///< String indicating the Target Device
#endif


//**************************************************************************************************
/**
JTAG I/O Pin                 | SWD I/O Pin          | CMSIS-DAP Hardware pin mode
---------------------------- | -------------------- | ---------------------------------------------
TCK: Test Clock              | SWCLK: Clock         | Output Push/Pull
TMS: Test Mode Select        | SWDIO: Data I/O      | Output Push/Pull; Input (for receiving data)
TDI: Test Data Input         |                      | Output Push/Pull
TDO: Test Data Output        |                      | Input
nTRST: Test Reset (optional) |                      | Output Open Drain with pull-up resistor
nRESET: Device Reset         | nRESET: Device Reset | Output Open Drain with pull-up resistor

DAP Hardware I/O Pin Access Functions
*/


// Configure DAP I/O pins ------------------------------

#define SWD_PORT			GPIOA
#define SWCLK_PIN			GPIO_Pin_0
#define SWDIO_PIN			GPIO_Pin_1
#define SWRST_PIN			GPIO_Pin_2

#define LED_PORT	        GPIOC
#define LED_CONNECTED_PIN	GPIO_Pin_0
#define LED_RUNNING_PIN		GPIO_Pin_1



// SWCLK/TCK I/O pin -------------------------------------

// Current status of the SWCLK/TCK DAP hardware I/O pin
static __inline uint32_t PIN_SWCLK_TCK_IN(void)
{
    return (SWD_PORT->INDR &SWCLK_PIN) ? 1 : 0;
 }

static __inline void PIN_SWCLK_TCK_SET(void)
{
    SWD_PORT->BSHR = SWCLK_PIN;
}

static __inline void PIN_SWCLK_TCK_CLR(void)
{
    SWD_PORT->BCR = SWCLK_PIN;
}

// SWDIO/TMS I/O Pin --------------------------------------

// Current status of the SWDIO/TMS DAP hardware I/O pin
static __inline uint32_t PIN_SWDIO_TMS_IN(void)
{
    return (SWD_PORT->INDR &SWDIO_PIN) ? 1 : 0;
}

static __inline void PIN_SWDIO_TMS_SET(void)
{
    SWD_PORT->BSHR = SWDIO_PIN;
}

static __inline void PIN_SWDIO_TMS_CLR(void)
{
    SWD_PORT->BCR = SWDIO_PIN;
}

// SWDIO I/O pin (used in SWD mode only) ------------------
static __inline uint32_t PIN_SWDIO_IN(void)
{
    return PIN_SWDIO_TMS_IN();
}

static __inline void PIN_SWDIO_OUT(uint32_t bit)
{
    if(bit&1)
        PIN_SWDIO_TMS_SET();
    else
        PIN_SWDIO_TMS_CLR();
}

static __inline void PIN_SWDIO_OUT_ENABLE(void)
{
    uint32_t tmp = SWD_PORT->CFGLR;
    tmp &= (~0xF0);
    tmp |= (3 << 4); // PP OUTPUT 50M
    SWD_PORT->CFGLR = tmp;
}

static __inline void PIN_SWDIO_OUT_DISABLE(void)
{
    uint32_t tmp = SWD_PORT->CFGLR;
    tmp &= (~0xF0);
    tmp |= (4 << 4); // PDPU INPUT
    SWD_PORT->CFGLR = tmp;
}


// TDI Pin I/O ---------------------------------------------
#if (DAP_JTAG != 0)

/** Setup JTAG I/O pins: TCK, TMS, TDI, TDO, nTRST, and nRESET.
 - TCK, TMS, TDI, nTRST, nRESET to output mode and set to high level.
 - TDO to input mode.
*/
static void PORT_JTAG_SETUP(void)
{

}

#endif

// TDO Pin I/O ---------------------------------------------
static __inline uint32_t PIN_TDO_IN(void)
{
    return 0;
}

static __inline void PIN_nTRST_OUT(uint32_t bit)
{
}

static __inline uint32_t PIN_TDI_IN(void)
{
    return 0;
}

static __inline void PIN_TDI_OUT(uint32_t bit)
{
}

// nTRST Pin I/O -------------------------------------------

static __inline uint32_t PIN_nTRST_IN(void)
{
    return 0;
}

// nRESET Pin I/O------------------------------------------
static __inline uint32_t PIN_nRESET_IN(void)
{
    return (SWD_PORT->INDR &SWRST_PIN) ? 1 : 0;
}

static __inline void PIN_nRESET_OUT(uint32_t bit)
{
    if(bit&1)
        SWD_PORT->BSHR = SWRST_PIN;
    else
        SWD_PORT->BCR = SWRST_PIN;
}

static uint32_t timestamp =0;
static __inline uint32_t TIMESTAMP_GET (void) {
	//return (DWT->CYCCNT) / (CPU_CLOCK / TIMESTAMP_CLOCK);
    return timestamp++ ;
}

#include <string.h>

/** Get Vendor ID string.
\param str Pointer to buffer to store the string.
\return String length.
*/
static __inline uint8_t DAP_GetVendorString (char *str) {
	memcpy((unsigned char*)str, "NIE", sizeof("NIE"));
	return sizeof("NIE");
}

/** Get Product ID string.
\param str Pointer to buffer to store the string.
\return String length.
*/
static __inline uint8_t DAP_GetProductString (char *str) {
	memcpy((unsigned char*)str, "HS-Link CMSIS-DAP", sizeof("HS-Link CMSIS-DAP"));
	return sizeof("HS-Link CMSIS-DAP");
}

/** Get Serial Number string.
\param str Pointer to buffer to store the string.
\return String length.
*/
static __inline uint8_t DAP_GetSerNumString (char *str) {
    memcpy((unsigned char*)str, "20220601001", sizeof("20220601001"));
	return sizeof("20220601001");
}

/** Get firmware version string.
\param str Pointer to buffer to store the string.
\return String length.
*/
static __inline uint8_t DAP_ProductFirmwareVerString (char *str) {
    memcpy((unsigned char*)str, "2.0", sizeof("2.0"));
	return sizeof("2.0");
}

#endif // __DAP_CONFIG_H__
