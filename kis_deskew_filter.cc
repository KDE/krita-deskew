/*
 * This file is part of Krita
 *
 * Copyright (c) 2007 Michael Thaler <michael.thaler@physik.tu-muenchen.de>
 *
 * ported from the deskew gimp plugin
 * Copyright (C) 2007 Karl Chen <quarl@cs.berkeley.edu>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */


// TODO: remove that
#define LCMS_HEADER <lcms.h>
// TODO: remove it !

#include <stdlib.h>
#include <vector>

#include <qpoint.h>
#include <qspinbox.h>

#include <kis_iterators_pixel.h>

#include "kis_multi_integer_filter_widget.h"
#include "kis_deskew_filter.h"
#include "kritafact.h"
#include "deskewer.h"

KisDeskewFilter::KisDeskewFilter() : KisFilter(id(), "enhance", i18n("&Deskew..."))
{
}

void KisDeskewFilter::process(KisPaintDeviceSP src, KisPaintDeviceSP dst, KisFilterConfiguration* /*configuration*/, const QRect& rect)
{

    /*if (!configuration) {
        kdWarning() << "No configuration object for deskew filter\n";
        return;
    }*/
    
    Q_UNUSED(dst);

    KritaFactory f(src, rect);
    KSharedPtr<BWImage> b = f.create();
    double alpha = pagetools::Deskewer::findSkew(*b);
    kdDebug() << "Alpha: " << alpha << endl;
    //OilPaint(src, dst, x, y, width, height, brushSize, smooth);

    Q_ASSERT(src != 0);
    Q_ASSERT(dst != 0);

    KisRectIteratorPixel dstIt = dst->createRectIterator(rect.x(), rect.y(), rect.width(), rect.height(), true );
    KisRectIteratorPixel srcIt = src->createRectIterator(rect.x(), rect.y(), rect.width(), rect.height(), false);

    int pixelsProcessed = 0;
    setProgressTotalSteps(rect.width() * rect.height());

    KisColorSpace * cs = src->colorSpace();
    Q_INT32 psize = cs->pixelSize();


    while( ! srcIt.isDone() )
    {
        if(srcIt.isSelected())
        {
            if (src!=dst)
                memcpy(dstIt.rawData(), srcIt.oldRawData(), psize);
        }
        setProgress(++pixelsProcessed);
        ++srcIt;
        ++dstIt;
    }

    rotateLayer(dst, alpha);

    setProgressDone(); // Must be called even if you don't really support progression
}

void KisDeskewFilter::rotateLayer(KisPaintDeviceSP dev, double radians)
{
    if (!dev) return;

    /*KisSelectedTransaction * t = 0;
    if (undoAdapter() && undoAdapter()->undo()) {
        t = new KisSelectedTransaction(i18n("Rotate Layer"), dev);
        Q_CHECK_PTR(t);
    }*/

    KisFilterStrategy *filter = KisFilterStrategyRegistry::instance()->get(KisID("Triangle"));
    QRect r;
    if(dev->hasSelection())
        r = dev->selection()->selectedExactRect();
    else
        r = dev->exactBounds();
    double cx = r.x()+r.width()/2.0;
    double cy = r.y()+r.height()/2.0;
    Q_INT32 tx = Q_INT32(cx*cos(radians) - cy*sin(radians) - cx + 0.5);
    Q_INT32 ty = Q_INT32(cy*cos(radians) + cx*sin(radians) - cy + 0.5);

    KisTransformWorker tw(dev, 1.0, 1.0, 0, 0, radians, -tx, -ty, 0, filter);
    tw.run();

    //if (t) undoAdapter()->addCommand(t);

    //m_doc->setModified(true);
    //layersUpdated();
    //updateCanvas();
}

KisFilterConfigWidget * KisDeskewFilter::createConfigurationWidget(QWidget* parent, KisPaintDeviceSP /*dev*/)
{
    vKisIntegerWidgetParam param;
    //param.push_back( KisIntegerWidgetParam( 1, 5, 1, i18n("Brush size"), "brushSize" ) );
    //param.push_back( KisIntegerWidgetParam( 10, 255, 30, i18n("Smooth"), "smooth" ) );
    return new KisMultiIntegerFilterWidget(parent, id().id().ascii(), id().id().ascii(), param );
}

KisFilterConfiguration* KisDeskewFilter::configuration(QWidget* nwidget)
{
    //KisMultiIntegerFilterWidget* widget = (KisMultiIntegerFilterWidget*) nwidget;
    return new KisDeskewFilterConfiguration( 1, 30);
    /*if( widget == 0 )
    {
        return new KisDeskewFilterConfiguration( 1, 30);
    } else {
        return new KisDeskewFilterConfiguration( widget->valueAt( 0 ), widget->valueAt( 1 ) );
    }*/
}

std::list<KisFilterConfiguration*> KisDeskewFilter::listOfExamplesConfiguration(KisPaintDeviceSP )
{
    std::list<KisFilterConfiguration*> list;
    list.insert(list.begin(), new KisDeskewFilterConfiguration( 1, 30));
    return list;
}

