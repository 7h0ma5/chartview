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

        foreach(Chart* chart, airport->getCharts()) {
          QTreeWidgetItem* chartItem = new QTreeWidgetItem;
          chartItem->setText(0, chart->getName());
          chartItem->setData(0, Qt::UserRole, qVariantFromValue(chart));
          item->addChild(chartItem);
        }

        this->addTopLevelItem(item);
    }
}

void ChartTree::itemSelected(QTreeWidgetItem* item, int column) {
    Chart* chart = qVariantValue<Chart*>(item->data(0, Qt::UserRole));
    if (chart) {
        emit chartSelected(chart);
    }
}
