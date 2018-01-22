/****************************************************************************************/
/*********************************** GameTime header ************************************/
/****************************************************************************************/
/* To do animation correctly, we will need to keep track of the time. In particular, we */
/* will need to measure the amount of time that elapses between frames of animation. If */
/* the frame rate is high, these time intervals between frames will be very short;      */
/* therefore, we need a timer with a high level of accuracy.                            */
/****************************************************************************************/

#ifndef GAMETIMER_H
#define GAMETIMER_H

class GameTimer {

public:
	GameTimer();

	float TotalTime()const; //in seconds
	float DeltaTime()const; //in seconds

	void Reset(); //Call before message loop
	void Start(); //Call when unpaused
	void Stop(); //Call when paused
	void Tick(); //Call every frame

private:
	double mSecondsPerCount;
	double mDeltaTime;

	__int64 mBaseTime;
	__int64 mPausedTime;
	__int64 mStopTime;
	__int64 mPrevTime;
	__int64 mCurrTime;

	bool mStopped;

};

#endif