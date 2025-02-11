 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.0
*/

/*
� [2022] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/
#include "mcc_generated_files/system/system.h"

/* Create a pointer of the type TMR_INTERFACE and assign it to the address of the TCA0_Interface TMR_INTERFACE struct.
This enables us to access the portable API interface, which ensures changing the peripheral instance of the timer runs on is easy. */
const struct TMR_INTERFACE *Timer = &TCA0_Interface;
volatile bool SEND_FRAME = false;

void Timer_Callback_100ms(void){
    DataStreamer.adcResult = ADC0_GetConversion(ADC_MUXPOS_AIN18_gc); //Get the conversion result
    DataStreamer.adcResult >>= 4;
    DataStreamer.adcSampleCount++;
    LED_Toggle();
    SEND_FRAME = true;
}

/*
    Main application
*/

int main(void)
{
    SYSTEM_Initialize();
    
    DataStreamer.adcSampleCount = 0;
    DataStreamer.adcResult = 0;
    
    Timer->TimeoutCallbackRegister(Timer_Callback_100ms);
    
    while(1)
    {
        if(SEND_FRAME){
            WriteFrame();
            SEND_FRAME = false;
        }
    }
}

