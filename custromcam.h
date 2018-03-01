#ifndef CUSTOMCAM_H
#define CUSTOMCAM_H

#include <Qt3DCore/QEntity>
#include <Qt3DInput>
#include <Qt3DRender>
#include <Qt3DLogic>
class CustromCam : public Qt3DCore::QEntity
{
    Q_OBJECT
public:
    CustromCam(Qt3DCore::QNode *parent = Q_NULLPTR);
    void setCamera(Qt3DRender::QCamera *camera);

    float lookSpeed() const;
    void setLookSpeed(float lookSpeed);

    float linearSpeed() const;
    void setLinearSpeed(float linearSpeed);
protected slots:
    void activeChanged(bool);
    void valueChanged(float value);
    void frameActionTriggered(float dt);

private:
    Qt3DInput::QKeyboardDevice *m_keyBoardDevice;
    Qt3DInput::QMouseDevice *m_mouseDevice;
    Qt3DInput::QLogicalDevice *m_logicalDevice;
    Qt3DInput::QAction *m_leftMouseBtnAction;
    Qt3DInput::QAction *m_keyUpAction;
    Qt3DInput::QActionInput *m_keyUpActionInput;
    Qt3DInput::QActionInput *m_leftMouseBtnActionInput;
    Qt3DInput::QAxis *m_xAxis;
    Qt3DInput::QAxis *m_yAxis;

    Qt3DInput::QAnalogAxisInput *m_mouseInputX;
    Qt3DInput::QAnalogAxisInput *m_mouseInputY;

    Qt3DRender::QCamera *m_camera;

    Qt3DLogic::QFrameAction *m_frameAction;

    float m_lookSpeed;
    float m_linearSpeed;

    bool m_leftMouseBtnPressed;
    bool m_keyUpPressed;

    float m_dx;
    float m_dy;
};

#endif // CUSTOMCAM_H
