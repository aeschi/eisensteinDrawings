#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

//--------------------------------------------------------------
void ofApp::setup()
{
    ofBackground(255, 255, 255);
    ofSetVerticalSync(true);
    frameByframe = true;

    // Uncomment this to show movies with alpha channels
    // video.setPixelFormat(OF_PIXELS_RGBA);

    video.load("movies/farmersspring_480_noframe.mp4");
    video.setLoopState(OF_LOOP_NORMAL);
    video.play();

    videoPosX = 20.;
    videoPosY = 40.;
}
//--------------------------------------------------------------

void ofApp::update()
{
    video.update();

    if (video.isFrameNew())
    {
        convertColor(video, gray, CV_RGB2GRAY);
        threshold(gray, thresh, mouseY / 4.0, false);

        Canny(gray, edge, mouseX, mouseY, 3);
        Sobel(gray, sobel);
        // CLD(gray, sobel);

        thresh.update();
        sobel.update();
        edge.update();
    }
}

//--------------------------------------------------------------
void ofApp::draw()
{

    ofSetHexColor(0xFFFFFF);

    video.draw(videoPosX, videoPosY);
    thresh.draw(videoPosX, videoPosY + 390);

    ofSetColor(255, 50, 50);
    edge.draw(videoPosX + 500., videoPosY);
    sobel.draw(videoPosX + 500., videoPosY + 390);

    // ofSetHexColor(0x000000);
    // ofPixels &pixels = video.getPixels();

    // int vidWidth = pixels.getWidth();
    // int vidHeight = pixels.getHeight();
    // int nChannels = pixels.getNumChannels();

    // // let's move through the "RGB(A)" char array
    // // using the red pixel to control the size of a circle.
    // for (int i = 4; i < vidWidth; i += 8)
    // {
    //     for (int j = 4; j < vidHeight; j += 8)
    //     {
    //         unsigned char r = pixels[(j * 480 + i) * nChannels];
    //         float val = 1 - ((float)r / 255.0f);
    //         // ofDrawCircle(500 + i, 20 + j, 10 * val);
    //     }
    // }

    drawInstructions();
}

//--------------------------------------------------------------
void ofApp::drawInstructions()
{

    // LABELS / INSTRUCTIONS / METRICS
    ofSetHexColor(0x000000);

    // VIDEO LABELS
    ofDrawBitmapString("VIDEO SOURCE", videoPosX, videoPosY - 10.);
    ofDrawBitmapString("TRESHOLD", videoPosX, videoPosY + 380.);
    ofDrawBitmapString("CANNY EDGE FILTER", videoPosX + 500., videoPosY - 10.);
    ofDrawBitmapString("SOBEL FILTER", videoPosX + 500., videoPosY + 380.);

    // INSTRUCTIONS
    float textPosX = 20.;
    float textPosY = 800.;
    ofDrawBitmapString("press f to change/lock frame rate", textPosX, textPosY);
    if (frameByframe)
        ofSetHexColor(0xCCCCCC);
    ofDrawBitmapString("mouse speed position", textPosX, textPosY + 20.);
    if (!frameByframe)
        ofSetHexColor(0xCCCCCC);
    else
        ofSetHexColor(0x000000);
    ofDrawBitmapString("keys <- -> frame by frame ", textPosX + 170., textPosY + 20.);
    ofSetHexColor(0x000000);

    ofDrawBitmapString("press mouse to stop on frame", textPosX, textPosY + 40.);

    ofDrawBitmapString("change treshold value with mouse Y position", textPosX + 500., textPosY);

    ofDrawBitmapString("change canny edge filter values with mouse X & Y position", textPosX + 500., textPosY + 20);

    // METRICS
    ofDrawBitmapString("frame: " + ofToString(video.getCurrentFrame()) + "/" + ofToString(video.getTotalNumFrames()), textPosX, textPosY + 60.);
    ofDrawBitmapString("duration: " + ofToString(video.getPosition() * video.getDuration(), 2) + "/" + ofToString(video.getDuration(), 2), textPosX + 150., textPosY + 60.);
    ofDrawBitmapString("speed: " + ofToString(video.getSpeed(), 2), textPosX + 340., textPosY + 60.);

    if (video.getIsMovieDone())
    {
        ofSetHexColor(0xFF0000);
        ofDrawBitmapString("end of movie", textPosX + 120., textPosY);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    switch (key)
    {
    case 'f':
        frameByframe = !frameByframe;
        video.play();
        break;
    case OF_KEY_LEFT:
        video.previousFrame();
        break;
    case OF_KEY_RIGHT:
        video.nextFrame();
        break;
    case '0':
        video.firstFrame();
        break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
    if (!frameByframe)
    {
        int width = ofGetWidth();
        float pct = (float)x / (float)width;
        float speed = (2 * pct - 1) * 5.0f;
        video.setSpeed(speed);
    }
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
    if (!frameByframe)
    {
        int width = ofGetWidth();
        float pct = (float)x / (float)width;
        video.setPosition(pct);
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
    if (!frameByframe)
    {
        video.setPaused(true);
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
    if (!frameByframe)
    {
        video.setPaused(false);
    }
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
}
