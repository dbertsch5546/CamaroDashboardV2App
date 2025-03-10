#include "iconController.h"

iconController::iconController(QObject *parent) : QObject(parent){

}

bool iconController::isLeftTurnVisible() const{
    return m_isLeftTurnVisible;
}

void iconController::setLeftTurnVisible(bool setLeftTurnVisibility){
    if (m_isLeftTurnVisible != setLeftTurnVisibility) {
        m_isLeftTurnVisible = setLeftTurnVisibility;
        emit leftTurnVisibilityChanged();
    }
}

bool iconController::isRightTurnVisible() const{
    return m_isRightTurnVisible;
}

void iconController::setRightTurnVisible(bool setRightTurnVisibility){
    if (m_isRightTurnVisible != setRightTurnVisibility) {
        m_isRightTurnVisible = setRightTurnVisibility;
        emit rightTurnVisibilityChanged();
    }
}

bool iconController::isHeadlightVisible() const{
    return m_isHeadlightVisible;
}

void iconController::setHeadlightVisible(bool setHeadlightVisibility){
    if (m_isHeadlightVisible != setHeadlightVisibility) {
        m_isHeadlightVisible = setHeadlightVisibility;
        emit headlightVisibilityChanged();
    }
}

bool iconController::isHighBeamVisible() const{
    return m_isHighBeamVisible;
}

void iconController::setHighBeamVisible(bool setHighBeamVisibility){
    if (m_isHighBeamVisible != setHighBeamVisibility) {
        m_isHighBeamVisible = setHighBeamVisibility;
        emit highBeamVisibilityChanged();
    }
}

