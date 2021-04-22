#ifndef TAB_HEALER_H
#define TAB_HEALER_H

#include <QWidget>

namespace Ui {
class TabHealer;
}

class TabHealer : public QWidget
{
    Q_OBJECT

public:
    explicit TabHealer(QWidget *parent = nullptr);
    ~TabHealer();

private:
    void initializeTabs();

private:
    Ui::TabHealer *ui;
};

#endif // TAB_HEALER_H
