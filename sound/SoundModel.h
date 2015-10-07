#ifndef SOUNDMODEL_H
#define SOUNDMODEL_H

#include "viewmodels/systemstateviewmodel.h"
#include "interaction/keyboard.h"
#include "ILevithan.h"

namespace Sound {

class SoundModel : public QObject
{
    Q_OBJECT
public:
    SoundModel(ViewModels::SystemStateViewModel *viewModel, Interaction::Keyboard *keyboard, ILevithan *levithan, QObject *parent = 0);

private slots:
    void proccessTsvcVigilanceRequired(bool required);
    void proccessTsvcPreAlarmActive(bool active);
    void proccessVigilanceRequired(bool value);

private:
    ILevithan *levithan;
};

}


#endif // SOUNDMODEL_H
