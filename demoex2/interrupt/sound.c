#include <stdint.h>
#include "sound.h"
#include "efm32gg.h"
#include "math.h"
#include <stdbool.h>

#define PI 3.14159265

int amplitude = 100;
uint8_t sound_type = 0;
double time = 0.0;
int sawtooth_val = 0;
int frequency = 250;
bool square_high = false;
int square_count = 0;
uint16_t triangle_val = 0;
bool triangle_rise = true;
bool done_playing_startup = false;
uint8_t startup = 1;
int startup_timer = 0;


void play_sound()
{
    if(done_playing_startup)
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
                play_triangle();
                break;
            case 2:
                play_sawtooth();
                break;
            case 3:
                play_square();
                break;
        }
    }
    else
    {
        sound_type = 1;
        startup_tune();
    }
}

void play_triangle()
{
    if(time > 1)
    {
        time = 0;
        sound_type = 0;
    }
    if(triangle_val > amplitude)
    {
        triangle_rise = false;
    }
    if (triangle_rise)
    {
        triangle_val += (int)round(amplitude * 0.00002264285 * ((double)frequency*2));
    }
    else
    {
        if (triangle_val < (int)round(amplitude * 0.00002264285 * ((double)frequency*2)))
        {
            triangle_rise = true;
        }
        else
        {
            triangle_val -= (int)round(amplitude * 0.00002264285 * ((double)frequency*2));
        }
        
    }
    *DAC0_CH0DATA = triangle_val;
    *DAC0_CH1DATA = triangle_val;
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
    sawtooth_val += (int)(round((double)amplitude * 0.00002264285 * (double)frequency));
    *DAC0_CH0DATA = sawtooth_val;
    *DAC0_CH1DATA = sawtooth_val;
}

void change_volume(int delta_volume)
{
    if((abs(delta_volume) > amplitude) && (delta_volume < 0))
    {
        amplitude = 0;
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
    if(time > 1)
    {
        time = 0.0;
        sound_type = 0;
    }
    double period = round((41000/(double)frequency));
    square_count += 1;
    if (square_count > period)
    {
        square_count = 0;
        if(square_high)
        {
            square_high = false;
            *DAC0_CH0DATA = 0;
            *DAC0_CH1DATA = 0;
        }
        else
        {
            square_high = true;
            *DAC0_CH0DATA = amplitude;
            *DAC0_CH1DATA = amplitude;
        }
        
    }

}

void set_sound_type(uint8_t sound)
{
    time = 0.0;
    sound_type = sound;
}

void startup_tune()
{
    if(startup == 1)
    {
        frequency = 522;
    }
    else if(startup == 2)
    {
        frequency = 660;
    }
    else if(startup == 2)
    {
        frequency = 784;
    }
    play_triangle();
    if(startup_timer > 15000)
    {
        startup++;
        startup_timer = 0;
    }
    if(startup == 4)
    {
        done_playing_startup = true;
        sound_type = 0;
    }
    startup_timer++;

}

