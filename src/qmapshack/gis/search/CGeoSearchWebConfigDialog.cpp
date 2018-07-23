/**********************************************************************************************
    Copyright (C) 2018 Oliver Eichler oliver.eichler@gmx.de

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

**********************************************************************************************/

#include "CGeoSearchWebConfigDialog.h"

#include <QtWidgets>

CGeoSearchWebConfigDialog::CGeoSearchWebConfigDialog(QList<CGeoSearchWeb::service_t>& services, QWidget *parent)
    : QDialog(parent)
    , services(services)
{
    setupUi(this);

    connect(pushAddNew, &QPushButton::clicked, this, &CGeoSearchWebConfigDialog::slotAddNew);
    connect(pushDelSelected, &QPushButton::clicked, this, &CGeoSearchWebConfigDialog::slotDelSelected);
    connect(treeServices, &QTreeWidget::itemSelectionChanged, this, &CGeoSearchWebConfigDialog::slotSelectionChanged);

    const QString& msg = tr("<b>Add your own service</b>"
                            "<p>To add your own service you need a name and an URL with placeholders for "
                            "coordinates. Placeholders are:</p>"
                            "<table>"
                            "<tr><th>placeholder</th><th>replaced by...</th></tr>"
                            "<tr><td>%1</td><td>longitude</td></tr>"
                            "<tr><td>%2</td><td>latitude</td></tr>"
                            "</table>"
                            "To edit a service select either it's name or URL and do a double click (alternative: press F2). "
                            "You can change the default services, too. If you remove all services the default ones will be "
                            "restored on the next start of QMapShack."
                            );

    labelHelp->setText(msg);

    for(const CGeoSearchWeb::service_t& service : services)
    {
        QTreeWidgetItem * item = new QTreeWidgetItem(treeServices);
        item->setText(0, service.name);
        item->setText(1, service.url);
        item->setFlags(item->flags()|Qt::ItemIsEditable);
    }

    treeServices->header()->resizeSections(QHeaderView::ResizeToContents);
    adjustSize();
}

void CGeoSearchWebConfigDialog::accept()
{
    services.clear();

    const qint32 N = treeServices->topLevelItemCount();
    for(int n = 0; n < N; n++)
    {
        QTreeWidgetItem * item = treeServices->topLevelItem(n);
        const QString& name = item->text(0);
        const QString& url  = item->text(1);
        if(name.isEmpty() || url.isEmpty() || !url.startsWith("http"))
        {
            continue;
        }

        services << CGeoSearchWeb::service_t(name, url);
    }

    QDialog::accept();
}

void CGeoSearchWebConfigDialog::slotSelectionChanged()
{
    pushDelSelected->setDisabled(treeServices->selectedItems().isEmpty());
}

void CGeoSearchWebConfigDialog::slotAddNew()
{
    QTreeWidgetItem * item = new QTreeWidgetItem(treeServices);
    item->setText(0, tr("enter name and URL"));
    item->setFlags(item->flags()|Qt::ItemIsEditable);
}

void CGeoSearchWebConfigDialog::slotDelSelected()
{
    qDeleteAll(treeServices->selectedItems());
}
