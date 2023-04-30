#include "CanBusEventHandler.h"

CanBusEventHandler::CanBusEventHandler(        
        SpeedDisplayer *speedDisplayer, 
        HeadingDisplayer *headingDisplayer, 
        NavModeDisplayer *navModeDisplayer, 
        AltitudeDisplayer *altitudeDisplayer, 
        VerticalDisplayer *verticalDisplayer
) {
    _speedDisplayer = speedDisplayer;
    _headingDisplayer = headingDisplayer; 
    _navModeDisplayer = navModeDisplayer; 
    _altitudeDisplayer = altitudeDisplayer; 
    _verticalDisplayer = verticalDisplayer;
    _forceRefreshDisplay = true;
}

void CanBusEventHandler::frameReceived(Frame *frame)
{
    SERIAL_PRINTLN("frame " + String(frame->getId()));
    
    switch (frame->getId()) {
        case FcuDisplayFrame::ID :
            _fcuDisplayFrame.decode(frame);
            if(_brightnessSevenSegmentsFrame.fcu != 0x0) {
                display();
            }
            break;
        case BrightnessSevenSegmentsFrame::ID :
            _brightnessSevenSegmentsFrame.decode(frame);
            
            setContrast(_brightnessSevenSegmentsFrame.fcu);
            
            if(_brightnessSevenSegmentsFrame.fcu == 0x0) {
                displayNone();
            } else if(_brightnessSevenSegmentsFrame.isTestLight) {
                setTestLightIndicators();
            } else {
                display();
            }
            
            break;
    }
}

void CanBusEventHandler::setContrast(unsigned char contrast)
{
    _speedDisplayer->setContrast(contrast);
    _headingDisplayer->setContrast(contrast);
    _navModeDisplayer->setContrast(contrast);
    _altitudeDisplayer->setContrast(contrast);
    _verticalDisplayer->setContrast(contrast);
}

void CanBusEventHandler::displayNone()
{
    _speedDisplayer->displayNone();
    _headingDisplayer->displayNone();
    _navModeDisplayer->displayNone();
    _altitudeDisplayer->displayNone();
    _verticalDisplayer->displayNone();
    _forceRefreshDisplay = true;
}

void CanBusEventHandler::setTestLightIndicators()
{
    _speedDisplayer->displayTest();
    _headingDisplayer->displayTest();
    _navModeDisplayer->displayTest();
    _altitudeDisplayer->displayTest();
    _verticalDisplayer->displayTest();
    _forceRefreshDisplay = true;
}

void CanBusEventHandler::display()
{
    if(_speedDisplayer->checkMutation(&_fcuDisplayFrame) || _forceRefreshDisplay) {
        _speedDisplayer->display(&_fcuDisplayFrame);
    }

    if(_headingDisplayer->checkMutation(&_fcuDisplayFrame) || _forceRefreshDisplay) {
        _headingDisplayer->display(&_fcuDisplayFrame);
    }

    if(_navModeDisplayer->checkMutation(&_fcuDisplayFrame) || _forceRefreshDisplay) {
        _navModeDisplayer->display(&_fcuDisplayFrame);
    }

    if(_altitudeDisplayer->checkMutation(&_fcuDisplayFrame) || _forceRefreshDisplay) {
        _altitudeDisplayer->display(&_fcuDisplayFrame);
    }

    if(_verticalDisplayer->checkMutation(&_fcuDisplayFrame) || _forceRefreshDisplay) {
        _verticalDisplayer->display(&_fcuDisplayFrame);
    }

    _forceRefreshDisplay = false;
}