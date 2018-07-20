//////// Fuses: XT,XTPLL,EC_IO,EC,ECPIO,ECPLL,INTRC_IO,INTRC,PROTECT
//////// Fuses: NOPROTECT,BROWNOUT_NOSL,BROWNOUT_SW,NOBROWNOUT,BROWNOUT,WDT1
//////// Fuses: WDT2,WDT4,WDT8,WDT16,WDT32,WDT64,WDT128,WDT,NOWDT,BORV20
//////// Fuses: BORV28,BORV43,BORV46,PUT,NOPUT,CPD,NOCPD,NOSTVREN,STVREN
//////// Fuses: NODEBUG,DEBUG,NOLVP,LVP,WRT,NOWRT,WRTD,NOWRTD,IESO,NOIESO
//////// Fuses: FCMEN,NOFCMEN,PBADEN,NOPBADEN,CCP2B3,CCP2C1,WRTC,NOWRTC,WRTB
//////// Fuses: NOWRTB,EBTR,NOEBTR,EBTRB,NOEBTRB,CPB,NOCPB,MCLR,NOMCLR
//////// Fuses: LPT1OSC,NOLPT1OSC,XINST,WDT256,WDT512,WDT1024,WDT2048
//////// Fuses: WDT4096,WDT8192,WDT16384,WDT32768,NOXINST,INTXT,INTHS,HS
//////// Fuses: HSPLL,PLL1,PLL2,PLL3,PLL4,PLL5,PLL6,PLL10,PLL12,CPUDIV1
//////// Fuses: CPUDIV2,CPUDIV3,CPUDIV4,USBDIV,NOUSBDIV,VREGEN,NOVREGEN

#FUSES XT //Usando Xtal
#FUSES NOWDT //No Watch Dog Timer
#FUSES WDT128 //Watch Dog Timer uses 1:128 Postscale
#FUSES HS //High speed Osc (> 4mhz)
#FUSES NOPROTECT //Code not protected from reading
#FUSES BROWNOUT //Reset when brownout detected
#FUSES BORV20 //Brownout reset at 2.0V
#FUSES NOPUT //No Power Up Timer
#FUSES NOCPD //No EE protection
#FUSES STVREN //Stack full/underflow will cause reset
#FUSES NODEBUG //No Debug mode for ICD
#FUSES LVP //Low Voltage Programming on B3(PIC16) or B5(PIC18)
#FUSES WRT //Program memory write protected
#FUSES NOWRT //Program memory not write protected
#FUSES WRTD //Data EEPROM write protected
#FUSES NOWRTD //Data EEPROM not write protected
#FUSES IESO //Internal External Switch Over mode enabled
#FUSES NOIESO //Internal External Switch Over mode disabled
#FUSES FCMEN //Fail-safe clock monitor enabled
#FUSES NOPBADEN //PORTB pins are configured as digital I/O on RESET
#FUSES NOWRTC //configuration not registers write protected
#FUSES NOWRTB //Boot block not write protected
#FUSES NOEBTR //Memory not protected from table reads
#FUSES NOEBTRB //Boot block not protected from table reads
#FUSES NOCPB //No Boot Block code protection
#FUSES MCLR //Master Clear pin enabled
#FUSES LPT1OSC //Timer1 configured for low-power operation
#FUSES XINST //Extended set extension and Indexed Addressing mode enabled
#FUSES PLL12 //Divide By 12(48MHz oscillator input)
#FUSES CPUDIV4 //System Clock by 4
#FUSES USBDIV //USB clock source comes from PLL divide by 2
#FUSES VREGEN //USB voltage regulator enabled
