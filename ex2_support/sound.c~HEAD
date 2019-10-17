#include <stdint.h>
#include "sound.h"
#include "efm32gg.h"
#include "math.h"
#include <stdbool.h>
#define PI 3.14159


uint16_t amplitude = 100;
uint8_t sound_type = 0;
double time = 0.0;
uint16_t sawtooth_val;
uint16_t frequency = 200;
double time_since_shift = 0;
bool square_up = false;

void play_sound()
{
    time += 0.00002264285;
    switch(sound_type)
    {
        case 0:
            *DAC0_CH0DATA = 0;
            *DAC0_CH1DATA = 0;
            time = 0.0;
            break;
        case 1:
            play_sine();
            break;
        case 2:
            play_sawtooth();
            break;
        case 3:
            play_square();
            break;
    }
}

void play_sine()
{
    if (time > 1)
    {
        time = 0.0;
        sound_type = 0;
    }
    int val = amplitude + (int)round(amplitude * cos(time * 2 * PI * (double)((double)1/(double)frequency)));
    *DAC0_CH0DATA = val;
    *DAC0_CH1DATA = val;
}

void play_sawtooth()
{
    if (time > 1)
    {
        time = 0.0;
        sound_type = 0;
    }
    if (sawtooth_val > amplitude)
    {
        sawtooth_val = 0;
    }
    sawtooth_val += (int)(round((double)amplitude*0.00002264285*(double)frequency));
    *DAC0_CH0DATA = sawtooth_val;
    *DAC0_CH1DATA = sawtooth_val;
}

void change_volume(int delta_volume)
{
    if((abs(delta_volume) > amplitude) && (delta_volume < 0))
    {
        amplitude = 0;
    }
    else if(amplitude > 1500)
    {
    }
    else
    {
        amplitude += delta_volume;
    }
    
}

void change_frequency(int delta_freq)
{
    if ((abs(delta_freq) > frequency) && delta_freq < 0)
    {
        frequency = 1;
    }
    else
    {
        frequency += delta_freq;
    }
    
} 

void play_square()
{
    if (time > 1)
    {
        time = 0.0;
        sound_type = 0;
    }
    time_since_shift += 0.00002264285;
    if (time_since_shift > (double)(1/frequency))
    {
        time_since_shift = 0;
        square_up = !square_up;
    }
    if (square_up)
    {
        *DAC0_CH0DATA = amplitude;
        *DAC0_CH1DATA = amplitude;
    }
}

void set_sound_type(uint8_t sound)
{
    time = 0.0;
    sound_type = sound;
}
