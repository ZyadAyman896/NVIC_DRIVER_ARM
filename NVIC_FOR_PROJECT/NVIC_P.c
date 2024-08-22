/*
 * NVIC_P.c
 *
 *  Created on: Jul 28, 2024
 *      Author: Zyad Ayman
 */

#include "NVIC_P.h"


/*********************************************************************
 * Service Name: NVIC_EnableIRQ
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): IRQ_Num - Number of the IRQ from the target vector table
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to enable Interrupt request for this specific IRQ.
**********************************************************************/

void NVIC_EnableIRQ(NVIC_IRQType IRQ_Num)
{

    /*Enabling The Specified Interrupt*/
    switch(IRQ_Num)
    {
        case 0 ... 31 :
            SET_PIN(NVIC_EN0_REG,IRQ_Num);
        break;
        case 32 ... 63 :
            SET_PIN(NVIC_EN1_REG,IRQ_Num);
        break;
        case 64 ... 95 :
            SET_PIN(NVIC_EN2_REG,IRQ_Num);
        break;
        case 96 ... 127 :
            SET_PIN(NVIC_EN3_REG,IRQ_Num);
        break;
        case 128 ... 159 :
            SET_PIN(NVIC_EN4_REG,IRQ_Num);
        break;
    }

}


/*********************************************************************
 * Service Name: NVIC_DisableIRQ
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): IRQ_Num - Number of the IRQ from the target vector table
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to disable Interrupt request for this specific IRQ.
**********************************************************************/

void NVIC_DisableIRQ(NVIC_IRQType IRQ_Num)
{

    /*Disabling The Specified Interrupt*/
    switch(IRQ_Num)
    {
        case 0 ... 31 :
            SET_PIN(NVIC_DIS0_REG,IRQ_Num);
        break;
        case 32 ... 63 :
            SET_PIN(NVIC_DIS1_REG,IRQ_Num);
        break;
        case 64 ... 95 :
            SET_PIN(NVIC_DIS2_REG,IRQ_Num);
        break;
        case 96 ... 127 :
            SET_PIN(NVIC_DIS3_REG,IRQ_Num);
        break;
        case 128 ... 159 :
            SET_PIN(NVIC_DIS4_REG,IRQ_Num);
        break;
    }


}



/*********************************************************************
 * Service Name: NVIC_SetPriorityIRQ
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): IRQ_Num , IRQ_Priority
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to set the priority value for specific IRQ
**********************************************************************/


void NVIC_SetPriorityIRQ(NVIC_IRQType IRQ_Num, NVIC_IRQPriorityType IRQ_Priority)
{

    /*Enabling The Specified Interrupt*/
    switch(IRQ_Num)
    {
        case 0 ... 31 :
            SET_PIN(NVIC_EN0_REG,IRQ_Num);
        break;
        case 32 ... 63 :
            SET_PIN(NVIC_EN1_REG,IRQ_Num);
        break;
        case 64 ... 95 :
            SET_PIN(NVIC_EN2_REG,IRQ_Num);
        break;
        case 96 ... 127 :
            SET_PIN(NVIC_EN3_REG,IRQ_Num);
        break;
        case 128 ... 159 :
            SET_PIN(NVIC_EN4_REG,IRQ_Num);
        break;
    }

    /*Setting The Priority Of The Specified Interrupt*/


    /*1- Getting The Number Of The Register Required For This Interrupt */
    uint8 Number_Of_Req_Reg = (IRQ_Num / 4) ;


    /*2- Using Pointer to Point to the required PRIORITY REGISTER*/
    /*Initially it has the Address Of The First PRIORITY REGISTER*/
    volatile uint32 *Ptr_Registers = (volatile uint32 *)0xE000E400 ;

    /*Pointing to the Required Register*/
    Ptr_Registers +=  Number_Of_Req_Reg ;


    if( IRQ_Num == ( 4 * Number_Of_Req_Reg ) ) /*if the IRQ_Num is the first interrupt in the register*/
    {

        *Ptr_Registers |= ( IRQ_Priority << 5) ;

    }

    else if ( IRQ_Num == ( ( 4 * Number_Of_Req_Reg ) + 1 ) )/*if the IRQ_Num is the Second interrupt in the register*/
    {

        *Ptr_Registers |=  ( IRQ_Priority << 13) ;

    }

    else if ( IRQ_Num == ( ( 4 * Number_Of_Req_Reg ) + 2 ) )/*if the IRQ_Num is the Third interrupt in the register*/
    {

        *Ptr_Registers |= ( IRQ_Priority << 21) ;

    }

    else if( IRQ_Num ==  ( 4 * ( Number_Of_Req_Reg + 1 ) ) )/*if the IRQ_Num is the Last interrupt in the register*/
    {

        *Ptr_Registers |= ( IRQ_Priority << 29) ;

    }

    /*Assigning again the start register (PRI0)*/
    Ptr_Registers = (volatile uint32 *)0xE000E400 ;



}



