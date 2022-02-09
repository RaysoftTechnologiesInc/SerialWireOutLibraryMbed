#include "mbed.h"
#include "SWOPrinter.h"

Mutex SWOPrinter::loggerPrint;
bool SWOPrinter::isInit = false;
bool SWOPrinter::isPassThruEnabled = true;

SWOPrinter SWOPrinter::loggers[MBED_CONF_SWO_TOTAL_CHANNEL_NUMBER]  = {SWOPrinter(Error), SWOPrinter(Warning), SWOPrinter(Info), SWOPrinter(Debug), SWOPrinter(custom1), SWOPrinter(custom2), SWOPrinter(custom3),
                                                                       SWOPrinter(custom4), SWOPrinter(custom5), SWOPrinter(custom6), SWOPrinter(custom7), SWOPrinter(custom8),
                                                                       SWOPrinter(custom9), SWOPrinter(custom10), SWOPrinter(custom11), SWOPrinter(custom12), SWOPrinter(custom13),
                                                                       SWOPrinter(custom14), SWOPrinter(custom15), SWOPrinter(custom16), SWOPrinter(custom17), SWOPrinter(custom18),
                                                                       SWOPrinter(custom19), SWOPrinter(custom20), SWOPrinter(custom21), SWOPrinter(custom22), SWOPrinter(custom23),
                                                                       SWOPrinter(custom24), SWOPrinter(custom25), SWOPrinter(custom26), SWOPrinter(custom27), SWOPrinter(custom28)
                                                                      };

SWOPrinter::SWOPrinter(logger_t aChannel) : _channel(aChannel)
{
    loggerPrint.lock();
    if (!isInit) {
        Itm_Init();
    }
    loggerPrint.unlock();
    portNum = portNumCalculation(aChannel);
}

SWOPrinter &SWOPrinter::getLogger(logger_t aLogger)
{
    int i = portNumCalculation(aLogger);
    return loggers[i];
}

int SWOPrinter::portNumCalculation(logger_t aLogger)
{
    int portNum = -1;
    for (; aLogger > 0; portNum++, aLogger = (logger_t)(aLogger >> 1)) 
    {
        ;
    }
    return portNum;
}

void SWOPrinter::Itm_Init()
{
    CoreDebug->DEMCR = CoreDebug_DEMCR_TRCENA_Msk;                                                     /* enable trace in core debug */
    *((volatile unsigned *)(ITM_BASE + PIN_PROTOCOL_REG_OFFSET)) = PIN_PROTOCOL_REG_DEFAULT;           /* "Selected PIN Protocol Register": Select which protocol to use for trace output (2: SWO NRZ, 1: SWO Manchester encoding) */
    *((volatile unsigned *)(ITM_BASE + CLK_PRESC_REG_OFFSET)) = SWO_PRESCALER;                         /* "Async Clock Prescaler Register" Scale the baud rate of the asynchronous output */
    *((volatile unsigned *)(ITM_BASE + LOCK_ACCESS_REG_OFFSET)) = LOCK_ACCESS_REG_DEFAULT;             /* ITM Lock Access Register, C5ACCE55 enables more write access to Control Register 0xE00 :: 0xFFC */
    ITM->TCR = ITM_TCR_TraceBusID_Msk | ITM_TCR_SWOENA_Msk | ITM_TCR_SYNCENA_Msk | ITM_TCR_ITMENA_Msk; /* ITM Trace Control Register */
    ITM->TPR = ITM_TPR_PRIVMASK_Msk;                                                                   /* ITM Trace Privilege Register */
    ITM->TER = MBED_CONF_SWO_DEFAULT_ENABLED_CHANNELS;                                                 /* ITM Trace Enable Register. Enabled tracing on stimulus ports. One bit per stimulus port. */
    *((volatile unsigned *)(ITM_BASE + DWT_CTRL_REG_OFFSET)) = DWT_CTRL_REG_DEFAULT;                   /* DWT_CTRL */
    *((volatile unsigned *)(ITM_BASE + FORMATTER_CTRL_REG_OFFSET)) = FORMATTER_CTRL_REG_DEFAULT;       /* Formatter and Flush Control. Bit 8 always set, to indicate that triggers are indicated*/
    isInit = true;
}

bool SWOPrinter::isChannelEnabled()
{
    return (ITM->TER & (1 << portNum));
}

void SWOPrinter::Log(const char *format, ...)
{
    if (!isChannelEnabled()) { //If this channel is disabled there is nothing left for this function to do.
        return;
    }
    char buffer[1024];
    int i = 0;
    va_list args;
    va_start(args, format);
    loggerPrint.lock();
    if (isPassThruEnabled) {
        printf("[%d] ", portNum);
    }
    int n = vsnprintf(buffer, 1024, format, args);
    SWO_PrintString(buffer, n);
    loggerPrint.unlock();
    va_end(args);
}

void SWOPrinter::SWO_PrintChar(char c)
{
    volatile int timeout;
    if ((ITM->TCR & ITM_TCR_ITMENA_Msk) == 0) {
        return;
    }
    timeout = 5000;
    while (ITM->PORT[portNum].u32 == 0) {
        ThisThread::yield();
        timeout--;
        if (timeout == 0) {
            return;
        }
    }
    ITM->PORT[portNum].u8 = (uint8_t)c;
    if (isPassThruEnabled) {
        printf("%c", c);
    }
}

void SWOPrinter::SWO_PrintString(const char *s, int size)
{
    for (int i = 0; i < size; i++) {
        SWO_PrintChar(*s++);
    }
}

void SWOPrinter::channelEnable(uint32_t channel)
{
    ITM->TER |= channel;
}

void SWOPrinter::channelDisable(uint32_t channel)
{
    ITM->TER &= ~channel;
}

void SWOPrinter::setSerialPassThruEnable(bool isEnabled)
{
    isPassThruEnabled = isEnabled;
}
