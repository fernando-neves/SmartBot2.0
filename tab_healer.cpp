#include "tab_healer.h"
#include "ui_tab_healer.h"
#include "tab_spell_healer.h"

TabHealer::TabHealer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TabHealer)
{
    ui->setupUi(this);
    this->initializeTabs();
}

TabHealer::~TabHealer()
{
    delete ui;
}

void TabHealer::initializeTabs()
{
    ui->tabWidget->addTab(new TabSpellHealer(this),"Spell Healer");
}
