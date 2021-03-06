/*
    Config.h - Configuration file functions

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

    This file is derivative of ZynAddSubFX original code, modified 2010
*/

#ifndef CONFIG_H
#define CONFIG_H

#include <csignal>
#include <cstring>
#include <deque>
#include <list>

using namespace std;

#include "MusicIO/MusicClient.h"
#include "Misc/HistoryListItem.h"
#include "Misc/MiscFuncs.h"

typedef enum { no_audio = 0, jack_audio, alsa_audio, } audio_drivers;
typedef enum { no_midi = 0, jack_midi, alsa_midi, } midi_drivers;

class XMLwrapper;
class BodyDisposal;
class SynthEngine;
class ProgramBanks;

class Config : public MiscFuncs
{
    public:
        Config();
        ~Config();
        bool Setup(int argc, char **argv);
        void StartupReport(void);
        void Announce(void);
        void Usage(void);
        void Log(string msg, bool tostderr = true);
        void flushLog(void);
        void saveConfig(void);
        void saveState(void);
        bool restoreState(SynthEngine *synth);
        bool restoreJsession(SynthEngine *synth);
        void setJackSessionSave(int save_type, const char *session_dir, const char *client_uuid);

        static void sigHandler(int sig);
        void setInterruptActive(void);
        void setLadi1Active(void);
        void signalCheck(void);
        void setRtprio(int prio);
        bool startThread(pthread_t *pth, void *(*thread_fn)(void*), void *arg,
                         bool schedfifo, bool midi);

        string addParamHistory(string file);
        string historyFilename(int index);

        string ConfigDirectory;
        string DataDirectory;
        string ConfigFile;
        int BankSelectMethod;
        string paramsLoad;
        string instrumentLoad;
        bool   doRestoreState;
        string StateFile;
        string CurrentXMZ;
        bool   doRestoreJackSession;
        string jackSessionUuid;
        string jackSessionFile;

        unsigned int Samplerate;
        unsigned int Buffersize;
        unsigned int Oscilsize;

        bool runSynth;
        bool showGui;
        bool showConsole;
        bool noStderr;
        int  VirKeybLayout;

        string audioDevice;
        string midiDevice;
        audio_drivers audioEngine;
        midi_drivers  midiEngine;

        string jackServer;
        bool   startJack;        // false
        bool   connectJackaudio; // false

        string        alsaAudioDevice;
        unsigned int  alsaSamplerate;
        int           alsaBuffersize;

        string alsaMidiDevice;
        string nameTag;

        bool   Float32bitWavs;
        string DefaultRecordDirectory;
        string CurrentRecordDirectory;

        int    BankUIAutoClose;
        int    Interpolation;
        int    CheckPADsynth;
        int    rtprio;

        deque<HistoryListItem> ParamsHistory;
        deque<HistoryListItem>::iterator itx;
        static const unsigned short MaxParamsHistory;
        list<string> LogList;
        BodyDisposal *deadObjects;
        ProgramBanks *progBanks;
        char initialBank;
        char initialProgram;
        
    private:
        void loadCmdArgs(int argc, char **argv);
        bool extractConfigData(XMLwrapper *xml);
        bool extractRuntimeData(XMLwrapper *xml);
        bool checkProgramDb(string homedir);
        void addConfigXML(XMLwrapper *xml);
        void addRuntimeXML(XMLwrapper *xml);
        void saveSessionData(string savefile);
        bool restoreSessionData(SynthEngine *synth, string sessionfile);
        int SSEcapability(void);
        void AntiDenormals(bool set_daz_ftz);
        void saveJackSession(void);

        static unsigned short nextHistoryIndex;
        static struct sigaction sigAction;
        static int sigIntActive;
        static int ladi1IntActive;
        int sse_level;
        int jsessionSave;
        const string programCmd;
        string jackSessionDir;
};

extern Config Runtime;

#endif
