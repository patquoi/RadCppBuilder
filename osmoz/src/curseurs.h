//---------------------------------------------------------------------------
#ifndef curseursH
#define curseursH
//---------------------------------------------------------------------------
#include <windows.h>
//---------------------------------------------------------------------------
#define NBCURSEURS   29
#define CUR_PLUS_1   ((TCursor)(27))
#define CUR_DEPL     ((TCursor)(28))
#define CUR_DEPLUS_1 ((TCursor)(29))
#define CUR_LAP ((TCursor)(LettreAPoser-'A'+1))
#define CUR_LAD ((TCursor)(LettreADeplacer-'A'+1))
//---------------------------------------------------------------------------
extern const BYTE ANDmaskCursor[NBCURSEURS][128];
extern const BYTE XORmaskCursor[NBCURSEURS][128];
//---------------------------------------------------------------------------
#endif
