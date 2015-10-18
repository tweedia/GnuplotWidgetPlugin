#ifndef GNUPLOTWIDGETPLUGIN_H
#define GNUPLOTWIDGETPLUGIN_H

#include <QtPlugin>
#include <QList>

#include "gnuplot-widget.h"

#include "../Tweedia/Tweedia-with-plugins/Tweedia/widget-plugin-interface.h"

class GnuplotWidgetPlugin : public QObject, WidgetPluginInterface
{
    Q_OBJECT
    Q_INTERFACES(WidgetPluginInterface)

public:
    explicit GnuplotWidgetPlugin();
    ~GnuplotWidgetPlugin();
    int set_dbinstance(QSqlDatabase *argDatabase) {mDatabase = argDatabase; return 0;}
    QWidget* new_widget(int argObsobjID);
    int called_when_DatabaseUpdated(int argObsobjID);
    QString getMenuText(){return mMenuText;}
    QObject* getCorrespondingAction() {return mCorrespondingAction;}
    int setCorrespondingAction(QObject* argAction) {mCorrespondingAction = argAction;}

private:
    QSqlDatabase *mDatabase;
    QList<GnuplotWidget*> mWidgets;
    QString mMenuText;
    QObject *mCorrespondingAction;

};



#endif // GNUPLOTWIDGETPLUGIN_H
