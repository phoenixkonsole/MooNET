// Copyright (c) 2019 The PIVX developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QWidget>
#include "qt/moonet/pwidget.h"
#include "qt/moonet/settings/settingsbackupwallet.h"
#include "qt/moonet/settings/settingsexportcsv.h"
#include "qt/moonet/settings/settingsbittoolwidget.h"
#include "qt/moonet/settings/settingssignmessagewidgets.h"
#include "qt/moonet/settings/settingswalletrepairwidget.h"
#include "qt/moonet/settings/settingswalletoptionswidget.h"
#include "qt/moonet/settings/settingsmainoptionswidget.h"
#include "qt/moonet/settings/settingsdisplayoptionswidget.h"
#include "qt/moonet/settings/settingsmultisendwidget.h"
#include "qt/moonet/settings/settingsinformationwidget.h"
#include "qt/moonet/settings/settingsconsolewidget.h"

class muuGUI;

QT_BEGIN_NAMESPACE
class QDataWidgetMapper;
QT_END_NAMESPACE

namespace Ui {
class SettingsWidget;
}

class SettingsWidget : public PWidget
{
    Q_OBJECT

public:
    explicit SettingsWidget(muuGUI* parent);
    ~SettingsWidget();

    void loadClientModel() override;
    void loadWalletModel() override;
    void setMapper();
    void showDebugConsole();

signals:
    /** Get restart command-line parameters and handle restart */
    void handleRestart(QStringList args);

private slots:
    // File
    void onFileClicked();
    void onBackupWalletClicked();
    void onSignMessageClicked();
    void onExportCSVClicked();

    // Wallet Configuration
    void onConfigurationClicked();
    void onBipToolClicked();
    void onMultisendClicked();

    // Options
    void onOptionsClicked();
    void onMainOptionsClicked();
    void onWalletOptionsClicked();
    void onDisplayOptionsClicked();

    void onDiscardChanges();

    // Tools
    void onToolsClicked();
    void onInformationClicked();
    void onDebugConsoleClicked();
    void onWalletRepairClicked();

    // Help
    void onHelpClicked();
    void onAboutClicked();

    void onResetAction();
    void onSaveOptionsClicked();
private:
    Ui::SettingsWidget *ui;

    SettingsBackupWallet *settingsBackupWallet;
    SettingsExportCSV *settingsExportCsvWidget;
    SettingsBitToolWidget *settingsBitToolWidget;
    SettingsSignMessageWidgets *settingsSingMessageWidgets;
    SettingsWalletRepairWidget *settingsWalletRepairWidget;
    SettingsWalletOptionsWidget *settingsWalletOptionsWidget;
    SettingsMainOptionsWidget *settingsMainOptionsWidget;
    SettingsDisplayOptionsWidget *settingsDisplayOptionsWidget;
    SettingsMultisendWidget *settingsMultisendWidget;
    SettingsInformationWidget *settingsInformationWidget;
    SettingsConsoleWidget *settingsConsoleWidget;

    QDataWidgetMapper* mapper;

    QList<QPushButton*> options;

    void selectOption(QPushButton* option);
    void openStandardDialog(QString title = "", QString body = "", QString okBtn = "OK", QString cancelBtn = "");
};

#endif // SETTINGSWIDGET_H
