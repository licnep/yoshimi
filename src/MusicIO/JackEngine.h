/*
    JackEngine.h

    Copyright 2009-2010, Alan Calvert

    This file is part of yoshimi, which is free software: you can
    redistribute it and/or modify it under the terms of the GNU General
    Public License as published by the Free Software Foundation, either
    version 3 of the License, or (at your option) any later version.

    yoshimi is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with yoshimi.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef JACK_ENGINE_H
#define JACK_ENGINE_H

#include <string>
#include <pthread.h>
#include <semaphore.h>
#include <jack/jack.h>
#include <jack/ringbuffer.h>

#if defined(JACK_SESSION)
    #include <jack/session.h>
#endif

using namespace std;

#include "MusicIO/MusicIO.h"

class JackEngine : public MusicIO
{
    public:
        JackEngine();
        ~JackEngine() { Close(); };
        bool connectServer(string server);
        bool isConnected(void) { return (NULL != jackClient); }
        bool openAudio(WavRecord *recorder);
        bool openMidi(WavRecord *recorder);
        bool Start(void);
        void Close(void);
        #if defined(JACK_SESSION)
            bool jacksessionReply(string cmdline);
        #endif
        unsigned int getSamplerate(void) { return jackSamplerate; }
        int getBuffersize(void) { return jackNframes; };

    private:
        bool openJackClient(string server);
        bool new_openJackClient(string server);
        bool connectJackPorts(void);
        bool processAudio(jack_nframes_t nframes);
        bool processMidi(jack_nframes_t nframes);
        int processCallback(jack_nframes_t nframes);
        static int _processCallback(jack_nframes_t nframes, void *arg);
        static void _errorCallback(const char *msg);
        static int _xrunCallback(void *arg);

        #if defined(JACK_SESSION)
            static void _jsessionCallback(jack_session_event_t *event, void *arg);
            void jsessionCallback(jack_session_event_t *event);
            jack_session_event_t *lastevent;
        #endif

        jack_client_t  *jackClient;
        jack_port_t*    midiPort;
        unsigned int    jackSamplerate;
        unsigned int    jackNframes;
        jack_port_t    *audioPortL;
        jack_port_t    *audioPortR;
};

#endif