/*********************************************************************
 * Service Name: NVIC_EnableException
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): Exception_Num
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to enable specific ARM system or fault exceptions.
 *
**********************************************************************/

/*    EXCEPTION_RESET_TYPE,
    EXCEPTION_NMI_TYPE,
    EXCEPTION_HARD_FAULT_TYPE,
    *EXCEPTION_MEM_FAULT_TYPE,
    EXCEPTION_BUS_FAULT_TYPE,
   * EXCEPTION_USAGE_FAULT_TYPE,
   * EXCEPTION_SVC_TYPE,
  *  EXCEPTION_DEBUG_MONITOR_TYPE,
 *   EXCEPTION_PEND_SV_TYPE,
    EXCEPTION_SYSTICK_TYPE *
*/



void NVIC_EnableException(NVIC_ExceptionType Exception_Num)
{
    switch(Exception_Num)
    {
        case EXCEPTION_SYSTICK_TYPE :
            SET_PIN(NVIC_SYSTEM_SYSHNDCTRL , BIT_NO_11);
        break;
        case EXCEPTION_USAGE_FAULT_TYPE :
            SET_PIN(NVIC_SYSTEM_SYSHNDCTRL , BIT_NO_18);
        break;
        case EXCEPTION_MEM_FAULT_TYPE :
            SET_PIN(NVIC_SYSTEM_SYSHNDCTRL , BIT_NO_16);
        break;
        case EXCEPTION_BUS_FAULT_TYPE :
            SET_PIN(NVIC_SYSTEM_SYSHNDCTRL , BIT_NO_14);
        break;
    }

}



/*********************************************************************
 * Service Name: NVIC_DisableException
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): Exception_Num
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to disable specific ARM system or fault exceptions.
 *
**********************************************************************/

void NVIC_DisableException(NVIC_ExceptionType Exception_Num)
{


    switch(Exception_Num)
    {
        case EXCEPTION_SYSTICK_TYPE :
            CLR_PIN(NVIC_SYSTEM_SYSHNDCTRL , BIT_NO_11);
        break;
        case EXCEPTION_USAGE_FAULT_TYPE :
            CLR_PIN(NVIC_SYSTEM_SYSHNDCTRL , BIT_NO_18);
        break;
        case EXCEPTION_MEM_FAULT_TYPE :
            CLR_PIN(NVIC_SYSTEM_SYSHNDCTRL , BIT_NO_16);
        break;
        case EXCEPTION_BUS_FAULT_TYPE :
            CLR_PIN(NVIC_SYSTEM_SYSHNDCTRL , BIT_NO_14);
        break;
    }


}



/*********************************************************************
 * Service Name: NVIC_SetPriorityException
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): Exception_Num , Exception_Priority
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to set the priority value for specific ARM system or fault  exceptions.
 *
**********************************************************************/


void NVIC_SetPriorityException(NVIC_ExceptionType Exception_Num, NVIC_ExceptionPriorityType Exception_Priority)
{


    /*First Enabling the exception*/

    switch(Exception_Num)
    {
        case EXCEPTION_SYSTICK_TYPE :
            SET_PIN(NVIC_SYSTEM_SYSHNDCTRL , BIT_NO_11);
        break;
        case EXCEPTION_USAGE_FAULT_TYPE :
            SET_PIN(NVIC_SYSTEM_SYSHNDCTRL , BIT_NO_18);
        break;
        case EXCEPTION_MEM_FAULT_TYPE :
            SET_PIN(NVIC_SYSTEM_SYSHNDCTRL , BIT_NO_16);
        break;
        case EXCEPTION_BUS_FAULT_TYPE :
            SET_PIN(NVIC_SYSTEM_SYSHNDCTRL , BIT_NO_14);
        break;
    }

    /*Setting the priority of the exception*/

    if(Exception_Num == EXCEPTION_SYSTICK_TYPE)
    {

        NVIC_SYSTEM_PRI3_REG |= (Exception_Priority << 29);

    }
    else if(Exception_Num == EXCEPTION_USAGE_FAULT_TYPE)
    {

        NVIC_SYSTEM_PRI1_REG |= (Exception_Priority << 21);

    }
    else if (Exception_Num == EXCEPTION_PEND_SV_TYPE )
    {

        NVIC_SYSTEM_PRI3_REG |= (Exception_Priority << 21);

    }
    else if (Exception_Num == EXCEPTION_MEM_FAULT_TYPE)
    {

        NVIC_SYSTEM_PRI1_REG |= (Exception_Priority << 5) ;

    }
    else if (Exception_Num == EXCEPTION_BUS_FAULT_TYPE)
    {

        NVIC_SYSTEM_PRI1_REG |= (Exception_Priority << 13) ;

    }
    else if (Exception_Num == EXCEPTION_DEBUG_MONITOR_TYPE)
    {

        NVIC_SYSTEM_PRI3_REG |= (Exception_Priority << 5);

    }
    else if (Exception_Num == EXCEPTION_SVC_TYPE)
    {

        NVIC_SYSTEM_PRI2_REG |= (Exception_Priority << 29);

    }


}





