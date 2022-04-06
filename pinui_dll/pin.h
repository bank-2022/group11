#ifndef PIN_H
#define PIN_H

#include <QDialog>

namespace Ui {
class Pin;
}

class Pin : public QDialog
{
    Q_OBJECT

public:
    explicit Pin(QWidget *parent = nullptr);
    ~Pin();

private:
    Ui::Pin *ui;
    QString dialogValue;
};

#endif // PIN_H
