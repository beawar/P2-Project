#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <QPushButton>
#include <QMouseEvent>

class PushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit PushButton(QWidget *parent = 0);
    PushButton(const QIcon& icon, const QString& s = "", QWidget *parent = 0);
    PushButton(const QString& s, QWidget *parent = 0);
private slots:
    void mousePressEvent(QMouseEvent *e);
signals:
 void rightClicked();
public slots:

};

#endif // PUSHBUTTON_H
