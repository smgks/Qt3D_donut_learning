#include "custromcam.h"

CustromCam::CustromCam(Qt3DCore::QNode *parent) : Qt3DCore::QEntity(parent)
{
    m_keyUpPressed = 0;
    m_leftMouseBtnPressed = 0;

    m_lookSpeed = 100;
    m_linearSpeed = 100;

    m_dx = 0;
    m_dy = 0;

    m_mouseDevice = new Qt3DInput::QMouseDevice(this);
    m_keyBoardDevice = new Qt3DInput::QKeyboardDevice(this);

    m_logicalDevice = new Qt3DInput::QLogicalDevice(this);

    m_keyUpAction = new Qt3DInput::QAction(this);
    m_leftMouseBtnAction = new Qt3DInput::QAction(this);
    m_keyUpActionInput = new Qt3DInput::QActionInput(this);
    m_leftMouseBtnActionInput = new Qt3DInput::QActionInput(this);

    m_xAxis = new Qt3DInput::QAxis(this);
    m_xAxis->setObjectName("xAxis");

    m_yAxis = new Qt3DInput::QAxis(this);
    m_yAxis->setObjectName("yAxis");

    m_mouseInputX = new Qt3DInput::QAnalogAxisInput(this);
    m_mouseInputY = new Qt3DInput::QAnalogAxisInput(this);

    m_frameAction = new Qt3DLogic::QFrameAction(this);

    m_keyUpActionInput->setButtons(QVector<int>() << Qt::Key_Up);
    m_keyUpActionInput->setSourceDevice(m_keyBoardDevice);
    m_keyUpAction->addInput(m_keyUpActionInput);
    m_keyUpAction->setObjectName("keyUp");

    m_leftMouseBtnActionInput->setButtons(QVector<int>() << Qt::LeftButton);
    m_leftMouseBtnActionInput->setSourceDevice(m_mouseDevice);
    m_leftMouseBtnAction->addInput(m_leftMouseBtnActionInput);
    m_leftMouseBtnAction->setObjectName("leftMBtn");

    m_mouseInputX->setAxis(Qt3DInput::QMouseDevice::X);
    m_mouseInputX->setSourceDevice(m_mouseDevice);
    m_xAxis->addInput(m_mouseInputX);

    m_mouseInputY->setAxis(Qt3DInput::QMouseDevice::Y);
    m_mouseInputY->setSourceDevice(m_mouseDevice);
    m_yAxis->addInput(m_mouseInputY);

    m_logicalDevice->addAction(m_keyUpAction);
    m_logicalDevice->addAction(m_leftMouseBtnAction);
    m_logicalDevice->addAxis(m_xAxis);
    m_logicalDevice->addAxis(m_yAxis);

    connect(m_keyUpAction,SIGNAL(activeChanged(bool)),this,SLOT(activeChanged(bool)));
    connect(m_leftMouseBtnAction,SIGNAL(activeChanged(bool)),this,SLOT(activeChanged(bool)));
    connect(m_xAxis,SIGNAL(valueChanged(float)),SLOT(valueChanged(float)));
    connect(m_yAxis,SIGNAL(valueChanged(float)),SLOT(valueChanged(float)));
    connect(m_frameAction,SIGNAL(triggered(float)),this,SLOT(frameActionTriggered(float)));
}

void CustromCam::setCamera(Qt3DRender::QCamera *camera)
{
    m_camera = camera;
}

float CustromCam::lookSpeed() const
{
    return m_lookSpeed;
}

void CustromCam::setLookSpeed(float lookSpeed)
{
    m_lookSpeed = lookSpeed;
}

float CustromCam::linearSpeed() const
{
    return m_linearSpeed;
}

void CustromCam::setLinearSpeed(float linearSpeed)
{
    m_linearSpeed = linearSpeed;
}

void CustromCam::activeChanged(bool b)
{
    if(sender()->objectName ()== "keyUp"){
        m_keyUpPressed = b;
    }
    if(sender()->objectName() == "leftMBtn"){
        m_leftMouseBtnPressed = b;
    }
}

void CustromCam::valueChanged(float value)
{
    if(sender()->objectName() == "xAxis"){
        m_dx = value;
    }
    if(sender()->objectName() == "yAxis"){
        m_dy = value;
    }
}

void CustromCam::frameActionTriggered(float dt)
{
    if(m_camera == 0){
        return;
    }
    if(m_leftMouseBtnPressed == 1){
        m_camera->panAboutViewCenter(m_dx * m_lookSpeed * dt * -1);
        m_camera->tiltAboutViewCenter(m_dy * m_lookSpeed  *dt * -1);
    }
    if(m_keyUpPressed == 1){
        m_camera->rollAboutViewCenter(0.5 * m_lookSpeed * dt);
    }
}
