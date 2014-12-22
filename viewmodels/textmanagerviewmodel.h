#ifndef TEXTMANAGERVIEWMODEL_H
#define TEXTMANAGERVIEWMODEL_H

#include <QObject>
#include <QString>

#include <interaction/textmanager.h>

namespace ViewModels
{

class TextManagerViewModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString Text READ getText WRITE setText NOTIFY TextChanged)
public:
    explicit TextManagerViewModel(QObject *parent = 0);

signals:
    void TextChanged();

public slots:
    void setText (QString s) {  }

public:
    void assign (Interaction::TextManager *tm);
    QString getText() const;

private slots:
    void update ();

private:
    Interaction::TextManager *textManager;
};

}

#endif // TEXTMANAGERVIEWMODEL_H
