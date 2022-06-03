#include "ch32v30x_usbhs_device.h"
#include "debug.h"
#include "DAP_config.h"
#include "DAP.h"

int main(void)
{
    Delay_Init();
    USART_Printf_Init(1000000);
    printf("SystemClk:%d\r\n",SystemCoreClock);

    DAP_Setup();

    /* USB20 device init */
    USBHS_RCC_Init( );                                                         /* USB2.0高速设备RCC初始化 */
    USBHS_Device_Init( ENABLE );
    NVIC_EnableIRQ( USBHS_IRQn );

	while(1)
    {
	}
}

