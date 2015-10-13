#ifndef M7SOUNDCONTROLLER_H
#define M7SOUNDCONTROLLER_H

#include <QObject>
#include "viewmodels/systemstateviewmodel.h"
#include "interaction/keyboard.h"
#include "ILevithan.h"

namespace Sound {

class M7SoundController : public QObject
{
    Q_OBJECT
public:
    explicit M7SoundController(ViewModels::SystemStateViewModel *viewModel, Interaction::Keyboard *keyboard, ILevithan *levithan, QObject *parent = 0);

signals:

public slots:

};

}


#endif // M7SOUNDCONTROLLER_H
