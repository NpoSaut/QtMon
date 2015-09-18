#include "ShiftedInputActivity.h"

using namespace Interaction::Activities;


ShiftedInputActivity::ShiftedInputActivity(QString outputFormat, int *value, int shift, Interaction::TextManager *textManager, QObject *parent)
    : InputActivity (outputFormat, &shiftedValue, textManager, parent),
      shiftedValue (0),
      value (value),
      shift (shift)
{

}

void ShiftedInputActivity::run()
{
    shiftedValue = *value + shift;
    InputActivity::run();
}

void ShiftedInputActivity::submitted()
{
    InputActivity::submitted();
    *value = shiftedValue - shift;
}
