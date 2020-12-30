// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
	// Add your code here . . .

	void oTeleport::Init() {
		pView = zNEW(zCView)(0,0,F(70),F(50));
		pView->SetPos( F(15), F(50));
		pView->InsertBack( "dlg_conversation.tga" );
		pViewName = zNEW( zCView )( 0, 0, F(30), F(15) );
		pViewName->SetPos(8192 / 2 - F(15), F(25));
		pViewName->InsertBack("dlg_conversation.tga");
		menuNum = FALSE;

		// �������
		allKeys.Insert( KEY_0 ); allCharacters.Insert( "0" );
		allKeys.Insert( KEY_1 ); allCharacters.Insert( "1" );
		allKeys.Insert( KEY_2 ); allCharacters.Insert( "2" );
		allKeys.Insert( KEY_3 ); allCharacters.Insert( "3" );
		allKeys.Insert( KEY_4 ); allCharacters.Insert( "4" );
		allKeys.Insert( KEY_5 ); allCharacters.Insert( "5" );
		allKeys.Insert( KEY_6 ); allCharacters.Insert( "6" );
		allKeys.Insert( KEY_7 ); allCharacters.Insert( "7" );
		allKeys.Insert( KEY_8 ); allCharacters.Insert( "8" );
		allKeys.Insert( KEY_9 ); allCharacters.Insert( "9" );
		// �����
		allKeys.Insert( KEY_A ); allCharacters.Insert( "a" );
		allKeys.Insert( KEY_B ); allCharacters.Insert( "b" );
		allKeys.Insert( KEY_C ); allCharacters.Insert( "c" );
		allKeys.Insert( KEY_D ); allCharacters.Insert( "d" );
		allKeys.Insert( KEY_E ); allCharacters.Insert( "e" );
		allKeys.Insert( KEY_F ); allCharacters.Insert( "f" );
		allKeys.Insert( KEY_G ); allCharacters.Insert( "g" );
		allKeys.Insert( KEY_H ); allCharacters.Insert( "h" );
		allKeys.Insert( KEY_I ); allCharacters.Insert( "i" );
		allKeys.Insert( KEY_J ); allCharacters.Insert( "j" );
		allKeys.Insert( KEY_K ); allCharacters.Insert( "k" );
		allKeys.Insert( KEY_L ); allCharacters.Insert( "l" );
		allKeys.Insert( KEY_M ); allCharacters.Insert( "m" );
		allKeys.Insert( KEY_N ); allCharacters.Insert( "n" );
		allKeys.Insert( KEY_O ); allCharacters.Insert( "o" );
		allKeys.Insert( KEY_P ); allCharacters.Insert( "p" );
		allKeys.Insert( KEY_Q ); allCharacters.Insert( "q" );
		allKeys.Insert( KEY_R ); allCharacters.Insert( "r" );
		allKeys.Insert( KEY_S ); allCharacters.Insert( "s" );
		allKeys.Insert( KEY_T ); allCharacters.Insert( "t" );
		allKeys.Insert( KEY_U ); allCharacters.Insert( "u" );
		allKeys.Insert( KEY_V ); allCharacters.Insert( "v" );
		allKeys.Insert( KEY_W ); allCharacters.Insert( "w" );
		allKeys.Insert( KEY_X ); allCharacters.Insert( "x" );
		allKeys.Insert( KEY_Y ); allCharacters.Insert( "y" );
		allKeys.Insert( KEY_Z ); allCharacters.Insert( "z" );
		allKeys.Insert( KEY_MINUS ); allCharacters.Insert( "_" );
		allKeys.Insert( KEY_SPACE ); allCharacters.Insert( " " );
		allKeys.Insert( KEY_EQUALS ); allCharacters.Insert( "=" );
		allKeys.Insert( KEY_TAB ); allCharacters.Insert( "" );
		allKeys.Insert( KEY_SLASH ); allCharacters.Insert( "/" );
		allKeys.Insert( KEY_PERIOD ); allCharacters.Insert( "." );
	}

	void oTeleport::HandleEvent() {
		if ( menuNum != SAVE_NAME
			&& !ogame->singleStep
			&& !ogame->game_testmode ) {
			if ( KeyClick( KEY_P ) ) {
				INP_CLR;
				Toggle();
			}
		}

		if ( isActive ) {

			if ( menuNum == SAVE_NAME ) {
				for ( int i = 0; i < allKeys.GetNum(); i++ ) {
					if ( KeyPress( allKeys.GetSafe( i ) ) ) {
						
						if ( KeyPress( KEY_LSHIFT ) || KeyPress( KEY_LSHIFT ) ) {
							zSTRING str = zSTRING( allCharacters.GetSafe( i ) );
							str.Upper();
							teleportName = teleportName + str;
						} else {
							teleportName = teleportName + allCharacters.GetSafe( i );
						}
						
						INP_CLR;
						break;
					}
				}

				if ( KeyClick( KEY_BACKSPACE ) ) {
					INP_CLR;
					if ( teleportName.Length() > 0 ) {
						teleportName = teleportName.Cut( teleportName.Length() - 1, teleportName.Length() );
					}
				}

				if ( KeyPress( KEY_RETURN ) ) {
					INP_CLR;
					oTeleportSlot& slot = GetCurrent( saveNum );
					if ( !teleportName.IsEmpty() ) {
						slot.tpName = teleportName;
					}

					menuNum = MAIN_MENU;
					teleportName.Clear();
					Draw();
					printWin( slot.tpName + " saved." );
					slot.pos = player->GetPositionWorld();
					slot.atPos = player->trafoObjToWorld.GetAtVector();
				}
			}

			if ( KeyPress( KEY_ESCAPE ) || KeyPress( KEY_BACKSPACE ) ) {
				INP_CLR;
				if ( menuNum == MAIN_MENU ) {
					Toggle();
				} else if ( menuNum != MAIN_MENU ) {
					menuNum = MAIN_MENU;
					teleportName.Clear();
					Draw();
				}

			}

			for ( int i = 0; i < 10; i++ ) {
				int key =
					i == 0?KEY_0:
					i == 1?KEY_1:
					i == 2?KEY_2:
					i == 3?KEY_3:
					i == 4?KEY_4:
					i == 5?KEY_5:
					i == 6?KEY_6:
					i == 7?KEY_7:
					i == 8?KEY_8:
					KEY_9;
				if ( KeyPress(key) ) {
					INP_CLR;
					Choise( i );
				}
			}

			if ( menuNum != SAVE_NAME ) {
				if ( LogicKey( zLOGICKEY_INVENTORY )
					|| LogicKey( zLOGICKEY_SCREEN_LOG )
					|| LogicKey( zLOGICKEY_SCREEN_STATUS )
					|| LogicKey( zLOGICKEY_SCREEN_MAP )
					|| LogicKey( zLOGICKEY_WEAPON ) ) {
					INP_CLR;
				}
			}
		}
	}

	void oTeleport::Loop() {

		timer.Attach();

		HandleEvent();

		if ( isActive ) {
			DrawChoiseName();
		}
	}

	zSTRING oTeleport::GetVecString( zVEC3 vec ) {
		zSTRING str = zSTRING( vec.n[ 0 ], 10 ) + "#" + zSTRING( vec.n[ 1 ], 10 ) + "#" + zSTRING( vec.n[ 2 ], 10 );
		//zSTRING str = zSTRING( ( (int)vec.n[ 0 ] ) );
		return str;
	}

	zCArray<zSTRING> oTeleport::GetStringsFromSlots() {
		zCArray<zSTRING> saveArr;
		for ( int i = 0; i < allTeleports.GetNum(); i++ ) {
			oTeleportSlot& slot = allTeleports.GetSafe(i);
			zSTRING slotStr = slot.tpName
				+ "$" + slot.worldName
				+ "$" + slot.worldFilename 
				+ "$" + GetVecString( slot.pos ) 
				+ "$" + GetVecString( slot.atPos ) 
				+ "$" + zSTRING( slot.num );
			saveArr.Insert(slotStr);
		}
		return saveArr;
	}

	void oTeleport::Save() {
		zSTRING path = GetPathSave("FreeTeleports");
		zCArray<zSTRING> saveArr = GetStringsFromSlots();
		CString str = "";

		for ( int i = 0; i < saveArr.GetNum(); i++ ) {
			str += (CString)( saveArr.GetSafe( i ) + "|" );
		}
		str.WriteToFile( path );
	}

	void oTeleport::Load() {
		if ( zCWorld* pWorld = player->GetHomeWorld() ) {
			if ( oCWorld* oWorld = pWorld->CastTo<oCWorld>() ) {
				currentWorldName = oWorld->worldName;
			}
		}

		test = 0;
		allTeleports.DeleteList();

		CString str;
		CString sFileName = GetPathSave( "FreeTeleports" );
		test++;
		if ( !FileExists( sFileName ) ) {
			return;
		}
		str.ReadFromFile( sFileName );
		test++;
		if ( str.IsEmpty() ) {
			return;
		}
		test++;
		zCArray<zSTRING> arr = SplitStr( str.GetVector(), '|' );
		for ( int i = 0; i < arr.GetNum(); i++ ) {
			zSTRING slotStr = arr.GetSafe( i );
			oTeleportSlot slot = GetSlotFromStr(slotStr);
			if ( !slot.worldName.IsEmpty() ) {
				allTeleports.Insert( slot );
			}
		}
		test++;
		
	}

	oTeleportSlot oTeleport::GetSlotFromStr( zSTRING slotStr ) {
		oTeleportSlot slot;
		zCArray<zSTRING> arr = SplitStr( slotStr, '$' );
		if ( arr.GetNum() > 0 ) {
			slot.tpName = arr.GetSafe( 0 );
			slot.worldName = arr.GetSafe( 1 );
			slot.worldFilename = arr.GetSafe( 2 );

			zCArray<zSTRING> vec01 = SplitStr( arr.GetSafe( 3 ), '#' );
			if ( vec01.GetNum() > 0 ) {
				float x = vec01.GetSafe( 0 ).ToReal64();
				float y = vec01.GetSafe( 1 ).ToReal64();
				float z = vec01.GetSafe( 2 ).ToReal64();
				slot.pos = zVEC3(x, y, z);
			}

			zCArray<zSTRING> vec02 = SplitStr( arr.GetSafe( 4 ), '#' );
			if ( vec02.GetNum() > 0 ) {
				float x = vec02.GetSafe( 0 ).ToReal64();
				float y = vec02.GetSafe( 1 ).ToReal64();
				float z = vec02.GetSafe( 2 ).ToReal64();
				slot.atPos = zVEC3( x, y, z );
			}

			zSTRING strNum = arr.GetSafe( 5 );
			slot.num = strNum.ToInt32();
		}
		return slot;
	}

	void oTeleport::Activate( int start ) {
		if ( start ) {
			screen->InsertItem( pView );
			Draw();
			player->movlock = TRUE;
		} else {
			screen->RemoveItem( pView );
			screen->RemoveItem( pViewName );
			player->movlock = FALSE;
		}
	}

	void oTeleport::DrawChoiseName() {
		if ( menuNum == SAVE_NAME ) {
			screen->InsertItem( pViewName );
			pViewName->SetFont( "FONT_OLD_10_WHITE.TGA" );
			pViewName->ClrPrintwin();
			zSTRING name = "Teleport name:";
			int x = 8192 / 2 - pViewName->FontSize( name ) / 2;
			int y = 0;
			pViewName->Print( x, y, name );

			pViewName->SetFont( "FONT_OLD_20_WHITE.TGA" );

			name = ": ";
			x = F( 5 );
			y = 8192 / 2 - pViewName->FontY() / 2;
			pViewName->Print( x, y, name );

			static int drawLine = 0;

			if ( timer( 0, 500 ) ) {
				drawLine = !drawLine;
			}

			x = x + pViewName->FontSize( name );
			if ( !teleportName.IsEmpty() ) {
				pViewName->Print( x, y, teleportName );
				x = x + pViewName->FontSize( teleportName );
			}
			
			if ( drawLine ) {
				static zSTRING line = "|";
				pViewName->Print( x, y, line );
			}
		}
	}

	void oTeleport::Draw() {
		pView->ClrPrintwin();

		int x = F( 10 );
		int y = F( 15 );
		int margin = F( 8 );
		int count = 0;
		if ( menuNum == MAIN_MENU ) {
			menuName = "Main menu";
			pView->Print( x, y + count++ * margin, "1. Teleport to..." ); //1. Teleport to: 5 mana
			pView->Print( x, y + count++ * margin, "2. Teleport to another location..." ); //2. Teleport to another location: 10 mana
			pView->Print( x, y + count++ * margin, "3. Save current position." );
			pView->Print( x, y + count++ * margin, "0. Clear all savepoints." ); 

			screen->RemoveItem( pViewName );
			pViewName->ClrPrintwin();
		} else if ( menuNum == TELEPORT_TO || menuNum == SAVE || menuNum == SAVE_NAME ) {
			zCArray<oTeleportSlot> arr = GetCurrent();
			for ( int i = 0; i < arr.GetNum(); i++ ) {
				oTeleportSlot& slot = arr.GetSafe( i );
				pView->Print( x, y + count++ * margin, A( i + 1 ) + ". " + A slot.tpName );
			}
		} else if ( menuNum == TELEPORT_NEXT_LOCATION_CHOISE_WORLD ) {
			zCArray<zSTRING> arr = GetWorldNames();
			for ( int i = 0; i < arr.GetNum(); i++ ) {
				zSTRING slot = arr.GetSafe( i );
				pView->Print( x, y + count++ * margin, A( i + 1 ) + ". " + A slot );
			}
		} else if ( menuNum == TELEPORT_NEXT_LOCATION_TO ) {
			zCArray<oTeleportSlot> arr = GetNextLocationTo();
			for ( int i = 0; i < arr.GetNum(); i++ ) {
				oTeleportSlot& slot = arr.GetSafe( i );
				pView->Print( x, y + count++ * margin, A( i + 1 ) + ". " + A slot.tpName );
			}
		}
		pView->Print( x, y + count++ * margin, "Esc. Exit." );

		x = 8192 / 2 - pView->FontSize(menuName) / 2;
		y = F( 5 );
		pView->Print( x, y, menuName );


		
	}

	zCArray<oTeleportSlot> oTeleport::GetCurrent() {
		zCArray<oTeleportSlot> arr;

		for ( int i = 0; i < allTeleports.GetNum(); i++ ) {
			oTeleportSlot& slot = allTeleports.GetSafe(i);
			if ( slot.worldName == currentWorldName ) {
				arr.Insert(slot);
			}
		}
		
		if ( arr.GetNum() == 0 ) {
			for ( int i = 0; i < 3; i++ ) {
				oTeleportSlot slot;
				if ( zCWorld* pWorld = player->GetHomeWorld() ) {
					if ( oCWorld* oWorld = pWorld->CastTo<oCWorld>() ) {
						slot.worldName = oWorld->worldName;
						slot.worldFilename = oWorld->worldFilename;
					}
				}
				slot.num = i + 1;
				slot.tpName = "EmptySlot " + zSTRING( slot.num ) ;
				arr.Insert(slot);
				allTeleports.Insert(slot);
			}
		}

		return arr;
	}

	oTeleportSlot& oTeleport::GetCurrent( int num ) {
		for ( int i = 0; i < allTeleports.GetNum(); i++ ) {
			oTeleportSlot& slot = allTeleports.GetSafe( i );
			if ( slot.worldName == currentWorldName && slot.num == num ) {
				return slot;
			}
		}
	}

	void oTeleport::Choise( int num ) {
		if ( menuNum == MAIN_MENU ) {
			menuName = "Main menu";
			if ( num == 1 ) {
				menuNum = TELEPORT_TO;
				menuName = "Teleport to...";
				Draw();
			} else if ( num == 2 ) {
				menuNum = TELEPORT_NEXT_LOCATION_CHOISE_WORLD;
				menuName = "Choise next world...";
				Draw();
			} else if ( num == 3 ) {
				menuNum = SAVE;
				menuName = "Save";
				Draw();
			} else if ( num == 0 ) {
				allTeleports.DeleteList();
				currentWorld.DeleteList();
				Draw();
				printWin("Savepoints are cleaned");
			}
		} else if ( menuNum == TELEPORT_TO ) {
			menuNum = MAIN_MENU;
			menuName = "Main menu";
			Toggle();
			TeleportTo(num);
		} else if ( menuNum == TELEPORT_NEXT_LOCATION_CHOISE_WORLD ) {
			nextLocTo = GetWorldTpTo( num );
			if ( !nextLocTo.IsEmpty() ) {
				menuNum = TELEPORT_NEXT_LOCATION_TO;
				menuName = "Teleport to...";
				Draw();
			} else {
				printWin("The selected slot is empty.");
			}
			
		} else if ( menuNum == TELEPORT_NEXT_LOCATION_TO ) {
			menuNum = MAIN_MENU;
			menuName = "Main menu";
			Toggle();
			TeleportToLoc(num);
		} else if ( menuNum == SAVE ) {
			saveNum = num;
			menuNum = SAVE_NAME;
			menuName = "Save name menu";
			Draw();
		}
	}

	void oTeleport::TeleportToLoc( int num ) {
		zCArray<oTeleportSlot> arr = GetNextLocationTo();
		for ( int i = 0; i < arr.GetNum(); i++ ) {
			oTeleportSlot& slot = arr.GetSafe( i );
			if ( i + 1 == num ) {
				zVEC3 pos = slot.pos;

				if ( pos.n[ 0 ] == 0 && pos.n[ 1 ] == 0 && pos.n[ 2 ] == 0 ) {

					printWin( "The selected slot is empty." );
					return;
				}
				ogame->ChangeLevel( slot.worldFilename, "" );
				TeleportTo(num);
				return;
			}
		}
	}

	void oTeleport::TeleportTo( int num ) {
		if ( num >= 1 && num <= 3 ) {
			oTeleportSlot& slot = GetCurrent( num );
			
			zVEC3 pos = slot.pos;

			if ( pos.n[0] == 0 && pos.n[ 1 ] == 0 && pos.n[ 0 ] == 0 ) {
				return;
			}

			player->SetCollDet( FALSE );
			
			player->SetPositionWorld( slot.pos );
			player->SetHeadingAtWorld( slot.atPos );
			player->SetCollDet( TRUE );
			player->movlock = FALSE;
			player->Enable( player->GetPositionWorld() );

			
			printWin( "Teleport to " + slot.tpName );
			
			ogame->GetSpawnManager()->SpawnImmediately();


			oCVisualFX* fx = oCVisualFX::CreateAndPlay( "SPELLFX_TELEPORT_RING", player->GetPositionWorld(), 0, 1, 0, 0, 0 );
			if ( fx ) {
				fx->Release();
			}
		}
	}

	void oTeleport::Toggle() {
		isActive = !isActive;
		Activate( isActive );
	}

	zSTRING oTeleport::GetPathSave( zSTRING saveName ) {
		zSTRING path = zoptions->GetDirString( DIR_ROOT );
		path = path + zoptions->GetDirString( DIR_SAVEGAMES );
		path += "current\\";
		path = path + saveName;
		path += ".SAV";
		return path;
	}

	zCArray<zSTRING> oTeleport::GetWorldNames() {
		zCArray<zSTRING> arr;
		for ( int i = 0; i < allTeleports.GetNum(); i++ ) {
			oTeleportSlot& slot = allTeleports.GetSafe(i);
			if ( A slot.worldName != A currentWorldName && !arr.IsInList( slot.worldName ) ) {
				arr.Insert( slot.worldName );
			}
		}

		return arr;
	}

	zCArray<oTeleportSlot> oTeleport::GetNextLocationTo() {
		zCArray<oTeleportSlot> arr;
		for ( int i = 0; i < allTeleports.GetNum(); i++ ) {
			oTeleportSlot& slot = allTeleports.GetSafe( i );
			if ( slot.worldName == nextLocTo ) {
				arr.Insert( slot );
			}
		}

		return arr;
	}

	zSTRING oTeleport::GetWorldTpTo( int num ) {
		zCArray<zSTRING> arr = GetWorldNames();
		for ( int i = 0; i < arr.GetNum(); i++ ) {
			if ( i + 1 == num ) {
				zSTRING slot = arr.GetSafe( i );
				return slot;
			}
		}
		return "";
	}
}