#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFullscreen( false );
    
    grabber.setup( 1280, 720 );
    tracker.setup();
    
    image.load( "NoseGlasses.png" );
    
    blinkCounter = 0;
    blinkTotal = 0;
    eyeAspectRatioLeft = 0.0;
    eyeAspectRatioRight = 0.0;
    isOn = false;
    guiIsOn = false;
    
    gui.setup();
    gui.setPosition( 20, 0 );
    gui.add( guiSlider_threshold.setup( "EAR threshold", 0.24, 0.0, 1.0 ) );
    gui.add( guiSlider_consec_frames.setup( "Consec frames", 3, 0, 10 ) );
    gui.add( guiToggle_logToFile.setup( "Log to file", false ) );

}

//--------------------------------------------------------------
void ofApp::update(){
    
    grabber.update();

    // Update tracker when there are new frames
    if ( grabber.isFrameNew() ) {
        tracker.update( grabber );
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetBackgroundColor( 0, 0, 0 );
    
    // Draw camera image
    grabber.draw( 0, 0 );
    
    
    
    // Instance = New Face. Iterate over all faces
    for ( auto instance : tracker.getInstances() ) {
        // Iterate over all landmarks
        for ( int i = 0; i < NUM_OF_LANDMARKS; i++ ) {
            
            // Landmark points (positions)
            landmarkPos[i] = instance.getLandmarks().getImagePoint( i );
            
            if ( guiIsOn ) {
                ofDrawBitmapStringHighlight( ofToString( i ), landmarkPos[i].x, landmarkPos[i].y );
            }
            
        }
        
        
        float dist1 = ofDist( landmarkPos[37].x, landmarkPos[37].y, landmarkPos[41].x, landmarkPos[41].y );
        float dist2 = ofDist( landmarkPos[38].x, landmarkPos[38].y, landmarkPos[40].x, landmarkPos[40].y );
        float dist3 = ofDist( landmarkPos[36].x, landmarkPos[36].y, landmarkPos[39].x, landmarkPos[39].y );
        eyeAspectRatioLeft = ( dist1 + dist2 ) / ( 2.0 * dist3 );
        
        
        float dist4 = ofDist( landmarkPos[43].x, landmarkPos[43].y, landmarkPos[47].x, landmarkPos[47].y );
        float dist5 = ofDist( landmarkPos[44].x, landmarkPos[44].y, landmarkPos[46].x, landmarkPos[46].y );
        float dist6 = ofDist( landmarkPos[42].x, landmarkPos[42].y, landmarkPos[45].x, landmarkPos[45].y );
        eyeAspectRatioRight = ( dist4 + dist5 ) / ( 2.0 * dist6 );
        
        
        
        // Measure width of face
        //float landmarkDistance = ofDist( landmarkPos[2].x, landmarkPos[2].y, landmarkPos[14].x, landmarkPos[14].y );
        
        
        // Draw a red circle
        /*ofPushStyle();
        ofSetColor( 255, 0, 0 );
        float circleRadius = landmarkDistance/5;
        ofDrawCircle( landmarkPos[30].x, landmarkPos[30].y, circleRadius );
        ofPopStyle();*/
        
        //float imageWidth = landmarkDistance/2;
        
        // Image: image.draw( x, y, width, height );
        //image.draw( landmarkPos[30].x - (landmarkDistance/2), landmarkPos[30].y - (landmarkDistance/2), landmarkDistance, landmarkDistance );
        
    }
    
        
    
    float averageEAR = (eyeAspectRatioLeft + eyeAspectRatioRight) / 2.0;
    
    if ( guiToggle_logToFile ) {
        ofLogToFile( "myLogFile.txt", true );
        ofLog() << "average EAR: " << averageEAR;
    }
    
    if ( averageEAR < guiSlider_threshold ) {
        blinkCounter++;
    } else {
        if ( blinkCounter >= guiSlider_consec_frames ) {
            
            // This is where we register blinks
            
            blinkTotal++;
            blinkCounter = 0;
            
            if ( guiToggle_logToFile ) {
                ofLog() << "BLINK!";
            }
            
            if ( isOn == false ) {
                ofSetColor( 255, 0, 0 );
                isOn = true;
            } else {
                ofSetColor( 0, 255, 0 );
                isOn = false;
            }
            
        }
    }

    if ( guiIsOn ) {
        ofDrawBitmapStringHighlight( "Blinks: " + ofToString( blinkTotal ), 20, 100 );
        ofDrawBitmapStringHighlight( "Average EAR: " + ofToString( averageEAR ), 20, 150 );
    }
    
    
    

    
        
    // Draw tracker landmarks
    //tracker.drawDebug();
    
    //tracker.drawDebugPose();
    
    if ( guiIsOn ) {
        gui.draw();
    }
    

}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if ( key == 'g' || key == 'G' ) {
        if ( ! guiIsOn ) {
            guiIsOn = true;
        } else {
            guiIsOn = false;
        }
    }

}

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
