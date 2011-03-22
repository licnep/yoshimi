/*
    SynthEngine.h

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

    This file is derivative of ZynAddSubFX original code, modified November 2010
*/

#ifndef SYNTHENGINE_H
#define SYNTHENGINE_H

#include <limits.h>
#include <map>
#include <cstdlib>
#include <boost/interprocess/sync/interprocess_upgradable_mutex.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>

using namespace std;

#include "Misc/MiscFuncs.h"
#include "Misc/MiscFuncs.h"
#include "Misc/SynthHelper.h"
#include "Misc/Microtonal.h"
#include "Misc/SynthHelper.h"
#include "Params/midiController.h"
#include "WidgetPDialUI.h"
#include <FL/Fl_Valuator.H>
#include <list>

class EffectMgr;
class Part;
class XMLwrapper;
class FFTwrapper;
class Controller;

class SynthEngine : private SynthHelper, MiscFuncs
{
    public:
        SynthEngine();
        ~SynthEngine();
        bool Init(unsigned int audiosrate, int audiobufsize);
        void Defaults(void);

        bool saveXML(string filename);
        void add2XML(XMLwrapper *xml);

        bool loadXML(string filename);
        bool getfromXML(XMLwrapper *xml);
        void putalldata(char *data, int size);

        void cleanUp(void);
        void MasterAudio(float *outl, float *outr);
        void partOnOff(int npart, int what);
        void partEnable(unsigned char npart, bool maybe);

        void applyMidi(unsigned char* bytes);
        void noteOn(unsigned char chan, unsigned char note, unsigned char velocity);
        void noteOff(unsigned char chan, unsigned char note);
        void setPitchwheel(unsigned char chan, short int par);
        void programChange(unsigned char midichan, unsigned char bank, unsigned char prog);
        string bankName(unsigned char banknum);
        string programName(unsigned char prog);
        void lockExclusive(void);
        void unlockExclusive(void);
        bool trylockExclusive(void);
        bool timedlockExclusive(void);
        void lockSharable(void);
        void unlockSharable(void);
        float numRandom(void);
        unsigned int random(void);

        Part *part[NUM_MIDI_PARTS];

        //midi learn:
        void addController(int ccNumber, WidgetPDial* dial);
        void removeController(midiController* toRemove);

        bool shutup;

        // parameters
        unsigned int samplerate;
        float samplerate_f;
        float halfsamplerate_f;
        int buffersize;
        float buffersize_f;
        int bufferbytes;
        int oscilsize;
        float oscilsize_f;
        int halfoscilsize;
        float halfoscilsize_f;

        uint32_t synthperiodStartFrame;

        unsigned char Pvolume;
        unsigned char Pkeyshift;
        unsigned char Psysefxvol[NUM_SYS_EFX][NUM_MIDI_PARTS];
        unsigned char Psysefxsend[NUM_SYS_EFX][NUM_SYS_EFX];

        // parameters control
        void setPvolume(char value);
        void setPkeyshift(char Pkeyshift_);
        void setPsysefxvol(int Ppart, int Pefx, char Pvol);
        void setPsysefxsend(int Pefxfrom, int Pefxto, char Pvol);

        // effects
        EffectMgr *sysefx[NUM_SYS_EFX]; // system
        EffectMgr *insefx[NUM_INS_EFX]; // insertion

        // part that's apply the insertion effect; -1 to disable
        short int Pinsparts[NUM_INS_EFX];

        // peaks for part VU-meters
        float vuoutpeakpart[NUM_MIDI_PARTS];
        unsigned char fakepeakpart[NUM_MIDI_PARTS]; // this is used to compute the
                                                    // "peak" when the part is disabled
        // others ...
        Controller *ctl;
        Microtonal microtonal;
        FFTwrapper *fft;
        bool recordPending;

        // peaks for VU-meters
        void vuresetpeaks(void);
        float vuOutPeakL;
        float vuOutPeakR;
        float vuMaxOutPeakL;
        float vuMaxOutPeakR;
        float vuRmsPeakL;
        float vuRmsPeakR;
        bool vuClippedL;
        bool vuClippedR;

        list<midiController> assignedMidiControls; //contains all the pairs 'recived midi cc'->'action to execute'

    private:
        void setController(unsigned char channel, unsigned char ctrltype, unsigned char par);
        inline float dB2rap(float dB) { return exp10f((dB) / 20.0f); }
        XMLwrapper *stateXMLtree;
        float volume;
        float sysefxvol[NUM_SYS_EFX][NUM_MIDI_PARTS];
        float sysefxsend[NUM_SYS_EFX][NUM_SYS_EFX];
        float *tmpmixl; // temp mix of part samples
        float *tmpmixr; // to send to system effect
        int keyshift;
        char midiBankLSB;
        char midiBankMSB;
        float vuoutpeakl;
        float vuoutpeakr;
        float vumaxoutpeakl;
        float vumaxoutpeakr;
        float vurmspeakl;
        float vurmspeakr;
        bool clippedL;
        bool clippedR;
        static char random_state[];
        static struct random_data random_buf;
        int32_t random_result;
        float random_0_1;
        boost::interprocess::interprocess_upgradable_mutex synthMutex;
        boost::posix_time::time_duration lockgrace;
        boost::interprocess::interprocess_mutex meterMutex;
        char synthMuted;
};

extern SynthEngine *synth;

inline float SynthEngine::numRandom(void)
{
    if (!random_r(&random_buf, &random_result))
    {
        random_0_1 = (float)random_result / (float)INT_MAX;
        random_0_1 = (random_0_1 > 1.0f) ? 1.0f : random_0_1;
        random_0_1 = (random_0_1 < 0.0f) ? 0.0f : random_0_1;
        return random_0_1;
    }
    return 0.05f;
}

inline unsigned int SynthEngine::random(void)
{
    if (!random_r(&random_buf, &random_result))
        return random_result + INT_MAX / 2;
    return INT_MAX / 2;
}

#endif
