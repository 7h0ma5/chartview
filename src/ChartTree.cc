#include <QHeaderView>
#include "ChartTree.h"

Q_DECLARE_METATYPE(Chart*);

ChartTree::ChartTree(Database* db) {
    this->header()->hide();
    this->db = db;

    QObject::connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)),
                     this, SLOT(itemSelected(QTreeWidgetItem*, int)));
}

void ChartTree::rebuild() {
    for (int i = 0; i < this->topLevelItemCount(); ++i) {
        qDeleteAll(this->topLevelItem(i)->takeChildren());
    }
    this->clear();

    QStringList list = db->getAirportList();
    qSort(list.begin(), list.end());

    foreach(QString apt, list) {
        QTreeWidgetItem* item = new QTreeWidgetItem();
        item->setText(0, apt);
        Airport* airport = db->getAirport(apt);
        this->fillAirport(item, airport);
        this->addTopLevelItem(item);
    }
}

void ChartTree::fillAirport(QTreeWidgetItem* item, Airport* airport) {
    this->fillCategory(item, "Unknown", airport->getCharts(Chart::UNKNOWN));
    this->fillCategory(item, "Ground", airport->getCharts(Chart::GROUND));
    this->fillCategory(item, "SID", airport->getCharts(Chart::SID));
    this->fillCategory(item, "STAR", airport->getCharts(Chart::STAR));
    this->fillCategory(item, "Approach", airport->getCharts(Chart::APPR));
    this->fillCategory(item, "Transition", airport->getCharts(Chart::TRANS));
    this->fillCategory(item, "Misc", airport->getCharts(Chart::MISC));
}

void ChartTree::fillCategory(QTreeWidgetItem* item, QString name, QList<Chart*> charts) {
    if (!charts.count()) return;

    QTreeWidgetItem* category = new QTreeWidgetItem;
    category->setText(0, name);
    item->addChild(category);

    foreach(Chart* chart, charts) {
        QTreeWidgetItem* chartItem = new QTreeWidgetItem;
        chartItem->setText(0, chart->getName());
        chartItem->setData(0, Qt::UserRole, qVariantFromValue(chart));
        category->addChild(chartItem);
    }
}

void ChartTree::itemSelected(QTreeWidgetItem* item, int column) {
    Chart* chart = qVariantValue<Chart*>(item->data(0, Qt::UserRole));
    if (chart) {
        emit chartSelected(chart);
    }
}
