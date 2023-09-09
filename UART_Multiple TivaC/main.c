#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/uart.h"

void Send(uint8_t color);

void Uart_init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
    while (!(SysCtlPeripheralReady(SYSCTL_PERIPH_UART1)))
        ;
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    while (!(SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB)))
        ;
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while (!(SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)))
        ;
    GPIOPinConfigure(GPIO_PB0_U1RX);
    GPIOPinConfigure(GPIO_PB1_U1TX);
    GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,
    GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
    UARTClockSourceSet(UART1_BASE, UART_CLOCK_PIOSC);
    UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(), 9600,
                        (UART_CONFIG_WLEN_5 | UART_CONFIG_STOP_ONE |
                        UART_CONFIG_PAR_NONE));
    UARTEnable(UART1_BASE);

}


int main(void)
{
    Uart_init();
    while (1)
    {

        //Receiving mechanism
        uint8_t receivedChar = UARTCharGet(UART1_BASE);
        if (receivedChar == 5)
        {
            //sending mechanism
            Send(0);
        }
        else
        {
        }
    }
}

//
void Send(uint8_t color)
{
    if (color == 0)
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
        SysCtlDelay(1600 * 4000);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);
        UARTCharPut(UART1_BASE, 5);
    }
    else if (color == 1)
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
        SysCtlDelay(1600 * 4000);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0);
        UARTCharPut(UART1_BASE, 5);
    }
    else
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
        SysCtlDelay(1600 * 4000);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0);
        UARTCharPut(UART1_BASE, 5);
    }

}

