#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetVerticalSync(true);
	
	_strDisplayMsg = "";
	_BackgroundColor.set(0);
	_iDisplayAlpha = 0;

	_FontFrabk72.loadFont("frabk.ttf", 72);
	_Logo.loadImage("logo.png");

	//Initialization
	_CheatMgr.setup(); 
	_CheatMgr.addCheatCodes("KONAMI!!", "[U][U][D][D][L][R][L][R]ba");
	_CheatMgr.addCheatCodes("MONEY!!!", "give me the moneys");
	
	ofAddListener(ofxCheatCodesTrigger::CheatTriggerEvent, this, &ofApp::onCheatCodeTriggerEvent);
}

//--------------------------------------------------------------
void ofApp::update()
{
	_CheatMgr.update();

	if(_iDisplayAlpha > 0)
	{
		_iDisplayAlpha *= 0.995;
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofBackground(_BackgroundColor);

	if(_iDisplayAlpha > 0)
	{
		ofSetColor(255, 255, 255, _iDisplayAlpha);
		_Logo.draw(ofGetWindowWidth()/2 - _Logo.getWidth()/2, ofGetWindowHeight()/2 - _Logo.getHeight()/2);
		
		ofSetColor(ofColor(255) - _BackgroundColor, _iDisplayAlpha);
		ofRectangle StringBounding_ =  _FontFrabk72.getStringBoundingBox(_strDisplayMsg, 0, 0);
		_FontFrabk72.drawString(_strDisplayMsg,
								ofGetWindowWidth()/2 - StringBounding_.getWidth()/2,
								ofGetWindowHeight()/2 - StringBounding_.getHeight()/2
								);
	}
}

//--------------------------------------------------------------
void ofApp::onCheatCodeTriggerEvent(string& e)
{
	ofLog(OF_LOG_NOTICE, "Cheat Event!!! Name:" + e);

	_strDisplayMsg = e;
	_BackgroundColor.set(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255));
	_iDisplayAlpha = 255;
}