#ifndef SMOOTHSCROLLBAR_H
#define SMOOTHSCROLLBAR_H

#include <QWidget>
#include <QScrollBar>
#include <QPropertyAnimation>

class SmoothScrollBar : public QScrollBar
{
    Q_OBJECT
public:
    explicit SmoothScrollBar(QWidget *parent = nullptr);

signals:
    void scrollFinished();

public slots:
    void setValueSmooth(int value);
    void scrollSmooth(int value);
    void stopScroll();

protected:
    void mouseReleaseEvent(QMouseEvent *e) override;

private:
    int m_targetValue;

    QPropertyAnimation *m_propertyAnimation;
};


#endif // SMOOTHSCROLLBAR_H
