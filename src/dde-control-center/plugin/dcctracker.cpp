// SPDX-FileCopyrightText: 2024 - 2026 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "dcctracker.h"

#include "dccobject.h"

#include <QDebug>

namespace dccV25 {

DccTracker *DccTracker::m_instance = nullptr;

DccTracker *DccTracker::instance()
{
    if (!m_instance) {
        m_instance = new DccTracker();
    }
    return m_instance;
}

DccTracker::DccTracker(QObject *parent)
    : QObject(parent)
{
}

DccTracker::~DccTracker()
{
}

void DccTracker::addObject(QObject *obj)
{
    if (!obj)
        return;

    QMutexLocker locker(&m_mutex);
    ObjectInfo info;
    info.typeName = obj->metaObject()->className();
    info.objectName = obj->objectName();
    info.addTime = QDateTime::currentDateTime();
    info.destroyed = false;
    m_objects.insert(obj, info);
    qWarning() << __LINE__ << __FUNCTION__
               << "Object add:" << obj
               << "Type:" << m_objects[obj].typeName
               << "ObjectName:" << m_objects[obj].objectName << obj->objectName()
               << "Added at:" << m_objects[obj].addTime.toString("yyyy-mm-dd HH:MM:ss.zzz");

    connect(obj, &QObject::destroyed, this, [this, obj]() {
        removeObject(obj);
    });
    DccObject *dObj = qobject_cast<DccObject*>(obj);
    if(dObj){
        connect(dObj, &DccObject::objectDestroyed, this, [this, obj]() {
            removeObject(obj);
        });
    }
}

void DccTracker::removeObject(QObject *obj)
{
    QMutexLocker locker(&m_mutex);
    if (m_objects.contains(obj)) {
        m_objects[obj].destroyTime = QDateTime::currentDateTime();
        m_objects[obj].destroyed = true;
        qWarning() << __LINE__ << __FUNCTION__
                   << "Object destroyed:" << obj
                   << "Type:" << m_objects[obj].typeName
                   << "ObjectName:" << m_objects[obj].objectName << obj->objectName()
                   << "Added at:" << m_objects[obj].addTime.toString("yyyy-mm-dd HH:MM:ss.zzz")
                   << "Destroyed at:" << m_objects[obj].destroyTime.toString("yyyy-mm-dd HH:MM:ss.zzz");
        m_objects.remove(obj);
    }
}

void DccTracker::printUnreleasedObjects()
{
    QMutexLocker locker(&m_mutex);
    int count = 0;
    for (auto it = m_objects.constBegin(); it != m_objects.constEnd(); ++it) {
        if (!it.value().destroyed) {
            count++;
            qWarning() << __LINE__ << __FUNCTION__
                       << "Unreleased object:" << it.key()
                       << "Type:" << it.value().typeName
                       << "ObjectName:" << it.value().objectName << it.key()->objectName()
                       << "Added at:" << it.value().addTime.toString("yyyy-mm-dd HH:MM:ss.zzz");
        }
    }
    if (count == 0) {
        qWarning() << __LINE__ << __FUNCTION__ << "All objects have been released.";
    } else {
        qWarning() << __LINE__ << __FUNCTION__ << "Total unreleased objects:" << count;
    }
}

} // namespace dccV25
