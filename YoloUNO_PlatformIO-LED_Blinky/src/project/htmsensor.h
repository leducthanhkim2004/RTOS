/*
 * htmsensor.h
 * 
 * Header file for the Smart Climate Control System on the YoloUNO platform (ESP32 S3).
 * Reads humidity and temperature from the DHT20 sensor (I2C) every 5 seconds using a
 * custom scheduler and software timer. Outputs data to Serial with timestamps.
 * No actuators or delay() calls are used.
 * 
 * Note: Uses DHT20 sensor for humidity and temperature readings via I2C.
 * 
 * Author: Generated based on user specifications
 * Date: April 29, 2025
 */

#ifndef SMART_CLIMATE_CONTROL_H
#define SMART_CLIMATE_CONTROL_H

#ifdef __cplusplus
extern "C" {
#endif

void init_smart_climate_control(void);
void smart_climate_control_task(void);

#ifdef __cplusplus
}
#endif

#endif /* htmsensor_h */

/*What is extern "C"?
Purpose: In C++, the compiler uses name mangling to encode function names with additional information (e.g., parameter types, namespaces) 
to support features like function overloading. This results in complex symbol names in the compiled object 
code (e.g., _Z3fooi for a function foo(int)).
Problem: C code does not use name mangling; it generates simple symbol names (e.g., foo for foo). If a C++ program tries to call a C function 
or vice versa, the linker may fail to match the mangled C++ names with the unmangled C names, causing linking errors.
Solution: extern "C" tells the C++ compiler to treat the enclosed declarations (functions, variables, etc.) as if they were C functions, 
disabling name mangling and using the C calling convention.*/

/*Why am I using this in my header file?
Effect: The functions init_smart_climate_control and smart_climate_control_task are declared with C linkage. In the compiled code, their symbols 
remain simple (e.g., init_smart_climate_control instead of a mangled name like _Z22init_smart_climate_controlv).
Why Needed: The scheduler’s SCH_Add_Task likely expects a C-style function pointer. Without extern "C", the C++ compiler would mangle the task 
function’s name, causing a linker error when the scheduler tries to reference smart_climate_control_task.*/
