/*
 * This file is part of the KDE project
 *
 * Copyright (c) Michael Thaler <michael.thaler@physik.tu-muenchen.de>
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

#ifndef _KIS_DESKEW_FILTER_H_
#define _KIS_DESKEW_FILTER_H_

#include "kis_filter.h"
#include "kis_filter_config_widget.h"
#include "kis_filter_strategy.h"
#include "kis_selection.h"
#include "kis_transform_worker.h"

class KisDeskewFilterConfiguration : public KisFilterConfiguration
{

public:

    KisDeskewFilterConfiguration(Q_UINT32 brushSize, Q_UINT32 smooth)
        : KisFilterConfiguration( "deskew", 1 )
        {
            setProperty("brushSize", brushSize);
            setProperty("smooth", smooth);
        };
public:

    inline Q_UINT32 brushSize() { return getInt("brushSize"); };
    inline Q_UINT32 smooth() {return getInt("smooth"); };

};


class KisDeskewFilter : public KisFilter
{
public:
    KisDeskewFilter();
public:
    virtual void process(KisPaintDeviceSP,KisPaintDeviceSP, KisFilterConfiguration* , const QRect&);
    static inline KisID id() { return KisID("deskew", i18n("Deskew")); };
    virtual ColorSpaceIndependence colorSpaceIndependence() { return FULLY_INDEPENDENT; };
    virtual bool supportsPainting() { return false; }
    virtual bool supportsPreview() { return true; }
    virtual bool supportsAdjustmentLayers() { return false; }
    virtual std::list<KisFilterConfiguration*> listOfExamplesConfiguration(KisPaintDeviceSP dev);
    public:
    virtual KisFilterConfigWidget * createConfigurationWidget(QWidget* parent, KisPaintDeviceSP dev);
    virtual KisFilterConfiguration * configuration(QWidget*);
    virtual KisFilterConfiguration * configuration() { return new KisDeskewFilterConfiguration( 1, 30); };
private:
    void rotateLayer(KisPaintDeviceSP dev, double radians);
};

#endif
