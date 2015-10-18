#ifndef GNUPLOTWIDGET_H
#define GNUPLOTWIDGET_H

#include <QWidget>
#include <QSqlQuery>
#include <QProcess>

#include "../Tweedia/Tweedia-with-plugins/Tweedia/widget-plugin-interface.h"

namespace Ui {
class GnuplotWidget;
}

class GnuplotWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit GnuplotWidget(QWidget *parent = 0, QSqlDatabase *argDatabase = 0, int argObsobjID = -1, QString argTitle = QString());
    int called_when_DatabaseUpdated();
    int ObsobjID() {return mObsobjID;}
    ~GnuplotWidget();
    
private:
    Ui::GnuplotWidget *ui;

    QSqlDatabase *mDatabase;
    int mObsobjID;
    MetadataOfObsObj metadataOfObsObj;
    MetadataOfObservation metadataOfObservation;

    QString mObstblName;

    QProcess *mProcess;
    volatile bool m_running;
    QString mPathname;
    QString mArgument;

    QString getObstblName();

private slots:
    void processFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void processError(QProcess::ProcessError error);

    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

#endif // GNUPLOTWIDGET_H
