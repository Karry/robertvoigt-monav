/*
Copyright 2010  Christian Vetter veaac.fdirct@gmail.com

This file is part of MoNav.

MoNav is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

MoNav is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with MoNav.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GPSGRID_H
#define GPSGRID_H

#include "interfaces/ipreprocessor.h"
#include "ggdialog.h"
#include "cell.h"
#include "table.h"
#include <vector>


class GPSGrid : public QObject, public IPreprocessor {
	Q_OBJECT
	Q_INTERFACES( IPreprocessor )

public:

			GPSGrid();
	virtual ~GPSGrid();
	virtual QString GetName();
	virtual Type GetType();
	virtual void SetOutputDirectory( const QString& dir );
	virtual void ShowSettings();
	virtual bool Preprocess( IImporter* importer );

protected:

	struct GridImportEdge {
		gg::Cell::Edge edge;
		int x;
		int y;
		bool operator<( const GridImportEdge& right ) const {
			if ( x != right.x )
				return x < right.x;
			return y < right.y;
		}
		bool operator==( const GridImportEdge& right ) const {
			return x == right.x && y == right.y && edge == right.edge;
		}
	};

	bool clipHelper( double directedProjection, double directedDistance, double* tMinimum, double* tMaximum );
	bool clipEdge( ProjectedCoordinate source, ProjectedCoordinate target, ProjectedCoordinate min, ProjectedCoordinate max );

	QString outputDirectory;
	GGDialog* settingsDialog;
};

#endif // GPSGRID_H
