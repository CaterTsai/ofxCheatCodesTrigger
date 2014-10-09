#ifndef _OFX_CHEAT_CODES_TRIGGER_
#define _OFX_CHEAT_CODES_TRIGGER_

#include "ofMain.h"

static const int cCHEAT_CODE_MAXIMUM_LENGTH = 60;

struct stCheatUnit
{
	int		aiCheatCode[cCHEAT_CODE_MAXIMUM_LENGTH];
	int		iCodeLength;
	int		iInputIdx;
	float	fFailedTimer;
	bool	bInitialSuccess;

	stCheatUnit(int (&aiCode)[cCHEAT_CODE_MAXIMUM_LENGTH], int iLength)
	{
		if(iLength > 0)
		{
			memcpy(aiCheatCode, aiCode, sizeof(int) * iLength);
			iCodeLength = iLength;
			bInitialSuccess = true;
		}
		else
		{
			bInitialSuccess = false;
		}
		
		fFailedTimer = 0.0;
		iInputIdx = 0;
	}
};

typedef map<string, stCheatUnit> CHEAT_CODES_MAP;

class ofxCheatCodesTrigger
{
public:
	ofxCheatCodesTrigger();
	~ofxCheatCodesTrigger();
	
	void setup(float fFailedTimerout = 10.0);
	void update();
	
	void addCheatCodes(string strCodeName, string strCode);
	void clearCheatCodes();
	int getCheatCodesNum();

	void keyPressed(ofKeyEventArgs &e);
	void keyReleased(ofKeyEventArgs &e){};

public:
	static ofEvent<string> CheatTriggerEvent;

private:
	int CodesProcess(int (&aiResult)[cCHEAT_CODE_MAXIMUM_LENGTH], string& strCode);
	int DecodeKey(string strKey);

private:
	bool				_bIsRegistered;

	CHEAT_CODES_MAP		_CheatCodesMap;
	float				_fMainTimer;
	float				_fFailedTimeout;
};

#endif //_OFX_CHEAT_CODES_TRIGGER_