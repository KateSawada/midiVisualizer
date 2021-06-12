#pragma once

#include "ofMain.h"
#include "ofxMidi.h"
#define MAX_NOTE_NUM 256
/*
typedef struct
{
    ofPoint pos;
    int time_counter;
    int note_num;
    int note_vel;
    bool now_pressed;

} NoteData;
*/
typedef struct
{
    int keyId;
    int passedTimeFromPress;
    int passedTimeFromRelease;
    int posX;
    bool isPressed;
    bool isShown;
} NoteData;

class ofApp : public ofBaseApp, public ofxMidiListener{

	public:
		void setup();
		void update();
		void draw();
        void exit();

		void keyPressed(int key);
        void newMidiMessage(ofxMidiMessage& eventArgs);

        NoteData noteData[MAX_NOTE_NUM];
        int upperLimit;
        int lowerLimit;
        int barWidth;
        int barSpeed;
        int windowHeight;
        ofRectangle bar;
        /*
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        */

    private:
        ofxMidiIn midiIn;
        bool showingInstructions;
		
};
