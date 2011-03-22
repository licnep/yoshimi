/*
    EffectMgr.h - Effect manager, an interface betwen the program and effects

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

    This file is derivative of original ZynAddSubFX code, modified November 2010
*/

#ifndef EFFECTMGR_H
#define EFFECTMGR_H

#include <boost/interprocess/sync/interprocess_mutex.hpp>

#include "Effects/Effect.h"
#include "Effects/Reverb.h"
#include "Effects/Echo.h"
#include "Effects/Chorus.h"
#include "Effects/Phaser.h"
#include "Effects/Alienwah.h"
#include "Effects/Distorsion.h"
#include "Effects/EQ.h"
#include "Effects/DynamicFilter.h"
#include "Params/Presets.h"

class XMLwrapper;
class FilterParams;

class EffectMgr : public Presets
{
    public:
        EffectMgr(const bool insertion_);
        ~EffectMgr();
        void add2XML(XMLwrapper *xml);
        void defaults(void);
        void getfromXML(XMLwrapper *xml);
        void out(float *smpsl, float *smpsr);
        void setdryonly(bool value);
        float sysefxgetvolume(void);
        void cleanup(void);
        void changeeffect(int nefx_);
        int geteffect(void);
        void changepreset(unsigned char npreset);
        void changepreset_nolock(unsigned char npreset);
        unsigned char getpreset(void);
        void seteffectpar(int npar, unsigned char value, bool midicontrol = false);
        unsigned char geteffectpar(int npar);
        float getEQfreqresponse(float freq); // used by UI

        float *efxoutl;
        float *efxoutr;
        bool insertion; // the effect is connected as insertion effect (or not)
        FilterParams *filterpars;
        Effect *efx;

    private:
        int nefx;
        bool dryonly;
        int privatemoment;
};

#endif

