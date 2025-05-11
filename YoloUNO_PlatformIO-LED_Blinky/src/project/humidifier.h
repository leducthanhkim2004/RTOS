// Humidifier control header
#ifndef HUMIDIFIER_H
#define HUMIDIFIER_H

extern float humidifier_threshold;
void humidifier_fsm(void);
extern float humdifier_threshold;
#define INIT 0
#define OFF 1
#define GREEN 2
#define YELLOW 3
#define RED 4

#endif