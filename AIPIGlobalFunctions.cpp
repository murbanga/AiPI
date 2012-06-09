// Copyright (c) MEAP.  All rights reserved.
//------------------------------------------------------------------------------


#include "stdafx.h"
//#include "AIPIGlobalFunctions.h"
#include "AIPIGlobals.h"

//International configuration 

LANGID GetUserLanguagePrimaryID()
{
	
	langUser = GetUserDefaultLangID();
	languagePrimaryID = PRIMARYLANGID( langUser );

return languagePrimaryID;

}

LANGID GetSystemLanguagePrimaryID()
{
	
	langSystem = GetSystemDefaultLangID();
	languagePrimaryID = PRIMARYLANGID( langSystem );

return languagePrimaryID;

}


LCID GetUserLanguageLCID()
{
	
	LCIDUser = GetUserDefaultLCID();
	languageLCID = PRIMARYLANGID( LCIDUser );

return languageLCID;

}

LCID GetSystemLanguageLCID()
{
	
	LCIDSystem = GetSystemDefaultLCID();
	languageLCID = PRIMARYLANGID( LCIDSystem );

return languageLCID;

}
