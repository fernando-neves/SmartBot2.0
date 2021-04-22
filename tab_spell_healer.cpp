#include "tab_spell_healer.h"
#include "ui_tab_spell_healer.h"

TabSpellHealer::TabSpellHealer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TabSpellHealer)
{
    ui->setupUi(this);
}

TabSpellHealer::~TabSpellHealer()
{
    delete ui;
}
