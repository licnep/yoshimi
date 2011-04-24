/*
    Chorus.h - Chorus and Flange effects

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

    This file is a derivative of a ZynAddSubFX original, modified October 2010
*/

#ifndef CHORUS_H
#define CHORUS_H

#include "Effects/Effect.h"
#include "Effects/EffectLFO.h"

class Chorus : public Effect
{
    public:
        Chorus(bool insertion_, float *efxoutl_, float *efxoutr_);
        ~Chorus() { };

        void out(float *smpsl, float *smpsr);
        void setpreset(unsigned char npreset);
        void changepar(int npar, unsigned char value);
        unsigned char getpar(int npar);
        void cleanup();

        // Chorus Parameters
        unsigned char Pvolume;
        unsigned char Ppanning;
        unsigned char Pdepth;      // the depth of the Chorus(ms)
        unsigned char Pdelay;      // the delay (ms)
        unsigned char Pfb;         // feedback
        unsigned char Plrcross;    // feedback
        unsigned char Pflangemode; // how the LFO is scaled, to result chorus or flange
        unsigned char Poutsub;     // if I wish to substract the output instead of the adding it
        EffectLFO lfo;             // lfo-ul chorus
        
    private:


        // Parameter Controls
        void setvolume(unsigned char Pvolume_);
        void setpanning(unsigned char Ppanning_);
        void setdepth(unsigned char Pdepth_);
        void setdelay(unsigned char Pdelay_);
        void setfb(unsigned char Pfb_);
        void setlrcross(unsigned char Plrcross_);
        float getdelay(float xlfo);

        // Internal Values
        float depth;
        float delay;
        float fb;
        float lrcross;
        float panning;
        float dl1;
        float dl2;
        float dr1;
        float dr2;
        float lfol;
        float lfor;

        float *delayl;
        float *delayr;
        int maxdelay;
        int dlk;
        int drk;
        int dlhi;
        int dlhi2;
        float dllo;
        float mdel;
};

#endif

