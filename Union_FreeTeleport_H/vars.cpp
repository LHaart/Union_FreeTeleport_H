// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
	// Add your code here . . .
#define KeyClick(a)   zinput->KeyToggled(a)
#define LogicKey(a)			zinput->GetState(a)
#define KeyPress(a)   zinput->KeyPressed(a)
#define INP_CLR zinput->ClearKeyBuffer();
#define FACTOR 81.919998
#define F(a) a * FACTOR			// 8
#define printWin(a) ogame->game_text->Printwin(zSTRING(a));			// 8

	zSTRING Substr( zSTRING _this, unsigned int pos, unsigned long npos = -1 ) {
		std::string s = _this.ToChar();
		std::string s1;
		s1 = s.substr( pos, npos );
		zSTRING tmp = s1.c_str();
		return tmp;
	}

	zCArray<zSTRING> SplitStr( zSTRING str, char t ) {
			zCArray<zSTRING> arr;
			int pos = 0;
			int count = 0;
			for ( int i = 1; i < str.Length() - 1; i++ ) {
				count++;
				if ( str[(unsigned int)i] == t ) {
					zSTRING nStr = Substr( str, pos, count );
					nStr.TrimLeft( t );
					nStr.TrimRight( t );
					count = 0;
					pos = i;
					arr.Insert( nStr );
				}
			}
			zSTRING nStr = Substr( str, pos );
			nStr.TrimLeft( t );
			nStr.TrimRight( t );
			arr.Insert( nStr );
			return arr;
	};

	

	bool FileExists( const char *fname ) {
		return _access( fname, 0 ) != -1;
	}
}