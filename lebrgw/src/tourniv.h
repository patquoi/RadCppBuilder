//---------------------------------------------------------------------------
#ifndef tournivH
#define tournivH
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
class TThreadTour : public TThread
{
private:
protected:
    void __fastcall Execute();
public:
    __fastcall TThreadTour(bool CreateSuspended);
};
//---------------------------------------------------------------------------
#endif
