/***************************************************************************
 *   Copyright (C) 2005 by Tommy Carlsson   *
 *   tc@coderworld.net   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

/**
@file
Implementation of the Ui::PushButton class
*/

#include "uipushbutton.h"

#include <uicolor.h>

using namespace Ui;

PushButton::PushButton()
 : Widget()
{

  pPressedBorder = NULL;
  pReleasedBorder = NULL;
  pImage = NULL;
  setBorder( NULL );
  pText = L"Ok";
  pPressed = false;

  setWidth( 100 );
  setHeight( 24 );
//  setPreferredWidth( 100 );
//  setPreferredHeight( 24 );
//  setHSizeType( sizeExpanding );
//  setVSizeType( sizeFixed );
}

PushButton::PushButton( Frame* parent )
 : Widget( parent )
{
  pPressedBorder = NULL;
  pReleasedBorder = NULL;
  pImage = NULL;
  pText = L"Ok";
  pPressed = false;

  setWidth( 100 );
  setHeight( 24 );
//  setPreferredWidth( 100 );
//  setPreferredHeight( 24 );
//  setHSizeType( sizeExpanding );
//  setVSizeType( sizeFixed );
}

void PushButton::setTheme( Theme& t, const string prefix )
{
  beginUpdate();
	Widget::setTheme( t, prefix );
	setReleasedBorder( t.getBorder( prefix+"pushbutton_released" ) );
  setPressedBorder( t.getBorder( prefix+"pushbutton_pressed" ) );
  setFont( t.getFont( prefix+"pushbutton" ) );
  setFontColor( t.getColor( prefix+"pushbutton_font" ) );
  setImage( t.getImage( prefix+"pushbutton" ) );
	setCursor( t.getCursor( prefix+"pushbutton" ) );
  endUpdate();
}


Border* PushButton::pressedBorder()
{
  return pPressedBorder;
}



void PushButton::setPressedBorder( Border* bs )
{
  pPressedBorder = bs;
  if ( pressed() ) {
    setBorder( pPressedBorder );
  } else {
    setBorder( pReleasedBorder );
  }
}



Border* PushButton::releasedBorder()
{
  return pReleasedBorder;
}



void PushButton::setReleasedBorder( Border* bs )
{
  pReleasedBorder = bs;

  if ( pressed() ) {
    setBorder( pPressedBorder );
  } else {
    setBorder( pReleasedBorder );
  }
}



bool PushButton::pressed()
{
  return pPressed;
}

wstring PushButton::text()
{
  return pText;
}

void PushButton::setText( wstring s )
{
  pText = s;
	updated();
}

void PushButton::buttonPressed()
{
  onButtonPressed( *this );
}

Widget* PushButton::keyPressed( Key key)
{
  Widget::keyPressed( key );
  return this;
}

Widget* PushButton::mouseClick(int x, int y, MouseButtons mb)
{
  Widget::mouseClick(x, y, mb);
  buttonPressed();
  return this;
}

Widget* PushButton::mouseIn(MouseButtons mb)
{
	Widget::mouseIn( mb );
  if ( mb == MBT_LEFT ) {
    beginUpdate();
    pPressed = true;
    setBorder( pPressedBorder );
    endUpdate();
  }
  return this;
}

Widget* PushButton::mouseOut(MouseButtons mb)
{
	Widget::mouseOut( mb );
	if ( mb == MBT_LEFT ) {
    beginUpdate();
    pPressed = false;
    setBorder( pReleasedBorder );
    endUpdate();
  }
  return this;
}

Widget* PushButton::mousePressed(int x, int y, MouseButtons mb)
{
  //cout << "* Ui::PushButton::mousePressed(  )" << endl;
	Widget::mousePressed( x, y, mb );
	beginUpdate();
  pPressed = true;
  setBorder( pPressedBorder );
  grabMouseInput();
  endUpdate();
  return this;
}

Widget* PushButton::mouseReleased(int x, int y, MouseButtons mb)
{
  beginUpdate();
	cout << "PushButton::mouseReleased( " << x << ", " << y << " )" << endl;
	Widget::mouseReleased( x, y, mb );
	pPressed = false;
  setBorder( pReleasedBorder );
  releaseMouseInput();
  endUpdate();
  return this;
}

void PushButton::render( ImageObject& img, const Rect& r )
{
  if ( !visible() ) return;

	Rect r2 = Rect( 0, 0, clientVisibleWidth(), clientVisibleHeight() );
  int theight = 0;
  int twidth = 0;
  if ( (font() != NULL) && ( text() != L"" ) ) {
    theight = font()->textHeight();
    twidth = font()->textWidth( pText ) + 2;
  }
  if ( pImage != NULL ) {

    twidth += pImage->width();
    r2.top = ( r2.height / 2 - pImage->height() / 2 );
    r2.left = ( r2.width / 2 - twidth / 2 );
    r2.width = pImage->width();
    r2.height = pImage->height();
    if ( pressed() ) {
      r2.top += 1;
      r2.left += 1;
    }
    img.drawImage( *pImage, r2 );
    r2.left += pImage->width() + 2;
		r2.width = clientVisibleWidth();
		r2.height = clientVisibleHeight();

  } else {
    r2.left = ( r2.width / 2 - (twidth-2) / 2 );
  }
  r2.top = ( r2.height / 2 - theight / 2 );
  if ( font() != NULL ) {
    if ( pressed() ) {
      img.outText( pText, *font(), (int)r2.left+1, (int)r2.top+1, fontColor() );
    } else {
      img.outText( pText, *font(), (int)r2.left, (int)r2.top, fontColor() );
    }
  }
}


