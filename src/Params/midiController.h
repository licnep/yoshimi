/* 
 * File:   midiController.h
 * Author: alox
 *
 * Created on February 15, 2011, 7:46 PM
 */

#ifndef MIDICONTROLLER_H
#define	MIDICONTROLLER_H

#include <WidgetPDialUI.h>
#include <FL/Fl_Spinner.H>
#include "ParamChangeFunc.h"
#include "Effects/EffectMgr.h"


class midiController {
public:
    midiController();
    midiController(WidgetPDial* dial);
    midiController(XMLwrapper *xml);
    virtual ~midiController();

    void execute(char val);
    void doComplexCallback(double val);
    void removeDialPointer();
    void dialCreated(WidgetPDial* dial);
    void duplicatedKnobCreated(WidgetPDial* duplicatedKnob);
    void setMidiCCNumber(int n);
    char* getLabel();
    void setLabel(const char* str);
    static parameterStruct whichParameterDoesThisDialControl(WidgetPDial* d) ;
    void add2XML(XMLwrapper *xml);

    void setMin(double v);
    void setMax(double v);

    int ccNumber;
    parameterStruct param;

    bool recording;
    char label[30];
    double customMin;double customMax;

    WidgetPDial* knob;
    WidgetPDial* DuplicatedKnobInMidiCCPanel;
    Fl_Spinner* SpinnerInMidiCCPanel;

private:
    void rotateDial(double val);
    static bool checkAgainst(parameterStruct* p, WidgetPDial* dial, void* original, int parName);
    static bool checkAgainstEffects(parameterStruct* p, WidgetPDial* dial, EffectMgr* fx);
};

class parID {
public:
    static const int PNullParam = 0;
    static const int PMasterVolume = 1;
    static const int PMasterDetune = 2;
    static const int PPartPanning = 3;
    static const int PPartVolume = 4;
    static const int PAddSynthPan = 5;
    static const int PAddSynthPunchStrength = 6;
    static const int PAddPunchTime = 7;
    static const int PAddSynthPunchTime = 8;
    static const int PAddSynthPunchStretch = 9;
    static const int PAddSynthPunchVelocity = 10;
    static const int PAddSynthAmpEnv1 = 11;
    static const int PAddSynthAmpEnv2 = 12;
    static const int PAddSynthAmpEnv3 = 13;
    static const int PAddSynthAmpEnv4 = 14;
    static const int PAddSynthAmpEnvStretch = 15;
    static const int PAddSynthAmpLfoFreq = 16;
    static const int PAddSynthAmpLfoIntensity = 17;
    static const int PAddSynthAmpLfoStart = 18;
    static const int PAddSynthAmpLfoDelay = 19;
    static const int PAddSynthAmpLfoStretch = 20;
    static const int PAddSynthAmpLfoRand = 21;
    static const int PAddSynthAmpLfoFreqRand = 22;

    static const int PAddSynthFreqLfoFreq = 23;
    static const int PAddSynthFreqLfoIntensity = 24;
    static const int PAddSynthFreqLfoStart = 25;
    static const int PAddSynthFreqLfoDelay = 26;
    static const int PAddSynthFreqLfoStretch = 27;
    static const int PAddSynthFreqLfoRand = 28;
    static const int PAddSynthFreqLfoFreqRand = 29;


    static const int PAddSynthFilterLfoFreq = 30;
    static const int PAddSynthFilterLfoIntensity = 31;
    static const int PAddSynthFilterLfoStart = 32;
    static const int PAddSynthFilterLfoDelay = 33;
    static const int PAddSynthFilterLfoStretch = 34;
    static const int PAddSynthFilterLfoRand = 35;
    static const int PAddSynthFilterLfoFreqRand = 36;

    static const int PAddSynthFreqEnv1 = 40;
    static const int PAddSynthFreqEnv2 = 41;
    static const int PAddSynthFreqEnv3 = 42;
    static const int PAddSynthFreqEnv4 = 43;
    static const int PAddSynthFreqEnv5 = 44;

    static const int PAddFilter1 = 51;
    static const int PAddFilter2 = 52;
    static const int PAddFilter3 = 53;
    static const int PAddFilter4 = 54;
    static const int PAddFilter5 = 55;
    static const int PAddFilter6 = 56;

