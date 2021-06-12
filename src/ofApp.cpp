#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetFrameRate(60);

    //midi setup
    midiIn.openPort(1); //error doubtful
    midiIn.addListener(this);

    ofBackground(0);
    ofSetColor(0, 127, 255, 127);
    showingInstructions = true;

    //initialize noteData array
    for (int i = 0; i < MAX_NOTE_NUM; i++){
        noteData[i].isPressed = false;
        noteData[i].isShown = false;
    }

    //key range setting  http://www.asahi-net.or.jp/~hb9t-ktd/music/Japan/Research/DTM/freq_map.html
    //25 keys
    //upperLimit = 72;
    //lowerLimit = 48;

    //88keys
    upperLimit = 21;
    lowerLimit = 108;

    //bar flowing speed
    barSpeed = 3;
}

void ofApp::newMidiMessage (ofxMidiMessage& msg){
    //when key pressed
    if (msg.status == MIDI_NOTE_ON && msg.velocity != 0){
        for (int i = 0; i < MAX_NOTE_NUM; i++){
            if(!noteData[i].isShown){
                noteData[i].isShown = true;
                noteData[i].isPressed = true;
                noteData[i].keyId = msg.pitch;
                noteData[i].passedTimeFromPress = 0;
                noteData[i].passedTimeFromRelease = 0;
                break;
            }
        }
    //when key released
    } else if (msg.status == MIDI_NOTE_OFF){
        for (int i = 0; i < MAX_NOTE_NUM; i++){
            if(noteData[i].isPressed && noteData[i].keyId == msg.pitch){
                noteData[i].isPressed = false;
                break;
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    barWidth = ofGetWidth() / (upperLimit - lowerLimit + 1);
    windowHeight = ofGetHeight();
}

//--------------------------------------------------------------
void ofApp::draw(){
    for (int i = 0; i < MAX_NOTE_NUM; i++){
        if(noteData[i].isShown){
            //bar.set(barWidth * (noteData[i].keyId - lowerLimit), noteData[i].passedTimeFromRelease, barWidth, noteData[i].passedTimeFromPress - noteData[i].passedTimeFromRelease);
            ofDrawRectangle(ofGetWidth() - barWidth * (noteData[i].keyId - lowerLimit), windowHeight - noteData[i].passedTimeFromRelease, barWidth, -1 * (noteData[i].passedTimeFromPress - noteData[i].passedTimeFromRelease));
            noteData[i].passedTimeFromPress += barSpeed;
            if(!noteData[i].isPressed){
                noteData[i].passedTimeFromRelease += barSpeed;
            }
            if(noteData[i].passedTimeFromRelease > ofGetHeight()){
                noteData[i].isShown = false;
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

void ofApp::exit(){
    midiIn.closePort();
    midiIn.removeListener(this);
}

/*
//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
*/
