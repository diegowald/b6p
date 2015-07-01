#ifndef MULTICOLORLEDWIDGET_H
#define MULTICOLORLEDWIDGET_H

#include <QWidget>

class MulticolorLedWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MulticolorLedWidget(QWidget *parent = 0);

    void setBackgroundColor(QColor color);
    QColor backgroundColor() const;

    void setLedColor(QColor color);
    QColor ledColor() const;

protected:
    void paintEvent(QPaintEvent *paintEvt);

signals:

public slots:

private:
    QColor m_BackgroundColor;
    QColor m_LedColor;
};

#endif // MULTICOLORLEDWIDGET_H
