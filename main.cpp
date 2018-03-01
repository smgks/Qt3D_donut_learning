
#include <QGuiApplication>
#include <Qt3DExtras>
#include <Qt3DRender>
#include <QObject>

#include "custromcam.h"

Qt3DCore::QEntity *createEnt();

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);
    Qt3DExtras::Qt3DWindow window;;
    Qt3DCore::QEntity *rootEnt = createEnt();
    Qt3DRender::QCamera *camera = window.camera();

    CustromCam *control = new CustromCam(rootEnt);
    control->setCamera(camera);
    control->setLookSpeed(100.0f);
    control->setLinearSpeed(100.0f);

    camera->lens()->setPerspectiveProjection(65, float(window.width())/float(window.height()),0.1f,1000.0f);
    camera->setPosition(QVector3D(0.0f,0.0f,40.0f));
    camera->setViewCenter(QVector3D(0.0f,0.0f,0.0f));

    Qt3DExtras::QSkyboxEntity *skyEnt = new Qt3DExtras::QSkyboxEntity(control);
    skyEnt->setBaseName("qrc:/sky/Day_Skybox");
    skyEnt->setExtension(".png");

    window.setRootEntity(rootEnt);
    window.show();

    return a.exec();
}
Qt3DCore::QEntity *createEnt()
{
    Qt3DCore::QEntity *temp = new Qt3DCore::QEntity;


    Qt3DExtras::QTorusMesh *mesh = new Qt3DExtras::QTorusMesh(temp);
    mesh->setRadius(15.0f);
    mesh->setMinorRadius(6.0f);
    mesh->setSlices(16);
    mesh->setRings(256);


    Qt3DExtras::QPhongMaterial * phong = new Qt3DExtras::QPhongMaterial(temp);
    phong->setAmbient(Qt::green);
    Qt3DCore::QTransform *transform = new Qt3DCore::QTransform(temp);

    Qt3DRender::QPointLight *ligth = new Qt3DRender::QPointLight(temp);

    Qt3DCore::QEntity *ligthEnt = new Qt3DCore::QEntity(temp);
    ligth->setColor(Qt::white);
    ligthEnt->addComponent(ligth);

    Qt3DCore::QTransform *ligthTransform = new Qt3DCore::QTransform(ligthEnt);
    ligthTransform->setTranslation(QVector3D(0.0f,0.0f,3.0f));
    ligthEnt->addComponent(ligthTransform);

    temp->addComponent(mesh);
    temp->addComponent(phong);
    temp->addComponent(transform);
    return temp;
}
