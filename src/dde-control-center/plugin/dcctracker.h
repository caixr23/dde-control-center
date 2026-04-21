// SPDX-FileCopyrightText: 2024 - 2026 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later
#ifndef DCCTRACKER_H
#define DCCTRACKER_H

#include <QObject>
#include <QDateTime>
#include <QHash>
#include <QMutex>

namespace dccV25 {

class DccTracker : public QObject
{
    Q_OBJECT

public:
    struct ObjectInfo
    {
        QString typeName;
        QString objectName;
        QDateTime addTime;
        QDateTime destroyTime;
        bool destroyed = false;
    };

    static DccTracker *instance();

    void addObject(QObject *obj);
    void removeObject(QObject *obj);
    void printUnreleasedObjects();

private:
    explicit DccTracker(QObject *parent = nullptr);
    ~DccTracker() override;

    static DccTracker *m_instance;
    QHash<QObject *, ObjectInfo> m_objects;
    QMutex m_mutex;
};

} // namespace dccV25

#endif // DCCTRACKER_H
