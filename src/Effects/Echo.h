/*
    Echo.h - Echo Effect

    Original ZynAddSubFX author Nasca Octavian Paul
    Copyright (C) 2002-2005 Nasca Octavian Paul
    Copyright 2009-2010, Alan Calvert

    This file is part of yoshimi, which is free software: you can redistribute
    it and/or modify it under the terms of version 2 of the GNU General Public
    License as published by the Free Software Foundation.

    yoshimi is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.   See the GNU General Public License (version 2 or
    later) for more details.

    You should have received a copy of the GNU General Public License along with
    yoshimi; if not, write to the Free Software Foundation, Inc., 51 Franklin
    Street, Fifth Floor, Boston, MA  02110-1301, USA.

    This file is a derivative of a ZynAddSubFX original, modified November 2010
*/

#ifndef ECHO_H
#define ECHO_H

#include <boost/shared_array.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>

#include "Effects/Effect.h"

class Echo : public Effect
{
    public:
        Echo(bool insertion_, float *efxoutl_, float *efxoutr_);
        ~Echo() { }

        void out(float *smpsl, float *smpr);
        void setpreset(unsigned char npreset);
        void changepar(int npar, unsigned char value);
        unsigned char getpar(int npar);
        int getnumparams(void);
        void cleanup(void);
        void setdryonly(void);

        // Parameters
        unsigned char Pvolume;  // #1 Volume or Dry/Wetness
        unsigned char Ppanning; // #2 Panning
        unsigned char Pdelay;   // #3 Delay of the Echo
        unsigned char Plrdelay; // #4 L/R delay difference
        unsigned char Plrcross; // #5 L/R Mixing
        unsigned char Pfb;      // #6 Feedback
        unsigned char Phidamp;  // #7 Dampening of the Echo

    private:
        void initdelays(void);
        void setvolume(unsigned char Pvolume_);
        void setpanning(unsigned char Ppanning_);
        void setdelay(unsigned char Pdelay_);
        void setlrdelay(unsigned char Plrdelay_);
        void setlrcross(unsigned char Plrcross_);
        void setfb(unsigned char Pfb_);
        void sethidamp(unsigned char Phidamp_);


        // Real Parameters
        float panning;
        float lrcross;
        float fb;
        float hidamp;
        int dl;
        int dr;
        int delay;
        int lrdelay;
        boost::shared_array<float> ldelay;
        boost::shared_array<float> rdelay;
        float oldl; // pt. lpf
        float oldr;
        int kl;
        int kr;
        boost::interprocess::interprocess_mutex echomutex;
};

#endif
