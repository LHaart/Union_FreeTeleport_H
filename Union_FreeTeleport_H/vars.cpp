// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
	// Add your code here . . .
#define LogicKey(a)	zBindPressed(a)
#define INP_CLR zinput->ClearKeyBuffer();
#define FACTOR 81.919998
#define F(a) a * FACTOR			// 8
#define printWin(a) ogame->game_text->Printwin(zSTRING(a));			// 8	

	bool FileExists( const char *fname ) {
		return _access( fname, 0 ) != -1;
	}
}