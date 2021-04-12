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
 
#include "exphelper.h"

#include <QHeaderView>

ExpHelper::ExpHelper( QTreeView *parent ) : QObject( parent ), viewPtr( parent )
{
  if( !viewPtr )
    return;
  
  viewPtr->setIndentation( 0 );
  viewPtr->setRootIsDecorated( false );
  viewPtr->header()->hide();

  connect( viewPtr, SIGNAL(clicked(QModelIndex)), this, SLOT(itemClicked(QModelIndex)) );
}
  
void ExpHelper::itemClicked( const QModelIndex &index )
{
  if( !viewPtr )
    return;
    
  if( index.parent().isValid() )
  {
    if( index.model()->data( index, SignalValueRole ).isValid() )
      emit itemClicked( index.model()->data( index, SignalValueRole ).toInt() );
  }
  else
  { 
    if( viewPtr->isExpanded( index ) )
      viewPtr->setExpanded( index, false );
    else
    {
      viewPtr->setExpanded( index, true );
//      int childIndex = -1;
//      while( index.child( childIndex+1, 0 ).isValid() )
//        childIndex++;
        
//      if( childIndex != -1 )
//        viewPtr->scrollTo( index.child( childIndex, 0 ) );
    }
  }
}
