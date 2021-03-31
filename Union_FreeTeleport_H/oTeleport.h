// Supported with union (c) 2020 Union team
// Union HEADER file

namespace GOTHIC_ENGINE {
	// Add your code here . . .

	enum {
		MAIN_MENU,
		TELEPORT_TO,
		TELEPORT_TO_CHOISE,
		TELEPORT_NEXT_LOCATION_CHOISE_WORLD,
		TELEPORT_NEXT_LOCATION_TO,
		SAVE,
		SAVE_NAME
	};

	class oTeleport {
	public:
		CTimer timer;
		zSTRING currentWorldName;
		zCArray<oTeleportSlot> allTeleports;
		zCArray<oTeleportSlot> currentWorld;

		zCArray<int> allKeys;					// список всех кнопок
		zCArray<zSTRING> allCharacters;			// список всех букв

		zCView* pView;
		zCView* pViewName;

		int isActive;
		int menuNum;
		int saveNum;
		int numOfTeleportSlots;
		zSTRING teleportName;
		zSTRING nextLocTo;
		zSTRING menuName;

		zSTRING sSaved;
		zSTRING sTpName;
		zSTRING sMenu01;
		zSTRING sMenu01_01;
		zSTRING sMenu01_02;
		zSTRING sMenu01_03;
		zSTRING sMenu01_04;
		zSTRING sMenu02;
		zSTRING sMenu03;
		zSTRING sMenu04;
		zSTRING sMenu05;
		zSTRING sSlotIsEmpty;
		zSTRING sSaveCleaned;
		zSTRING sExit;
		zSTRING sDefSlotName;
		zSTRING sTeleportTo;

	public:
		~oTeleport();
		void Loop();
		void Save();
		void Load();
		void Init();
		void Activate(int start);
		void Draw();
		void DrawChoiseName();
		zCArray<oTeleportSlot> GetCurrent();
		oTeleportSlot& GetCurrent(int num);
		void Choise(int num);
		void TeleportTo( int num );
		void TeleportToLoc( int num);
		void Toggle();
		zSTRING GetPathSave( zSTRING saveName );
		zCArray<zSTRING> GetStringsFromSlots();
		zSTRING GetVecString(zVEC3 vec);
		oTeleportSlot GetSlotFromStr(zSTRING slotStr);
		zCArray<zSTRING> GetWorldNames();
		zCArray<oTeleportSlot> GetNextLocationTo();
		zSTRING GetWorldTpTo(int num);
		void HandleEvent();
		zSTRING GetString( CStringA* );
	};
}