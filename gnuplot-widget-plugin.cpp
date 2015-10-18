#include "gnuplot-widget-plugin.h"

GnuplotWidgetPlugin::GnuplotWidgetPlugin(): QObject(0)
{
    mWidgets.clear();
    mMenuText.clear();
    mMenuText.append("Gnuplot");

}

GnuplotWidgetPlugin::~GnuplotWidgetPlugin()
{
    mWidgets.clear();
}

QWidget* GnuplotWidgetPlugin::new_widget(int argObsobjID)
{
    GnuplotWidget* gnuplotWidget = new GnuplotWidget(0, mDatabase, argObsobjID, mMenuText);
    mWidgets.append(gnuplotWidget);
    return gnuplotWidget;
}

int GnuplotWidgetPlugin::called_when_DatabaseUpdated(int argObsobjID)
{
    GnuplotWidget* gnuplotWidget;
    for (int i = 0; i < mWidgets.size(); ++i) {
        gnuplotWidget = mWidgets.at(i);
        if (gnuplotWidget->ObsobjID() == argObsobjID) {
            gnuplotWidget->called_when_DatabaseUpdated();
        }
    }
    return 0;
}

Q_EXPORT_PLUGIN2(libGnuplotWidgetPlugin, GnuplotWidgetPlugin);

/* References, Quotation:
 */


