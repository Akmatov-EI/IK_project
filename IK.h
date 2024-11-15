#include <avr/io.h>
#ifndef IK_H
#define IK_H

#define MAXSIZE 100
#define CONSTTIME 10

enum 
{
START_STATUS = 0,
STATUS_HIGH = 1,
STATUS_LOW = 2,
};

typedef struct
{
    uint16_t BufferIK[MAXSIZE];

} IK_READ;

typedef struct
{
    volatile uint8_t Port;
    uint8_t Pin;
} IK_INIT;

typedef struct 
{
    IK_READ x;
    IK_INIT y;
}Main_IK;


void ReadIK(Main_IK *p);

#endif