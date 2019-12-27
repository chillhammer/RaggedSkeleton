#pragma once
#include <Objects/Player/PlayerObject.h>
#include <Net/Net.h>
#include <Net/Address.h>

namespace Skel::Net
{
	struct ClientSlot
	{
		uint16 ID;
		Address ClientAddress;
		ClientSlot(uint16 id, Address address) : ID(id), ClientAddress(address) {}
	};

	// Handles the player management from the server perspective
	// Note an optimization can be made as to making the active PlayerObjects always adjacent in memory
	class ClientHandler
	{
	public:
		ClientHandler();

		uint16 ActivePlayers() const { return m_ActivePlayers; }
		uint16 RemainingSlots() const { return MAX_PLAYERS - m_ActivePlayers; }
		uint16 AddPlayer(Address address);
		void RemovePlayer(uint16 clientIndex);
		void SetPlayerObjectArray(class PlayerObject* arr) { m_PlayerObjectArray = arr; }
		bool IsActive(uint16 clientID) const;
		const class PlayerObject* GetPlayerObject(uint16 clientID) const;
		const std::vector<ClientSlot>& GetClientSlots() const;


	private:
		// Helper Functions
		uint16 FindAvailableSlotIndex() const;

	private:
		bool m_SlotAvailability[MAX_PLAYERS];
		std::vector<ClientSlot> m_ClientSlots; // List of active player addresses
		class PlayerObject* m_PlayerObjectArray; // Active/Non-active player objects
		uint16 m_ActivePlayers = 0;
	};
}