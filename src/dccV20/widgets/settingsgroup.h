// SPDX-FileCopyrightText: 2016 - 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef SETTINGSGROUP_H
#define SETTINGSGROUP_H

#include <DBackgroundGroup>

#include <QFrame>
#include <QTimer>

#include "widgets/translucentframe.h"

class QVBoxLayout;

DWIDGET_USE_NAMESPACE

namespace dcc {
namespace widgets {

class SettingsItem;
class SettingsHeaderItem;

class SettingsGroup : public TranslucentFrame
{
    Q_OBJECT

public:
    enum BackgroundStyle {
        ItemBackground = 0,
        GroupBackground,
        NoneBackground
    };

    explicit SettingsGroup(QFrame *parent = nullptr, BackgroundStyle bgStyle = ItemBackground);
    explicit SettingsGroup(const QString &title, QFrame *parent = nullptr);
    ~SettingsGroup();

    SettingsHeaderItem *headerItem() const { return m_headerItem; }
    void setHeaderVisible(const bool visible);

    SettingsItem *getItem(int index);
    void insertWidget(QWidget *widget);
    void insertItem(const int index, SettingsItem *item);
    void appendItem(SettingsItem *item);
    void appendItem(SettingsItem *item, BackgroundStyle bgStyle);
    /**
     * @brief 从group中移除item，并析构它，如果不想析构item，可使用`removeItemAndNotDestruct`方法
     */
    void removeItem(SettingsItem *item);
    void removeItemAndNotDestruct(SettingsItem *item);
    void moveItem(SettingsItem *item, const int index);
    void setSpacing(const int spaceing);
    SettingsItem *searchItem(const QString& title);

    int itemCount() const;
    void clear();
    QVBoxLayout *getLayout() const { return m_layout; }

private:
    BackgroundStyle m_bgStyle{ItemBackground};
    QVBoxLayout *m_layout;
    SettingsHeaderItem *m_headerItem;
    DTK_WIDGET_NAMESPACE::DBackgroundGroup *m_bggroup{nullptr};
};

}
}

#endif // SETTINGSGROUP_H
