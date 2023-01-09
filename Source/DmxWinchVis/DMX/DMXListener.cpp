#include "DMXListener.h"

#include "DMXProtocol/Public/IO/DMXInputPort.h"
#include "DMXProtocol/Public/IO/DMXPortManager.h"

DMXListener::DMXListener()
{
	_dmxSubsystem = UDMXSubsystem::GetDMXSubsystem_Callable();
	_universe = 0;
	_portName.Empty();
}

bool DMXListener::FindPort(FString portName) noexcept
{
	SetPortName(portName);
	auto inputPorts = FDMXPortManager::Get().GetInputPorts();
	if (inputPorts.Num() == 0)
	{
		return false;
	}
	if (_portName.IsEmpty())
	{
		_inputPortRef = FDMXInputPortReference(inputPorts[0]->GetPortGuid(), true);
		return true;
	}
	for (auto& eachPort : inputPorts)
	{
		if (eachPort.Get().GetPortName() == _portName)
		{
			_inputPortRef = FDMXInputPortReference(eachPort->GetPortGuid(), true);
			break;
		}
		return false;
	}
	return true;
}

#pragma region Accessors

int DMXListener::GetCurrentUniverse() const noexcept
{
	return _universe;
}

FString DMXListener::GetCurrentPortName() const noexcept
{
	return _portName;
}

TArray<uint8> DMXListener::GetDataFromUniverse(int universe) noexcept
{
	if (_universe != -1)
	{
		SetUniverse(universe);
	}
	TArray<uint8> data;
	data.Reserve(512);
	_dmxSubsystem->GetDMXDataFromInputPort(_inputPortRef, data, _universe);
	return TArray<uint8>(MoveTemp(data));
}

#pragma endregion Accessors

#pragma region Mutators

void DMXListener::SetPortName(FString portName) noexcept
{
	if (portName.IsEmpty())
	{
		return;
	}
	_portName = portName;
}

void DMXListener::SetUniverse(int universe) noexcept
{
	_universe = universe < 0 ? 0 : universe;
}

#pragma endregion Mutators
