/******************************************************************************
 * Copyright (C) 2005-2009 by Tommy Carlsson
 *
 * This file is part of GameUI.
 *
 * GameUI is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * GameUI is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public License
 * along with GameUI.  If not, see <http://www.gnu.org/licenses/>.
 *
 ******************************************************************************/


/**
 * @file
 * Header and implementationfile of the UiColor class
 */

#ifndef UICOLOR_H
#define UICOLOR_H

#include <gameui.h>
#include <uiutils.h>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

namespace Ui
{

	const int ColorType_r = 0;
	const int ColorType_g = 1;
	const int ColorType_b = 2;
	const int ColorType_a = 3;

	const unsigned char ColorOpaque = 255;
	const unsigned char ColorTransparent = 0;

	/**
	 * Union used as a common way to store and set color information.
	 */
	union ColorType {
		unsigned long c;
		unsigned char rgba[4];

		ColorType (  ) {
			c = 0;
		};
		ColorType ( const unsigned long col ) {
			c = col;
		};
		ColorType ( const unsigned char r, const unsigned char g, const unsigned char b ) {
			rgba[ColorType_r] = r;
			rgba[ColorType_g] = g;
			rgba[ColorType_b] = b;
			rgba[ColorType_a] = ColorOpaque;
		};
		ColorType ( const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a ) {
			rgba[ColorType_r] = r;
			rgba[ColorType_g] = g;
			rgba[ColorType_b] = b;
			rgba[ColorType_a] = a;
		};
	};

	/**
	 * Class used to store information on a specific color.
	 */
	class Color
	{
		public:

			Color() {
				setColor( 0, 0, 0 );
			};
			Color( const unsigned char R, const unsigned char G, const unsigned char B ) {
				setColor( R, G, B );
			};
			Color( const unsigned char R, const unsigned char G, const unsigned char B, const unsigned char A ) {
				setColor( R, G, B, A );
			};
			virtual ~Color() { };

			virtual void setColor( const unsigned char R, const unsigned char G, const unsigned char B, const unsigned char A = ColorOpaque ) {
				c.rgba[ColorType_r] = R;
				c.rgba[ColorType_g] = G;
				c.rgba[ColorType_b] = B;
				c.rgba[ColorType_a] = A;
			};

			/**
			 * Sets the color to be held by the Color class.
			 * @param col the color, if rgba the first byte should contain the red color, the second green, the third blue and the fourth is the alpha.
			 */
			virtual void setColor( const unsigned long col ) {
				c.c = col;
			}

			virtual void setColor( const ColorType col ) {
				c.c = col.c;
			}

			virtual unsigned char getR() const {
				return c.rgba[ColorType_r];
			}
			virtual unsigned char getG() const {
				return c.rgba[ColorType_g];
			}
			virtual unsigned char getB() const {
				return c.rgba[ColorType_b];
			}
			virtual unsigned char getA() const {
				return c.rgba[ColorType_a];
			}

			virtual void setR( const unsigned char& r ) {
				c.rgba[ColorType_r] = r;
			}
			virtual void setG( const unsigned char& g ) {
				c.rgba[ColorType_g] = g;
			}
			virtual void setB( const unsigned char& b ) {
				c.rgba[ColorType_b] = b;
			}
			virtual void setA( const unsigned char& a ) {
				c.rgba[ColorType_a] = a;
			}

			virtual unsigned long getColor(  ) const {
				return c.c;
			}
			virtual ColorType getColorType(  ) const {
				return c;
			}

			virtual bool operator==( const Color& c2 ) const {
				return ( ( getR() == c2.getR() ) && ( getG() == c2.getG() ) && ( getB() == c2.getB() ) && ( getA() == c2.getA() ) );
			}

			virtual bool operator!=( const Color& c2 ) const {
				return ( ( getR() != c2.getR() ) || ( getG() != c2.getG() ) || ( getB() != c2.getB() ) || ( getA() != c2.getA() ) );
			}

		private:

			ColorType c;

	};

}

#endif
