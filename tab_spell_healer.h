#ifndef TAB_SPELL_HEALER_H
#define TAB_SPELL_HEALER_H

#include <QWidget>

namespace Ui {
class TabSpellHealer;
}

class TabSpellHealer : public QWidget
{
    Q_OBJECT

public:
    explicit TabSpellHealer(QWidget *parent = nullptr);
    ~TabSpellHealer();

private:
    Ui::TabSpellHealer *ui;
};

#endif // TAB_SPELL_HEALER_H
