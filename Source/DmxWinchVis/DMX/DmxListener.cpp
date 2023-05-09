#include "DmxListener.hpp"

#include "DMXProtocol/Public/IO/DMXInputPort.h"
#include "DMXProtocol/Public/IO/DMXPortManager.h"

DmxListener::DmxListener()
{
	_dmxSubsystem = UDMXSubsystem::GetDMXSubsystem_Callable();
	_universe = 0;
	_portName.Empty();
	state = DmxListenerState::ZeroCheck;
}

bool DmxListener::FindPort(FString portName) noexcept
{
	SetPortName(portName);
	auto inputPorts = FDMXPortManager::Get().GetInputPorts();
	if (inputPorts.Num() == 0)
	{
		state = DmxListenerState::ZeroCheck;
		return false;
	}
	if (_portName.IsEmpty())
	{
		_inputPortRef = FDMXInputPortReference(inputPorts[0]->GetPortGuid(), true);
		state = DmxListenerState::PortFounded;
	}
	else
	{
		for (auto& eachPort : inputPorts)
		{
			if (eachPort.Get().GetPortName() == _portName)
			{
				_inputPortRef = FDMXInputPortReference(eachPort->GetPortGuid(), true);
				state = DmxListenerState::PortFounded;
				break;
			}
		}
	}
	return state == DmxListenerState::PortFounded;
}

#pragma region Accessors

int DmxListener::GetCurrentUniverse() const noexcept
{
	return _universe;
}

const FString& DmxListener::GetCurrentPortName() const noexcept
{
	return _portName;
}

TArray<uint8_t> DmxListener::GetDataFromUniverse(int universe) const noexcept
{
	TArray<uint8> data;
	_dmxSubsystem->GetDMXDataFromInputPort(_inputPortRef, data, universe < 0 ? 0 : universe);
	return data;
}

TArray<FWinchPacket> DmxListener::GetPacketFromUniverse(int universe) const noexcept
{
	TArray<uint8> data;
	TArray<FWinchPacket> dataViaPacket;
	data.Reserve(UniverseDataLength);
	/// FWinchPacket ignores 3 bytes in each packet
	dataViaPacket.Reserve(UniversalPacketCount);
	_dmxSubsystem->GetDMXDataFromInputPort(_inputPortRef, data, universe < 0 ? 0 : universe);

	if (data.Num() > 1)
	{
		FWinchPacket packet;
		for (uint8_t packetCount = 0; packetCount < UniversalPacketCount; ++packetCount)
		{
			packet[WinchByte::Dimmer] = data[packetCount * FWinchPacket::WinchPacketLength];
			packet[WinchByte::Red] = data[packetCount * FWinchPacket::WinchPacketLength + 1];
			packet[WinchByte::Green] = data[packetCount * FWinchPacket::WinchPacketLength + 2];
			packet[WinchByte::Blue] = data[packetCount * FWinchPacket::WinchPacketLength + 3];
			packet[WinchByte::Roll] = data[packetCount * FWinchPacket::WinchPacketLength + 6];
			packet[WinchByte::Speed] = data[packetCount * FWinchPacket::WinchPacketLength + 8];
			packet[WinchByte::Ctrl] = data[packetCount * FWinchPacket::WinchPacketLength + 9];
			dataViaPacket.Push(packet);
		}
	}
	return dataViaPacket;
}

#pragma endregion Accessors

#pragma region Mutators

void DmxListener::SetPortName(const FString& portName) noexcept
{
	if (portName.IsEmpty())
	{
		return;
	}
	_portName = portName;
}

void DmxListener::SetUniverse(int universe) noexcept
{
	_universe = universe < 0 ? 0 : universe;
}

#pragma endregion Mutators
