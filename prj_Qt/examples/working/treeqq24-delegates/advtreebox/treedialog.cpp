/*
 * Copyright (c) 2007, Johan Thelin
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met:
 * 
 *     * Redistributions of source code must retain the above copyright notice, 
 *       this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright 
 *       notice, this list of conditions and the following disclaimer in the 
 *       documentation and/or other materials provided with the distribution.
 *     * The name of Johan Thelin may be used to endorse or promote products 
 *       derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
#include "treedialog.h"

#include <QColor>
#include <QMessageBox>
#include <QStandardItemModel>

#include "exphelper.h"
#include "advexpdelegate.h"

TreeDialog::TreeDialog( QWidget *parent ) : QWidget( parent )
{
  ui.setupUi( this );
  
  populateTree();
  
  AdvExpDelegate *delegate = new AdvExpDelegate ( ui.treeView );
  ui.treeView->setItemDelegate( delegate );

  ExpHelper *helper = new ExpHelper( ui.treeView );
  
  connect( helper, SIGNAL(itemClicked(int)), this,
           SLOT(itemClicked(int)) );
}

void TreeDialog::itemClicked( int item )
{
  QMessageBox::information( this, "Item Clicked",
                            QString("Item %1 clicked!").arg( item ) );
}

void TreeDialog::populateTree()
{
  QStandardItemModel *model = new QStandardItemModel();
  
  QStandardItem *parentItem = model->invisibleRootItem();
  for( int i=0; i<4; ++i)
  {
    QStandardItem *item = new QStandardItem(QString("item %0").arg(i));
    parentItem->appendRow(item);
    if( i == 0 )
      parentItem = item;
    else
      item->setData( QImage( ":/trolltech/styles/commonstyle/images/viewlist-16.png" ), Qt::DecorationRole );
        
    item->setData( QColor(Qt::green),
                   Qt::BackgroundRole/* :BackgroundColorRole*/ );
    item->setData( ExpHelper::Item, ExpHelper::TypeRole );
    item->setData( i, ExpHelper::SignalValueRole );
  }

  parentItem = model->invisibleRootItem();
  QStandardItem *item = new QStandardItem();
  parentItem->appendRow(item);
  item->setData( ExpHelper::Spacer, ExpHelper::TypeRole );
  for( int i=0; i<4; ++i)
  {
    QStandardItem *item = new QStandardItem(QString("item %0").arg(i+4));
    parentItem->appendRow(item);
    if( i == 0 )
      parentItem = item;
    else
      item->setData( QImage( ":/trolltech/styles/commonstyle/images/viewlist-16.png" ), Qt::DecorationRole );
        
    item->setData( QColor(Qt::red), Qt::BackgroundRole/* :BackgroundColorRole*/ );
    item->setData( ExpHelper::Item, ExpHelper::TypeRole );
    item->setData( i+4, ExpHelper::SignalValueRole );
  }
  
  ui.treeView->setModel( model );
}

