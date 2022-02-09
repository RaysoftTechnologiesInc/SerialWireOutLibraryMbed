# Introduction 
This library is used to send debug messages as strings via a single trace pin which is used to stream out data packets. 
SWO is a single trace pin which is used to stream out data packets with a certain clock rate, derived from the CPU core clock.

#Installation/Setup
In the launch.json file of the project, the SWO can be configured as follows snd with each output port also to be configured.
For example to have SWO_Channel_0 output, we can configure as follows
```json
"swoConfig": 
            {
                "enabled": true,
                "swoFrequency": 115200,
                "cpuFrequency": 100000000,
                "source": "probe",
                "decoders": 
                [
                    {
                        "port": 0,
                        "label": "SWO_Channel_0",
                        "type": "console",
                        "number": 0,
                        "encoding": "ascii"
                    }
                ]
            }

```
Other channels can be added under the decoders array of the the json with their configuration parameters.

# Getting Started
Clone the SWOLogger Library to the directory containing your project using 
`git clone https://dev.azure.com/iotnxt/Raptor/_git/IoTnxt.uRaptor.Firmware.Core.SWOLogger`


# Example

```c++
#include "mbed.h"
#include "SWOLogger.h"



Thread t2;
Thread t3;
Thread t4;


void test_thread(void const *name) 
{
    SWOLogger myLogger = SWOLogger::getLogger(Error);
    
    while (true) 
    {
      myLogger.SWOLog("Thes is my [Error] log, and I love it much\r\n");
    }
}

void test_thread1(void const *name) 
{
    
    SWOLogger myLogger = SWOLogger::getLogger(Warning);
    while (true) 
    {
      myLogger.SWOLog("Thes is my [Warning] log, and I love it much\r\n"); 
    }
}

void test_thread2(void const *name) 
{
    SWOLogger myLogger = SWOLogger::getLogger(Info);
    while (true) 
    {
      myLogger.SWOLog("Thes is my [Info] log, and I love it much\r\n");
    }
}

int main()
{     
    t2.start(callback(test_thread,  (void *)"Th 2"));
    t3.start(callback(test_thread1, (void *)"Th 3"));
    t4.start(callback(test_thread2, (void *)"Th 4"));
      
}
```