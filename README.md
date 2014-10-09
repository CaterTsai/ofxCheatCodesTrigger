ofxCheatCodesTrigger
====================

Description
-----------
An openframeworks add-on that help you add texting event easily. Just like the game cheat codes.
You can add your own "Cheat Codes" like:

	ofxCheatCodesTrigger		_CheatMgr;
	void setup()
	{
		//initial with input timeout (second)
		_CheatMgr.setup(20.0);
		
		//add cheat codes with "Cheat Code Name" and "Cheat Code"
		//"Cheat Code" support 'a-z', 'A-Z', '0-9', 'punctuation', 'space', and arrow keys:
		//[U]:key up, [D]:key down, [L]:key left, [R]:key right
		_CheatMgr.addCheatCodes("TEST", "[U][U][D][D][L][R][L][R]ba");
		
		//add the listener
		ofAddListener(ofxCheatCodesTrigger::CheatTriggerEvent, this, &ofApp::onCheatCodeTriggerEvent);
	}
	
	void onCheatCodeTriggerEvent(string& e)
	{
		ofLog(OF_LOG_NOTICE, "Cheat Event!!! Name:" + e);
	}
	
Example
-------
The example is test on visual studio 2012 with openframework 0.8.1.