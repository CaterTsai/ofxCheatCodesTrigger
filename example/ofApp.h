#pragma once

#include "ofMain.h"
#include "ofxCheatCodesTrigger.h"

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	void onCheatCodeTriggerEvent(string& e);

private:
	ofxCheatCodesTrigger		_CheatMgr;

	int							_iDisplayAlpha;
	string						_strDisplayMsg;
	ofColor						_BackgroundColor;
	ofTrueTypeFont				_FontFrabk72;

	ofImage						_Logo;
};
