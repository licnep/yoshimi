#include "ParamChangeFunc.h"
#include "midiController.h"
#include "Misc/SynthEngine.h"
#include "Misc/Part.h"
#include "ADnoteParameters.h"

parameterStruct::parameterStruct() {
    paramName = parID::PNullParam;
    partN = 0;
    kitItemN = 0;
    voiceN = 0;
    effN = 0;
    EQbandN = 0;
    duplicated = 0;
    label[0] = '\0';
    min = 0;
    max = 127;
    paramPointer = NULL;
    pointerType = 0; //unsigned char*
}

//we redefine the == operator, to be able to compare parameterStructs
bool parameterStruct::operator ==(parameterStruct other) {
    if (other.paramName!=this->paramName) return false;
    if (other.partN!=this->partN) return false;
    if (other.kitItemN!=this->kitItemN) return false;
    if (other.voiceN!=this->voiceN) return false;
    if (other.duplicated!=this->duplicated) return false;
    if (other.effN!=this->effN) return false;
    if (other.EQbandN!=this->EQbandN) return false;
    return true;
}
