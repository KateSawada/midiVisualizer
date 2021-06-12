#ifndef MIDIKEYSTATUS_H
#define MIDIKEYSTATUS_H

#define MAX_NOTE_NUM 256

typedef struct
{
    int keyId;
    int passesTimeFromPress;
    int passesTimeFromRelease;
    bool isPressed;
} NoteData;

class MidiKeyStatus
{
public:
    MidiKeyStatus();
    NoteData noteData[MAX_NOTE_NUM];

};

#endif // MIDIKEYSTATUS_H
