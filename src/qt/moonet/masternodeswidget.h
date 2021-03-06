// Copyright (c) 2019 The PIVX developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef MASTERNODESWIDGET_H
#define MASTERNODESWIDGET_H

#include <QWidget>
#include "qt/moonet/pwidget.h"
#include "qt/moonet/furabstractlistitemdelegate.h"
#include "qt/moonet/mnmodel.h"
#include "qt/moonet/tooltipmenu.h"
#include <QTimer>
#include "masternodeman.h"
#include "main.h"
class muuGUI;
#if defined(HAVE_CONFIG_H)
#include "config/moonet-config.h" /* for USE_QTCHARTS */
#endif

#ifdef USE_QTCHARTS

#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

QT_CHARTS_USE_NAMESPACE

using namespace QtCharts;

#endif
namespace Ui {
class MasterNodesWidget;
}

QT_BEGIN_NAMESPACE
class QModelIndex;
QT_END_NAMESPACE

class MasterNodesWidget : public PWidget
{
    Q_OBJECT

public:

    explicit MasterNodesWidget(muuGUI *parent = nullptr);
    ~MasterNodesWidget();

    void loadWalletModel() override;
    void showEvent(QShowEvent *event) override;
    void hideEvent(QHideEvent *event) override;
    void initChart();
    void loadChart();
    void showHideEmptyChart(bool showEmpty, bool loading, bool forceView);
private slots:
    void changeTheme(bool isLightTheme, QString &theme) override;
    void onMNClicked(const QModelIndex &index);
    void onEditMNClicked();
    void onDeleteMNClicked();
    void onInfoMNClicked();
    void updateListState();
    void onTierChartBtnClicked();
    void onCreateMNClicked();
#ifdef USE_QTCHARTS
    void changeChartColors();
#endif
private:
    Ui::MasterNodesWidget *ui;
    FurAbstractListItemDelegate *delegate;
    MNModel *mnModel = nullptr;
    TooltipMenu* menu = nullptr;
    QModelIndex index;
    QTimer *timer = nullptr;
    #ifdef USE_QTCHARTS
    QChart *chart = nullptr;
    QChartView *chartView = nullptr;
    QPieSeries *series;
    #endif
    int tier1 = 0,tier2 = 0,tier3 = 0,tier4 = 0,tier5 = 0; 
    void startAlias(QString strAlias);
};

#endif // MASTERNODESWIDGET_H
