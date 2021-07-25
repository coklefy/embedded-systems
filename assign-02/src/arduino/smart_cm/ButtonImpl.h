#ifndef ___BUTTONIMPL__
#define ___BUTTONIMPL__

#include "Button.h"

/* ButtonImpl implements Button */
class ButtonImpl:public Button {

    public:
        ButtonImpl(int);
        bool isPressed();

    private:
        int pin;
};

#endif
