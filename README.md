ofxCheatCodesTrigger
====================

An openframeworks add-on that help you add texting event easily. Just like the game cheat codes.
You can add your own "Cheat Codes" like:

	ofxCheatCodesTrigger		_CheatMgr;
	void ofApp::setup()
	{
		//initial with input timeout (second)
		_CheatMgr.setup(20.0);
		
		//add cheat codes with "Cheat Code Name" and "Cheat Code"
		//"Cheat Code" support 'a-z', 'A-Z', '0-9', 'punctuation', 'space', and four special key like:
		//[U]:key up, [D]:key down, [L]:key left, [R]:key right (now only support those four control key)
		_CheatMgr.addCheatCodes("KONAMI!!", "[U][U][D][D][L][R][L][R]ba");
		_CheatMgr.addCheatCodes("MONEY!!!", "give me the moneys");
		
		//add the listener
		ofAddListener(ofxCheatCodesTrigger::CheatTriggerEvent, this, &ofApp::onCheatCodeTriggerEvent);
	}
	
	void ofApp::onCheatCodeTriggerEvent(string& e)
	{
		ofLog(OF_LOG_NOTICE, "Cheat Event!!! Name:" + e);
	}

