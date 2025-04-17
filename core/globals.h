#pragma once

#include <cstdint>
#include <unordered_map>

#include "domain.h"

namespace cafeteria_app {
	/*-----  GROUPS  -----*/
	inline const char* __TAA__ = "TAA";
	inline const char* __TAC__ = "TAC";
	inline const char* __TAIS__ = "TAIS";

	/*-----  PROPS  -----*/

	inline const std::unordered_map<domain::Props, const char*> __PROPS_TO_TEXT__ = {
																						{domain::Props::NAME, "name"},
																						{domain::Props::INDENTIFIER, "identifier"},
																						{domain::Props::GENDER, "gender"},
																						{domain::Props::GROUP, "group"}
																					};

			inline const std::unordered_map<domain::props::Gender, const char*> __GENDER_TO_TEXT__ = {
																										{domain::props::Gender::FEMALE, "female"},
																										{domain::props::Gender::MALE, "male"}
																									 };

	/*-----  FILESYSTEM  -----*/

	//Settings

	inline const char* __SETTINGS_PARENT_FOLDER__ = "Settings";
	////////
			inline const char* __PATH_SETTINGS_FILE__ = "paths.json";


	inline const char* __DATABASE_PARENT_FOLDER__ = "Database";
	////////

			//Data

			inline const char* __DATA_FOLDER__ = "Data";
			////////
					inline const char* __QUEUE_DATA_FILE__ = "queue.dat";
			////////
					inline const char* __IDENTIFIER_DATA_FILE__ = "identifier.dat";
			////////
					inline const char* __NAME_DATA_FILE__ = "name.dat";
			////////
					inline const char* __GENDER_DATA_FILE__ = "gender.dat";
			////////
					inline const char* __GROUP_DATA_FILE__ = "group.dat";
			
			

			//Backup

			inline const char* __BACKUP_FOLDER__ = "Backup";


	inline const char* __EXPORTS_PARENT_FOLDER__ = "Exports";
	////////

			//Stats

			inline const char* __STATS_FOLDER__ = "Stats";

			//QR codes

			inline const char* __QR_FOLDER__ = "QrCode";
}