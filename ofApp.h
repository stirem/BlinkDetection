#pragma once

#include "ofMain.h"
#include "ofxFaceTracker2.h"
#include "ofxGui.h"
#include "ofxOsc.h"

#define NUM_OF_LANDMARKS 68
#define HOST "localhost"
#define PORT 1234

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
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
    
    ofVideoGrabber grabber;
    ofxFaceTracker2 tracker;
    ofxPanel gui;
    ofxFloatSlider guiSlider_threshold;
    ofxIntSlider guiSlider_consec_frames;
    ofxToggle guiToggle_logToFile;
    ofxOscSender oscSender;
    
    ofVec2f landmarkPos[NUM_OF_LANDMARKS];
    
    float eyeAspectRatioLeft;
    float eyeAspectRatioRight;
    int blinkCounter;
    int blinkTotal;
    bool isOn;
    bool guiIsOn;
		
};
