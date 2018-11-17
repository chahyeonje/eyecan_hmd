
#include <cstdio>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <fstream>
#include <utility>
#include <vector>
#include <iostream>

#include "include/hmdgps.h"
#include "include/geomagnetic.h"
#include "include/switch.h"
#include "include/hmdcurl.h"
#include "include/speaker.h"
#include "include/camera.h"

#include <alsa/asoundlib.h>
#include <alsa/pcm.h>
#include <math.h>
/*
#define BUFFER_LEN 30000 // total beep length $$$$$$ by hmd

static char *device = "default";                       //soundcard
snd_output_t *output = NULL;
float buffer [BUFFER_LEN];
*/
int main()
{
    cout<<"test started!"<<endl;

    initGPS();
    updateGPS();


    initGeo();
    updateGeo();
 //   sendData();
 //   cout<<gps_lat<< gps_long<<endl;
/*    int err;
    int j,k;
    
    int f =400;              //frequency
    int fs = 48000;             //sampling frequency
    
    snd_pcm_t *handle;
    snd_pcm_sframes_t frames;
    
    
    // ERROR HANDLING
    
    if ((err = snd_pcm_open(&handle, device, SND_PCM_STREAM_PLAYBACK, 0)) < 0) {
        printf("Playback open error: %s\n", snd_strerror(err));
        exit(EXIT_FAILURE);
    }
    
    if ((err = snd_pcm_set_params(handle,
                                  SND_PCM_FORMAT_FLOAT,
                                  SND_PCM_ACCESS_RW_INTERLEAVED,
                                  1,
                                  48000,
                                  1,
                                  500000)) < 0) {
        printf("Playback open error: %s\n", snd_strerror(err));
        exit(EXIT_FAILURE);
        
        
    }
    
    // SINE WAVE
    printf("Sine tone at %dHz ",f);
    
    for (k=0; k<BUFFER_LEN; k++){
        
        buffer[k] = (sin(2*M_PI*f/fs*k));                 //sine wave value generation
    }
    
    for (j=0; j<1; j++){ // j is number of beep sound $$$$$$ by hmd
        frames = snd_pcm_writei(handle, buffer, BUFFER_LEN);    //sending values to sound driver
    }
    
    snd_pcm_close(handle);
    */
    return 0;
}
