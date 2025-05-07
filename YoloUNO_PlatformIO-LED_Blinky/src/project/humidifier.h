// Humidifier control header
#ifndef HUMIDIFIER_H
#define HUMIDIFIER_H

extern float humidifier_threshold;
void humidifier_fsm(void);
#define INIT 0
#define CHECK_STATE 1
#define GREEN 2
#define YELLOW 3
#define RED 4

#endif