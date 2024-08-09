// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef MULTISELECTLISTVIEW_H
#define MULTISELECTLISTVIEW_H

#include <DListView>

DWIDGET_USE_NAMESPACE

class SmoothScrollBar;
namespace dcc {
namespace widgets {

class MultiSelectListView : public DListView
{
    Q_OBJECT
public:
    explicit MultiSelectListView(QWidget *parent = nullptr);
    void resetStatus(const QModelIndex &index);

protected:
    void currentChanged(const QModelIndex &current, const QModelIndex &previous) override;
    QModelIndex moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers) override;
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *e) override;
private:
    int m_currentIndex;
    SmoothScrollBar *m_scrollbar;
};

} // namespace widgets
} // namespace dcc

#endif // MULTISELECTLISTVIEW_H
