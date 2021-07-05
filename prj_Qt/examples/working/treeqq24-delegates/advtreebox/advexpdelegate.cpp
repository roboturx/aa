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
 
#include "advexpdelegate.h"
#include "exphelper.h"

#include <QPainter>
#include <QLinearGradient>
#include <QPainterPath>

#include <QModelIndex>

const int radius = 10;
const int margin = 10;

AdvExpDelegate::AdvExpDelegate( QTreeView *parent ) : QAbstractItemDelegate( parent ), viewPtr( parent )
{
}

void AdvExpDelegate::paint( QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
  if( !viewPtr )
    return;
  
  if( index.model()->data( index, ExpHelper::TypeRole ) == ExpHelper::Spacer )
  {
    // No need to draw spacer items

    return;
  }
  
  // Setup pens and colors
  QColor backgroundColor, darkColor;
  if( index.model()->data( index, Qt::BackgroundRole/* :BackgroundColorRole*/ ).isValid() )
    backgroundColor = index.model()->data( index, Qt::BackgroundRole/* :BackgroundColorRole*/ ).value<QColor>();
  else
    backgroundColor = Qt::gray;
      
  darkColor = backgroundColor.darker();
  
  QPen borderPen( darkColor );
  borderPen.setWidth( 2 );
    
  if( !hasParent( index ) )
  {
    // Paint the top-item
   
    QLinearGradient titleGradient( option.rect.topLeft(), option.rect.topRight() );
    titleGradient.setColorAt( 0.0, Qt::yellow );
    titleGradient.setColorAt( 0.5, Qt::white );
    titleGradient.setColorAt( 1.0, backgroundColor );
      
    QPainterPath titlePath;
    
    if( isExpanded( index ) )
    {
      titlePath.moveTo( option.rect.bottomLeft() );
      titlePath.lineTo( option.rect.topLeft()+QPoint( 0, radius ) );
      titlePath.arcTo( option.rect.left(), option.rect.top(), 2*radius, 2*radius, 180, -90 );
      titlePath.lineTo( option.rect.topRight()-QPoint( radius, 0 ) );
      titlePath.arcTo( option.rect.right()-2*radius, option.rect.top(), 2*radius, 2*radius, 90, -90 );
      titlePath.lineTo( option.rect.bottomRight() );
      titlePath.closeSubpath();
    }
    else
    {
      titlePath.lineTo( option.rect.topLeft()+QPoint( 0, radius ) );
      titlePath.arcTo( option.rect.left(), option.rect.top(), 2*radius, 2*radius, 180, -90 );
      titlePath.lineTo( option.rect.topRight()-QPoint( radius, 0 ) );
      titlePath.arcTo( option.rect.right()-2*radius, option.rect.top(), 2*radius, 2*radius, 90, -90 );
      titlePath.lineTo( option.rect.bottomRight()-QPoint( 0, radius ) );
      titlePath.arcTo( option.rect.right()-2*radius, option.rect.bottom()-2*radius, 2*radius, 2*radius, 0, -90 );
      titlePath.lineTo( option.rect.bottomLeft()+QPoint( radius, 0 ) );
      titlePath.arcTo( option.rect.left(), option.rect.bottom()-2*radius, 2*radius, 2*radius, 270, -90 );      
      titlePath.closeSubpath();
    }

    painter->setBrush( titleGradient );
    painter->setPen( borderPen );
    painter->drawPath( titlePath );
    
    QFont font = option.font;
    font.setBold( true );
    painter->setFont( font );
  }
  else if( isLast( index ) )
  {
    // Paint the bottom item
    
    QPainterPath endPath;
    endPath.moveTo( option.rect.topLeft() );
    endPath.lineTo( option.rect.bottomLeft()-QPoint( 0, radius ) );
    endPath.arcTo( option.rect.left(), option.rect.bottom()-2*radius, 2*radius, 2*radius, 180, 90 );
    endPath.lineTo( option.rect.bottomRight()-QPoint( radius, 0 ) );
    endPath.arcTo( option.rect.right()-2*radius, option.rect.bottom()-2*radius, 2*radius, 2*radius, 270, 90 );
    endPath.lineTo( option.rect.topRight() );
    
    painter->setBrush( backgroundColor );
    painter->setPen( borderPen );
    painter->drawPath( endPath );

    painter->setFont( option.font );
  }
  else
  {
    // Paint middle items
    
    painter->setBrush( backgroundColor );
    painter->setPen( Qt::NoPen );
    painter->drawRect( option.rect );
    
    painter->setPen( borderPen );
    painter->drawLine( option.rect.topLeft(), option.rect.bottomLeft() );
    painter->drawLine( option.rect.topRight(), option.rect.bottomRight() );

    painter->setFont( option.font );
  }
  
  // Draw common parts here (decoration and text)
  painter->setPen( darkColor );
    
  QImage decoration = index.model()->data( index, Qt::DecorationRole ).value<QImage>();
  int decorationWidth = 0;
  if( !decoration.isNull() )
  {
    decorationWidth = decoration.width() + margin;
    painter->drawImage( option.rect.left()+margin, option.rect.top()+(option.rect.height()-decoration.height())/2, decoration );
  }
  
  painter->drawText( QRect( option.rect.x()+margin+decorationWidth, option.rect.y(), option.rect.width()-2*margin-decorationWidth, option.rect.height() ), Qt::AlignLeft | Qt::AlignVCenter, index.model()->data( index, Qt::DisplayRole ).toString() );
}

QSize AdvExpDelegate::sizeHint( const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
  if( index.model()->data( index, ExpHelper::TypeRole ) == ExpHelper::Spacer )
    return QSize( 10, 10 );
  else
    return QSize( 100, 30 );
}

bool AdvExpDelegate::hasParent( const QModelIndex &index ) const
{
  if( index.parent().isValid() )
    return true;
    
  return false;
}
  
bool AdvExpDelegate::isLast( const QModelIndex &index ) const
{
  if( index.parent().isValid() )
    //if( !index.parent().child( index.row()+1, index.column() ).isValid() )
      return true;
      
  return false;
}

bool AdvExpDelegate::isExpanded( const QModelIndex &index ) const
{
  if( !viewPtr )
    return false;
    
  return viewPtr->isExpanded( index );
}
