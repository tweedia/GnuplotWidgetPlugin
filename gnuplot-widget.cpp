#include <QByteArray>
#include <QFileDialog>

#include "gnuplot-widget.h"
#include "ui_gnuplot-widget.h"

GnuplotWidget::GnuplotWidget(QWidget *parent, QSqlDatabase *argDatabase, int argObsobjID, QString argTitle) :
    QWidget(parent),
    ui(new Ui::GnuplotWidget)
{
    mDatabase = argDatabase;
    mObsobjID = argObsobjID;

    ui->setupUi(this);

    QString wkString;
    wkString.clear();
    wkString.append(this->getObstblName());
    wkString.append(" - ");
    wkString.append(argTitle);
    this->setWindowTitle((const QString)wkString);

    mProcess = new QProcess(this);
    mPathname.clear();
    mPathname.append("/usr/local/bin/gnuplot");
//    mArgument.clear();
//    mArgument.append("");
    m_running = false;

    connect(mProcess, SIGNAL(readyReadStandardOutput()),
            this, SLOT(refreshWidget()));
    connect(mProcess, SIGNAL(finished(int, QProcess::ExitStatus)),
            this, SLOT(processFinished(int, QProcess::ExitStatus)));
    connect(mProcess, SIGNAL(error(QProcess::ProcessError)),
            this, SLOT(processError(QProcess::ProcessError)));

    if (!m_running)
    {
        m_running = true;
        mProcess->start(mPathname);
    }

//    QByteArray data = mProcess->readAll();
//    QString str;
//    str.clear();
//    str.append(data.data());

    this->called_when_DatabaseUpdated();

}

GnuplotWidget::~GnuplotWidget()
{
    delete ui;
}

int GnuplotWidget::called_when_DatabaseUpdated()
{
    QSqlQuery query(*mDatabase);
    QString str = QString();
    str.clear();
    str.append(ui->fldDataname->text());
    str.append(" <<EOD\n");
    query.exec((const QString)metadataOfObservation.SqlSelectAll(mObsobjID,1));
    while (query.next()){
        str.append(query.value(0).toByteArray());
        str.append(" ");
        str.append(query.value(1).toByteArray());
        str.append("\n");
    }
    str.append("EOD\n");

    str.append(ui->fldCommand->toPlainText());
    str.append("\n");

    mProcess->write(str.toAscii());
}

QString GnuplotWidget::getObstblName()
{
    QSqlQuery query(*mDatabase);

    query.exec((const QString)metadataOfObsObj.SqlSelectObstblName(mObsobjID));
    if (query.next()){
        mObstblName.clear();
        mObstblName.append(query.value(0).toByteArray());
    }

    return mObstblName;

}

void GnuplotWidget::processFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    m_running = false;
}

void GnuplotWidget::processError(QProcess::ProcessError error)
{
    if (error == QProcess::FailedToStart) {
        m_running = false;
    }
}


void GnuplotWidget::on_pushButton_clicked()
{
    this->called_when_DatabaseUpdated();
}

void GnuplotWidget::on_pushButton_2_clicked()
{

}
