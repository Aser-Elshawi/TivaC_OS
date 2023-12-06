/*******************************************************************************
 * Title                 :   ****MODULE_TITLE*****
 * Module                :   WDT
 * Filename              :   WDT.h
 * Author                :   Mohamed Osama
 * Origin Date           :   May 10, 2022
 * Version               :   1.0.0
 * Compiler              :   Texas Instruments v20.2.6 LTS
 * Target                :   TM4C123GH6PM
 * Notes                 :   None
 *******************************************************************************/
/*************** MODULE REVISION LOG ******************************************
 *
 *    Date         Software Version    Initials     Description
 *  May 10, 2022         1.0.0          Mohamed       Module Created.
 *
 *******************************************************************************/


#ifndef BSW_WDT_WDT_H_
#define BSW_WDT_WDT_H_

/******************************************************************************
 * Preprocessor Macros (Definitions and static Configurations)
 *******************************************************************************/

/******************************************************************************
 * Macros (Functions)
 *******************************************************************************/
#define WDT0_num                  0x00000000
#define WDT1_num                  0x00000001
#define USED_WDT_NUM              2
/******************************************************************************
 * User-defined Types
 *
 *******************************************************************************/
typedef enum WDT_status_e{
    WDT_status_uninitialized,
    WDT_status_Ok,
    WDT_status_Activated,
    WDT_status_Failed,
    WDT_status_Expired
}WDT_status_t;


typedef struct WDT_stateinfo_s{
  WDT_status_t wdst;
  uint32_t curr;
  uint32_t prev;
} WDT_stateinfo_t;



typedef struct WDT_cfg_e
{
    const uint8_t WDT_num        ;
    const uint32_t WDT_base      ;
    const uint32_t WDT_peri      ;

}WDT_cfg_t;


WDT_cfg_t wdt_cfg[USED_WDT_NUM] = {

{.WDT_num = WDT0_num,.WDT_base = 0x40000000,.WDT_peri =0xf0000000},
{.WDT_num = WDT1_num,.WDT_base = 0x40001000,.WDT_peri =0xf0000001}

};
/******************************************************************************
 * Extern for Public Global Variables
 *******************************************************************************/

/******************************************************************************
 * Function Prototypes
 *******************************************************************************/




#endif /* BSW_WDT_WDT_H_ */
