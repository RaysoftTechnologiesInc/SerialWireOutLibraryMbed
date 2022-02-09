#ifndef SWOPRINTER_H
#define SWOPRINTER_H
#include "mbed.h"

#define ITM_STIM_U32 (*(volatile unsigned int *)0xE0000000)  // Stimulus Port Register word access
#define ITM_STIM_U8 (*(volatile char *)0xE0000001)           // Stimulus Port Register byte access
#define ITM_ENA (*(volatile unsigned int *)0xE0000E00)       // Trace Enable Ports Register  
#define ITM_TCR (*(volatile unsigned int *)0xE0000E80)       // Trace control register
#define SWO_PRESCALER (MBED_CONF_SWO_CPU_CORE_FREQHZ / MBED_CONF_SWO_SWO_SPEED) - 1;
#define PIN_PROTOCOL_REG_OFFSET     0x400F0                  
#define CLK_PRESC_REG_OFFSET        0x40010                  
#define LOCK_ACCESS_REG_OFFSET      0x00FB0                  
#define DWT_CTRL_REG_OFFSET         0x01000
#define FORMATTER_CTRL_REG_OFFSET   0x40304
#define PIN_PROTOCOL_REG_DEFAULT    0x00000002
#define LOCK_ACCESS_REG_DEFAULT     0xC5ACCE55
#define DWT_CTRL_REG_DEFAULT        0x400003FE
#define FORMATTER_CTRL_REG_DEFAULT  0x00000100

/**
  * @brief      an enumerated type containing all the logs for all the 32 channels
  */
enum logger_t 
{
    Error       = 0b00000000000000000000000000000001,
    Warning     = 0b00000000000000000000000000000010,
    Info        = 0b00000000000000000000000000000100,
    Debug       = 0b00000000000000000000000000001000,
    custom1     = 0b00000000000000000000000000010000,
    custom2     = 0b00000000000000000000000000100000,
    custom3     = 0b00000000000000000000000001000000,
    custom4     = 0b00000000000000000000000010000000,
    custom5     = 0b00000000000000000000000100000000,
    custom6     = 0b00000000000000000000001000000000,
    custom7     = 0b00000000000000000000010000000000,
    custom8     = 0b00000000000000000000100000000000,
    custom9     = 0b00000000000000000001000000000000,
    custom10    = 0b00000000000000000010000000000000,
    custom11    = 0b00000000000000000100000000000000,
    custom12    = 0b00000000000000001000000000000000,
    custom13    = 0b00000000000000010000000000000000,
    custom14    = 0b00000000000000100000000000000000,
    custom15    = 0b00000000000001000000000000000000,
    custom16    = 0b00000000000010000000000000000000,
    custom17    = 0b00000000000100000000000000000000,
    custom18    = 0b00000000001000000000000000000000,
    custom19    = 0b00000000010000000000000000000000,
    custom20    = 0b00000000100000000000000000000000,
    custom21    = 0b00000001000000000000000000000000,
    custom22    = 0b00000010000000000000000000000000,
    custom23    = 0b00000100000000000000000000000000,
    custom24    = 0b00001000000000000000000000000000,
    custom25    = 0b00010000000000000000000000000000,
    custom26    = 0b00100000000000000000000000000000,
    custom27    = 0b01000000000000000000000000000000,
    custom28    = 0b10000000000000000000000000000000,
};

/**
 * @brief           SWOPrinter - a class used to print out debug messages via the serial wire out using the ITM
 * 
 *
 * @details         ITM  -  The instrumentation Trace Macrocell (ITM) supports printf style debugging 
 *                  information for diagnostics. Packets can be invoked by software – a direct 
 *                  write to the ITM or by hardware – triggered from the data watchpoint trigger (DWT).
 */
class SWOPrinter {
private:
    logger_t _channel;
    int portNum;
    static Mutex loggerPrint;
    static bool isInit;
    static bool isPassThruEnabled;
    static SWOPrinter loggers[MBED_CONF_SWO_TOTAL_CHANNEL_NUMBER];

    /**
    * @brief         Constructor to a SWO object, takes an enum as an argument.
    * @details       it assigns the enum value to the private variable portNum used to sent data to that specific port.
    *
    * @param [in]    logger_t enum           enum logger_t
    */
    SWOPrinter(logger_t aChannel);

    /**
    * @brief         prints out a character on a selected port.
    *
    * @param [in]    c               the character to be printed
    */
    void SWO_PrintChar(char c);

    /**
    * @brief         prints out a string on a selected port.
    *
    * @param [in]    *s              the pointer to the first character of the string to be printed
    * @param [in]    size            the size of the data to be printed out
    */
    void SWO_PrintString(const char *s, int size);

    /**
    * @brief         used to check whether a channel is enabled or not before a print command can be sent to the channel
    */
    bool isChannelEnabled();

    /**
    * @brief         Initialises the ITM with all the required register values for the ITM to work properly.
    */
    static void Itm_Init();

    /**
    * @brief         This function calculates the integral value of portNum by the use of logarithms.
    */
    static int portNumCalculation(logger_t aLogger);

public:
    /**
     * @brief        sends data to be printed on a selected port  for a selected SWOPrinter object.
     * @param [in]   *format            pointer to the text string to be printed on the port.
     */
    void Log(const char *format, ...);

    /**
     * @brief        used to select a specific swo outputs from the list of outputs in the enum logger_t assign it to 
     * @param [in]   aLogger            an enum value from logger_t
     *
     * @returns      SWOPrinter[i]      a SWOPrinter object from the static array of swo outputs.
     */
    static SWOPrinter &getLogger(logger_t aLogger);

    /**
    * @brief         Enables selected ports
    * @param [in]    channel            takes a number corresponding to a specific channel to be enabled
    */
    static void channelEnable(uint32_t channel);

    /**
    * @brief         Disables selected ports
    * @param [in]    channel            takes a number corresponding to a specific channel to be disabled
    */
    static void channelDisable(uint32_t channel);

    /**
    * @brief         sets whether data should also be output on the serial port or not
    * @param [in]    isEnabled          boolean value setting whether we want serial output or not.
    */
    static void setSerialPassThruEnable(bool isEnabled);
};

#endif