#pragma once

enum ePackageRecovSend
{
	ADMINS_CMD = -18,

	// То что отправляет серевер
	
	RPC_SERVER_VEHICLE_CAR_POSSITIONS	= 300,
	RPC_VEHICLE_SPAWN					= 301,
	RPC_VEHICLE_ID_DEATCH				= 302,


	// То что Присылает Клиент
	RECOV_VEHICLE_CAR_POSSITIONS		= 403,


	PLAYER_ACTOR_NEW_POSSITIONS = 7,
	UNKNOW_PRMS = 666
};
