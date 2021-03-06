#include "UART2.h"
#include <pic18f26j50.h>

//HABILITA PUERTO SERIE 2
void UART2_Init(unsigned long BAUD)
{
    //CONFIGURACION BAUDIOS
    if (BAUD == 115200) 
    {
        B2 = ((_XTAL_FREQ/BAUD)/16)-1;
        TXSTA2bits.BRGH2 = 1;                                                   //Alta velocidad
    }
    else if (BAUD == 9600)
    {
        B2 = ((_XTAL_FREQ/BAUD)/64)-1;
        TXSTA2bits.BRGH2 = 0;                                                   //Baja velocidad
    }
    //CONFIGURACION BAUD RATE
    BAUDCON2bits.BRG162 = 0;                                                    //8 bits
    SPBRG2 = B2;                                                                //Baud rate 9600
    
    //CONFIGURACION PUERTO SERIE
    TRISCbits.TRISC2 = 1;                                                       //RX Input
    TRISCbits.TRISC1 = 0;                                                       //TX Output
    
    //Configuracion
    TXSTA2bits.SYNC2 = 0;                                                       //Transmision asincrona UART
    RCSTA2bits.SPEN2 = 1;                                                       //Habilita UART
    
     //Recepcion
    RCSTA2bits.CREN2 = 1;                                                       //Habilita recepcion
    RCSTA2bits.RX92 = 0;                                                        //8 bits
    
      
    //Transmision
    TXSTA2bits.TX92 = 0;                                                        //8 bits
    TXSTA2bits.TXEN2 = 1;                                                       //Habilitar transmision
       
}
////////////////////////////////////////////////////////////////////////////////

void UART2_Write(char data) 
{
    while(0 == PIR3bits.TX2IF);
    TXREG2 = data;                                                              // Write the data byte to the USART.
}

void UART2_printf(char* trama)
{
    while(*trama)  UART2_Write(*trama++);    
}

char UART2_Read(void)
{
    if (PIR3bits.RC2IF == 1) return RCREG2;
    else return 0;
}

bool UART2_Rx_Ready(void)
{
    return (bool)(PIR3bits.RC2IF);
}