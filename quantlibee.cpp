
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <tchar.h>

//#include <ql/time/date.hpp>
#include "time/Date.hpp"
#include "custview.h"

#include "quantlibee.h"

//using namespace QuantLib;
using namespace NICELib;

static HRESULT FormatQuantLibDate( NICELib::Date *date, char *pResult, int result_size )
{
    wsprintf(pResult, "%d-%d-%d", date->GetYear(), date->GetMonth(), date->GetDayofMonth());
    return S_OK;
}

HRESULT ADDIN_API AddIn_quantlibdate( DWORD dwAddress, DEBUGHELPER *pHelper, int nBase, BOOL bUniStrings, char *pResult, size_t max, DWORD reserved )
{
    NICELib::Date date;
    DWORD nGot;

    // read date from debuggee memory space
    if (pHelper->ReadDebuggeeMemoryEx(pHelper, pHelper->GetRealAddress(pHelper), sizeof(NICELib::Date), &date, &nGot) != S_OK)
        return E_FAIL;
    if (nGot != sizeof(NICELib::Date))
        return E_FAIL;

    return FormatQuantLibDate(&date, pResult, max);
}