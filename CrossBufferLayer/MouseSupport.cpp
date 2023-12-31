#include "MouseSupport.h"

CS_Mouse::CS_Mouse(){
    x = 0;
    y = 0;
    lastX = 0;
    lastY = 0;
    deltaX = 0;
    deltaY = 0;
    windowWidth = 0;
    windowHeight = 0;

    lBtnState = csFalse;
    mBtnState = csFalse;
    rBtnState = csFalse;
    infinityMode = csFalse;
}

CS_Mouse::CS_Mouse(i32 windowWidth_, i32 windowHeight_){
    x = 0;
    y = 0;
    lastX = 0;
    lastY = 0;
    deltaX = 0;
    deltaY = 0;
    windowWidth = windowWidth_;
    windowHeight = windowHeight_;

    lBtnState = csFalse;
    mBtnState = csFalse;
    rBtnState = csFalse;
    infinityMode = csFalse;
}

string CS_Mouse::ToString(){
    stringstream ss;
    
    ss << "MouseX: ";
    ss << x;
    ss << "; MouseY: ";
    ss << y;

    ss << "; WindowWidth: ";
    ss << windowWidth;
    ss << "; WindowHeight: ";
    ss << windowHeight;
    

    ss << "; LBtnState: ";
    if (lBtnState == csTrue) {
        ss << "True";
    }
    else {
        ss << "False";
    }


    ss << "; MBtnState: ";
    if (mBtnState == csTrue) {
        ss << "True";
    }
    else {
        ss << "False";
    }


    ss << "; RBtnState: ";
    if (rBtnState == csTrue) {
        ss << "True";
    }
    else {
        ss << "False";
    }

    ss << "; InfinityMode: ";
    if (infinityMode == csTrue) {
        ss << "True";
    }
    else {
        ss << "False";
    }
    
    ss << "\n";
    return ss.str();
}

void CS_Mouse::OpenInfinityMode(){
    infinityMode = csTrue;
}

void CS_Mouse::CloseInfinityMode(){
    infinityMode = csFalse;
}

i32 CS_Mouse::GetX()
{
	return x;
}

i32 CS_Mouse::GetY()
{
	return y;
}

i32 CS_Mouse::GetLastX()
{
	return lastX;
}

i32 CS_Mouse::GetLastY()
{
	return lastY;
}

i32 CS_Mouse::GetDeltaX()
{
	return deltaX;
}

i32 CS_Mouse::GetDeltaY()
{
	return deltaY;
}

i32 CS_Mouse::GetWindowWidth()
{
	return windowWidth;
}

i32 CS_Mouse::GetWindowHeight()
{
	return windowHeight;
}

bool CS_Mouse::GetLBtnState()
{
	return lBtnState;
}

bool CS_Mouse::GetMBtnState()
{
	return mBtnState;
}

bool CS_Mouse::GetRBtnState()
{
	return rBtnState;
}

csbool CS_Mouse::IsInfinityModeOpened()
{
    return infinityMode;
}

void CS_Mouse::__DONT_USE__SetX(i32 x_)
{
	x = x_;
}

void CS_Mouse::__DONT_USE__SetY(i32 y_)
{
	y = y_;
}

void CS_Mouse::__DONT_USE__SetLastX(i32 lastX_)
{
	lastX = lastX_;
}

void CS_Mouse::__DONT_USE__SetLastY(i32 lastY_)
{
	lastY = lastY_;
}

void CS_Mouse::__DONT_USE__SetDeltaX(i32 deltaX_)
{
	deltaX = deltaX_;
}

void CS_Mouse::__DONT_USE__SetDeltaY(i32 deltaY_)
{
	deltaY = deltaY_;
}

void CS_Mouse::__DONT_USE__SetLBtnState(csbool lBtnState_)
{
	lBtnState = lBtnState_;
}

void CS_Mouse::__DONT_USE__SetMBtnState(csbool mBtnState_)
{
	mBtnState = mBtnState_;
}

void CS_Mouse::__DONT_USE__SetRBtnState(csbool rBtnState_)
{
	rBtnState = rBtnState_;
}
