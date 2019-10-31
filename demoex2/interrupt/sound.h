#ifndef SOUND_H
#define SOUND_H

void play_sound();
void set_sound_type(uint8_t sound);
void change_volume(int delta_volume);
void change_frequency(int delta_freq);
void startup_tune();

#endif