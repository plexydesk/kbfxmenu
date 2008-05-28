/*
 *   Copyright (C) 2006
 *   Siraj Razick <siraj@kdemail.net>
 *   PhobosK <phobosk@mail.kbfx.org>
 *   see Also AUTHORS
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU Library General Public License version 2 as
 *   published by the Free Software Foundation
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details
 *
 *   You should have received a copy of the GNU Library General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "kbfxplasmacanvasitemwrapper.h"
#include <qptrlist.h>
#include <kbfxplasmapixmapprovider.h>

KbfxPlasmaCanvasItemWrapper::KbfxPlasmaCanvasItemWrapper ( QCanvas * canvas )
{
	m_canvas = canvas;
}

KbfxPlasmaCanvasItemWrapper::~KbfxPlasmaCanvasItemWrapper ()
{}

QCanvasItem *
KbfxPlasmaCanvasItemWrapper::item ( KbfxPlasmaCanvasItem::Type __type )
{
	QPixmap _img_sep = ( *KbfxPlasmaPixmapProvider::pixmap ( "separator" ) );
	QImage _tmp_img = _img_sep.convertToImage();
	_tmp_img = _tmp_img.smoothScale ( ConfigInit().m_itemView_w, _img_sep.height (),QImage::ScaleFree );
	_img_sep = QPixmap ( _tmp_img );

	QPixmap _img_tnorm = ( *KbfxPlasmaPixmapProvider::pixmap ( "tilenormal" ) );
	_tmp_img = _img_tnorm.convertToImage();
	_tmp_img = _tmp_img.smoothScale ( ConfigInit().m_itemView_w, _img_tnorm.height (),QImage::ScaleFree );
	_img_tnorm = QPixmap ( _tmp_img );

	QPixmap _img_thov = ( *KbfxPlasmaPixmapProvider::pixmap ( "tilehover" ) );
	_tmp_img = _img_thov.convertToImage();
	_tmp_img = _tmp_img.smoothScale ( ConfigInit().m_itemView_w, _img_thov.height (),QImage::ScaleFree );
	_img_thov = QPixmap ( _tmp_img );

	if ( __type == KbfxPlasmaCanvasItem::SEPARATOR )
	{
		QValueList<QPixmap> list;
		list.append ( _img_sep );
		KbfxPlasmaCanvasItem *_ret =
		    new KbfxPlasmaCanvasItem ( new QCanvasPixmapArray ( list ),m_canvas );
		_ret->setType ( __type );
		return ( QCanvasItem * ) _ret;
	}

	if ( __type == KbfxPlasmaCanvasItem::EXECUTABLE )
	{

		QValueList<QPixmap> list;
		list.append ( _img_tnorm );
		list.append ( _img_thov );

		QCanvasPixmapArray * _pArray = new QCanvasPixmapArray ( list );

		KbfxPlasmaCanvasItem *_ret = new KbfxPlasmaCanvasItem ( _pArray,
		                             m_canvas );

		_ret->setType ( __type );
		return ( QCanvasItem * ) _ret;
	}


	return 0;
}


QCanvasItem *
KbfxPlasmaCanvasItemWrapper::itemIndex ( KbfxPlasmaCanvasItem::Type __type )
{
	QPixmap _img_isep = ( *KbfxPlasmaPixmapProvider::pixmap ( "indexseparator" ) );
	QImage _tmp_img = _img_isep.convertToImage();
	_tmp_img = _tmp_img.smoothScale ( ConfigInit().m_listBox_w, _img_isep.height (),QImage::ScaleFree );
	_img_isep = QPixmap ( _tmp_img );

	QPixmap _img_r = ( *KbfxPlasmaPixmapProvider::pixmap ( "rhstile" ) );
	_tmp_img = _img_r.convertToImage();
	_tmp_img = _tmp_img.smoothScale ( ConfigInit().m_listBox_w, _img_r.height (),QImage::ScaleFree );
	_img_r = QPixmap ( _tmp_img );

	QPixmap _img_rhov = ( *KbfxPlasmaPixmapProvider::pixmap ( "rhshovertile" ) );
	_tmp_img = _img_rhov.convertToImage();
	_tmp_img = _tmp_img.smoothScale ( ConfigInit().m_listBox_w, _img_rhov.height (),QImage::ScaleFree );
	_img_rhov = QPixmap ( _tmp_img );

	if ( __type == KbfxPlasmaCanvasItem::SEPARATOR )
	{
		QValueList<QPixmap> list;
		list.append ( _img_isep );
		KbfxPlasmaIndexItem *_ret =
		    new KbfxPlasmaIndexItem ( new QCanvasPixmapArray ( list ),m_canvas );
		_ret->setType ( __type );
		return ( QCanvasItem * ) _ret;
	}
	if ( __type  == KbfxPlasmaCanvasItem::INDEX )
	{
		QValueList<QPixmap> list2;
		list2.append ( _img_r );
		list2.append ( _img_rhov );
		KbfxPlasmaIndexItem *_ret = new KbfxPlasmaIndexItem ( new QCanvasPixmapArray ( list2 ),
		                            m_canvas );

		_ret->setType ( __type );
		return ( QCanvasItem * ) _ret;

	}
	return 0;
}

#include "kbfxplasmacanvasitemwrapper.moc"
