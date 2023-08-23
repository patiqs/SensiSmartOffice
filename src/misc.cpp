#include "main.h"

bool ledstate = HIGH;

void Toggle_Status_Led() { 
   digitalWrite(18, ledstate = HIGH-ledstate);
}