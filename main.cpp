#include "mbed.h"
#include "SWOPrinter.h"



Thread t2;
Thread t3;
Thread t4;
Thread t5;
Thread t6;
Thread t7;
Thread t8;
Thread t9;
Thread t10;
Thread t11;
Thread t12;
Thread t13;
Thread t14;

void test_thread(void const *name) {
    SWOPrinter myLogger = SWOPrinter::getLogger(Error);
    
    while (true) 
    {
      myLogger.Log("Thes is my [Error] log, and I love it much\r\n");
    }
}

void test_thread1(void const *name) {
    
    SWOPrinter myLogger = SWOPrinter::getLogger(Warning);
    while (true) 
    {
      myLogger.Log("Thes is my [Warning] log, and I love it much\r\n"); 
    }
}

void test_thread2(void const *name) {
     SWOPrinter myLogger = SWOPrinter::getLogger(Info);
    while (true) 
    {
      myLogger.Log("Thes is my [Info] log, and I love it much\r\n");
    }
}

void test_thread3(void const *name) {
    SWOPrinter myLogger = SWOPrinter::getLogger(Debug);
    while (true) 
    {
      myLogger.Log("Thes is my [Debug] log, and I love it much\r\n");
    }
}

void test_thread4(void const *name) {
    SWOPrinter myLogger = SWOPrinter::getLogger(custom1);
    while (true) 
    {
      myLogger.Log("Thes is my channel %d log, and I love it much\r\n", custom1); 
    }
}

void test_thread5(void const *name) {
    SWOPrinter myLogger = SWOPrinter::getLogger(custom2);
    while (true) 
    {
      myLogger.Log("Thes is my channel %d log, and I love it much\r\n", custom2); 
    }
}

void test_thread6(void const *name) {
   SWOPrinter myLogger = SWOPrinter::getLogger(custom3);
   while (true) 
   {       
      myLogger.Log("Thes is my channel %d log, and I love it much\r\n", custom3);
   }
}

void test_thread7(void const *name) {
    SWOPrinter myLogger = SWOPrinter::getLogger(custom4);
    while (true) 
    {
      myLogger.Log("Thes is my channel %d log, and I love it much\r\n", custom4);
    }
}

void test_thread8(void const *name) {
    SWOPrinter myLogger = SWOPrinter::getLogger(custom5);
    while (true) 
    {
      myLogger.Log("Thes is my channel %d log, and I love it much\r\n", custom5); 
    }
}

void test_thread9(void const *name) {
    SWOPrinter myLogger = SWOPrinter::getLogger(custom6);
    while (true) 
    {
      myLogger.Log("Thes is my channel %d log, and I love it much\r\n", custom6);
    }
}

void test_thread10(void const *name) {
   SWOPrinter myLogger = SWOPrinter::getLogger(custom7);
   while (true) 
    {
      myLogger.Log("Thes is my channel %d log, and I love it much\r\n", custom7);
    }
}
void test_thread18(void const *name) {
   SWOPrinter myLogger = SWOPrinter::getLogger(custom15);
   while (true) 
   {
      myLogger.Log("Thes is my channel %d log, and I love it much\r\n", custom15); 
      
   }
}
void test_thread26(void const *name) {
   SWOPrinter myLogger = SWOPrinter::getLogger(custom23);
   while (true)
   {
      myLogger.Log("Thes is my channel %d log, and I love it much\r\n", custom23); 
   }
}

int main()
{     
                                                                                                                                    


      SystemCoreClock;
      
      //SWOPrinter::channelDisable(Error|Debug|Warning|Info);
      SWOPrinter::channelEnable(Error|Debug);
      SWOPrinter::setSerialPassThruEnable(true);
      t2.start(callback(test_thread,  (void *)"Th 2"));
      t3.start(callback(test_thread1, (void *)"Th 3"));
      t4.start(callback(test_thread2, (void *)"Th 4"));
      t5.start(callback(test_thread3, (void *)"Th 5"));
      t6.start(callback(test_thread4, (void *)"Th 6"));
      t7.start(callback(test_thread5, (void *)"Th 7"));
      t8.start(callback(test_thread6, (void *)"Th 8"));
      t9.start(callback(test_thread7, (void *)"Th 9"));
      t10.start(callback(test_thread8,(void *)"Th 10"));
      t11.start(callback(test_thread9,(void *)"Th 11"));
      t12.start(callback(test_thread10,(void *)"Th 12"));
      t13.start(callback(test_thread18,(void *)"Th 14"));
      t14.start(callback(test_thread26,(void *)"Th 14"));
}