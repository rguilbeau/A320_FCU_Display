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
        case FRAME_ID_FCU_DISPLAY:
            _fcuDisplayFrame.decode(frame);

            if(!_fcuDisplayFrame.isPowerOn) {
                setPowerOff();
            } else {
                display();
            }
            break;
        case FRAME_ID_LIGHT_INDICATORS:
            _lightIndicatorsFrame.decode(frame);

            if(_lightIndicatorsFrame.isTestLight) {
                setTestLightIndicators();
            } else {
                display();
            }
            break;
        case FRAME_ID_BRIGHTNESS:
            _brightnessFrame.decode(frame);

            //setContrast();
            break;
    }
}

void CanBusEventHandler::setContrast()
{
    _speedDisplayer->setContrast(_brightnessFrame.fcuDisplayContrast);
    _headingDisplayer->setContrast(_brightnessFrame.fcuDisplayContrast);
    _navModeDisplayer->setContrast(_brightnessFrame.fcuDisplayContrast);
    _altitudeDisplayer->setContrast(_brightnessFrame.fcuDisplayContrast);
    _verticalDisplayer->setContrast(_brightnessFrame.fcuDisplayContrast);
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

void CanBusEventHandler::setPowerOff()
{
    _speedDisplayer->displayNone();
    _headingDisplayer->displayNone();
    _navModeDisplayer->displayNone();
    _altitudeDisplayer->displayNone();
    _verticalDisplayer->displayNone();
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