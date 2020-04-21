//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "tourniv.h"
#include "base.h"

#pragma package(smart_init)

__fastcall TThreadTour::TThreadTour(bool CreateSuspended)
    : TThread(CreateSuspended)
{
 Priority=tpNormal;
}

//---------------------------------------------------------------------------
void __fastcall TThreadTour::Execute()
{
 Synchronize((TThreadMethod)&(Niv->JoueTour));
}

