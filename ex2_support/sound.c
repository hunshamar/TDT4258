#include <stdint.h>
#include "sound.h"
#include "efm32gg.h"
#include "math.h"

#define AMPLITUDE 2000 

uint8_t sound_type = 0;
double time = 0.0;
uint16_t sawtooth_val = 0;
uint16_t frequency = 0;

void play_sound()
{
    switch(sound_type)
    {
        case 0:
            *DAC0_CH0DATA = 0;
            *DAC0_CH1DATA = 0;
            time = 0.0;
            break;
        case 1:
            play_sine();
        case 2:
            play_sawtooth();
        case 3:
            play_square()
    }
}

void play_sine()
{
    time += 0.00002264285;
    if (time > 1)
    {
        time = 0.0;
        sound_type = 0;
    }
    uint16_t val = 1000 + round(sin(2*3.14*time));
    *DAC0_CH0DATA = val;
    *DAC0_CH1DATA = val;
}

void play_sawtooth()
{
    time += 0.00002264285;
    if (time > 1)
    {
        time = 0.0;
        sound_type = 0;
    }
    if (sawtooth_val > AMPLITUDE)
    {
        sawtooth_val = 0;
    }
    sawtooth_val += (int)(round((double)AMPLITUDE*0.00002264285*(double)frequency));
}

void play_square()
{
    time += 0.00002264285;
    if(fmod(time, 1/frequency) > 1/(2*frequency))
    {
        *DAC0_CH0DATA = 0;
        *DAC0_CH1DATA = 0;
    }
    else
    {
        *DAC0_CH0DATA = AMPLITUDE;
        *DAC0_CH1DATA = AMPLITUDE;
    }
}

void set_sound_type(uint8_t sound)
{
    sound_type = sound;
    time = 0.0;
}

void set_frequency(uint16_t freq)
{
    frequency = freq;
}
