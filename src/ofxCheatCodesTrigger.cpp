#include "ofxCheatCodesTrigger.h"


ofEvent<string> ofxCheatCodesTrigger::CheatTriggerEvent = ofEvent<string>(); 

ofxCheatCodesTrigger::ofxCheatCodesTrigger()
	:_bIsRegistered(false)
{}

//--------------------------------------------------------------
ofxCheatCodesTrigger::~ofxCheatCodesTrigger()
{
	if(_bIsRegistered)
	{
		ofUnregisterKeyEvents(this);
		_bIsRegistered = false;
		this->clearCheatCodes();
	}
}

//--------------------------------------------------------------
void ofxCheatCodesTrigger::setup(float fFailedTimerout)
{	
	if(!_bIsRegistered)
	{	
		ofRegisterKeyEvents(this);
		_bIsRegistered = true;

		_fFailedTimeout = fFailedTimerout;
		_fMainTimer = ofGetElapsedTimef();

		ofLog(OF_LOG_NOTICE, "Setup ofxCheatCodesTrigger success!");
	}
}

//--------------------------------------------------------------
void ofxCheatCodesTrigger::update()
{
	if(!_bIsRegistered)
	{
		return;
	}

	float fDelta_ = ofGetElapsedTimef() - _fMainTimer;
	_fMainTimer += fDelta_;

	auto Iter_ = _CheatCodesMap.begin();
	while(Iter_ != _CheatCodesMap.end())
	{
		if(!Iter_->second.bInitialSuccess || Iter_->second.iInputIdx <= 0)
		{
			++Iter_;
			continue;
		}

		Iter_->second.fFailedTimer += fDelta_;
		if(Iter_->second.fFailedTimer > _fFailedTimeout)
		{
			Iter_->second.iInputIdx = 0;
			Iter_->second.fFailedTimer = 0.0;
		}
		++Iter_;
	}
	return;
	
}

//--------------------------------------------------------------
void ofxCheatCodesTrigger::addCheatCodes(string strCodeName, string strCode)
{
		
	auto Iter_ = _CheatCodesMap.find(strCodeName);
	if(Iter_ != _CheatCodesMap.end())
	{
		ofLog(OF_LOG_ERROR, "Cheat codes name duplicate. Name:%s", strCodeName);
	}

	int aiCheatCode_[cCHEAT_CODE_MAXIMUM_LENGTH] = {0};
	int iCodeLength_ = this->CodesProcess(aiCheatCode_, strCode);
	stCheatUnit stNewCheatUnit_(aiCheatCode_, iCodeLength_);

	_CheatCodesMap.insert(make_pair(strCodeName, stNewCheatUnit_));
}

//--------------------------------------------------------------
void ofxCheatCodesTrigger::clearCheatCodes()
{
	_CheatCodesMap.clear();
}

//--------------------------------------------------------------
int ofxCheatCodesTrigger::getCheatCodesNum()
{
	return _CheatCodesMap.size();
}

//--------------------------------------------------------------
void ofxCheatCodesTrigger::keyPressed(ofKeyEventArgs &e)
{
	//Pandding?
	auto Iter_ = _CheatCodesMap.begin();
	while(Iter_ != _CheatCodesMap.end())
	{
		if(!Iter_->second.bInitialSuccess)
		{
			Iter_++;
			continue;
		}
		
		if(Iter_->second.aiCheatCode[Iter_->second.iInputIdx] == e.key)
		{
			Iter_->second.iInputIdx++;
			Iter_->second.fFailedTimer = 0;
			
			if(Iter_->second.iInputIdx == Iter_->second.iCodeLength)
			{
				string strCheatName_ = Iter_->first;
				ofNotifyEvent(CheatTriggerEvent, strCheatName_);
				Iter_->second.iInputIdx = 0;
			}
		}
		else
		{
			Iter_->second.iInputIdx = 0;
			Iter_->second.fFailedTimer = 0.0;
		}
		++Iter_;
	}
}

//--------------------------------------------------------------
int ofxCheatCodesTrigger::CodesProcess(int (&aiResult)[cCHEAT_CODE_MAXIMUM_LENGTH], string& strCode)
{
	char acCode_[cCHEAT_CODE_MAXIMUM_LENGTH];
	strcpy(acCode_, strCode.c_str());

	int idx_ = 0;
	int iResultIdx_ = 0;
	while(idx_ < strCode.size())
	{
		if(acCode_[idx_] == '[')
		{
			string strKey_ = strCode.substr(idx_, 3);
			int iKeyValue_ = this->DecodeKey(strKey_);

			aiResult[iResultIdx_] = iKeyValue_;
			iKeyValue_ == '['?(idx_++):(idx_+=3);
		}
		else
		{
			aiResult[iResultIdx_] = acCode_[idx_];
			idx_++;
		}
		iResultIdx_++;
	}

	return iResultIdx_;
}

//--------------------------------------------------------------
int ofxCheatCodesTrigger::DecodeKey(string strKey)
{
	int iResult_ = -1;
	if(strKey == "[U]")
	{
		iResult_ = OF_KEY_UP;
	}
	else if(strKey == "[D]")
	{
		iResult_ = OF_KEY_DOWN;
	}
	else if(strKey == "[L]")
	{
		iResult_ = OF_KEY_LEFT;
	}
	else if(strKey == "[R]")
	{
		iResult_ = OF_KEY_RIGHT;
	}
	else
	{
		iResult_ = '[';
	}

	return iResult_;
}