    static const int  PAddFilterEnv1 = 60;
    static const int  PAddFilterEnv2 = 61;
    static const int  PAddFilterEnv3 = 62;
    static const int  PAddFilterEnv4 = 63;
    static const int  PAddFilterEnv5 = 64;
    static const int  PAddFilterEnv6 = 65;
    static const int  PAddFilterEnv7 = 66;

    static const int PAddVPanning = 69;
    static const int PAddVStereoSpread = 70;
    static const int PAddVVibratto = 71;
    static const int PAddVVibSpeed = 72;

    static const int PaddVAmpEnv1 = 80;
    static const int PaddVAmpEnv2 = 81;
    static const int PaddVAmpEnv3 = 82;
    static const int PaddVAmpEnv4 = 83;
    static const int PaddVAmpEnvStretch = 84;

    static const int PaddVFilterEnv1 = 90;
    static const int PaddVFilterEnv2 = 91;
    static const int PaddVFilterEnv3 = 92;
    static const int PaddVFilterEnv4 = 93;
    static const int PaddVFilterEnv5 = 94;
    static const int PaddVFilterEnv6 = 95;
    static const int PaddVFilterEnv7 = 96;

    static const int PAddVFilter1 = 97;
    static const int PAddVFilter2 = 98;
    static const int PAddVFilter3 = 99;
    static const int PAddVFilter4 = 100;

    static const int PAddVoiceAmpLfoFreq = 101;
    static const int PAddVoiceAmpLfoIntensity = 102;
    static const int PAddVoiceAmpLfoStart = 103;
    static const int PAddVoiceAmpLfoDelay = 104;
    static const int PAddVoiceAmpLfoStretch = 105;
    static const int PAddVoiceAmpLfoRand = 106;
    static const int PAddVoiceAmpLfoFreqRand = 107;

    static const int PaddModAmpEnv1 = 111;
    static const int PaddModAmpEnv2 = 112;
    static const int PaddModAmpEnv3 = 113;
    static const int PaddModAmpEnv4 = 114;
    static const int PaddModAmpEnvStretch = 115;

    static const int PaddVFreqLfoFreq = 123;
    static const int PaddVFreqLfoIntensity = 124;
    static const int PaddVFreqLfoStart = 125;
    static const int PaddVFreqLfoDelay = 126;
    static const int PaddVFreqLfoStretch = 127;
    static const int PaddVFreqLfoRand = 128;
    static const int PaddVFreqLfoFreqRand = 129;

    static const int PaddVFilterLfoFreq = 130;
    static const int PaddVFilterLfoIntensity = 131;
    static const int PaddVFilterLfoStart = 132;
    static const int PaddVFilterLfoDelay = 133;
    static const int PaddVFilterLfoStretch = 134;
    static const int PaddVFilterLfoRand = 135;
    static const int PaddVFilterLfoFreqRand = 136;

    static const int PaddVFreqEnv1 = 140;
    static const int PaddVFreqEnv2 = 141;
    static const int PaddVFreqEnv3 = 142;
    static const int PaddVFreqEnv4 = 143;
    static const int PaddVFreqEnv5 = 144;

    static const int PaddModFreqEnv1 = 150;
    static const int PaddModFreqEnv2 = 151;
    static const int PaddModFreqEnv3 = 152;
    static const int PaddModFreqEnv4 = 153;
    static const int PaddModFreqEnv5 = 154;

    //effects:
    static const int PsysEQgain = 300;
    static const int PsysEQBfreq = 301;
    static const int PsysEQBgain = 302;
    static const int PsysEQBq = 303;

    static const int PsysDis1 = 304;
    static const int PsysDis2 = 305;
    static const int PsysDis3 = 306;
    static const int PsysDis4 = 307;
    static const int PsysDis5 = 308;
    static const int PsysDis6 = 309;
    static const int PsysDis7 = 310;

    static const int PsysAlien0 = 320;
    static const int PsysAlien1 = 321;
    static const int PsysAlien2 = 322;
    static const int PsysAlien3 = 323;
    //static const int PsysAlien4 = 324;
    static const int PsysAlien5 = 325;
    static const int PsysAlien6 = 326;
    static const int PsysAlien7 = 327;
    static const int PsysAlien9 = 329;
    static const int PsysAlien10 = 3210;

};

#endif	/* MIDICONTROLLER_H */

