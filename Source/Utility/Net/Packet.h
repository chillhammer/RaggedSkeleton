#pragma once
#include <Macros.h>
#include "Packets/PacketTypes.h"
#include "Buffer.h"

namespace Skel::Net
{

// Creates a packet and writes it to buffer immediately
#define WRITE_PACKET(packet_type, param, buffer) packet_type packet##__LINE__##param; packet##__LINE__##.WriteToBuffer(buffer);

	enum PacketType : uint8
	{
		CUSTOM_PACKETS
	};

	class Packet
	{
	public:
		Packet(PacketType type) : m_Type(type) {}

		void ReadFromBuffer(Buffer& buffer);
		void WriteToBuffer(Buffer& buffer);
	protected:
		virtual void WriteToBuffer_Internal(Buffer& buffer) {}
		virtual void ReadFromBuffer_Internal(Buffer& buffer) {}
	private:
		PacketType m_Type;

	};
}