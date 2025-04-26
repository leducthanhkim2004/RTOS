// Humidifier control header
#ifndef HUMIDIFIER_H
#define HUMIDIFIER_H

#ifdef __cplusplus
extern "C" {
#endif

extern float humidifier_threshold;
void init_humidifier(void);
void humidifier_fsm(void);
void red_humid(void);
void setLedColor(int color);

#ifdef __cplusplus
}
#endif

#endif /* HUMIDIFIER_H */