// Copyright (c) 2017-2019 The PIVX developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "zmuucontroldialog.h"
#include "ui_zmuucontroldialog.h"

#include "zmuu/accumulators.h"
#include "main.h"
#include "walletmodel.h"
#include "guiutil.h"


std::set<std::string> ZmuuControlDialog::setSelectedMints;
std::set<CMintMeta> ZmuuControlDialog::setMints;

bool CZmuuControlWidgetItem::operator<(const QTreeWidgetItem &other) const {
    int column = treeWidget()->sortColumn();
    if (column == ZmuuControlDialog::COLUMN_DENOMINATION || column == ZmuuControlDialog::COLUMN_VERSION || column == ZmuuControlDialog::COLUMN_CONFIRMATIONS)
        return data(column, Qt::UserRole).toLongLong() < other.data(column, Qt::UserRole).toLongLong();
    return QTreeWidgetItem::operator<(other);
}


ZmuuControlDialog::ZmuuControlDialog(QWidget *parent) :
    QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint),
    ui(new Ui::ZmuuControlDialog),
    model(0)
{
    ui->setupUi(this);
    setMints.clear();

    /* Open CSS when configured */
    this->setStyleSheet(GUIUtil::loadStyleSheet());

    ui->frame->setProperty("cssClass", "container-dialog");

    // Title
    ui->labelTitle->setText(tr("Select zmuu Denominations to Spend"));
    ui->labelTitle->setProperty("cssClass", "text-title-dialog");


    // Label Style
    ui->labelZmuu->setProperty("cssClass", "text-main-purple");
    ui->labelZmuu_int->setProperty("cssClass", "text-main-purple");
    ui->labelQuantity->setProperty("cssClass", "text-main-purple");
    ui->labelQuantity_int->setProperty("cssClass", "text-main-purple");

    ui->layoutAmount->setProperty("cssClass", "container-border-purple");
    ui->layoutQuantity->setProperty("cssClass", "container-border-purple");

    // Buttons

    ui->btnEsc->setText("");
    ui->btnEsc->setProperty("cssClass", "ic-close");
    ui->pushButtonAll->setProperty("cssClass", "btn-check");

    // click on checkbox
    connect(ui->treeWidget, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(updateSelection(QTreeWidgetItem*, int)));
    // push select/deselect all button
    connect(ui->pushButtonAll, SIGNAL(clicked()), this, SLOT(ButtonAllClicked()));
}

ZmuuControlDialog::~ZmuuControlDialog()
{
    delete ui;
}

void ZmuuControlDialog::setModel(WalletModel *model)
{
    this->model = model;
    updateList();
}


//Update the tree widget
void ZmuuControlDialog::updateList()
{
    // need to prevent the slot from being called each time something is changed
    ui->treeWidget->blockSignals(true);
    ui->treeWidget->clear();

    // add a top level item for each denomination
    QFlags<Qt::ItemFlag> flgTristate = Qt::ItemIsEnabled | Qt::ItemIsUserCheckable | Qt::ItemIsTristate;
    std::map<libzerocoin::CoinDenomination, int> mapDenomPosition;
    for (auto denom : libzerocoin::zerocoinDenomList) {
        CZmuuControlWidgetItem* itemDenom(new CZmuuControlWidgetItem);
        ui->treeWidget->addTopLevelItem(itemDenom);

        //keep track of where this is positioned in tree widget
        mapDenomPosition[denom] = ui->treeWidget->indexOfTopLevelItem(itemDenom);

        itemDenom->setFlags(flgTristate);
        itemDenom->setText(COLUMN_DENOMINATION, QString::number(denom));
        itemDenom->setData(COLUMN_DENOMINATION, Qt::UserRole, QVariant((qlonglong) denom));
    }

    

    ui->treeWidget->blockSignals(false);
    updateLabels();
}

// Update the list when a checkbox is clicked
void ZmuuControlDialog::updateSelection(QTreeWidgetItem* item, int column)
{
    // only want updates from non top level items that are available to spend
    if (item->parent() && column == COLUMN_CHECKBOX && !item->isDisabled()){

        // see if this mint is already selected in the selection list
        std::string strPubcoin = item->text(COLUMN_PUBCOIN).toStdString();
        bool fSelected = setSelectedMints.count(strPubcoin);

        // set the checkbox to the proper state and add or remove the mint from the selection list
        if (item->checkState(COLUMN_CHECKBOX) == Qt::Checked) {
            if (fSelected) return;
            setSelectedMints.insert(strPubcoin);
        } else {
            if (!fSelected) return;
            setSelectedMints.erase(strPubcoin);
        }
        updateLabels();
    }
}

// Update the Quantity and Amount display
void ZmuuControlDialog::updateLabels()
{
    int64_t nAmount = 0;
    for (const CMintMeta& mint : setMints) {
        if (setSelectedMints.count(mint.hashPubcoin.GetHex()))
            nAmount += mint.denom;
    }

    //update this dialog's labels
    ui->labelZmuu_int->setText(QString::number(nAmount));
    ui->labelQuantity_int->setText(QString::number(setSelectedMints.size()));

    //update PrivacyDialog labels
    //privacyDialog->setZmuuControlLabels(nAmount, setSelectedMints.size());
}

std::vector<CMintMeta> ZmuuControlDialog::GetSelectedMints()
{
    std::vector<CMintMeta> listReturn;
    for (const CMintMeta& mint : setMints) {
        if (setSelectedMints.count(mint.hashPubcoin.GetHex()))
            listReturn.emplace_back(mint);
    }

    return listReturn;
}

// select or deselect all of the mints
void ZmuuControlDialog::ButtonAllClicked()
{
    ui->treeWidget->blockSignals(true);
    Qt::CheckState state = Qt::Checked;
    for (int i = 0; i < ui->treeWidget->topLevelItemCount(); i++) {
        if(ui->treeWidget->topLevelItem(i)->checkState(COLUMN_CHECKBOX) != Qt::Unchecked) {
            state = Qt::Unchecked;
            break;
        }
    }

    //much quicker to start from scratch than to have QT go through all the objects and update
    ui->treeWidget->clear();

    if (state == Qt::Checked) {
        for(const CMintMeta& mint : setMints)
            setSelectedMints.insert(mint.hashPubcoin.GetHex());
    } else {
        setSelectedMints.clear();
    }

    updateList();
}
