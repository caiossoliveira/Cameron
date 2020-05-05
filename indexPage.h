#ifndef index_h
#define index_h

#include <Arduino.h>

class indexPage{ 
  public:
    indexPage(String Ip);
    String getPage();

   private:
    String mainPage;
};

#endif
