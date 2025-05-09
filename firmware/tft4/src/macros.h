#ifndef macros_h
#define macros_h
  #ifdef SERIAL_PRINTING
    #define SERIAL_DEBUG  (Serial.begin(ESP_SERIAL_BAUD))
    #define Sprintln(a) (Serial.println(a))
    #define Sprint(a) (Serial.print(a))
    #define Sprintf(...) (Serial.printf(__VA_ARGS__))
  #else
    #define SERIAL_DEBUG
    #define Sprintln(a) 
    #define Sprint(a) 
    #define Sprintf(...) 
  #endif
#endif 