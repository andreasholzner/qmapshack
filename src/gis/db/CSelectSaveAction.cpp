/**********************************************************************************************
    Copyright (C) 2014 Oliver Eichler oliver.eichler@gmx.de

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

#include "gis/IGisItem.h"
#include "gis/db/CSelectSaveAction.h"

CSelectSaveAction::CSelectSaveAction(const IGisItem *src, const IGisItem *tar, QWidget *parent)
    : QDialog(parent)
    , result(eResultNone)
{
    setupUi(this);

    labelIcon1->setPixmap(src->getIcon());
    labelInfo1->setText(src->getInfo());
    labelIcon2->setPixmap(tar->getIcon());
    labelInfo2->setText(tar->getInfo());

    adjustSize();

    connect(pushSave, SIGNAL(clicked()), this, SLOT(slotSelectResult()));
    connect(pushSkip, SIGNAL(clicked()), this, SLOT(slotSelectResult()));
}

CSelectSaveAction::~CSelectSaveAction()
{
}

bool CSelectSaveAction::allOthersToo()
{
    return checkAllOtherToo->isChecked();
}

void CSelectSaveAction::slotSelectResult()
{
    if(sender() == pushSave)
    {
        result = eResultSave;
    }
    else if(sender() == pushSkip)
    {
        result = eResultSkip;
    }

    accept();
}