#include "api.h"
#include "plugin/Menu.h"

bool ScarfaceHook_GetMenuActive()
{
    if (TheMenu)
        return TheMenu->m_bIsActive;
    else
        return false;
}

void ScarfaceHook_GetPlayerPosition(Vector* out)
{
    if (GetMainCharacter())
        *out = GetMainCharacter()->GetLocation();
}
