// Copyright (c) 2019 The PIVX developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef NAVMENUWIDGET_H
#define NAVMENUWIDGET_H

#include <QWidget>

class muuGUI;

namespace Ui {
class NavMenuWidget;
}

class NavMenuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NavMenuWidget(muuGUI* mainWindow, QWidget *parent = nullptr);
    ~NavMenuWidget();

public slots:
    void selectSettings();

private slots:
    void onSendClicked();
    void onDashboardClicked();
    void onLinksClicked();
    void onAddressClicked();
    void onMasterNodesClicked();
    void onSettingsClicked();
    void onReceiveClicked();
    void updateButtonStyles();
private:
    Ui::NavMenuWidget *ui;
    muuGUI* window;
    QList<QWidget*> btns;

    void connectActions();
    void onNavSelected(QWidget* active, bool startup = false);
};

#endif // NAVMENUWIDGET_H
