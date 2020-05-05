#ifndef login_h
#define login_h

#include <Arduino.h>

class login{
    
  public:
    String getCommand(String req);
    String getSSID(String req);
    String getPSWD(String req);
    String read();
    String store(String conectionInfo);
    void clean();

  private:
    void processRequest(String req);
    String command;
    String ssid;
    String pswd;
};

#endif
